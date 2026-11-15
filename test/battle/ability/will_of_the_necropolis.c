#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(gSpeciesInfo[SPECIES_DEATHKNIGHT_BLOOD].abilities[0] == ABILITY_WILL_OF_THE_NECROPOLIS);
    ASSUME(gSpeciesInfo[SPECIES_DEATHKNIGHT_BLOOD].abilities[2] == ABILITY_DARK_AURA);
    ASSUME(gSpeciesInfo[SPECIES_DEATHKNIGHT_FROST].abilities[0] == ABILITY_SNOW_WARNING);
    ASSUME(gSpeciesInfo[SPECIES_DEATHKNIGHT_FROST].abilities[2] == ABILITY_SNIPER);
    ASSUME(gSpeciesInfo[SPECIES_DEATHKNIGHT_UNHOLY].abilities[0] == ABILITY_POISON_TOUCH);
    ASSUME(gSpeciesInfo[SPECIES_DEATHKNIGHT_UNHOLY].abilities[2] == ABILITY_PARENTAL_BOND);
}

SINGLE_BATTLE_TEST("Will of the Necropolis reduces damage taken below half HP by a third", s16 damage)
{
    u32 hp;
    PARAMETRIZE { hp = 400; }
    PARAMETRIZE { hp = 150; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_DEATHKNIGHT_BLOOD) { Ability(ABILITY_WILL_OF_THE_NECROPOLIS); MaxHP(400); HP(hp); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_BITE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, Q_4_12(1.5), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Will of the Necropolis does not reduce damage at exactly half HP", s16 damage)
{
    u32 hp;
    PARAMETRIZE { hp = 400; }
    PARAMETRIZE { hp = 200; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_DEATHKNIGHT_BLOOD) { Ability(ABILITY_WILL_OF_THE_NECROPOLIS); MaxHP(400); HP(hp); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_BITE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Snow Warning on Frost DK summons snow")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_FROST) { Ability(ABILITY_SNOW_WARNING); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_SNOW_WARNING);
    }
}

SINGLE_BATTLE_TEST("Dark Aura on Blood DK boosts Dark moves", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_WILL_OF_THE_NECROPOLIS; }
    PARAMETRIZE { ability = ABILITY_DARK_AURA; }
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_BLOOD) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BITE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Parental Bond on Unholy DK hits twice")
{
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_UNHOLY) { Ability(ABILITY_PARENTAL_BOND); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        HP_BAR(opponent);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Poison Touch on Unholy DK may poison on contact")
{
    PASSES_RANDOMLY(3, 10, RNG_POISON_TOUCH);
    GIVEN {
        PLAYER(SPECIES_DEATHKNIGHT_UNHOLY) { Ability(ABILITY_POISON_TOUCH); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_POISON_TOUCH);
        STATUS_ICON(opponent, poison: TRUE);
    }
}
