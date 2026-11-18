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

## Shaman (implemented v0.1.25-v0.1.26)

| Form | Types | Stats | BST | Ability | Hidden ability |
|---|---|---|---|---|---|
| Shaman | Electric | 65 / 50 / 75 / 70 / 75 / 60 | 395 | | |
| Rsham | Electric/Water | 120 / 50 / 115 / 90 / 115 / 85 | 575 | Storm Drain | Drizzle |
| Enhance | Electric/Flying | 95 / 125 / 75 / 70 / 75 / 124 | 564 | | |
| Ele | Electric/Fire | 100 / 60 / 80 / 135 / 80 / 120 | 575 | | Solar Power (a *Parental Bond* entry follows it in the source; assignment unclear) |

### Shaman design decisions (2026-11-17)
- **Windfury Weapon** (Enhancement ability): every physical attack has a 20% chance to repeat; repeats can chain, up to 5 times.
- **Elemental Overload** (Elemental ability): same idea for special attacks, 20% repeat, chains up to 5.
- **No Maelstrom** for now (no resource counter). Moves are being chosen one by one with Charlie; none agreed yet.
- **Agreed moves:**
  - Lightning Bolt: Electric special, 55 power, 100% accuracy, small (10%) chance to paralyze. Learned early (about level 5).
  - Flame Shock: Fire special, 15 power, 100% accuracy, 20 PP, always burns the target. About level 12.
  - Lava Burst: Fire special, 55 power, 85% accuracy, 10 PP, always crits a burned target. Elemental, about level 24.
  - Stormstrike: Electric physical, 65 power, 100% accuracy, 15 PP, single hit, 50% chance to lower the target's Sp. Def by 1. Enhancement, about level 20.
  - Healing Wave: Water status, 10 PP, heals any friendly target (self or ally) by 40% max HP. Restoration, about level 16.
  - Riptide: Water status, 10 PP, any friendly target; heals 12.5% max HP now, then 1/16 max HP at the end of each of the next 4 turns (about 37% total). Restoration, about level 28.
  - Chain Lightning: Electric special, 60 power, 100% accuracy, 5 PP. Hits the main target at full power and the second foe at half power. Elemental, about level 32.
  - Bloodlust (covers both Bloodlust and Heroism): Electric status, 1 PP, +2 Atk and +2 Sp. Atk for the user and all allies. About level 36.
  - Totems (each a separate status move, all last 4 turns on the user's side; numbers for PP/type/level still being settled):
    - Stoneskin Totem: 25% less damage from physical moves, none from special.
    - Windfury Totem: allies get Windfury Weapon's 20% chained physical repeat while it lasts (preferred: a side effect, not overwriting abilities; fall back to overwriting if too hard).
    - Healing Stream Totem: side heals 1/16 max HP each turn.
    - Grounding Totem: Light Screen plus Mud Sport effects.
    - Searing Totem: opponents lose 1/8 max HP each turn. Learned by every Shaman, level 20.
    - Stoneskin Totem learned by every Shaman at level 16. Windfury ~42 (Enhancement), Healing Stream ~44 (Restoration), Grounding ~46 (all).
    - Earthbind Totem: about level 30; for 4 turns, every foe's Speed is held 1 stage lower, including foes that switch in; it ends when the totem ends (lasting version, confirmed).
    - Magma Totem (Elemental only): lasts 2 turns, casts Lava Plume once at the end of each turn starting the turn after it is cast, at full power (80), with Lava Plume's 30% burn chance. Foes only (assumed; confirm).
  - Earth Shock: Ground special, 60 power, lowers the target's Sp. Atk by 1, 100% chance. About level 28.
  - Frost Shock: Ice special, 65 power, lowers the target's Speed by 1, 100% chance. About level 30.
  - Shock Wave (vanilla) dropped from the draft learnset in favour of these.
    - All totems 5 PP (proposed), Electric Shaman types: Stoneskin Rock, Windfury Flying, Healing Stream Water, Grounding Ground, Searing/Magma Fire.
- **Restoration ability: Storm Drain** (decided 2026-11-17). Enemy Storm Drain users can steal Healing Wave and Riptide in doubles, which Charlie likes. **Base Shaman ability: Static** (decided 2026-11-17).

## Druid (design draft, not implemented)

| Form | Types | Stats | BST | Notes |
|---|---|---|---|---|
| Druid | Grass | not filled in | | |
| Resto Druid | Grass | 130 / 80 / 85 / 80 / 85 / 115 | 575 | |
| Feral | Grass/Normal | 100 / 160 / 60 / 30 / 60 / 165 | 575 | Could work like Honedge forms |
| Guardian | Grass/Rock | 220 / 110 / 90 / 30 / 70 / 55 | 575 | |
| Boomy | Grass/Fairy | 90 / 50 / 75 / 160 / 95 / 105 | 575 | |

### Druid design decisions (2026-11-17)
- **Gimmick:** shapeshifting. Every Druid learns Moonkin, Bear, Cat and Tree Form (status moves). Using one swaps the Druid's battle form (stats/moves, sprite if art exists) for the rest of the fight. Each spec masters one form (Boomy/Moonkin, Guardian/Bear, Feral/Cat, Resto/Tree). Honedge-style form change.
- **Abilities (proposed, approved in spirit):** base Natural Cure or a small passive heal (Regrowth); Resto: **Efflorescence** (user's pick, replaces Lifebloom); Feral: Predatory Swiftness (next move after a crit gets priority); Guardian: Thick Hide (less damage taken at low HP); Boomy: Eclipse (Grass moves boosted one turn, Fairy the next).
- **Base Druid stats:** proposed 65/55/70/70/70/60 (BST 390), not yet confirmed.
- **Evolution items:** open (Moon/Sun/Shiny are used by Warrior and Shaman; four specs need four items, e.g. add Dawn Stone).
- **Art:** undecided, Charlie is thinking about it. Do not implement until chosen.
- **Efflorescence (Resto):** triggers when the Druid enters the field. Proposed: bloom on its side for 3 turns, each ally on the field heals 1/16 max HP at end of turn (duration and amount not confirmed).
- **Moves and levels:** not yet designed.

## Monk (design draft, not implemented)

| Form | Types | Stats | BST |
|---|---|---|---|
| Monk | Fairy | 75 / 65 / 60 / 45 / 55 / 75 | 375 |
| Mistweaver Monk | Fairy | 100 / 85 / 90 / 70 / 90 / 90 | 525 |
| Brewmaster Monk | Fairy/Fire | not filled in | |
| Windwalker Monk | Fairy/Fighting | not filled in | |

## Warrior (design notes, not implemented)

Specs: Arms, Fury, Protection.

**Rage resource:** builds when the Warrior hits or is hit. Needs a new counter that goes much higher than 3 (ideally 10). Several moves spend it.

**Moves**
- Mortal Strike (Arms): costs 4 rage, 60 base power, plus a heal block effect.
- Sunder Armor: -3 Defense on the target.
- Victory Rush: a bit of damage, and heals when the user has just knocked out an enemy (look at Retaliate for an inverse trigger).
- Whirlwind: 40 damage to all other targets, plus bleed if bleed is implemented.
- Sweeping Strikes (maybe): for 4 turns, all your attacks target all enemies.
- Execute: spends all rage, 15 or 20 damage per point.
- Charge: first turn only, like Fake Out. Generates 5 rage and lowers the enemy's Speed.
- Spell Reflect (Protection): Mirror Coat, plus no damage taken if the enemy uses a special attack. Probably 3 PP.
- Rampage (Fury): costs 5 rage, 4 hits of 20 base power, raises own crit rate by 1 stage.
- Battle Shout: +1 Attack for self and ally.
- Commanding Shout: heals self and ally by 40% (stronger Life Dew). 1 PP.
- Colossus: 1 PP. +2 Defense, +1 Attack, +1 Sp. Def.
- Rend: costs 2 rage, 20 base power plus bleed (poison if bleed isn't implemented).
- Taunt: Follow Me redirection.

**Abilities**
- Shield Specialization (Protection): 20% chance to negate all physical damage when hit.
- Enrage (Fury): +1 Speed or +1 Attack at random on a KO.
- Sudden Death (Arms, confirmed 2026-11-16): 20% chance, after any hit, to refund the rage that move cost. Replaces Resilient Fighter (removes the first negative status each battle), which is dropped.

### Warrior implementation status (v0.1.21)
Species: Warrior (Fighting) -> Arms / Fury / Protection (all Fighting/Steel) via Moon / Sun / Shiny Stone. Placeholder sprites: Timburr, Machamp, Mienshao, Bastiodon. Stats are a draft proposal (Arms 100/140/100/45/70/90, Fury 90/150/75/45/70/125, Protection 140/95/150/40/90/55), not from the sheet.
- **Rage:** `volatiles.warriorRage` (0-10). +1 when the Warrior damages an opponent, +1 when an opponent damages it. Resets on switch-out. Moves fail without enough rage. In-battle display: a message after each change ("rage: N/10"). Healthbox red number or fill bar is a later nice-to-have.
- **Done:** Mortal Strike, Execute, Charge!, Victory Rush, Rampage, Rend (2 rage), Sunder Armor, Battle Shout, Command Shout, Colossus, Challenge (Taunt), W. Whirlwind; abilities Sudden Death, Enrage, Shield Specialization (20% negate, silent). Names that clash with vanilla moves got different display names (Charge!, W. Whirlwind, Challenge, Command Shout).
- **Spell Reflect / Sweeping Strikes:** done (v0.1.23). Spell Reflect is a Protect variant for special moves that reflects the move's real damage back at 1x (v0.1.24).
- **Not yet:** bleed (not in the codebase; poison stands in), healthbox rage display, real sprites, wild/trainer use. Tests in `test/battle/ability/warrior_rage.c`.


### Shaman implementation status (v0.1.26)
- Species ids 1585-1588 (Shaman, Resto, Enhancement, Elemental). Placeholder art: Timburr (base), Conkeldurr (specs), recolored (yellow / blue / purple / red). Stones: Moon -> Resto, Shiny -> Enhancement, Sun -> Elemental (assumed mapping). Warrior line also recolored.
- Abilities: Static, Storm Drain, Windfury Weapon and Elemental Overload (`CancelerMultihitMoves`: 20% repeat roll, then 20% per extra repeat up to 5, `RNG_WINDFURY`). Only plain EFFECT_HIT moves repeat.
- Totems live in `SideTimer` (stoneskin/searing/windfuryTotem/healingStream/earthbind/magma + magmaCaster), planted by `BS_TryPlantTotem`. Effects: stoneskin in the damage calc, earthbind in `GetBattlerTotalSpeedStat` (x2/3), windfury in the repeat roll, searing/healing stream/magma damage in `FIRST_EVENT_BLOCK_TOTEMS`, countdown in `SECOND_EVENT_BLOCK_TOTEMS` (only the first expiry per side per turn prints a message). Magma Totem uses the caster's slot at tick time; 30% burn (`BS_TryMagmaBurn`).
- Riptide: `volatiles.riptideTimer`, `ENDTURN_RIPTIDE`. Lava Burst crit hook is in `IsCriticalHit`. Chain Lightning is TARGET_SELECTED; `MOVEEND_CHAIN_LIGHTNING` arcs to the target's partner for half damage (skips Volt Absorb / Lightning Rod / Motor Drive holders).
- Not yet: Maelstrom (declined for now), AI awareness of totems, tests are in `test/battle/ability/shaman.c`.
