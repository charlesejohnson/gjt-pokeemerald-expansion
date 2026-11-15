#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(MoveMakesContact(MOVE_TACKLE));
    ASSUME(!MoveMakesContact(MOVE_SWIFT));
    ASSUME(gSpeciesInfo[SPECIES_MAGE].abilities[0] == ABILITY_FROST_ARMOR);
    ASSUME(gSpeciesInfo[SPECIES_MAGE_FROST].abilities[0] == ABILITY_FROST_ARMOR);
}

SINGLE_BATTLE_TEST("Frost Armor may frostbite attackers that make contact")
{
    PASSES_RANDOMLY(30, 100, RNG_FROST_ARMOR);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MAGE_FROST) { Ability(ABILITY_FROST_ARMOR); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_FROST_ARMOR);
        STATUS_ICON(player, frostbite: TRUE);
    }
}

SINGLE_BATTLE_TEST("Frost Armor does not trigger on non-contact moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MAGE_FROST) { Ability(ABILITY_FROST_ARMOR); }
    } WHEN {
        TURN { MOVE(player, MOVE_SWIFT); }
    } THEN {
        EXPECT(!(player->status1 & STATUS1_FROSTBITE));
    }
}

SINGLE_BATTLE_TEST("Frost Armor can frostbite Fire-type attackers")
{
    PASSES_RANDOMLY(30, 100, RNG_FROST_ARMOR);
    GIVEN {
        PLAYER(SPECIES_MAGE_FIRE);
        OPPONENT(SPECIES_MAGE_FROST) { Ability(ABILITY_FROST_ARMOR); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        STATUS_ICON(player, frostbite: TRUE);
    }
}

SINGLE_BATTLE_TEST("Frost Armor does not affect Ice-type attackers")
{
    GIVEN {
        PLAYER(SPECIES_GLALIE);
        OPPONENT(SPECIES_MAGE_FROST) { Ability(ABILITY_FROST_ARMOR); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } THEN {
        EXPECT(!(player->status1 & STATUS1_FROSTBITE));
    }
}
