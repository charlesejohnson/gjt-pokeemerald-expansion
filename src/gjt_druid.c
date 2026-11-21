#include "global.h"
#include "gjt_druid.h"
#include "battle.h"
#include "battle_util.h"
#include "pokemon.h"
#include "move.h"
#include "constants/moves.h"
#include "constants/script_menu.h"
#include "constants/vars.h"
#include "event_data.h"
#include "script_menu.h"
#include "string_util.h"
#include "text.h"
#include "malloc.h"
#include "list_menu.h"

EWRAM_DATA static struct DruidLoadout sAiLoadouts[MAX_BATTLERS_COUNT] = {0}; // opponents' loadouts are never saved

EWRAM_DATA static u16 sTestForced[DRUID_FORM_COUNT][DRUID_FORM_SLOTS] = {0};

void DruidTestForceSlot(u32 form, u32 slot, enum Move move)
{
    sTestForced[form - 1][slot] = move;
}

u32 GetDruidMoveAffinity(enum Move move)
{
    switch (move)
    {
    case MOVE_MAUL:
    case MOVE_MANGLE:
    case MOVE_IRONFUR:
    case MOVE_THRASH_DRUID:
    case MOVE_FRENZIED_REGEN:
        return 1;
    case MOVE_SHRED:
    case MOVE_RAKE:
    case MOVE_FEROCIOUS_BITE:
        return 2;
    case MOVE_REJUVENATION:
    case MOVE_SWIFTMEND:
    case MOVE_WILD_GROWTH:
    case MOVE_TRANQUILITY:
        return 3;
    case MOVE_WRATH:
    case MOVE_STARFIRE:
    case MOVE_STARSURGE:
    case MOVE_CELESTIAL_ALIGNMENT:
        return 4;
    default:
        return 0;
    }
}

bool32 IsDruidExclusiveMove(enum Move move)
{
    u32 affinity = GetDruidMoveAffinity(move);

    return affinity == 1 || affinity == 2 || move == MOVE_UNSHIFT;
}

void DruidResetLoadouts(void)
{
    CpuFill16(0, gSaveBlock3Ptr->druidLoadouts, sizeof(gSaveBlock3Ptr->druidLoadouts));
    gSaveBlock3Ptr->druidLoadoutNext = 0;
    memset(sTestForced, 0, sizeof(sTestForced));
}

void DruidRefillLoadoutPP(void)
{
    for (u32 i = 0; i < DRUID_LOADOUT_COUNT; i++)
        memset(gSaveBlock3Ptr->druidLoadouts[i].pp, DRUID_PP_FULL, sizeof(gSaveBlock3Ptr->druidLoadouts[i].pp));
}

static void InitEntry(struct DruidLoadout *entry, u32 personality)
{
    memset(entry, 0, sizeof(*entry));
    entry->personality = personality;
    memset(entry->pp, DRUID_PP_FULL, sizeof(entry->pp));
}

static struct DruidLoadout *FindEntry(u32 personality, bool32 create)
{
    struct SaveBlock3 *sb = gSaveBlock3Ptr;
    u32 i;

    for (i = 0; i < DRUID_LOADOUT_COUNT; i++)
    {
        if (sb->druidLoadouts[i].personality == personality)
            return &sb->druidLoadouts[i];
    }
    if (!create)
        return NULL;
    for (i = 0; i < DRUID_LOADOUT_COUNT; i++)
    {
        if (sb->druidLoadouts[i].personality == 0)
        {
            InitEntry(&sb->druidLoadouts[i], personality);
            return &sb->druidLoadouts[i];
        }
    }
    i = sb->druidLoadoutNext % DRUID_LOADOUT_COUNT; // all full: recycle round-robin
    sb->druidLoadoutNext = (i + 1) % DRUID_LOADOUT_COUNT;
    InitEntry(&sb->druidLoadouts[i], personality);
    return &sb->druidLoadouts[i];
}

// Fills empty slots with the moves the mon has learned for each form, in level order, up to 3 per form.
// Moves a form may use besides its own affinity moves. Moonfire is open to every form.
static const u16 sBearMoves[] = {MOVE_MOONFIRE, MOVE_GROWL, MOVE_VINE_WHIP, MOVE_BULK_UP, MOVE_ROCK_THROW, MOVE_ROCK_SLIDE, MOVE_BODY_PRESS, MOVE_STONE_EDGE, MOVE_EARTHQUAKE, MOVE_NONE};
static const u16 sCatMoves[] = {MOVE_MOONFIRE, MOVE_GROWL, MOVE_VINE_WHIP, MOVE_RAZOR_LEAF, MOVE_QUICK_ATTACK, MOVE_SLASH, MOVE_POISON_JAB, MOVE_X_SCISSOR, MOVE_SWORDS_DANCE, MOVE_NONE};
static const u16 sTreeMoves[] = {MOVE_MOONFIRE, MOVE_LEECH_SEED, MOVE_MEGA_DRAIN, MOVE_SYNTHESIS, MOVE_AROMATHERAPY, MOVE_GIGA_DRAIN, MOVE_INGRAIN, MOVE_SOLAR_BEAM, MOVE_NONE};
static const u16 sOwlkinMoves[] = {MOVE_MOONFIRE, MOVE_LEECH_SEED, MOVE_FAIRY_WIND, MOVE_DISARMING_VOICE, MOVE_ENERGY_BALL, MOVE_DAZZLING_GLEAM, MOVE_CALM_MIND, MOVE_MOONBLAST, MOVE_SOLAR_BEAM, MOVE_NONE};

static const u16 *const sFormMoves[DRUID_FORM_COUNT] = {sBearMoves, sCatMoves, sTreeMoves, sOwlkinMoves};

// A form can only hold its own affinity moves plus its shared list (Bear can't cast Wrath).
bool32 IsMoveAllowedInDruidForm(enum Move move, u32 form)
{
    const u16 *list;

    if (form < 1 || form > DRUID_FORM_COUNT)
        return FALSE;
    if (GetDruidMoveAffinity(move) == form)
        return TRUE;
    for (list = sFormMoves[form - 1]; *list != MOVE_NONE; list++)
    {
        if (*list == move)
            return TRUE;
    }
    return FALSE;
}

static bool32 SlotIsEmpty(u16 move)
{
    return move == MOVE_NONE || move == DRUID_SLOT_CLEARED;
}

static void AutoFill(struct Pokemon *mon, struct DruidLoadout *entry)
{
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(GetMonData(mon, MON_DATA_SPECIES));
    u32 level = GetMonData(mon, MON_DATA_LEVEL);

    for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        u32 form = GetDruidMoveAffinity(learnset[i].move);
        u16 *slots;
        u32 s;

        if (form == 0 || learnset[i].level == 0 || learnset[i].level > level)
            continue;
        slots = entry->moves[form - 1];
        for (s = 0; s < DRUID_FORM_SLOTS; s++)
        {
            if (slots[s] == learnset[i].move)
                break;
        }
        if (s < DRUID_FORM_SLOTS)
            continue;
        for (s = 0; s < DRUID_FORM_SLOTS; s++)
        {
            if (slots[s] == MOVE_NONE) // cleared slots stay empty
            {
                slots[s] = learnset[i].move;
                entry->pp[form - 1][s] = DRUID_PP_FULL;
                break;
            }
        }
    }
}

static struct Pokemon *GetMonOfBattler(enum BattlerId battler)
{
    return &GetBattlerParty(battler)[gBattlerPartyIndexes[battler]];
}

static struct DruidLoadout *GetEntryForBattler(enum BattlerId battler, bool32 create)
{
    struct Pokemon *mon = GetMonOfBattler(battler);
    struct DruidLoadout *entry;

    if (GetBattlerSide(battler) != B_SIDE_PLAYER)
    {
        if (create)
        {
            InitEntry(&sAiLoadouts[battler], 1);
            AutoFill(mon, &sAiLoadouts[battler]);
        }
        return &sAiLoadouts[battler];
    }
    entry = FindEntry(GetMonData(mon, MON_DATA_PERSONALITY), create);
    if (entry != NULL && create)
    {
        for (u32 f = 0; f < DRUID_FORM_COUNT; f++)
        {
            for (u32 s = 0; s < DRUID_FORM_SLOTS; s++)
            {
                if (sTestForced[f][s] != MOVE_NONE)
                    entry->moves[f][s] = sTestForced[f][s];
            }
        }
        AutoFill(mon, entry);
    }
    return entry;
}

bool32 DruidAssignSlot(struct Pokemon *mon, u32 form, u32 slot, enum Move move)
{
    struct DruidLoadout *entry;

    if (form < 1 || form > DRUID_FORM_COUNT || slot >= DRUID_FORM_SLOTS)
        return FALSE;
    entry = FindEntry(GetMonData(mon, MON_DATA_PERSONALITY), TRUE);
    entry->moves[form - 1][slot] = move;
    entry->pp[form - 1][slot] = DRUID_PP_FULL;
    return TRUE;
}

void DruidApplyFormMoves(enum BattlerId battler, u32 form)
{
    struct DruidLoadout *entry = GetEntryForBattler(battler, TRUE);
    u32 n = 0;

    for (u32 s = 0; s < DRUID_FORM_SLOTS; s++)
    {
        enum Move move = entry->moves[form - 1][s];
        u32 maxPp, pp;

        if (SlotIsEmpty(move) || !IsMoveAllowedInDruidForm(move, form))
            continue;
        maxPp = GetMovePP(move);
        pp = entry->pp[form - 1][s];
        gBattleMons[battler].moves[n] = move;
        gBattleMons[battler].pp[n] = (pp > maxPp) ? maxPp : pp;
        n++;
    }
    gBattleMons[battler].moves[n] = MOVE_UNSHIFT;
    gBattleMons[battler].pp[n] = GetMovePP(MOVE_UNSHIFT);
    for (n++; n < MAX_MON_MOVES; n++)
    {
        gBattleMons[battler].moves[n] = MOVE_NONE;
        gBattleMons[battler].pp[n] = 0;
    }
    gBattleMons[battler].volatiles.mimickedMoves = MAX_BITS(MAX_MON_MOVES); // keeps form PP out of the party mon
}

void DruidRestoreBaseMoves(enum BattlerId battler)
{
    struct Pokemon *mon = GetMonOfBattler(battler);

    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        gBattleMons[battler].moves[i] = GetMonData(mon, MON_DATA_MOVE1 + i);
        gBattleMons[battler].pp[i] = GetMonData(mon, MON_DATA_PP1 + i);
    }
    gBattleMons[battler].volatiles.mimickedMoves = 0;
}

void DruidSaveFormPP(enum BattlerId battler, u32 movePosition)
{
    u32 form = gBattleMons[battler].volatiles.druidForm;
    struct DruidLoadout *entry;
    u32 n = 0;

    if (form == 0 || GetBattlerSide(battler) != B_SIDE_PLAYER)
        return;
    entry = GetEntryForBattler(battler, FALSE);
    if (entry == NULL)
        return;
    for (u32 s = 0; s < DRUID_FORM_SLOTS; s++)
    {
        if (SlotIsEmpty(entry->moves[form - 1][s]) || !IsMoveAllowedInDruidForm(entry->moves[form - 1][s], form))
            continue;
        if (n == movePosition)
        {
            entry->pp[form - 1][s] = gBattleMons[battler].pp[movePosition];
            return;
        }
        n++;
    }
}

// ---- Druid trainer NPC (field script helpers) ----
// Variables: VAR_0x8004 party slot, 0x8005 form (1-4), 0x8006 slot (1-3), 0x8007 chosen move.

static const u8 sText_BearForm[] = _("Bear Form");
static const u8 sText_CatForm[] = _("Cat Form");
static const u8 sText_TreeForm[] = _("Tree Form");
static const u8 sText_OwlkinForm[] = _("Owlkin Form");
static const u8 sText_Done[] = _("Done");
static const u8 sText_Back[] = _("Back");
static const u8 sText_Empty[] = _("-----");
static const u8 sText_ClearSlot[] = _("Clear slot");
static const u8 sText_Sep[] = _(": ");

#define DRUID_MENU_CLEAR 4095

static void PushMenuItem(const u8 *text, u32 id)
{
    struct ListMenuItem item;
    u8 *buffer = Alloc(100); // freed by the menu when it closes

    StringCopy(buffer, text);
    item.name = buffer;
    item.id = id;
    MultichoiceDynamic_PushElement(item);
}

static struct Pokemon *GetChosenDruid(void)
{
    return &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
}

static bool32 IsDruidFormMove(enum Move move)
{
    return move == MOVE_BEAR_FORM || move == MOVE_CAT_FORM || move == MOVE_TREE_FORM
        || move == MOVE_OWLKIN_FORM || move == MOVE_UNSHIFT;
}

void DruidTrainer_Begin(void)
{
    enum Species species = GetMonData(GetChosenDruid(), MON_DATA_SPECIES);

    gSpecialVar_Result = IsDruidSpecies(species);
}

void DruidTrainer_PushForms(void)
{
    enum Species species = GetMonData(GetChosenDruid(), MON_DATA_SPECIES);

    species = NormalizeClassSpecies(species);
    PushMenuItem(sText_BearForm, 1);
    PushMenuItem(sText_CatForm, 2);
    if (species == SPECIES_DRUID_RESTORATION)
        PushMenuItem(sText_TreeForm, 3);
    if (species == SPECIES_DRUID_BOOMY)
        PushMenuItem(sText_OwlkinForm, 4);
    PushMenuItem(sText_Done, 0);
}

void DruidTrainer_PushSlots(void)
{
    struct Pokemon *mon = GetChosenDruid();
    struct DruidLoadout *entry = FindEntry(GetMonData(mon, MON_DATA_PERSONALITY), TRUE);
    u8 text[40];

    AutoFill(mon, entry);
    for (u32 s = 0; s < DRUID_FORM_SLOTS; s++)
    {
        u16 move = entry->moves[gSpecialVar_0x8005 - 1][s];
        u8 *end = ConvertIntToDecimalStringN(text, s + 1, STR_CONV_MODE_LEFT_ALIGN, 1);

        end = StringAppend(text, sText_Sep);
        StringAppend(text, SlotIsEmpty(move) ? sText_Empty : GetMoveName(move));
        PushMenuItem(text, s + 1);
        (void)end;
    }
    PushMenuItem(sText_Back, 0);
}

// Known moves: everything on the Druid's learnset at or below its level, except the shift moves.
void DruidTrainer_PushMoves(void)
{
    struct Pokemon *mon = GetChosenDruid();
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(GetMonData(mon, MON_DATA_SPECIES));
    u32 level = GetMonData(mon, MON_DATA_LEVEL);
    enum Move seen[64];
    u32 count = 0;

    for (u32 i = 0; learnset[i].move != LEVEL_UP_MOVE_END && count < ARRAY_COUNT(seen); i++)
    {
        enum Move move = learnset[i].move;
        bool32 dup = FALSE;

        if (learnset[i].level == 0 || learnset[i].level > level || IsDruidFormMove(move)
         || !IsMoveAllowedInDruidForm(move, gSpecialVar_0x8005))
            continue;
        for (u32 j = 0; j < count; j++)
        {
            if (seen[j] == move)
                dup = TRUE;
        }
        if (dup)
            continue;
        seen[count++] = move;
        PushMenuItem(GetMoveName(move), move);
    }
    PushMenuItem(sText_ClearSlot, DRUID_MENU_CLEAR);
}

void DruidTrainer_Assign(void)
{
    struct Pokemon *mon = GetChosenDruid();
    struct DruidLoadout *entry = FindEntry(GetMonData(mon, MON_DATA_PERSONALITY), TRUE);
    u32 form = gSpecialVar_0x8005 - 1;
    u32 slot = gSpecialVar_0x8006 - 1;
    u16 move = gSpecialVar_0x8007;

    if (move == DRUID_MENU_CLEAR)
    {
        entry->moves[form][slot] = DRUID_SLOT_CLEARED;
        return;
    }
    for (u32 s = 0; s < DRUID_FORM_SLOTS; s++)
    {
        if (s != slot && entry->moves[form][s] == move) // no duplicates within a form
            entry->moves[form][s] = DRUID_SLOT_CLEARED;
    }
    entry->moves[form][slot] = move;
    entry->pp[form][slot] = DRUID_PP_FULL;
}
