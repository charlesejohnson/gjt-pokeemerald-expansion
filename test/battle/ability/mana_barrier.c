#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMovePP(MOVE_TACKLE) == 35);
    ASSUME(GetMovePP(MOVE_HYPER_BEAM) == 5);
    ASSUME(GetMovePP(MOVE_ROCK_SLIDE) == 10);
    ASSUME(GetMoveCategory(MOVE_GROWL) == DAMAGE_CATEGORY_STATUS);
    ASSUME(gSpeciesInfo[SPECIES_MAGE].abilities[0] == ABILITY_FROST_ARMOR);
    ASSUME(gSpeciesInfo[SPECIES_MAGE_ARCANE].abilities[0] == ABILITY_MANA_BARRIER);
}

SINGLE_BATTLE_TEST("Mana Barrier costs max HP divided by the move's PP")
{
    s16 expected;
    GIVEN {
        PLAYER(SPECIES_MAGE_ARCANE);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent);
        HP_BAR(player);
    } THEN {
        expected = player->maxHP / GetMovePP(MOVE_TACKLE);
        EXPECT_EQ(player->hp, player->maxHP - expected);
    }
}

SINGLE_BATTLE_TEST("Mana Barrier costs more for low-PP moves")
{
    s16 expected;
    GIVEN {
        PLAYER(SPECIES_MAGE_ARCANE);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_BEAM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_BEAM, player);
        HP_BAR(opponent);
        HP_BAR(player);
    } THEN {
        expected = player->maxHP / GetMovePP(MOVE_HYPER_BEAM);
        EXPECT_EQ(player->hp, player->maxHP - expected);
    }
}

SINGLE_BATTLE_TEST("Mana Barrier cost never exceeds 25% of max HP")
{
    GIVEN {
        ASSUME(GetManaBarrierRecoil(0, MOVE_HYPER_BEAM) >= 1);
        PLAYER(SPECIES_MAGE_ARCANE);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_BEAM); }
    } THEN {
        EXPECT_GE(player->hp, player->maxHP - player->maxHP / 4);
    }
}

SINGLE_BATTLE_TEST("Mana Barrier does not trigger on status moves")
{
    GIVEN {
        PLAYER(SPECIES_MAGE_ARCANE);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_GROWL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GROWL, player);
        NOT HP_BAR(player);
    } THEN {
        EXPECT_EQ(player->hp, player->maxHP);
    }
}

SINGLE_BATTLE_TEST("Mana Barrier is absent on other mages")
{
    GIVEN {
        PLAYER(SPECIES_MAGE);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, player);
        HP_BAR(opponent);
        NOT HP_BAR(player);
    } THEN {
        EXPECT_EQ(player->hp, player->maxHP);
    }
}

DOUBLE_BATTLE_TEST("Mana Barrier costs HP once for a spread move")
{
    s16 expected;
    GIVEN {
        PLAYER(SPECIES_MAGE_ARCANE);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_ROCK_SLIDE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROCK_SLIDE, playerLeft);
    } THEN {
        expected = playerLeft->maxHP / GetMovePP(MOVE_ROCK_SLIDE);
        EXPECT_EQ(playerLeft->hp, playerLeft->maxHP - expected);
    }
}

SINGLE_BATTLE_TEST("Mana Barrier recoil is negated by Magic Guard")
{
    GIVEN {
        PLAYER(SPECIES_MAGE_ARCANE) { Ability(ABILITY_MAGIC_GUARD); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } THEN {
        EXPECT_EQ(player->hp, player->maxHP);
    }
}
