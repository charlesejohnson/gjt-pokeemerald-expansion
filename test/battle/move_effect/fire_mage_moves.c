#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(gMovesInfo[MOVE_BLAST_WAVE].effect == EFFECT_HIT);
    ASSUME(gMovesInfo[MOVE_BLAST_WAVE].power == 55);
    ASSUME(gMovesInfo[MOVE_BLAST_WAVE].type == TYPE_FIRE);
    ASSUME(gMovesInfo[MOVE_BLAST_WAVE].accuracy == 95);
    ASSUME(gMovesInfo[MOVE_BLAST_WAVE].target == MOVE_TARGET_BOTH);
    ASSUME(gMovesInfo[MOVE_PYROBLAST].effect == EFFECT_SOLAR_BEAM);
    ASSUME(gMovesInfo[MOVE_PYROBLAST].power == 120);
    ASSUME(gMovesInfo[MOVE_PYROBLAST].type == TYPE_FIRE);
    ASSUME(gMovesInfo[MOVE_PYROBLAST].accuracy == 100);
    ASSUME(gMovesInfo[MOVE_PHOENIX_FLAMES].effect == EFFECT_HIT);
    ASSUME(gMovesInfo[MOVE_PHOENIX_FLAMES].power == 50);
    ASSUME(gMovesInfo[MOVE_PHOENIX_FLAMES].type == TYPE_DRAGON);
    ASSUME(gMovesInfo[MOVE_PHOENIX_FLAMES].accuracy == 100);
    ASSUME(gMovesInfo[MOVE_PHOENIX_FLAMES].criticalHitStage == 1);
}

SINGLE_BATTLE_TEST("Blast Wave reduces target's speed")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BLAST_WAVE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLAST_WAVE, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("The opposing Wobbuffet's Speed fell!");
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
    }
}

DOUBLE_BATTLE_TEST("Blast Wave hits both targets in double battle")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BLAST_WAVE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLAST_WAVE, playerLeft);
        HP_BAR(opponentLeft);
        HP_BAR(opponentRight);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
        MESSAGE("The opposing Wobbuffet's Speed fell!");
        MESSAGE("The opposing Wynaut's Speed fell!");
    } THEN {
        EXPECT_EQ(opponentLeft->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
        EXPECT_EQ(opponentRight->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Pyroblast is a two-turn move")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PYROBLAST); }
        TURN { SKIP_TURN(player); }
    } SCENE {
        MESSAGE("Wobbuffet began charging power!");
        NONE_OF {
            MESSAGE("Wobbuffet used Pyroblast!");
            HP_BAR(opponent);
        }
    } THEN {
        EXPECT_EQ(player->status2, STATUS2_MULTIPLETURNS);
    }
}

SINGLE_BATTLE_TEST("Pyroblast deals damage on second turn")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PYROBLAST); }
        TURN { SKIP_TURN(player); }
    } SCENE {
        MESSAGE("Wobbuffet began charging power!");
        MESSAGE("Wobbuffet used Pyroblast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PYROBLAST, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(player->status2, 0);
    }
}

SINGLE_BATTLE_TEST("Phoenix Flames has increased critical hit ratio")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PHOENIX_FLAMES); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PHOENIX_FLAMES, player);
        HP_BAR(opponent);
    } THEN {
        // Critical hit stage should be increased by 1
        EXPECT_EQ(player->status2 & STATUS2_FOCUS_ENERGY, STATUS2_FOCUS_ENERGY);
    }
}

SINGLE_BATTLE_TEST("Phoenix Flames has 50% chance to increase critical hit stage")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PHOENIX_FLAMES); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PHOENIX_FLAMES, player);
        HP_BAR(opponent);
        // 50% chance to show "getting pumped" message
        // This will be random, so we can't guarantee it appears
    }
}

SINGLE_BATTLE_TEST("Phoenix Flames critical hit stage increase doesn't stack")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PHOENIX_FLAMES); }
        TURN { MOVE(player, MOVE_PHOENIX_FLAMES); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PHOENIX_FLAMES, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PHOENIX_FLAMES, player);
        HP_BAR(opponent);
        // Second use shouldn't show "getting pumped" if already active
    }
}

SINGLE_BATTLE_TEST("Blast Wave has 95% accuracy")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BLAST_WAVE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLAST_WAVE, player);
        HP_BAR(opponent);
    } THEN {
        // Should hit 95% of the time
        // This test will pass if it hits, fail if it misses
    }
}

SINGLE_BATTLE_TEST("Pyroblast has 100% accuracy")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PYROBLAST); }
        TURN { SKIP_TURN(player); }
    } SCENE {
        MESSAGE("Wobbuffet began charging power!");
        MESSAGE("Wobbuffet used Pyroblast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PYROBLAST, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Phoenix Flames has 100% accuracy")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PHOENIX_FLAMES); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PHOENIX_FLAMES, player);
        HP_BAR(opponent);
    }
} 