#include "global.h"
#include "test/battle.h"
#include "event_data.h"
#include "constants/vars.h"

SINGLE_BATTLE_TEST("Hunter: Concussive Shot lowers Speed by 2")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER) { Speed(100); Moves(MOVE_CONCUSSIVE_SHOT); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_CONCUSSIVE_SHOT); }
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 2);
    }
}

SINGLE_BATTLE_TEST("Hunter: Serpent Sting always poisons")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER) { Speed(100); Moves(MOVE_SERPENT_STING); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SERPENT_STING); }
    } THEN {
        EXPECT(opponent->status1 & STATUS1_POISON);
    }
}

SINGLE_BATTLE_TEST("Hunter: Steady Shot charges for a turn, then hits")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER_MARKSMANSHIP) { Speed(100); Moves(MOVE_STEADY_SHOT); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_STEADY_SHOT); }
        TURN { SKIP_TURN(player); }
    } THEN {
        EXPECT_LT(opponent->hp, 10000);
    }
}

SINGLE_BATTLE_TEST("Hunter: Immolation Trap burns the next switch-in and is consumed")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER) { Speed(100); Moves(MOVE_IMMOLATION_TRAP); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WYNAUT) { Speed(1); }
        OPPONENT(SPECIES_WYNAUT) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_IMMOLATION_TRAP); }
        TURN { SWITCH(opponent, 1); }
        TURN { SWITCH(opponent, 2); }
    } THEN {
        EXPECT(GetMonData(&gParties[B_TRAINER_OPPONENT_A][1], MON_DATA_STATUS) & STATUS1_BURN);
        EXPECT(opponent->status1 == 0);
    }
}

SINGLE_BATTLE_TEST("Hunter: Freezing Trap freezes the next switch-in")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER) { Speed(100); Moves(MOVE_FREEZING_TRAP); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WYNAUT) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_FREEZING_TRAP); }
        TURN { SWITCH(opponent, 1); }
    } THEN {
        EXPECT(GetMonData(&gParties[B_TRAINER_OPPONENT_A][1], MON_DATA_STATUS) & STATUS1_FREEZE);
    }
}

SINGLE_BATTLE_TEST("Hunter: Snake Trap damages and poisons the next switch-in")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER) { Speed(100); Moves(MOVE_SNAKE_TRAP); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WYNAUT) { Speed(1); HP(400); MaxHP(400); }
    } WHEN {
        TURN { MOVE(player, MOVE_SNAKE_TRAP); }
        TURN { SWITCH(opponent, 1); }
    } THEN {
        EXPECT(GetMonData(&gParties[B_TRAINER_OPPONENT_A][1], MON_DATA_STATUS) & STATUS1_POISON);
        EXPECT_LT(GetMonData(&gParties[B_TRAINER_OPPONENT_A][1], MON_DATA_HP), 400);
    }
}

SINGLE_BATTLE_TEST("Hunter: Disengage blocks physical attacks and raises Speed")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER) { Speed(100); HP(10000); MaxHP(10000); Moves(MOVE_DISENGAGE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); Moves(MOVE_TACKLE); }
    } WHEN {
        TURN { MOVE(player, MOVE_DISENGAGE); MOVE(opponent, MOVE_TACKLE); }
    } THEN {
        EXPECT_EQ(player->hp, player->maxHP);
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
    }
}

DOUBLE_BATTLE_TEST("Hunter: Kill Command buffs the pet")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER_BEAST_MASTERY) { Speed(100); Moves(MOVE_KILL_COMMAND); }
        PLAYER(SPECIES_WYNAUT) { Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_KILL_COMMAND, target: playerRight); MOVE(playerRight, MOVE_CELEBRATE); MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(playerRight->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
    }
}

DOUBLE_BATTLE_TEST("Hunter: Spirit Bond heals both beside the pet")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER_BEAST_MASTERY) { Speed(100); HP(100); MaxHP(400); }
        PLAYER(SPECIES_WYNAUT) { Speed(50); HP(100); MaxHP(400); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_CELEBRATE); MOVE(playerRight, MOVE_CELEBRATE); MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_GT(playerLeft->hp, 100);
        EXPECT_GT(playerRight->hp, 100);
    }
}

SINGLE_BATTLE_TEST("Hunter: Mongoose Bite fails unless the last attack missed")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER_SURVIVAL) { Speed(100); Moves(MOVE_MONGOOSE_BITE, MOVE_TACKLE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_MONGOOSE_BITE); }
    } SCENE {
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Hunter: Mongoose Bite works after a miss")
{
    GIVEN {
        PLAYER(SPECIES_HUNTER_SURVIVAL) { Speed(100); Moves(MOVE_MONGOOSE_BITE, MOVE_TACKLE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE, hit: FALSE); }
        TURN { MOVE(player, MOVE_MONGOOSE_BITE); }
    } THEN {
        EXPECT_LT(opponent->hp, 10000);
    }
}

WILD_BATTLE_TEST("Hunter: Tame Beast catches a weakened wild mon")
{
    VarSet(VAR_HUNTER_PET_PID_LO, 0);
    VarSet(VAR_HUNTER_PET_PID_HI, 0);
    GIVEN {
        PLAYER(SPECIES_HUNTER_BEAST_MASTERY) { Speed(100); Moves(MOVE_TAME_BEAST); }
        OPPONENT(SPECIES_MAGIKARP) { Speed(1); Level(5); HP(1); MaxHP(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_TAME_BEAST); }
    } SCENE {
        MESSAGE("Beast Hunter used Tame Beast!");
    } THEN {
        EXPECT_EQ(gBattleOutcome, 7);
    }
}
