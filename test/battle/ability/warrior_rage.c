#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Warrior gains rage when hitting and being hit")
{
    GIVEN {
        PLAYER(SPECIES_WARRIOR_ARMS) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Arms Warrior's rage: 1/10");
        MESSAGE("Arms Warrior's rage: 2/10");
    } THEN {
        EXPECT_EQ((u32)gBattleMons[0].volatiles.warriorRage, 2);
    }
}

SINGLE_BATTLE_TEST("Mortal Strike fails without 4 rage, then spends 4 and blocks healing")
{
    GIVEN {
        PLAYER(SPECIES_WARRIOR_ARMS) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_MORTAL_STRIKE); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT_EQ((u32)gBattleMons[0].volatiles.warriorRage, 0);
    }
}

SINGLE_BATTLE_TEST("Execute spends all rage")
{
    GIVEN {
        PLAYER(SPECIES_WARRIOR_ARMS) { Speed(100); Ability(ABILITY_GUTS); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN { MOVE(player, MOVE_TACKLE); }
        TURN { MOVE(player, MOVE_EXECUTE); }
    } THEN {
        EXPECT_EQ((u32)gBattleMons[0].volatiles.warriorRage, 0);
    }
}

SINGLE_BATTLE_TEST("Charge! builds 5 rage")
{
    GIVEN {
        PLAYER(SPECIES_WARRIOR_ARMS) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_WARRIOR_CHARGE); }
    } THEN {
        EXPECT_EQ((u32)gBattleMons[0].volatiles.warriorRage, 6);
    }
}

SINGLE_BATTLE_TEST("Spell Reflect blocks special attacks and hurts the caster")
{
    GIVEN {
        PLAYER(SPECIES_WARRIOR_PROTECTION) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_SPELL_REFLECT); MOVE(opponent, MOVE_SWIFT); }
    } SCENE {
        MESSAGE("Prot Warrior protected itself!");
    } THEN {
        EXPECT_EQ(player->hp, player->maxHP);
        EXPECT_LT(opponent->hp, opponent->maxHP);
        EXPECT_GT(opponent->maxHP - opponent->hp, 1); // real reflected damage
    }
}

DOUBLE_BATTLE_TEST("Sweeping Strikes makes single-target attacks hit every foe")
{
    GIVEN {
        PLAYER(SPECIES_WARRIOR_ARMS) { Speed(100); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); HP(10000); MaxHP(10000); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(5); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SWEEPING_STRIKES); }
        TURN { MOVE(playerLeft, MOVE_TACKLE, target: opponentLeft); }
    } THEN {
        EXPECT_LT(opponentLeft->hp, opponentLeft->maxHP);
        EXPECT_LT(opponentRight->hp, opponentRight->maxHP);
    }
}
