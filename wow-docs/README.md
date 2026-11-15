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
| Which trainers are replaced, tested, unused | [tracking/trainer-mapping.md](tracking/trainer-mapping.md) | Snapshot, update as you test |
| DK move history | [tracking/death-knight-moves.md](tracking/death-knight-moves.md) | Superseded by `data/stats-moves.csv` |
| Playtest results, bugs, per-boss design intent | [playtest/feedback.md](playtest/feedback.md) | |
| How battle data, moves, abilities and tests fit together in the code | [battle-data-specifications.md](battle-data-specifications.md) | Includes the Runic Power case study and testing guide |
| What the code actually does | `src/`, `data/`, `test/` | Always wins over any doc |

**Rule going forward:** edit these files in git. Do not make new Google Sheet copies. If a number differs between a doc and the code, fix the doc.

## Status from the code (inferred from commit history, not verified by building)

- Death Knight line: playable through the third gym in the last playtest build. Death Strike, runic power generation and Scourge Strike are working.
- Mage line: Fire Mage moves implemented with unit tests (`test/battle/move_effect/fire_mage_moves.c`). Per the last commits, all new mage moves work except Ice Block and Polymorph.
- Mana Barrier: builds, but does not work yet.
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
- Mana Barrier is on the base Mage species in code, but the decision is Arcane Mage only (base Mage gets Frost Armor). See [design/classes.md](design/classes.md). `data/classes.csv` (Aug 2025) still lists Mana Barrier on the base Mage and should be updated when the code is fixed.
- Druid has four specs in the design draft; the class rule is three specs per base class.
