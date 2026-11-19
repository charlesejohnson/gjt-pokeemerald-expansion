#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Druid: Bear Form raises Def and Sp. Def, Cat Form swaps the boosts")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_BEAR_FORM); }
        TURN { MOVE(player, MOVE_CAT_FORM); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Druid: Unshift protects and removes the form boosts")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_BEAR_FORM); }
        TURN { MOVE(player, MOVE_UNSHIFT); MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("Druid returned to\nits base form!");
        MESSAGE("Druid protected itself!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Druid: Tree Form is for Resto only")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TREE_FORM); }
    } SCENE {
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Druid: Tree Form boosts Sp. Def and makes heals 25% stronger")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_RESTORATION) { Speed(100); HP(10); MaxHP(100); Ability(ABILITY_BALL_FETCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TREE_FORM); }
        TURN { MOVE(player, MOVE_HEALING_WAVE, target: player); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(player->hp, 10 + 50);
    }
}

SINGLE_BATTLE_TEST("Druid: Efflorescence blooms on switch-in and heals for 3 turns")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_RESTORATION) { Speed(100); HP(50); MaxHP(160); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(player->hp, 50 + 3 * 10);
    }
}

SINGLE_BATTLE_TEST("Druid: Survival Instincts heals 60% once when HP first falls to 30%")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_GUARDIAN) { Speed(1); HP(95); MaxHP(300); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TACKLE, criticalHit: FALSE); }
    } SCENE {
        MESSAGE("Guard Druid's survival instincts\nkicked in!");
    } THEN {
        EXPECT_GT(player->hp, 150);
    }
}

SINGLE_BATTLE_TEST("Druid: Predatory Swiftness gives priority after a crit")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_FERAL) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: TRUE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_TACKLE, criticalHit: FALSE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet used Celebrate!");
        MESSAGE("Feral Druid used Tackle!");
        MESSAGE("Feral Druid used Tackle!");
        MESSAGE("The opposing Wobbuffet used Celebrate!");
    }
}

SINGLE_BATTLE_TEST("Druid: Eclipse boosts Grass moves on alternate turns", s16 damage)
{
    u32 idle;
    PARAMETRIZE { idle = 0; }
    PARAMETRIZE { idle = 1; }
    GIVEN {
        PLAYER(SPECIES_DRUID_BOOMY) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        if (idle)
            TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_VINE_WHIP, criticalHit: FALSE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.3), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Druid: Shred crits on the first turn after shifting and builds combo points")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_FERAL) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_CAT_FORM); }
        TURN { MOVE(player, MOVE_SHRED); }
    } SCENE {
        MESSAGE("A critical hit!");
        MESSAGE("Feral Druid's combo points: 2/5");
    } THEN {
        EXPECT_EQ((u32)player->volatiles.comboPoints, 2);
    }
}

SINGLE_BATTLE_TEST("Druid: Shred fails outside Cat Form")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_FERAL) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_SHRED); }
    } SCENE {
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Druid: Rake poisons and Ferocious Bite spends all combo points")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_FERAL) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_CAT_FORM); }
        TURN { MOVE(player, MOVE_RAKE); }
        TURN { MOVE(player, MOVE_RAKE); }
        TURN { MOVE(player, MOVE_FEROCIOUS_BITE); }
    } THEN {
        EXPECT(opponent->status1 & STATUS1_POISON);
        EXPECT_EQ((u32)player->volatiles.comboPoints, 0);
    }
}

SINGLE_BATTLE_TEST("Druid: Ferocious Bite hits harder per combo point", s16 damage)
{
    u32 builds;
    PARAMETRIZE { builds = 0; }
    PARAMETRIZE { builds = 2; }
    GIVEN {
        PLAYER(SPECIES_DRUID_FERAL) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_CAT_FORM); }
        if (builds >= 1)
            TURN { MOVE(player, MOVE_RAKE); }
        if (builds >= 2)
            TURN { MOVE(player, MOVE_RAKE); }
        TURN { MOVE(player, MOVE_FEROCIOUS_BITE, criticalHit: FALSE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        MESSAGE("Feral Druid used Ferocious Bite!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(3.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Druid: Bear Form builds rage and Maul spends 3")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_GUARDIAN) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_BEAR_FORM); }
        TURN { MOVE(player, MOVE_MANGLE); }
        TURN { MOVE(player, MOVE_MAUL); }
    } THEN {
        EXPECT_EQ((u32)player->volatiles.warriorRage, 1); // Mangle +3, Maul +1 then -3
    }
}

SINGLE_BATTLE_TEST("Druid: Frenzied Regeneration heals 60% and costs 5 rage")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_GUARDIAN) { Speed(100); HP(10); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_BEAR_FORM); }
        TURN { MOVE(player, MOVE_MANGLE); }
        TURN { MOVE(player, MOVE_MANGLE); }
        TURN { MOVE(player, MOVE_FRENZIED_REGEN); }
    } THEN {
        EXPECT_EQ((u32)player->volatiles.warriorRage, 1); // 3 + 3 - 5
        EXPECT_GE(player->hp, 70);
    }
}

SINGLE_BATTLE_TEST("Druid: Moonfire always burns")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_MOONFIRE); }
    } THEN {
        EXPECT(opponent->status1 & STATUS1_BURN);
    }
}

SINGLE_BATTLE_TEST("Druid: Celestial Alignment is Boomy only, boosts for 2 turns, then fades")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_BOOMY) { Speed(100); Ability(ABILITY_BALL_FETCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); HP(10000); MaxHP(10000); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELESTIAL_ALIGNMENT); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Boomy Druid aligned\nwith the stars!");
        MESSAGE("Boomy Druid's alignment faded!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ((u32)player->volatiles.bonusCritStages, 0);
    }
}

SINGLE_BATTLE_TEST("Druid: Celestial Alignment fails for other specs")
{
    GIVEN {
        PLAYER(SPECIES_DRUID_FERAL) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELESTIAL_ALIGNMENT); }
    } SCENE {
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Druid: Rejuvenation heals over time and Swiftmend consumes it")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); HP(10); MaxHP(160); Ability(ABILITY_BALL_FETCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_REJUVENATION, target: player); }
        TURN { MOVE(player, MOVE_SWIFTMEND, target: player); }
    } THEN {
        EXPECT_EQ(player->hp, 10 + 20 + 80);
        EXPECT_EQ((u32)player->volatiles.rejuvTimer, 0);
    }
}

SINGLE_BATTLE_TEST("Druid: Swiftmend fails without Rejuvenation")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); HP(10); MaxHP(160); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SWIFTMEND, target: player); }
    } SCENE {
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Druid: Tranquility heals the whole team and raises Sp. Def")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); HP(10); MaxHP(100); Ability(ABILITY_BALL_FETCH); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(5); HP(20); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_TRANQUILITY); }
    } THEN {
        EXPECT_EQ(player->hp, 45);
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HP), 55);
        EXPECT_EQ(player->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
    }
}

DOUBLE_BATTLE_TEST("Druid: Wild Growth heals the user and its ally")
{
    GIVEN {
        PLAYER(SPECIES_DRUID) { Speed(100); HP(10); MaxHP(100); Ability(ABILITY_BALL_FETCH); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(50); HP(10); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_WILD_GROWTH); MOVE(playerRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(playerLeft->hp, 35);
        EXPECT_EQ(playerRight->hp, 35);
    }
}
