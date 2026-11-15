# Death Knight move tracker (historical)

Source: Google Sheet "World of Pokemon Stats/Moves final final.docx FINAL.pptx", tab *Death Knight Moves* (early-to-mid 2025).

**This is superseded by [`../data/stats-moves.csv`](../data/stats-moves.csv) (Aug 2025)**, which has PP and level-learned columns and updated values. It is kept for the design history and the "remaining work" notes. Status key from the sheet: `x` = implemented, `s` = stub / partly working, blank = not started.

| Move | Type | Damage | Targets | Effects | Acc | Status | Remaining work (as written) |
|---|---|---|---|---|---|---|---|
| **Death Knight (base)** | | | | | | | |
| Scourge Strike | Ghost | 40 | targeted enemy | 20% chance to poison, +1 runic power | 100 | x | Look at Sappy Seed for bonus events triggering on kill |
| Death Strike | Dark | 60 | targeted enemy | heal for half | | x | Look at Sappy Seed for bonus events triggering on kill |
| AMS | Dark | -- | self | safeguard | | s | Applies safeguard but does not give SpD. Needs script rewrite. |
| Blood Boil | Dark | 20 | all enemies | seed | | s | Uses Leech Seed rather than a Blood Plague |
| Death Coil | Ghost | 40 x stockpile | targeted enemy | | | | |
| Howling Blast | Ice | 55 | all enemies | applies frostbite | | x | |
| Icebound Fortitude | Ice | | | 2 stage Def up, -1 Speed | | s | New script needed to avoid 1 point of self-damage |
| **Frost DK** | | | | | | | |
| Frost Strike | Ice | 60 x stockpile | | | | | |
| Remorseless Winter | | 45 (2-5 hits) | all | 10% flinch, 10% freeze | 85 | x | |
| Obliterate | | 90 | targeted enemy | high crit chance | 85 | x | |
| **Blood DK** | | | | | | | |
| Marrowrend | Ground | 60 | targeted enemy | 1 stage Def up | | x | |
| Dancing Rune Weapon | Dark | -- | self | 1 stage Atk up, 1 stage evasion up | | s | New script needed to avoid 1 point of self-damage |
| Consumption | | 75 | all enemies | heal for half | | x | |
| **Unholy DK** | | | | | | | |
| Army of the Dead | Ghost | 25, pop bomb | targeted enemy | | | x | |
| Dark Transformation | Dark | -- | all allies | | | s | Should be ally-only with a bigger buff. Script rewrite needed. |
| Gargoyle | Poison | | | | | x | |

The sheet ends with an empty "DK Learnset" heading.

Repo history after this sheet (from commit messages): Death Strike fully functional, runic power generation functional, Scourge Strike fixed. Check `data/stats-moves.csv` for the current implemented/remaining-work columns.
