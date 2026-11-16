#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Death Strike costs 2 Runic Power and has flat power")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_BLOOD) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGIC_GUARD); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCOURGE_STRIKE); }
        TURN { MOVE(player, MOVE_SCOURGE_STRIKE); }
        TURN { MOVE(player, MOVE_SCOURGE_STRIKE); }
        TURN { MOVE(player, MOVE_DEATH_STRIKE); }
    } SCENE {
        HP_BAR(opponent);
        HP_BAR(opponent);
        HP_BAR(opponent);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ((u32)player->volatiles.stockpileCounter, 1);
    }
}

SINGLE_BATTLE_TEST("Death Strike fails with fewer than 2 Runic Power")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_BLOOD) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGIC_GUARD); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCOURGE_STRIKE); }
        TURN { MOVE(player, MOVE_DEATH_STRIKE); }
    } SCENE {
        HP_BAR(opponent);
        MESSAGE("But it failed!");
    } THEN {
        EXPECT_EQ((u32)player->volatiles.stockpileCounter, 1);
    }
}

SINGLE_BATTLE_TEST("Frost Strike power scales with Runic Power", s16 damage)
{
    u32 scourges;
    PARAMETRIZE { scourges = 1; }
    PARAMETRIZE { scourges = 2; }
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_FROST) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGIC_GUARD); Speed(1); HP(1000); MaxHP(1000); }
    } WHEN {
        for (u32 j = 0; j < scourges; j++)
            TURN { MOVE(player, MOVE_SCOURGE_STRIKE); }
        TURN { MOVE(player, MOVE_FROST_STRIKE); }
    } SCENE {
        for (u32 j = 0; j < scourges; j++)
            HP_BAR(opponent);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage * 100, results[0].damage * 190);
        EXPECT_LT(results[1].damage * 100, results[0].damage * 210);
    }
}

SINGLE_BATTLE_TEST("Death Coil spends one Runic Power and damages a foe")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_UNHOLY) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGIC_GUARD); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCOURGE_STRIKE); }
        TURN { MOVE(player, MOVE_SCOURGE_STRIKE); }
        TURN { MOVE(player, MOVE_DEATH_COIL); }
    } SCENE {
        HP_BAR(opponent);
        HP_BAR(opponent);
        MESSAGE("Unholy DK used Death Coil!");
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ((u32)player->volatiles.stockpileCounter, 1);
    }
}

SINGLE_BATTLE_TEST("Death Coil fails without Runic Power")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_UNHOLY);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DEATH_COIL); }
    } SCENE {
        MESSAGE("But it failed!");
        NOT HP_BAR(opponent);
    }
}

DOUBLE_BATTLE_TEST("Death Coil heals a Ghost-type ally for half its max HP and spends one Runic Power")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_UNHOLY) { Speed(100); }
        PLAYER(SPECIES_DEATHKNIGHT) { MaxHP(400); HP(100); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGIC_GUARD); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGIC_GUARD); Speed(2); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SCOURGE_STRIKE, target: opponentLeft); MOVE(playerRight, MOVE_CELEBRATE); }
        TURN { MOVE(playerLeft, MOVE_DEATH_COIL, target: playerRight); MOVE(playerRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(playerRight->hp, 300);
        EXPECT_EQ((u32)playerLeft->volatiles.stockpileCounter, 0);
    }
}

DOUBLE_BATTLE_TEST("Death Coil fails on a non-Ghost ally")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_UNHOLY) { Speed(100); }
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(400); HP(100); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGIC_GUARD); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_MAGIC_GUARD); Speed(2); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SCOURGE_STRIKE, target: opponentLeft); MOVE(playerRight, MOVE_CELEBRATE); }
        TURN { MOVE(playerLeft, MOVE_DEATH_COIL, target: playerRight); MOVE(playerRight, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT_EQ(playerRight->hp, 100);
    }
}
