#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Monk: Blackout Kick hits twice")
{
    GIVEN {
        PLAYER(SPECIES_MONK_WINDWALKER) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_BLACKOUT_KICK); }
    } SCENE {
        MESSAGE("Wind Monk used Blackout Kick!");
        HP_BAR(opponent);
        HP_BAR(opponent);
    }
}

DOUBLE_BATTLE_TEST("Monk: Spinning Crane Kick hits everyone else")
{
    GIVEN {
        PLAYER(SPECIES_MONK_WINDWALKER) { Speed(100); }
        PLAYER(SPECIES_WYNAUT) { Speed(50); HP(10000); MaxHP(10000); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SPINNING_CRANE_KICK); MOVE(playerRight, MOVE_CELEBRATE); MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_LT(gParties[B_TRAINER_PLAYER][1].hp, 10000);
        EXPECT_LT(opponentLeft->hp, 10000);
        EXPECT_LT(opponentRight->hp, 10000);
        EXPECT_EQ(playerLeft->hp, playerLeft->maxHP);
        EXPECT_EQ(10000 - opponentLeft->hp, 10000 - opponentRight->hp);
    }
}

SINGLE_BATTLE_TEST("Monk: Whirling Dragon Punch needs Rising Sun Kick and Blackout Kick, then resets them")
{
    GIVEN {
        PLAYER(SPECIES_MONK_WINDWALKER) { Speed(100); Moves(MOVE_WHIRLING_DRAGON_PUNCH, MOVE_RISING_SUN_KICK, MOVE_BLACKOUT_KICK); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_WHIRLING_DRAGON_PUNCH); }
        TURN { MOVE(player, MOVE_RISING_SUN_KICK); }
        TURN { MOVE(player, MOVE_WHIRLING_DRAGON_PUNCH); }
        TURN { MOVE(player, MOVE_BLACKOUT_KICK); }
        TURN { MOVE(player, MOVE_WHIRLING_DRAGON_PUNCH); }
        TURN { MOVE(player, MOVE_WHIRLING_DRAGON_PUNCH); }
    } SCENE {
        MESSAGE("Wind Monk used Whirling Dragon!");
        MESSAGE("But it failed!");
        MESSAGE("Wind Monk used Rising Sun Kick!");
        MESSAGE("Wind Monk used Whirling Dragon!");
        MESSAGE("But it failed!");
        MESSAGE("Wind Monk used Blackout Kick!");
        MESSAGE("Wind Monk used Whirling Dragon!");
        HP_BAR(opponent);
        MESSAGE("Wind Monk used Whirling Dragon!");
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Monk: Combo Strikes boosts damage unless a move repeats")
{
    s16 damage[2];
    GIVEN {
        PLAYER(SPECIES_MONK_WINDWALKER) { Speed(100); Moves(MOVE_TIGER_PALM, MOVE_BLACKOUT_KICK); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_TIGER_PALM); }
        TURN { MOVE(player, MOVE_TIGER_PALM); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &damage[0]);
        HP_BAR(opponent, captureDamage: &damage[1]);
    } THEN {
        EXPECT_GT(damage[0], damage[1]); // rolls vary, so only check direction
    }
}

SINGLE_BATTLE_TEST("Brewmaster: Stagger builds with each hit, ticks, and boosts Atk and Speed at level 3")
{
    GIVEN {
        PLAYER(SPECIES_MONK_BREWMASTER) { Speed(1); HP(400); MaxHP(400); Defense(300); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Attack(40); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TACKLE); MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(opponent, MOVE_TACKLE); MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(opponent, MOVE_TACKLE); MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Brew Monk is hurt by\nits stagger!");
    } THEN {
        EXPECT_EQ((u32)player->volatiles.staggerLevel, 3);
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Brewmaster: Purifying Brew banks stagger and Celestial Brew shields")
{
    GIVEN {
        PLAYER(SPECIES_MONK_BREWMASTER) { Speed(1); HP(400); MaxHP(400); Defense(300); Moves(MOVE_PURIFYING_BREW, MOVE_CELESTIAL_BREW, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Attack(40); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TACKLE); MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(opponent, MOVE_TACKLE); MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_PURIFYING_BREW); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_CELESTIAL_BREW); }
    } THEN {
        EXPECT_EQ((u32)player->volatiles.staggerLevel, 0);
        EXPECT_EQ((u32)player->volatiles.brewStacks, 0);
        EXPECT_GT((u32)player->volatiles.monkShield, 0);
    }
}

SINGLE_BATTLE_TEST("Brewmaster: Keg Smash soaks the foe, then Breath of Fire always burns")
{
    GIVEN {
        PLAYER(SPECIES_MONK_BREWMASTER) { Speed(100); Moves(MOVE_KEG_SMASH, MOVE_BREATH_OF_FIRE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_KEG_SMASH); }
        TURN { MOVE(player, MOVE_BREATH_OF_FIRE); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet is covered in liquor!");
        MESSAGE("The opposing Wobbuffet was burned!");
    } THEN {
        EXPECT(opponent->status1 & STATUS1_BURN);
        EXPECT_EQ((u32)opponent->volatiles.liquor, 0);
        EXPECT_EQ(opponent->statStages[STAT_ACC], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Mistweaver: Life Cocoon gives Substitute and Aqua Ring")
{
    GIVEN {
        PLAYER(SPECIES_MONK_MISTWEAVER) { Speed(100); Moves(MOVE_LIFE_COCOON); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_LIFE_COCOON, target: player); }
    } THEN {
        EXPECT_EQ((u32)player->volatiles.substitute, 1);
        EXPECT_EQ((u32)player->volatiles.aquaRing, 1);
    }
}

SINGLE_BATTLE_TEST("Mistweaver: Soothing Mist heals the weakest party member")
{
    GIVEN {
        PLAYER(SPECIES_MONK_MISTWEAVER) { Speed(100); Moves(MOVE_TIGER_PALM); }
        PLAYER(SPECIES_WYNAUT) { Speed(50); HP(10); MaxHP(300); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_TIGER_PALM); }
    } SCENE {
        MESSAGE("Wynaut is soothed\nby the mist!");
    } THEN {
        EXPECT_GT(gParties[B_TRAINER_PLAYER][1].hp, 10);
    }
}

SINGLE_BATTLE_TEST("Monk: Ring of Peace blocks and slows a physical attacker")
{
    GIVEN {
        PLAYER(SPECIES_MONK) { Speed(100); Moves(MOVE_RING_OF_PEACE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_RING_OF_PEACE); MOVE(opponent, MOVE_TACKLE); }
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
        EXPECT_EQ(player->hp, player->maxHP);
    }
}
