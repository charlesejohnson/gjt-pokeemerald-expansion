#include "global.h"
#include "gjt_druid.h"
#include "battle.h"
#include "battle_util.h"
#include "pokemon.h"
#include "move.h"
#include "constants/moves.h"

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
            if (slots[s] == MOVE_NONE)
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

        if (move == MOVE_NONE)
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
        if (entry->moves[form - 1][s] == MOVE_NONE)
            continue;
        if (n == movePosition)
        {
            entry->pp[form - 1][s] = gBattleMons[battler].pp[movePosition];
            return;
        }
        n++;
    }
}
