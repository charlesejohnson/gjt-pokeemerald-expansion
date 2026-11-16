#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Howling Blast hits both foes and can frostbite or freeze them")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_FROST);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_HOWLING_BLAST, WITH_RNG(RNG_SECONDARY_EFFECT, TRUE)); }
    } SCENE {
        HP_BAR(opponentLeft);
        HP_BAR(opponentRight);
    } THEN {
        EXPECT(opponentLeft->status1 & (STATUS1_FROSTBITE | STATUS1_FREEZE));
        EXPECT(opponentRight->status1 & (STATUS1_FROSTBITE | STATUS1_FREEZE));
        EXPECT_EQ(playerRight->hp, playerRight->maxHP);
    }
}

DOUBLE_BATTLE_TEST("Remorseless Winter hits every other battler, including the user's ally")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_FROST);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_REMORSELESS_WINTER); }
    } THEN {
        EXPECT_LT(opponentLeft->hp, opponentLeft->maxHP);
        EXPECT_LT(opponentRight->hp, opponentRight->maxHP);
        EXPECT_LT(playerRight->hp, playerRight->maxHP);
        EXPECT_EQ(playerLeft->hp, playerLeft->maxHP);
    }
}

SINGLE_BATTLE_TEST("Remorseless Winter hits multiple times")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_FROST);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SHADOW_TAG); HP(1000); MaxHP(1000); }
    } WHEN {
        TURN { MOVE(player, MOVE_REMORSELESS_WINTER); }
    } SCENE {
        HP_BAR(opponent);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Obliterate has an increased critical hit ratio")
{
    ASSUME(GetMoveCriticalHitStage(MOVE_OBLITERATE) == 1);
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_FROST);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_OBLITERATE, criticalHit: TRUE); }
    } SCENE {
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Marrowrend can raise the user's Defense")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_BLOOD);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MARROWREND, WITH_RNG(RNG_SECONDARY_EFFECT, TRUE)); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Marrowrend does not always raise Defense")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_BLOOD);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MARROWREND, WITH_RNG(RNG_SECONDARY_EFFECT, FALSE)); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}

DOUBLE_BATTLE_TEST("Consumption hits both foes and heals the user for half the damage dealt")
{
    s16 damageLeft, damageRight;
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_BLOOD) { MaxHP(500); HP(100); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_CONSUMPTION); }
    } SCENE {
        HP_BAR(opponentLeft, captureDamage: &damageLeft);
        HP_BAR(opponentRight, captureDamage: &damageRight);
        HP_BAR(playerLeft);
    } THEN {
        EXPECT_GT(playerLeft->hp, 100);
    }
}

SINGLE_BATTLE_TEST("Army of the Dead is a population bomb")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_UNHOLY);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); }
    } WHEN {
        TURN { MOVE(player, MOVE_ARMY_OF_THE_DEAD); }
    } SCENE {
        MESSAGE("The Pokémon was hit 10 times!");
    }
}

SINGLE_BATTLE_TEST("Summon Gargoyle hits three times")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_UNHOLY);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SHADOW_TAG); HP(1000); MaxHP(1000); }
    } WHEN {
        TURN { MOVE(player, MOVE_SUMMON_GARGOYLE); }
    } SCENE {
        MESSAGE("The Pokémon was hit 3 times!");
    }
}
