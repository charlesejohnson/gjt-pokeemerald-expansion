#include "global.h"
#include "test/battle.h"

// GJT: Conclave Castforms carry only a weather move and Weather Ball.
// Once the weather is set, the AI should always pick Weather Ball.
AI_SINGLE_BATTLE_TEST("GJT: Castform uses Weather Ball once its weather is set")
{
    u64 aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT | AI_FLAG_SMART_MON_CHOICES;
    GIVEN {
        AI_FLAGS(aiFlags);
        PLAYER(SPECIES_WOBBUFFET) { HP(500); MaxHP(500); }
        OPPONENT(SPECIES_CASTFORM) { Moves(MOVE_RAIN_DANCE, MOVE_WEATHER_BALL); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_RAIN_DANCE); }
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_WEATHER_BALL); }
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_WEATHER_BALL); }
    }
}
