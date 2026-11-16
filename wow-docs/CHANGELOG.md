# GJT build changelog

The build version is shown at the very start of a new game (Khadgar's intro) and when you talk to the test NPC in the player's bedroom. Source: `data/text/gjt_version.inc`. ROM files are sent as `GJT-WoW-vX.Y.Z.gba` so a phone cannot reuse an older download with the same name. Bump the patch number for every ROM sent.

## v0.1.3 (2026-11-16)
- Ragnaros team: Magmar, Heatmor, Camerupt, Typhlosion (ace). Victory cutscene: defeat narration, forced warp to the Lavaridge Pokemon Center, Nurse Joy takes Flannery, Magni gives badge and TM. Lavaridge gym guide rewritten in Magni's voice.

## v0.1.2 (2026-11-16)
- Lavaridge lieutenants redesigned with Charlie: Beth'tilac (web control, DPS-check Larvesta), Alysrazor (Fly phases, Talonflame ace), Staghelm (Cat and Moonkin forms, Scovillain), Ryolith feet (mirrored Rock/Fire, Carkol aces). Ryolith's feet now face each other on B1F row 17 and should trigger one two-trainer double battle (untested). Ragnaros still draft.

## v0.1.1 (2026-11-16)
- Lavaridge gym first draft (Firelands): Ragnaros (leader, cap 29), Staghelm, Alysrazor, Beth'tilac, Ryolith's left and right feet. Cole, Gerald and Jeff removed; vanilla hot-sand puzzle kept. All teams and text are DRAFT.
- Test NPC: Lavaridge Gym warp.

## v0.1.0 (2026-11-16)
First numbered build.
- Synced to upstream pokeemerald-expansion v1.17.3.
- Death Knight (Blood/Frost/Unholy) and Mage (Frost/Fire/Arcane) classes, moves, abilities, recolored sprites.
- Gym text pass (Rustboro, Dewford, Mauville), Mauville post-win fix, unterminated-string fixes, one-time guide loot.
- Test NPC in the player's bedroom: gym warps, supplies, class Pokémon, per-badge toggles.
