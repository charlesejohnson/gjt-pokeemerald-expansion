#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Shaman: Healing Wave heals the user for 40% of max HP")
{
    GIVEN {
        PLAYER(SPECIES_SHAMAN_RESTORATION) { Speed(100); HP(50); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_HEALING_WAVE, target: player); }
    } THEN {
        EXPECT_EQ(player->hp, 90);
    }
}

SINGLE_BATTLE_TEST("Shaman: Riptide heals now and over time")
{
    GIVEN {
        PLAYER(SPECIES_SHAMAN_RESTORATION) { Speed(100); HP(10); MaxHP(160); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_RIPTIDE, target: player); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        // 10 + 20 (now) + 10 (end of turn 1) + 10 (end of turn 2)
        EXPECT_EQ(player->hp, 50);
    }
}

SINGLE_BATTLE_TEST("Shaman: Searing Totem burns foes for 1/8 each turn and expires after 4 turns")
{
    GIVEN {
        PLAYER(SPECIES_SHAMAN) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(160); MaxHP(160); }
    } WHEN {
        TURN { MOVE(player, MOVE_SEARING_TOTEM); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(opponent->hp, 160 - 4 * 20);
    }
}

SINGLE_BATTLE_TEST("Shaman: Stoneskin Totem reduces physical damage by 25%", s16 damage)
{
    u32 move;
    PARAMETRIZE { move = MOVE_CELEBRATE; }
    PARAMETRIZE { move = MOVE_STONESKIN_TOTEM; }
    GIVEN {
        PLAYER(SPECIES_SHAMAN) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, move); MOVE(opponent, MOVE_TACKLE, criticalHit: FALSE); }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.75), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Shaman: Magma Totem does no damage on the cast turn, then hits twice")
{
    GIVEN {
        PLAYER(SPECIES_SHAMAN_ELEMENTAL) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_MAGMA_TOTEM); }
    } THEN {
        EXPECT_EQ(opponent->hp, 10000);
    }
}

SINGLE_BATTLE_TEST("Shaman: Earthbind Totem slows the foe")
{
    GIVEN {
        PLAYER(SPECIES_SHAMAN) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(120); }
    } WHEN {
        TURN { MOVE(player, MOVE_EARTHBIND_TOTEM); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_TACKLE); MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet used Celebrate!");
        MESSAGE("Shaman used Tackle!");
        MESSAGE("The opposing Wobbuffet used Tackle!");
    }
}

SINGLE_BATTLE_TEST("Shaman: Windfury Weapon can repeat a physical hit")
{
    PASSES_RANDOMLY(20, 100, RNG_WINDFURY);
    GIVEN {
        PLAYER(SPECIES_SHAMAN_ENHANCEMENT) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("The Pokémon was hit 6 times!"); // forced rolls chain to the cap
    }
}
