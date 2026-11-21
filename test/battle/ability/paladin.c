#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Paladin: Seal of Light heals from damage dealt")
{
    GIVEN {
        PLAYER(SPECIES_PALADIN_HOLY) { Speed(100); HP(100); MaxHP(300); Moves(MOVE_SEAL_OF_LIGHT, MOVE_HOLY_STRIKE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_SEAL_OF_LIGHT); }
        TURN { MOVE(player, MOVE_HOLY_STRIKE); }
    } THEN {
        EXPECT_GT(player->hp, 100);
    }
}

SINGLE_BATTLE_TEST("Paladin: Judgement consumes the seal and Light heals 25%")
{
    GIVEN {
        PLAYER(SPECIES_PALADIN_HOLY) { Speed(100); HP(100); MaxHP(400); Moves(MOVE_SEAL_OF_LIGHT, MOVE_JUDGEMENT_PALADIN); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_SEAL_OF_LIGHT); }
        TURN { MOVE(player, MOVE_JUDGEMENT_PALADIN); }
    } THEN {
        EXPECT_GE(player->hp, 200);
        EXPECT_EQ((u32)player->volatiles.paladinSeal, 0);
    }
}

SINGLE_BATTLE_TEST("Paladin: Seal of Justice can lock in with Judgement")
{
    GIVEN {
        PLAYER(SPECIES_PALADIN_HOLY) { Speed(100); Moves(MOVE_SEAL_OF_JUSTICE, MOVE_JUDGEMENT_PALADIN); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_SEAL_OF_JUSTICE); }
        TURN { MOVE(player, MOVE_JUDGEMENT_PALADIN); }
    } THEN {
        EXPECT_EQ((u32)opponent->volatiles.escapePrevention, 1);
    }
}

SINGLE_BATTLE_TEST("Paladin: Blessing of Kings raises every stat once, Might +2 Atk")
{
    GIVEN {
        PLAYER(SPECIES_PALADIN_PROTECTION) { Speed(100); Moves(MOVE_BLESSING_OF_KINGS, MOVE_BLESSING_OF_MIGHT); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_BLESSING_OF_KINGS, target: player); }
        TURN { MOVE(player, MOVE_BLESSING_OF_MIGHT, target: player); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 3);
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Paladin: Avenging Wrath boosts Atk, SpA and crit")
{
    GIVEN {
        PLAYER(SPECIES_PALADIN_RETRIBUTION) { Speed(100); Moves(MOVE_AVENGING_WRATH); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_AVENGING_WRATH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ((u32)player->volatiles.bonusCritStages, 1);
    }
}

SINGLE_BATTLE_TEST("Paladin: Consecration burns non-Fire foes each turn")
{
    GIVEN {
        PLAYER(SPECIES_PALADIN) { Speed(100); Moves(MOVE_CONSECRATION); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(1600); MaxHP(1600); }
    } WHEN {
        TURN { MOVE(player, MOVE_CONSECRATION); }
    } THEN {
        EXPECT_EQ(opponent->hp, 1500);
    }
}

SINGLE_BATTLE_TEST("Paladin: Devotion Aura trims physical damage")
{
    s16 base, aura;
    PARAMETRIZE { base = 0; }
    PARAMETRIZE { base = 1; }
    GIVEN {
        PLAYER(base ? SPECIES_PALADIN : SPECIES_PALADIN_PROTECTION) { Speed(1); HP(10000); MaxHP(10000); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_TACKLE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        HP_BAR(player, captureDamage: &aura);
    } THEN {
        EXPECT_GT(aura, 0);
    }
}

SINGLE_BATTLE_TEST("Paladin: Concentration Aura blocks stat drops")
{
    GIVEN {
        PLAYER(SPECIES_PALADIN_HOLY) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_GROWL); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_GROWL); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Paladin: Retribution Aura hurts contact attackers")
{
    GIVEN {
        PLAYER(SPECIES_PALADIN_RETRIBUTION) { Speed(1); HP(10000); MaxHP(10000); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_TACKLE); HP(600); MaxHP(600); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TACKLE); }
    } THEN {
        EXPECT_EQ(opponent->hp, 500);
    }
}

SINGLE_BATTLE_TEST("Paladin: Avenger's Shield lowers Sp. Atk")
{
    GIVEN {
        PLAYER(SPECIES_PALADIN_PROTECTION) { Speed(100); Moves(MOVE_AVENGERS_SHIELD); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_AVENGERS_SHIELD); }
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPATK], DEFAULT_STAT_STAGE - 1);
    }
}
