#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(gSpeciesInfo[SPECIES_MAGE_FIRE].abilities[0] == ABILITY_FLASH_FIRE);
    ASSUME(gSpeciesInfo[SPECIES_MAGE_FIRE].abilities[2] == ABILITY_HOT_STREAK);
}

SINGLE_BATTLE_TEST("Hot Streak raises the user's crit stage after landing a critical hit")
{
    GIVEN {
        PLAYER(SPECIES_MAGE_FIRE) { Ability(ABILITY_HOT_STREAK); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: TRUE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_HOT_STREAK);
        MESSAGE("Fire Mage is on a hot streak!");
    } THEN {
        EXPECT_EQ((u32)gBattleMons[0].volatiles.bonusCritStages, 1);
    }
}

SINGLE_BATTLE_TEST("Hot Streak stacks with each critical hit up to the cap")
{
    GIVEN {
        PLAYER(SPECIES_MAGE_FIRE) { Ability(ABILITY_HOT_STREAK); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: TRUE); }
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: TRUE); }
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: TRUE); }
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: TRUE); }
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: TRUE); }
    } THEN {
        EXPECT_EQ((u32)gBattleMons[0].volatiles.bonusCritStages, HOT_STREAK_MAX_STAGES);
    }
}

SINGLE_BATTLE_TEST("Hot Streak does not trigger without a critical hit")
{
    GIVEN {
        PLAYER(SPECIES_MAGE_FIRE) { Ability(ABILITY_HOT_STREAK); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: FALSE); }
    } THEN {
        EXPECT_EQ((u32)gBattleMons[0].volatiles.bonusCritStages, 0);
    }
}

SINGLE_BATTLE_TEST("Hot Streak does not trigger when the opponent is the one critting")
{
    GIVEN {
        PLAYER(SPECIES_MAGE_FIRE) { Ability(ABILITY_HOT_STREAK); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_TACKLE, criticalHit: TRUE); }
    } THEN {
        EXPECT_EQ((u32)gBattleMons[0].volatiles.bonusCritStages, 0);
    }
}

SINGLE_BATTLE_TEST("Hot Streak bonus resets when the user switches out")
{
    GIVEN {
        PLAYER(SPECIES_MAGE_FIRE) { Ability(ABILITY_HOT_STREAK); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: TRUE); }
        TURN { SWITCH(player, 1); }
        TURN { SWITCH(player, 0); }
    } THEN {
        EXPECT_EQ((u32)gBattleMons[0].volatiles.bonusCritStages, 0);
    }
}
