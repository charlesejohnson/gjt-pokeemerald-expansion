#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "evolution_scene.h"
#include "field_screen_effect.h"
#include "item.h"
#include "overworld.h"
#include "pokemon.h"
#include "script.h"
#include "string_util.h"
#include "constants/species.h"
#include "gjt_spec_stone.h"

// GJT: Specialization Stone. One table row per class; stage decides which column
// (base and middle forms both go to a middle form, final forms stay final).
#define MAX_SPECS 4

struct GjtClassSpecs
{
    u16 base;
    u8 count;
    u16 mid[MAX_SPECS];
    u16 fin[MAX_SPECS];
};

static const struct GjtClassSpecs sClassSpecs[] =
{
    { SPECIES_DEATHKNIGHT, 3,
      { SPECIES_DEATHKNIGHT_BLOOD_MID, SPECIES_DEATHKNIGHT_FROST_MID, SPECIES_DEATHKNIGHT_UNHOLY_MID },
      { SPECIES_DEATHKNIGHT_BLOOD, SPECIES_DEATHKNIGHT_FROST, SPECIES_DEATHKNIGHT_UNHOLY } },
    { SPECIES_MAGE, 3,
      { SPECIES_MAGE_FROST_MID, SPECIES_MAGE_FIRE_MID, SPECIES_MAGE_ARCANE_MID },
      { SPECIES_MAGE_FROST, SPECIES_MAGE_FIRE, SPECIES_MAGE_ARCANE } },
    { SPECIES_WARRIOR, 3,
      { SPECIES_WARRIOR_ARMS_MID, SPECIES_WARRIOR_FURY_MID, SPECIES_WARRIOR_PROTECTION_MID },
      { SPECIES_WARRIOR_ARMS, SPECIES_WARRIOR_FURY, SPECIES_WARRIOR_PROTECTION } },
    { SPECIES_SHAMAN, 3,
      { SPECIES_SHAMAN_RESTORATION_MID, SPECIES_SHAMAN_ENHANCEMENT_MID, SPECIES_SHAMAN_ELEMENTAL_MID },
      { SPECIES_SHAMAN_RESTORATION, SPECIES_SHAMAN_ENHANCEMENT, SPECIES_SHAMAN_ELEMENTAL } },
    { SPECIES_DRUID, 4,
      { SPECIES_DRUID_RESTORATION_MID, SPECIES_DRUID_FERAL_MID, SPECIES_DRUID_GUARDIAN_MID, SPECIES_DRUID_BOOMY_MID },
      { SPECIES_DRUID_RESTORATION, SPECIES_DRUID_FERAL, SPECIES_DRUID_GUARDIAN, SPECIES_DRUID_BOOMY } },
    { SPECIES_MONK, 3,
      { SPECIES_MONK_MISTWEAVER_MID, SPECIES_MONK_BREWMASTER_MID, SPECIES_MONK_WINDWALKER_MID },
      { SPECIES_MONK_MISTWEAVER, SPECIES_MONK_BREWMASTER, SPECIES_MONK_WINDWALKER } },
    { SPECIES_PALADIN, 3,
      { SPECIES_PALADIN_HOLY_MID, SPECIES_PALADIN_PROTECTION_MID, SPECIES_PALADIN_RETRIBUTION_MID },
      { SPECIES_PALADIN_HOLY, SPECIES_PALADIN_PROTECTION, SPECIES_PALADIN_RETRIBUTION } },
    { SPECIES_HUNTER, 3,
      { SPECIES_HUNTER_BEAST_MASTERY_MID, SPECIES_HUNTER_MARKSMANSHIP_MID, SPECIES_HUNTER_SURVIVAL_MID },
      { SPECIES_HUNTER_BEAST_MASTERY, SPECIES_HUNTER_MARKSMANSHIP, SPECIES_HUNTER_SURVIVAL } },
};

// Finds the class row for a species. Sets *isFinal when the mon is a final form.
static const struct GjtClassSpecs *FindClass(u16 species, bool32 *isFinal)
{
    u32 i, j;

    *isFinal = FALSE;
    for (i = 0; i < ARRAY_COUNT(sClassSpecs); i++)
    {
        const struct GjtClassSpecs *c = &sClassSpecs[i];

        if (species == c->base)
            return c;
        for (j = 0; j < c->count; j++)
        {
            if (species == c->mid[j])
                return c;
            if (species == c->fin[j])
            {
                *isFinal = TRUE;
                return c;
            }
        }
    }
    return NULL;
}

// Script special. In: VAR_0x8004 = party slot. Out: VAR_RESULT = number of specs (0 if not a
// class Pokémon); spec names are placed in gStringVar1-4 for the menu.
void GjtSpecStonePrepare(void)
{
    bool32 isFinal;
    const struct GjtClassSpecs *c;
    u32 i;
    u8 *vars[MAX_SPECS] = { gStringVar1, gStringVar2, gStringVar3, gStringVar4 };

    if (gSpecialVar_0x8004 >= PARTY_SIZE)
    {
        gSpecialVar_Result = 0;
        return;
    }
    c = FindClass(GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_SPECIES), &isFinal);
    if (c == NULL)
    {
        gSpecialVar_Result = 0;
        return;
    }
    for (i = 0; i < c->count; i++)
        StringCopy(vars[i], GetSpeciesName(c->fin[i]));
    gSpecialVar_Result = c->count;
}

// Script special. In: VAR_0x8004 = party slot, VAR_0x8005 = chosen spec index.
// Out: VAR_RESULT = FALSE if the mon already has that spec, else TRUE and the
// evolution scene starts (script continues after waitstate).
void GjtSpecStoneApply(void)
{
    bool32 isFinal;
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    const struct GjtClassSpecs *c = FindClass(species, &isFinal);
    u16 target;

    if (c == NULL || gSpecialVar_0x8005 >= c->count)
    {
        gSpecialVar_Result = FALSE;
        return;
    }
    target = isFinal ? c->fin[gSpecialVar_0x8005] : c->mid[gSpecialVar_0x8005];
    if (target == species)
    {
        gSpecialVar_Result = FALSE;
        return;
    }
    gSpecialVar_Result = TRUE;
    RemoveBagItem(ITEM_SPECIALIZATION_STONE, 1);
    gCB2_AfterEvolution = CB2_ReturnToFieldContinueScriptPlayMapMusic;
    BeginEvolutionScene(mon, target, FALSE, gSpecialVar_0x8004);
}
