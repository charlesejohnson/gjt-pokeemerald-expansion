#include "global.h"
#include "gjt_elite_four.h"
#include "battle.h"
#include "battle_util.h"
#include "battle_scripts.h"
#include "battle_setup.h"
#include "move.h"
#include "random.h"
#include "constants/battle.h"
#include "constants/opponents.h"

// Elite Four environmental hazards. Each is keyed to the first opposing trainer id.

enum GjtEliteHazard GjtGetEliteHazard(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER) || (gBattleTypeFlags & BATTLE_TYPE_LINK))
        return GJT_HAZARD_NONE;

    switch (TRAINER_BATTLE_PARAM.opponentA)
    {
    case TRAINER_SIDNEY:
        return GJT_HAZARD_NZOTH;
    case TRAINER_PHOEBE:
        return GJT_HAZARD_YSHAARJ;
    default:
        return GJT_HAZARD_NONE;
    }
}

// N'Zoth: player switch-ins alternate confusion (first), then a whirlpool "used" by the foe.
bool32 GjtTryRumorsOfTheDeep(enum BattlerId battler)
{
    enum BattlerId foe;
    u32 n;

    if (GjtGetEliteHazard() != GJT_HAZARD_NZOTH || GetBattlerSide(battler) != B_SIDE_PLAYER)
        return FALSE;

    n = gBattleStruct->gjtRumorCounter++;
    foe = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
    if (!IsBattlerAlive(foe))
        foe = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
    gEffectBattler = battler;

    if ((n & 1) == 0)
    {
        if (!CanBeConfused(foe, battler))
            return FALSE;
        gBattleMons[battler].volatiles.confusionTimer = RandomUniform(RNG_CONFUSION_TURNS, 2, B_CONFUSION_TURNS);
        BattleScriptCall(BattleScript_GjtRumorConfuse);
        return TRUE;
    }

    if (gBattleMons[battler].volatiles.wrapped)
        return FALSE;
    SetWrapTurns(battler, HOLD_EFFECT_NONE);
    gBattleMons[battler].volatiles.wrapped = TRUE;
    gBattleMons[battler].volatiles.wrappedMove = MOVE_WHIRLPOOL;
    gBattleMons[battler].volatiles.wrappedBy = IsBattlerAlive(foe) ? foe : B_POSITION_OPPONENT_LEFT;
    BattleScriptCall(BattleScript_GjtRumorWhirlpool);
    return TRUE;
}

// Y'shaarj: after the player's Pokemon uses a move, the matching Sha strikes it.
const u8 *GjtTryShaTrigger(enum BattlerId battler, enum Move move, bool32 unableToUse)
{
    if (GjtGetEliteHazard() != GJT_HAZARD_YSHAARJ
     || GetBattlerSide(battler) != B_SIDE_PLAYER
     || unableToUse
     || !IsBattlerAlive(battler)
     || move == MOVE_NONE)
        return NULL;

    gBattlerAttacker = battler;
    if (IsBattleMoveStatus(move))
    {
        SetPassiveDamageAmount(battler, GetNonDynamaxMaxHP(battler) / 8);
        return BattleScript_GjtShaPride;
    }
    if (IsBattleMovePhysical(move))
    {
        if (gBattleMons[battler].volatiles.tauntTimer != 0)
            return NULL;
        gBattleMons[battler].volatiles.tauntTimer = B_TAUNT_TIMER - 1;
        return BattleScript_GjtShaAnger;
    }
    if (gBattleMons[battler].volatiles.shaCritPenalty < 7)
        gBattleMons[battler].volatiles.shaCritPenalty++;
    return BattleScript_GjtShaViolence;
}
