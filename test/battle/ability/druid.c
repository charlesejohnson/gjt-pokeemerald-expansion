#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Druid: Bear Form raises Def and Sp. Def, Cat Form swaps the boosts")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_BEAR_FORM); }
        TURN { MOVE(player, MOVE_CAT_FORM); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Druid: Unshift protects and removes the form boosts")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_BEAR_FORM); }
        TURN { MOVE(player, MOVE_UNSHIFT); MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Druid returned to\nits base form!");
        MESSAGE("Druid protected itself!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Druid: Tree Form is for Resto only")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TREE_FORM); }
    } SCENE {
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Druid: Tree Form boosts Sp. Def and makes heals 25% stronger")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_RESTORATION) { Speed(100); HP(10); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TREE_FORM); }
        TURN { MOVE(player, MOVE_HEALING_WAVE, target: player); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->hp, 10 + 50);
    }
}
