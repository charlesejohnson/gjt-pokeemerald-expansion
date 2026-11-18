# World of Pokémon (WoP): project docs

A Pokémon Emerald ROM hack (built on `rh-hideout/pokeemerald-expansion`) reskinned with World of Warcraft classes and bosses. This folder holds the project's design and tracking docs, moved here from Google Sheets so they are versioned with the code.

Docs here were consolidated on 2026-11-15 from sheets last edited in 2025. Anything not marked otherwise reflects the **May to Aug 2025 playtest build**, so check against the code before relying on it.

## Where things live (sources of truth)

| Topic | Source of truth | Notes |
|---|---|---|
| Move stats, PP, level learned, implemented status | [`data/stats-moves.csv`](data/stats-moves.csv) | Aug 2025 export. [`data/stats-moves-update.csv`](data/stats-moves-update.csv) is the "update file" from the same date. |
| Class stat lines for implemented classes (DK, Mage) | [`data/classes.csv`](data/classes.csv) | Aug 2025 export |
| Class designs including unimplemented drafts (Shaman, Druid, Monk) | [design/classes.md](design/classes.md) | From the older "final" sheet |
| Level caps and boss roster | [design/level-caps.md](design/level-caps.md) | |
| Boss teams (Rustboro, Dewford, Mauville, misc) | [design/bosses.md](design/bosses.md) | The in-game trainer data is authoritative for exact values |
| Feature list | [design/features.md](design/features.md) | |
| Magma/Aqua dialogue ideas | [design/enemy-teams.md](design/enemy-teams.md) | Early brainstorm |
| How bosses/gyms were built (reconstructed method, risks) | [design/boss-and-gym-method.md](design/boss-and-gym-method.md) | Inferred from git history; correct it if wrong |
| Which trainers are replaced, tested, unused | [tracking/trainer-mapping.md](tracking/trainer-mapping.md) | Snapshot, update as you test |
| DK move history | [tracking/death-knight-moves.md](tracking/death-knight-moves.md) | Superseded by `data/stats-moves.csv` |
| Playtest results, bugs, per-boss design intent | [playtest/feedback.md](playtest/feedback.md) | |
| How battle data, moves, abilities and tests fit together in the code | [battle-data-specifications.md](battle-data-specifications.md) | Includes the Runic Power case study and testing guide |
| What the code actually does | `src/`, `data/`, `test/` | Always wins over any doc |

**Rule going forward:** edit these files in git. Do not make new Google Sheet copies. If a number differs between a doc and the code, fix the doc.

## Status from the code (inferred from commit history, not verified by building)

- Death Knight line: playable through the third gym in the last playtest build. Death Strike, runic power generation and Scourge Strike are working.
- Mage line: Fire Mage moves implemented with unit tests (`test/battle/move_effect/fire_mage_moves.c`). Ice Block (25% heal, 50% in hail) and Polymorph (sleep plus a free substitute on the target) are fixed and tested (`test/battle/move_effect/ice_block_polymorph.c`).
- Mana Barrier is implemented for the Arcane Mage (PP-based recoil, tested in `test/battle/ability/mana_barrier.c`). Base Mage has Frost Armor. Hot Streak and Frost Armor are fixed and tested (`test/battle/ability/hot_streak.c`, `frost_armor.c`).
- Shaman, Druid, Monk: design drafts only.
- Boss teams documented through Mauville. Level caps are planned through the Champion.

## Original Google Sheets (kept as the historical source)

Shared by `archile21@gmail.com`; IDs are Drive file IDs (`https://docs.google.com/spreadsheets/d/<ID>`).

| Sheet | Last edited | ID |
|---|---|---|
| WoP Playtest, Documentation & Feedback | May 2025 | `1v7wc3Sw-B9nh640rg2ALT-w_jtACQk3ECzsrnOAmqOg` |
| World of Pokemon Stats/Moves final final.docx FINAL.pptx | May 2025 | `1SqCBUwOL8LKy__9BJIafk77GCXBW-1cLF3-KYuktTR0` |
| World of Pokemon Stats_Moves (newest of 6 copies) | Aug 2025 | `1_xIYhYO90fqjeLuakzWJjwyx9xWKIKgi-RCaXxatUHw` |
| WoP Playtest, Documentation & Feedback - Classes | Aug 2025 | `1SORk18gYH5jBO39ojsS56s4C76r4sQyU5s983Na50Wk` |

Older duplicate copies of "World of Pokemon Stats_Moves" (all Aug 2025): `1zlc7XKDiIM8bKJG8NJiDM2f1uTyq0G_pZEaVfphEVvA`, `1Dk71zPzJgPTJknImIb7dpc7sBY83kPMEQCJ0OFZ8uOo`, `1nM77SRaGlG8qifFzL5Gqs-fwiGtZI25Q2o1U8h8zzzU`, `1WWvRU6RxpowKLjxO6PeYzHVa7XcmE-FjAiBb5NGzlS4`, `1Ud5AXLw8g0u8jYFHpyqwUSlHac3TIOVq0_U3GINbfSc`.

## Not captured here

- The encounter-table images emailed to playtesters. They are not in the sheets or this repo.
- The Ed, Sam and Flynn feedback tabs, which are empty templates.
- The "Custom Bosses", "Rustboro Gym", "Dewford Gym", "Mauville Gym" and "Misc Bosses" tabs of the older "final" sheet. They duplicate the playtest sheet (the playtest sheet is the newer, more complete copy).
- The "pokemon plan" and "Pokémon Locations" sheets in Drive, which were not read and may be unrelated to this project.

## Open items spotted while consolidating

- "signs changed?" and "Magni changed?" checklist items are unchecked for Rustboro, and "Magni changed?" for Dewford and Mauville.
- Boss teams from Lavaridge onward are not documented anywhere I found.
- Mana Barrier / Frost Armor decision is implemented in code and `data/classes.csv`.
- Druid has four specs in the design draft; the class rule is three specs per base class.

## Upstream sync (rh-hideout/pokeemerald-expansion v1.17.3)

The fork was merged with upstream master on branch `upstream-sync`. Notes for future work:

- Custom move IDs (848-873) now sit after `MOVES_COUNT_GEN9`; `MOVES_COUNT` was changed to include them so Z-/Max-move IDs don't collide.
- `MULTI_CLASS_SELECT` is now part of the `MULTI_*` enum in `include/constants/script_menu.h`.
- Custom species have no data in `all_learnables.json` upstream; `DEATHKNIGHT` and `MAGE` entries were added by hand (teachables are generated from it).
- Battle effects now live in C: Runic Power / Crit Up 1 are set-effect handlers in `src/battle_set_effect.c`; Mana Barrier recoil is in `MoveEndMoveBlockRecoil`; spender moves (Death Strike, Frost Strike, Runic Consume) fail without Runic Power and consume it in the move-end stockpile block (`src/battle_move_resolution.c`).
- Ice Block counts as a protect move (`include/move.h`); Polymorph uses `argument.nonVolatileStatus = MOVE_EFFECT_SLEEP`.
- Known failing upstream tests, caused by fork config (Gen 3 exp / Stockpile settings) or custom content (move-name widths, missing animations): exp.c, stockpile.c, sheer_force, embargo, text.c, all_anims, AI splash.

## Known test failures (as of 2026-11-15, full `make check`)
Remaining failures are expected for this fork and not regressions:
- `exp.c`, `stockpile.c`, `sheer_force.c`, `embargo.c`, `competitive/defiant/guard_swap` assumptions: fork config (exp formula, stat-boost settings) differs from upstream defaults.
- `gimmick_z_move.c` (AI Z-Detect): AI/config difference, not touched by WoW work.
- `all_anims.c`: custom WoW moves have no unique animations yet (placeholder anims).
- `text.c` "?? was turned into a harmless creature": fixed by shortening the Polymorph message; Army of the Dead renamed "Army of Dead" for Contest-screen width.
- AI Splash test: custom effects (Anti-Magic Shell, Ice Block, Polymorph) are listed as "AI HANDLING" TODOs.

## Testing tools
- **Test NPC** (`data/scripts/gjt_test_warp.inc`): a man in the player's Littleroot bedroom (both Brendan's and May's 2F) at (7,4). Talk to him for a menu:
  - **Rustboro / Dewford / Mauville Gym**: warps to that gym's entrance.
  - **Supplies**: 10 Master Balls, 99 Rare Candies, 5 each of Fire/Water/Leaf Stone and the six vitamins, and TM39 Rock Tomb, TM08 Bulk Up, TM34 Shock Wave. Repeatable. (Rare Candy is not infinite; just 99 per visit.)
  - **Class Pokémon**: a level 5 Death Knight and a level 5 Mage. Add new class base forms in `GJT_TestWarp_EventScript_WowMons` as they are implemented.
  - **Badges**: a menu to flip badges 1 to 8 on or off one at a time (it stays open so you can flip several), plus Give All 8 and Clear All. The level cap is the value for the first badge you do **not** have, in order (`src/caps.c`): 0 badges = 15, badges 1 = 19, 1-2 = 24, 1-3 = 29, 1-4 = 31, 1-5 = 33, 1-6 = 42, 1-7 = 46, all 8 = 60 (until the Champion flag is set, after which there is no cap). Having badge 3 but not badge 2 still caps you at the badge-2 value.
  - It does not set "defeated gym" flags, so the gym guides' one-time loot is not triggered by this menu.
  - **Remove the two `GJT_TestWarp_EventScript_Guide` objects from `LittlerootTown_BrendansHouse_2F` and `LittlerootTown_MaysHouse_2F` map.json before release.** For each new gym add a menu entry and a warp line.


## Build version
Current dev build version lives in `data/text/gjt_version.inc` and is shown at the start of a new game (Khadgar intro) and by the bedroom test NPC. History: `wow-docs/CHANGELOG.md`. ROMs are sent as `GJT-WoW-vX.Y.Z.gba`.

## Roadmap (set 2026-11-16)
1. Finish the gyms in order: Rustboro through Mossdeep done as drafts (Fortree boss is Thunderaan, not Al'Akir); Sootopolis (Jaina) in progress: teams and map done, texts underway.
2. Team Aqua/Magma special encounters: guildies and people met in WoW as set-piece fights.
3. Pattern doc for building new route encounter tables.
4. **To-do: mid-fight lines.** Add trainer-slide lines (see the note at the end of `design/bosses.md`) for our harder or more interesting fights: ace sent out, first crit, super-effective hit, low HP, Mega Evolution. Done so far: Mekkatorque. Candidates: Nathanos (Hunter's Mark), Sylvanas and Alleria, Thunderaan, Ragnaros, Scott, Daelin, Jaina.
5. **Class implementation (set 2026-11-16):** Warrior first (rage counter, moves, abilities, species), then Shaman. Direction after that is open. Druid and Monk follow in the same pattern.
6. Still on the docket: rematch teams/text, Thunderfury effect, sprite pass (new Xal'atath sprite, DK/Mage icon palettes), Elite Four / Champion void arc. Also: Druid trainer NPC (scroll-menu move loadouts), Druid art choice.
Working method: one boss at a time, back and forth with Charlie, draft in the game, then notes in `design/bosses.md` and `CHANGELOG.md`.
