#ifndef GUARD_GJT_ELITE_FOUR_H
#define GUARD_GJT_ELITE_FOUR_H

enum GjtEliteHazard
{
    GJT_HAZARD_NONE,
    GJT_HAZARD_NZOTH,    // Sidney: Rumors of the Deep
    GJT_HAZARD_YSHAARJ,  // Phoebe: The Sha
    GJT_HAZARD_YOGG,     // Glacia: Memories of Betrayal
    GJT_HAZARD_XALATATH, // Drake: Her Master Plan
    GJT_HAZARD_DIMENSIUS,// Wallace: Black Hole
};

enum GjtEliteHazard GjtGetEliteHazard(void);
bool32 GjtTryEliteSwitchIn(enum BattlerId battler);
const u8 *GjtTryEliteMoveEnd(enum BattlerId battler, enum BattlerId defender, enum Move move, bool32 unableToUse);
bool32 GjtTryEchoEndTurn(enum BattlerId battler);
void GjtMasterPlanMirror(enum BattlerId battler, enum Stat stat, s32 stage);
void GjtBlackHoleKeep(enum BattlerId battler);

#endif // GUARD_GJT_ELITE_FOUR_H
