#ifndef GUARD_GJT_ELITE_FOUR_H
#define GUARD_GJT_ELITE_FOUR_H

enum GjtEliteHazard
{
    GJT_HAZARD_NONE,
    GJT_HAZARD_NZOTH,   // Sidney: Rumors of the Deep
    GJT_HAZARD_YSHAARJ, // Phoebe: The Sha
};

enum GjtEliteHazard GjtGetEliteHazard(void);
bool32 GjtTryRumorsOfTheDeep(enum BattlerId battler);
const u8 *GjtTryShaTrigger(enum BattlerId battler, enum Move move, bool32 unableToUse);

#endif // GUARD_GJT_ELITE_FOUR_H
