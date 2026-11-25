# Reserved flags and vars

Free slots confirmed in `include/constants/flags.h` and `vars.h` (v0.1.69). Do not use these for anything else.

- **Flags 0x2F to 0x4F** (33 contiguous `FLAG_UNUSED_*`): reserved for the Elite Four and Champion Void arc (hazard states, per-room scene flags, Dimensius intro), then post-game.
- **Flags 0x54, 0x55, 0x68, 0xE9, 0x1AA, 0x1AB**: spare singles, free for small features.
- **Vars 0x4083 to 0x40F7 unused entries** (see `VAR_UNUSED_*`): first three (0x4083, 0x408B, 0x4091) reserved for the Void arc and friend fights; the rest free.
- Already used by GJT: Mega Stone rematch flags 0x27 to 0x2E.
- Total unused flags in the file: 366 (most are R/S, FRLG or unreachable ranges and should be audited before use).
