#ifndef GUARD_GJT_DRUID_H
#define GUARD_GJT_DRUID_H

// struct DruidLoadout and its constants live in global.h (SaveBlock3 needs them)

u32 GetDruidMoveAffinity(enum Move move);     // which form auto-fills this move (1 Bear, 2 Cat, 3 Tree, 4 Owlkin, 0 none)
bool32 IsDruidExclusiveMove(enum Move move);  // never takes a normal move slot (Bear/Cat moves, Unshift)
void DruidResetLoadouts(void);
void DruidTestForceSlot(u32 form, u32 slot, enum Move move); // tests only: forces a slot on the player's Druid at shift time
void DruidRefillLoadoutPP(void);
bool32 DruidAssignSlot(struct Pokemon *mon, u32 form, u32 slot, enum Move move); // for the Druid trainer NPC and tests
void DruidApplyFormMoves(enum BattlerId battler, u32 form);
void DruidRestoreBaseMoves(enum BattlerId battler);
void DruidSaveFormPP(enum BattlerId battler, u32 movePosition);

#endif // GUARD_GJT_DRUID_H
