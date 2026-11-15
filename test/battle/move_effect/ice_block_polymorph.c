#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_ICE_BLOCK) == EFFECT_ICE_BLOCK);
    ASSUME(GetMoveEffect(MOVE_POLYMORPH) == EFFECT_SUBSTITUTE_AND_SLEEP);
}

SINGLE_BATTLE_TEST("Ice Block protects the user from damaging moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_BLOCK); MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ICE_BLOCK, player);
        NOT HP_BAR(player);
    }
}

SINGLE_BATTLE_TEST("Ice Block heals 25% of max HP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(100); MaxHP(400); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_BLOCK); }
    } SCENE {
        HP_BAR(player, damage: -100);
    } THEN {
        EXPECT_EQ(player->hp, 200);
    }
}

SINGLE_BATTLE_TEST("Ice Block heals 50% of max HP in hail")
{
    GIVEN {
        PLAYER(SPECIES_GLALIE) { HP(100); MaxHP(400); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_HAIL); }
        TURN { MOVE(player, MOVE_ICE_BLOCK); }
    } THEN {
        EXPECT_EQ(player->hp, 300);
    }
}

SINGLE_BATTLE_TEST("Ice Block does not heal above max HP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(350); MaxHP(400); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_BLOCK); }
    } THEN {
        EXPECT_EQ(player->hp, 400);
    }
}

SINGLE_BATTLE_TEST("Ice Block goes before regular moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_ICE_BLOCK); MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ICE_BLOCK, player);
        NOT HP_BAR(player);
    }
}

SINGLE_BATTLE_TEST("Polymorph puts the target to sleep and gives it a substitute")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_POLYMORPH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POLYMORPH, player);
        STATUS_ICON(opponent, sleep: TRUE);
    } THEN {
        EXPECT_EQ(opponent->status1 & STATUS1_SLEEP, opponent->status1);
        EXPECT_NE(opponent->status1, 0);
    }
}

SINGLE_BATTLE_TEST("Polymorph's substitute absorbs the next hit")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_POLYMORPH); }
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POLYMORPH, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        NOT HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Polymorph fails against a target that already has a status")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Status1(STATUS1_BURN); }
    } WHEN {
        TURN { MOVE(player, MOVE_POLYMORPH); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(!(opponent->status1 & STATUS1_SLEEP));
    }
}

SINGLE_BATTLE_TEST("Polymorph fails if the target already has a substitute")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUBSTITUTE); MOVE(player, MOVE_POLYMORPH); }
    } SCENE {
        MESSAGE("But it failed!");
    } THEN {
        EXPECT(!(opponent->status1 & STATUS1_SLEEP));
    }
}

SINGLE_BATTLE_TEST("Polymorph does not affect Insomnia targets")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_INSOMNIA); }
    } WHEN {
        TURN { MOVE(player, MOVE_POLYMORPH); }
    } THEN {
        EXPECT(!(opponent->status1 & STATUS1_SLEEP));
    }
}
