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
        PLAYER(SPECIES_DRUID_RESTORATION) { Speed(100); HP(10); MaxHP(100); Ability(ABILITY_BALL_FETCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TREE_FORM); }
        TURN { MOVE(player, MOVE_HEALING_WAVE, target: player); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->hp, 10 + 50);
    }
}

SINGLE_BATTLE_TEST("Druid: Efflorescence blooms on switch-in and heals for 3 turns")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_RESTORATION) { Speed(100); HP(50); MaxHP(160); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(player->hp, 50 + 3 * 10);
    }
}

SINGLE_BATTLE_TEST("Druid: Thick Hide cuts damage at half HP or less", s16 damage)
{
    u32 hp;
    PARAMETRIZE { hp = 300; }
    PARAMETRIZE { hp = 100; }
    GIVEN {
        PLAYER(SPECIES_DRUID_GUARDIAN) { Speed(1); HP(hp); MaxHP(300); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TACKLE, criticalHit: FALSE); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.75), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Druid: Predatory Swiftness gives priority after a crit")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_FERAL) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: TRUE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: FALSE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet used Celebrate!");
        MESSAGE("Feral Druid used Tackle!");
        MESSAGE("Feral Druid used Tackle!");
        MESSAGE("The opposing Wobbuffet used Celebrate!");
    }
}

SINGLE_BATTLE_TEST("Druid: Eclipse boosts Grass moves on alternate turns", s16 damage)
{
    u32 idle;
    PARAMETRIZE { idle = 0; }
    PARAMETRIZE { idle = 1; }
    GIVEN {
        PLAYER(SPECIES_DRUID_BOOMY) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        if (idle)
            TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_VINE_WHIP, criticalHit: FALSE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.3), results[0].damage);
    }
}
