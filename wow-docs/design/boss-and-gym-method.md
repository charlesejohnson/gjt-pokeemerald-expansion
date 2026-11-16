# How bosses and gyms were built (reconstructed method)

Written 2026-11-16 by reading the git history (Apr 29 to May 6 2025 commits `273d96191`, `0cac83f39`, `84bf69ae4`, `c84dc2292`, `ae1131949`, `2d10e069a`), `src/data/trainers.party`, the gym `map.json`/`scripts.inc` files and the Porymap layouts. Nothing here came from a design doc: it is inferred from what the data shows. **Confirmed** = visible in the repo. **Inferred** = my reading of intent, please correct.

## 1. The core idea: recycle a vanilla trainer, overwrite everything about it

**Confirmed.** A WoW boss is not a new trainer. It is a vanilla Emerald trainer whose constant, map object and script are kept, and whose *contents* are replaced:

| Layer | File | What changes | What stays |
|---|---|---|---|
| Identity and team | `src/data/trainers.party` | `Name`, `Class`, `Pic`, `Music`, `Double Battle`, `AI`, whole party | The `=== TRAINER_X ===` constant (e.g. `TRAINER_TOMMY` is now VEK'NILASH) |
| Map presence | `data/maps/<Map>/map.json` | Overworld sprite (`graphics_id`), `x`/`y`, facing, sight range, sometimes which script an object points at | Event script label (`RustboroCity_Gym_EventScript_Tommy`) |
| Dialogue | `data/maps/<Map>/scripts.inc` | The `.string` intro / defeat / post-battle text | The `trainerbattle_single` line and flag logic |
| Rewards | same scripts | Leader TM/badge text (e.g. Rock Tomb explanation) | Flags, badge, TM item |

`src/data/trainers.h` is **generated** from `trainers.party` by `tools/trainerproc` and is gitignored now. Several 2025 commits show 12k to 25k line diffs in it only because it was committed then. Edit `.party`, never `.h`.

Because only `.party` data changes, nothing in C or the scripts' flow control had to be touched. That is why a whole gym could be rebuilt in a day or two.

### Why the constants stay (inferred)
Trainer constants are wired into flags, the rematch system, the trainer-eye / "battled" bookkeeping, the Trainer Hill/Frontier lists and the opponent constant table (856 `TRAINER_` constants). Renaming `TRAINER_TOMMY` would mean touching all of that. Overwriting in place is free.

## 2. Team-building conventions (`trainers.party`)

**Confirmed patterns** (Rustboro, Dewford, Mauville, Petalburg Woods, museum):

- **AI flags** identify the tier:
  - Regular boss (Velithe, Ossirian, Huhuran, Twin Emperors): `Basic Trainer / Omniscient / Smart Mon Choices`
  - Gym leader (C'Thun, Garrosh): same plus `Ace Pokemon`
  - Early grunt-level (Alms, Jin'Rokh, Lei Shen): `Basic Trainer` only
  So "how smart is this boss" is a per-trainer dial, not per-gym.
- **Party size** 2 to 4. Leaders 4, side bosses 3, Twin Emperors 2 each (they are a pair).
- **The ace is last** and sits at the level cap (C'Thun's Minior is Lv 15 = Rustboro cap; see [level-caps.md](level-caps.md)). Other members are 1 to 3 levels below.
- **Each mon carries a "gimmick"** instead of a generic moveset: item + ability + nature chosen to express the character (Eviolite Pupitar, Rocky Helmet Ferroseed, Flame Orb Makuhita with Guts, Iron Ball Chansey).
- **IVs are used as a difficulty/level dial**, set per mon in the 12 to 31 range (12 early, 24 mid, 31 for the ace or the stat that matters). Some mons zero out unused stats (C'Thun's Minior has 0 SpA and 0 Spe) and Garrosh's Makuhita has 31 only in HP/Def/SpD. *(Inferred: IVs scale with the cap.)*
- **Music** is picked for the *character*, not the vanilla class (Huhuran, a Battle Girl sprite, uses `Hiker` music; Jin'Rokh uses `Intense`).
- **Sprite choice** reuses an existing trainer pic with the right silhouette (Hiker for Ossirian, Aqua Grunt for the Slateport/Petalburg Aqua members, Leader Roxanne for C'Thun). Boss identity is carried by name + dialogue, since there are no new trainer sprites.
- **Doubles** are used for set-piece bosses (Lei Shen: `Double Battle: Yes`, 4 mons).

## 3. Dialogue conventions

**Confirmed.** Each fight has three strings: intro (before), defeat (after losing), post-battle (talking afterwards). Text keeps the vanilla `\n`/`\l`/`\p` formatting.

**Narrative frame (inferred from C'Thun's lines):** original gym leaders are *kept as the NPC* but the boss is an outside entity acting on them. Roxanne's intro is a possessed "You... Are... Already... Dead...", and her defeat line becomes her waking up ("I felt a sinister presence in my mind"). The vanilla TM and badge scene is preserved, trimmed to fit the new tone. Expect the same device for later leaders.

**Known debt:** Allen's (Ossirian) intro/defeat/post-battle still point at `Route102_Text_Allen*` labels in the Route 102 script. The text works, but it lives in the wrong map and would break if Route 102 is edited.

## 4. Map-level changes (object events)

**Confirmed from `map.json` diffs.**

- Trainers were **moved to new coordinates** and given **new `graphics_id`s** to suit the boss (Rustboro: Allen became `OBJ_EVENT_GFX_HIKER` at 5,13; Marc became `GIRL_3` at 3,9; Tommy and Josh were re-seated).
- **Sight range** (`trainer_sight_or_berry_tree_id`) is edited per trainer to set how early the fight triggers.
- **Excess trainers were removed** to make space or cut count: trainers removed from Route 102 and Route 104 (commit `273d96191`), and Route 116 has fewer objects than vanilla. Petalburg Woods and Rusturf Tunnel were also edited (Velithe and Polerodeo replace grunts there).
- Removed/unused scripts are tracked in the "Unused trainer scripts" table in [trainer-mapping.md](../tracking/trainer-mapping.md). Treat those as a **spare-parts bin** for future bosses.
- A non-boss trainer can be **demoted to a talker**: Mauville's Ben (`TRAINER_BEN`) still has a script but is documented as "changed from trainer to text".

## 5. Gym layout editing (Porymap)

**Confirmed from `data/layouts/*/map.bin`** (compared old vs current metatiles):

| Gym | Size | Tiles changed | Reading |
|---|---|---|---|
| Rustboro | 11x20 | 124 of 220 | Outer shell identical; interior walls redrawn |
| Mauville | 10x21 | 117 of 210 | Outer shell identical; interior walls redrawn |
| Dewford | 18x28 | 432 of 504 | Nearly a new layout |
| Dewford Town, Verdanturf, Oldale, Slateport | | 4 to 14 | Touch-ups (doors/signs) |

Rules the edits follow:
- **Dimensions, tilesets and warps are not changed** (`layouts.json` untouched). Only the metatile grid is repainted, with the existing gym tileset. That keeps warp/exit coordinates and the entrance mat valid.
- The goal is **flow**: a new path past each trainer so sight lines hit the player in an intended order, ending at the leader.

**Mauville puzzle check (static analysis, 2026-11-16; not played in an emulator).** My first guess, that the puzzle scripts' beam coordinates no longer match the layout, turned out to be the wrong question: the redesigned interior has **no switch tiles and no switch objects at all**, so the vanilla switch puzzle is gone. Findings:

- **The gym is completable.** A flood fill over the new collision data reaches Wattson from the entrance even if every beam tile is treated as a wall. Beams are decoration plus partial walls (36 of 47 beam tiles are impassable).
- **The leftover puzzle code is mostly harmless.** The map-load script finds `VAR_MAUVILLE_GYM_STATE` = 0 and no barrier flag and does nothing. The post-victory special `MauvilleGymDeactivatePuzzle` scans for beam tiles (not fixed coordinates), so it correctly turns the beams "off" after Wattson.
- **Cosmetic bug (confirmed in code, not seen in-game):** the same special also paints 4 "pressed switch" tiles at the vanilla switch coordinates (0,15), (4,12), (3,9), (8,9) (`sMauvilleGymSwitchCoords` in `src/field_specials.c`). In the new layout those spots are a wall, floor, floor and a beam tile. After beating Wattson, stray switch graphics appear there, and the wall cell at (0,15) becomes walkable (collision is copied from the new tile).
- **Stale text:** the Gym Guide ("switch-controlled doors all over his GYM") and Ben's post-battle line ("little traps with switches") still describe the old puzzle.

Suggested fix, if wanted: skip the switch-painting loop in `MauvilleGymDeactivatePuzzle` and rewrite those two text lines.

## 6. Boss design recipe (what the sheets imply)

1. Pick the WoW boss and write one line of **inspiration** (see the per-boss table in [../playtest/feedback.md](../playtest/feedback.md)): theme, signature mechanic ("one has insane Def, one insane Sp. Def; they swap").
2. Translate the mechanic into **team rules** a battle can actually express: type theme, ability/item/move combos, doubles or not, and a favourite/ace.
3. Choose **cap level** and ace from [level-caps.md](level-caps.md); scale IVs and filler levels below it.
4. Choose **AI tier** (section 2) and music.
5. Write **three strings** (section 3).
6. Reseat the **object** and, if needed, repaint the **gym layout** (sections 4 to 5).
7. **Playtest** and log in [trainer-mapping.md](../tracking/trainer-mapping.md) ("Team tested", "Text tested", "AI edited").

## 7. What is *not* captured anywhere

- Why any specific IV or level was chosen (no balance rationale, only the numbers).
- The map plans: no sketches, no sight-line order, no puzzle notes for Rustboro/Dewford/Mauville.
- Boss moves that depend on custom moves or abilities (e.g. "purified salt", Shields Down Minior) have no check that they exist/are legal in this build.
- Sprites for bosses (all reuse vanilla trainer pics).
- Any documentation for gyms 4 to 8, the Elite Four and the Champion beyond their names and level caps.
