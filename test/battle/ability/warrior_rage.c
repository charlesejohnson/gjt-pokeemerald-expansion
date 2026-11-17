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
