# WoW classes

Source: Google Sheet "World of Pokemon Stats/Moves final final.docx FINAL.pptx", tab *Classes* (the fullest class list), cross-checked against the Aug 2025 exports in [`../data/classes.csv`](../data/classes.csv).

**Implemented in the game so far:** Death Knight line and Mage line only (per the repo and commit history). Shaman, Druid and Monk exist only as design drafts here.

**Precedence:** where this file disagrees with `data/classes.csv` (Aug 2025), the CSV is newer. The notable conflict is the Mage ability, listed below.

Stats are HP / Atk / Def / SpA / SpD / Spe (BST).

## Death Knight

| Form | Types | Stats | BST | Ability | Hidden ability |
|---|---|---|---|---|---|
| Unevolved DK | Ghost | 80 / 80 / 75 / 65 / 75 / 20 | 395 | Hyper Cutter | |
| Blood DK | Ghost/Dark | 170 / 110 / 105 / 90 / 100 / 20 | 575 | Will of the Necropolis (shown in game as "Necropolis Will") | Dark Aura |
| Unholy DK | Ghost/Poison | 130 / 90 / 90 / 135 / 110 / 20 | 575 | Poison Touch | Parental Bond |
| Frost DK | Ghost/Ice | 130 / 150 / 110 / 75 / 90 / 20 | 575 | Snow Warning | Sniper |

Decisions (confirmed by Charlie, 2026-11-15):
- *Will of the Necropolis* belongs to the **Blood DK** (replaces Cursed Body): takes 33% less damage while HP is below 50%. Implemented and tested. The in-game name is shortened to "Necropolis Will" because ability names are capped at 16 characters.
- Snow Warning, Sniper, Poison Touch, Parental Bond and Dark Aura were audited on the merged build and tested (`test/battle/ability/will_of_the_necropolis.c`).

Runic Power rules (confirmed 2026-11-15): Scourge Strike generates 1 (max 3). Death Strike costs exactly 2 for a flat 70 power (updated 2026-11-15). Frost Strike spends all of it and scales power per point (55). Death Coil spends 1 for flat 60 special power; used on a Ghost-type ally it heals 50% max HP instead, and it cannot target the user. The Sappy Seed note in the tracker was a reference for Blood Boil, not a kill-trigger requirement.

Early Blood DK move ideas: Marrowrend (physical, Ground or Dark, +1 Def), Death Strike (Dark, 70 power, costs 2 Runic Power, heals 50% of damage dealt), AMS (Ghost, +1 Sp. Def and Safeguard), Blood Boil (Leech Seed with a blood-boiling message). See [../tracking/death-knight-moves.md](../tracking/death-knight-moves.md) for current status.

## Mage

| Form | Types | Stats | BST | Ability | Hidden ability |
|---|---|---|---|---|---|
| Mage | Fire | 55 / 15 / 30 / 95 / 90 / 90 | 375 | Frost Armor | |
| Frost Mage | Fire/Ice | 100 / 20 / 65 / 128 / 125 / 116 | 554 | Frost Armor | |
| Fire Mage | Fire/Dragon | 95 / 20 / 45 / 158 / 110 / 126 | 554 | Flash Fire | Hot Streak (each crit landed raises crit stage by 1) |
| Arcane Mage | Fire/Psychic | 80 / 20 / 45 / 164 / 110 / 136 | 555 | Mirror Armor | Mana Barrier (all moves get recoil, but lots of HP) |

Decisions (confirmed by Charlie, 2026-11-15):
- Mana Barrier belongs to the **Arcane Mage** only. The base Mage's ability is **Frost Armor**. (Implemented.)
- Mana Barrier mechanic: every damaging move costs the user HP based on the move's PP. Cost = max HP / move PP, capped at 25% of max HP, minimum 1 HP (5 PP = 20%, 10 PP = 10%, 35 PP is about 3%). Status moves cost nothing, Magic Guard negates it, and spread moves charge once. The Arcane Mage compensates with a large HP pool.

- Hot Streak (confirmed 2026-11-15): each critical hit the Fire Mage lands raises its crit stage by 1. Stacks up to +3 and resets on switch-out. Implemented and tested. (An older sheet version said +1 SpA; superseded.)
- Frost Armor (confirmed 2026-11-15): 30% chance to inflict **frostbite** on an attacker that makes contact. Ice types are immune. Implemented and tested.
- Arcane Mage keeps Mirror Armor as its normal ability, with Mana Barrier hidden.

## Class structure

Every class has a **base form** that evolves at some point into one of **three WoW specializations**. For example, Mage evolves into Frost, Fire or Arcane, and Death Knight into Blood, Frost or Unholy. The Druid draft below lists four specs (Restoration, Feral, Guardian, Balance), which needs reconciling with this rule.

## Shaman (design draft, not implemented)

| Form | Types | Stats | BST | Ability | Hidden ability |
|---|---|---|---|---|---|
| Shaman | Electric | 65 / 50 / 75 / 70 / 75 / 60 | 395 | | |
| Rsham | Electric/Water | 120 / 50 / 115 / 90 / 115 / 85 | 575 | Storm Drain | Drizzle |
| Enhance | Electric/Flying | 95 / 125 / 75 / 70 / 75 / 124 | 564 | | |
| Ele | Electric/Fire | 100 / 60 / 80 / 135 / 80 / 120 | 575 | | Solar Power (a *Parental Bond* entry follows it in the source; assignment unclear) |

## Druid (design draft, not implemented)

| Form | Types | Stats | BST | Notes |
|---|---|---|---|---|
| Druid | Grass | not filled in | | |
| Rdruid | Grass | 130 / 80 / 85 / 80 / 85 / 115 | 575 | |
| Feral | Grass/Normal | 100 / 160 / 60 / 30 / 60 / 165 | 575 | Could work like Honedge forms |
| Guardian | Grass/Rock | 220 / 110 / 90 / 30 / 70 / 55 | 575 | |
| Boomy | Grass/Fairy | 90 / 50 / 75 / 160 / 95 / 105 | 575 | |

## Monk (design draft, not implemented)

| Form | Types | Stats | BST |
|---|---|---|---|
| Monk | Fairy | 75 / 65 / 60 / 45 / 55 / 75 | 375 |
| Mistweaver Monk | Fairy | 100 / 85 / 90 / 70 / 90 / 90 | 525 |
| Brewmaster Monk | Fairy/Fire | not filled in | |
| Windwalker Monk | Fairy/Fighting | not filled in | |
