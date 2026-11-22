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
    case TRAINER_GLACIA:
        return GJT_HAZARD_YOGG;
    case TRAINER_DRAKE:
        return GJT_HAZARD_XALATATH;
    case TRAINER_WALLACE:
        return GJT_HAZARD_DIMENSIUS;
    default:
        return GJT_HAZARD_NONE;
    }
}

static enum BattlerId GetEliteFoe(void)
{
    enum BattlerId foe = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
    if (!IsBattlerAlive(foe))
        foe = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
    return foe;
}

// Dimensius: Magma Storm that never expires. Silent re-apply if something breaks it.
static bool32 ApplyBlackHole(enum BattlerId battler)
{
    if (gBattleMons[battler].volatiles.wrapped)
        return FALSE;
    gBattleMons[battler].volatiles.wrapTurns = 7;
    gBattleMons[battler].volatiles.wrappedBindingBand = FALSE;
    gBattleMons[battler].volatiles.wrapped = TRUE;
    gBattleMons[battler].volatiles.wrappedMove = MOVE_MAGMA_STORM;
    gBattleMons[battler].volatiles.wrappedBy = GetEliteFoe();
    return TRUE;
}

void GjtBlackHoleKeep(enum BattlerId battler)
{
    if (GjtGetEliteHazard() != GJT_HAZARD_DIMENSIUS
     || GetBattlerSide(battler) != B_SIDE_PLAYER
     || !IsBattlerPresent(battler))
        return;
    if (!ApplyBlackHole(battler) && gBattleMons[battler].volatiles.wrappedMove == MOVE_MAGMA_STORM)
        gBattleMons[battler].volatiles.wrapTurns = 7;
}

// Xal'atath: boosts to the player's Pokemon are copied onto her active Pokemon.
void GjtMasterPlanMirror(enum BattlerId battler, enum Stat stat, s32 stage)
{
    enum BattlerId foe;

    if (stage <= 0
     || GjtGetEliteHazard() != GJT_HAZARD_XALATATH
     || GetBattlerSide(battler) != B_SIDE_PLAYER)
        return;
    foe = GetEliteFoe();
    if (!IsBattlerAlive(foe))
        return;
    gBattleMons[foe].statStages[stat] += stage;
    if (gBattleMons[foe].statStages[stat] > MAX_STAT_STAGE)
        gBattleMons[foe].statStages[stat] = MAX_STAT_STAGE;
    gBattleStruct->gjtMasterPlanFoe = foe + 1;
}

// Yogg-Saron: at end of turn, an echo of the move you used strikes back.
bool32 GjtTryEchoEndTurn(enum BattlerId battler)
{
    u32 echo = gBattleStruct->gjtEchoDamage[battler];

    if (echo == 0)
        return FALSE;
    gBattleStruct->gjtEchoDamage[battler] = 0;
    if (!IsBattlerPresent(battler) || !IsBattlerAlive(battler))
        return FALSE;

    gBattlerAttacker = battler;
    gBattleScripting.battler = battler;
    if ((echo & 0x8000) && !RandomPercentage(RNG_NONE, 50))
    {
        BattleScriptCall(BattleScript_GjtEchoFizzle);
        return TRUE;
    }
    SetPassiveDamageAmount(battler, echo & 0x7FFF);
    BattleScriptCall(BattleScript_GjtEcho);
    return TRUE;
}

// Elite Four switch-in hazards (N'Zoth rumors, Dimensius black hole).
bool32 GjtTryEliteSwitchIn(enum BattlerId battler)
{
    enum BattlerId foe;
    u32 n;

    if (GetBattlerSide(battler) != B_SIDE_PLAYER)
        return FALSE;
    if (GjtGetEliteHazard() == GJT_HAZARD_DIMENSIUS)
    {
        if (!ApplyBlackHole(battler))
            return FALSE;
        gEffectBattler = battler;
        BattleScriptCall(BattleScript_GjtBlackHole);
        return TRUE;
    }
    if (GjtGetEliteHazard() != GJT_HAZARD_NZOTH)
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
const u8 *GjtTryEliteMoveEnd(enum BattlerId battler, enum BattlerId defender, enum Move move, bool32 unableToUse)
{
    enum GjtEliteHazard hazard = GjtGetEliteHazard();

    if (hazard == GJT_HAZARD_XALATATH && gBattleStruct->gjtMasterPlanFoe != 0)
    {
        gEffectBattler = gBattleStruct->gjtMasterPlanFoe - 1;
        gBattleStruct->gjtMasterPlanFoe = 0;
        return BattleScript_GjtMasterPlan;
    }

    if (hazard == GJT_HAZARD_YOGG
     && GetBattlerSide(battler) == B_SIDE_PLAYER
     && !unableToUse
     && move != MOVE_NONE)
    {
        if (IsBattleMoveStatus(move))
            gBattleStruct->gjtEchoDamage[battler] = 0x8000 | (GetNonDynamaxMaxHP(battler) / 8);
        else if (defender != battler && gBattleStruct->moveDamage[defender] >= 8)
            gBattleStruct->gjtEchoDamage[battler] = gBattleStruct->moveDamage[defender] / 8;
        else
            gBattleStruct->gjtEchoDamage[battler] = 0;
        return NULL;
    }

    if (hazard != GJT_HAZARD_YSHAARJ
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
