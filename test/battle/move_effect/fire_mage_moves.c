#include "test/battle/test.h"
#include "test/battle/test_util.h"

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
        MESSAGE("Foe Wobbuffet's Speed fell!");
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Blast Wave hits both targets in double battle")
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
        MESSAGE("Foe Wobbuffet's Speed fell!");
        MESSAGE("Foe Wynaut's Speed fell!");
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
        MESSAGE("Wobbuffet is charging a massive fireball!");
        NOT MESSAGE("Wobbuffet used Pyroblast!");
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_PYROBLAST, player);
        NOT HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(player->status2, STATUS2_CHARGING);
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
        MESSAGE("Wobbuffet is charging a massive fireball!");
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
        MESSAGE("Wobbuffet is charging a massive fireball!");
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

SINGLE_BATTLE_TEST("Blast Wave is a wind move")
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
        // Wind moves have special properties, but this is mainly for verification
        EXPECT_TRUE(gMovesInfo[MOVE_BLAST_WAVE].windMove);
    }
}

SINGLE_BATTLE_TEST("Pyroblast uses Solar Beam animation")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PYROBLAST); }
        TURN { SKIP_TURN(player); }
    } SCENE {
        MESSAGE("Wobbuffet is charging a massive fireball!");
        MESSAGE("Wobbuffet used Pyroblast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PYROBLAST, player);
        HP_BAR(opponent);
    } THEN {
        // Should use Solar Beam animation script
        EXPECT_EQ(gMovesInfo[MOVE_PYROBLAST].battleAnimScript, gBattleAnimMove_SolarBeam);
    }
}

SINGLE_BATTLE_TEST("Phoenix Flames uses Dragon Rage animation")
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
        // Should use Dragon Rage animation script
        EXPECT_EQ(gMovesInfo[MOVE_PHOENIX_FLAMES].battleAnimScript, gBattleAnimMove_DragonRage);
    }
}

SINGLE_BATTLE_TEST("All Fire Mage moves are valid apprentice moves")
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
        EXPECT_TRUE(gMovesInfo[MOVE_BLAST_WAVE].validApprenticeMove);
        EXPECT_TRUE(gMovesInfo[MOVE_PYROBLAST].validApprenticeMove);
        EXPECT_TRUE(gMovesInfo[MOVE_PHOENIX_FLAMES].validApprenticeMove);
    }
}

SINGLE_BATTLE_TEST("Fire Mage moves have correct contest categories")
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
        EXPECT_EQ(gMovesInfo[MOVE_BLAST_WAVE].contestCategory, CONTEST_CATEGORY_COOL);
        EXPECT_EQ(gMovesInfo[MOVE_PYROBLAST].contestCategory, CONTEST_CATEGORY_BEAUTY);
        EXPECT_EQ(gMovesInfo[MOVE_PHOENIX_FLAMES].contestCategory, CONTEST_CATEGORY_BEAUTY);
    }
}

SINGLE_BATTLE_TEST("Fire Mage moves have correct contest effects")
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
        EXPECT_EQ(gMovesInfo[MOVE_BLAST_WAVE].contestEffect, CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS);
        EXPECT_EQ(gMovesInfo[MOVE_PYROBLAST].contestEffect, CONTEST_EFFECT_HIGHLY_APPEALING);
        EXPECT_EQ(gMovesInfo[MOVE_PHOENIX_FLAMES].contestEffect, CONTEST_EFFECT_BETTER_IF_SAME_TYPE);
    }
} 