#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("AMS raises Sp. Def by 1 stage and sets up Safeguard")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_AMS); }
        TURN { MOVE(opponent, MOVE_TOXIC); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_AMS, player);
        MESSAGE("Your side became cloaked in a mystical veil!");
        MESSAGE("Wobbuffet's Sp. Def rose!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        EXPECT(!(player->status1 & STATUS1_ANY));
    }
}

SINGLE_BATTLE_TEST("AMS fails to set Safeguard twice")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_AMS); }
        TURN { MOVE(player, MOVE_AMS); }
    } SCENE {
        MESSAGE("But it failed!");
    }
}

DOUBLE_BATTLE_TEST("Dark Transformation raises an ally's Attack by 2 and Defense by 1")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_DARK_TRANSFORMATION, target: playerRight); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DARK_TRANSFORMATION, playerLeft);
    } THEN {
        EXPECT_EQ(playerRight->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(playerRight->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(playerLeft->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Dark Transformation fails in a single battle")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DARK_TRANSFORMATION); }
    } SCENE {
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Blood Boil makes the target's blood boil and drains it each turn")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOD_BOIL); }
    } SCENE {
        MESSAGE("Wobbuffet used Blood Boil!");
        MESSAGE("The opposing Wobbuffet's blood is boiling!");
        HP_BAR(player);
    }
}

SINGLE_BATTLE_TEST("Blood Boil does not affect Grass types")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_BULBASAUR);
    } WHEN {
        TURN { MOVE(player, MOVE_BLOOD_BOIL); }
    } SCENE {
        NOT MESSAGE("The opposing Bulbasaur's blood is boiling!");
    }
}

SINGLE_BATTLE_TEST("Dancing Rune Weapon raises Attack and Evasion and has 2 PP")
{
    ASSUME(GetMovePP(MOVE_DANCING_RUNE_WEAPON) == 2);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DANCING_RUNE_WEAPON); }
    } SCENE {
        NOT HP_BAR(player);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->statStages[STAT_EVASION], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->hp, player->maxHP);
    }
}

SINGLE_BATTLE_TEST("Icebound Fortitude raises Defense by 2 and lowers Speed by 1 without costing HP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ICEBOUND_FORTITUDE); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 2);
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
        EXPECT_EQ(player->hp, player->maxHP);
    }
}
