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

## Learnset design principle (2026-11-18)
Classes should have weaker versions of the same kind of move early so there are upgrades to earn while leveling (e.g. a small heal early, a bigger one later). Duplicate-purpose moves of different strength are fine. Not a priority to hyper-focus on now, but keep it in mind when building out learnsets (revisit Shaman and Warrior too).

## Class structure

Every class has a **base form** that evolves at some point into one of **three WoW specializations**. For example, Mage evolves into Frost, Fire or Arcane, and Death Knight into Blood, Frost or Unholy. The Druid draft below lists four specs (Restoration, Feral, Guardian, Balance), which needs reconciling with this rule.

- **Learnset design principle (2026-11-17):** it's fine, and desirable, to have duplicate-purpose moves of different strength across a learnset (a weaker early heal, a stronger later one) so levelling always offers an upgrade and the power curve stays smooth. Not a priority yet, but keep it in mind when building out learners for every class.

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
- **Abilities (proposed, approved in spirit):** base Natural Cure or a small passive heal (Regrowth); Resto: **Efflorescence** (user's pick, replaces Lifebloom); Feral: Predatory Swiftness (next move after a crit gets priority); Guardian: Survival Instincts (first time HP falls to 30% or less, casts Frenzied Regeneration for free: heals 60%, once per switch-in) - replaced Thick Hide on 2026-11-18; Boomy: Eclipse (Grass moves boosted one turn, Fairy the next).
- **Base Druid stats:** proposed 65/55/70/70/70/60 (BST 390), not yet confirmed.
- **Evolution items:** open (Moon/Sun/Shiny are used by Warrior and Shaman; four specs need four items, e.g. add Dawn Stone).
- **Art:** undecided, Charlie is thinking about it. Do not implement until chosen.
- **Efflorescence (Resto):** triggers when the Druid enters the field. Proposed: bloom on its side for 3 turns, each ally on the field heals 1/16 max HP at end of turn (duration and amount not confirmed).
- **Forms are stage boosts** (no extra effectiveness penalty for other specs). Moonkin Form (Grass, status, 5 PP, ~lv10): +1 Sp. Atk. Switching forms removes the old form's stages and applies the new ones.
- **Unshift** (one shared move for all specs, Protect-like): protects the user this turn and returns it to base form (removing the form's stage boosts). Replaces per-form un-shifting.
- Bear Form (Grass, status, 5 PP, ~lv14): +1 Def, +1 Sp. Def. Approved as is.
- Cat Form (Grass, status, 5 PP, ~lv18): +1 Atk, +1 Speed, no crit bonus. Shifting forms counts as switching in for first-turn checks, so first-turn-only moves (and first-turn crit bonuses) work again after a shift.
- **Shred** (Normal/Grass physical, 20 PP, 100% acc, 40 power, ~lv20): always crits on the first turn after switching in or shifting forms. Builds combo points: +1, or +2 on a crit.
- **Resource systems:** Feral gets **combo points** (cap 5): some moves gain points, finishers spend them and scale with points spent (like runic power / rage). Guardian/Bear gets **rage**, same rules as Warrior (+1 hitting, +1 being hit, cap 10, resets on switch-out).
- **Maul** (Normal/Grass physical, 60 power, spends 3 rage) and **Ironfur** (Grass status, +2 Def, spends 4 rage): approved, Bear Form presumably required (to confirm).
- **Moonfire** (Fairy special, 40 power, 15 PP, 100% acc, lv10): always burns the target (the burn is the DoT). **Starfire** (Grass special, 80 power, 10 PP, 100% acc, 20% lower Sp. Def, lv26). Both approved.
- **Rejuvenation** (Grass status, 10 PP, lv14, self/ally): no up-front heal, 1/8 max HP at the end of each of the next 3 turns, doesn't stack with itself. **Swiftmend** (Grass status, 5 PP, lv30, self/ally): consumes Rejuvenation on the target, heals 50% instantly, fails without it. Approved.
- **Thrash** (Normal/Grass physical, 50 power, 15 PP, lv22, hits both foes in doubles, +2 rage, 35% poison, Bear Form). **Frenzied Regeneration** (Grass status, 5 PP, lv34, heals 60% max HP, costs 5 rage, Bear Form). Approved.
- **Wild Growth** (Grass status, 5 PP, lv38): heals every ally on the field 25% now. **Tranquility** (Grass status, 1 PP, lv50): heals the whole team 35% and gives +1 Sp. Def. Approved.
- **Wild Growth** (Grass status, 5 PP, lv38): heals every ally on the field 25% now. **Tranquility** (Grass status, 1 PP, lv50): heals the whole team 35% and +1 Sp. Def. Approved.
- **Type rule:** Cat and Bear form moves are either Normal or Grass; each move needs a single type, decided per move (earlier "Normal/Grass" notes mean undecided). Mangle is a Bear Form move (Normal/Grass TBD, 55 power, 15 PP, lv28).
- **Types decided:** Shred Normal, Rake Grass (35 power, 20 PP, lv16, always poisons, +1 combo, Cat), Ferocious Bite Normal, Thrash Grass, **Mangle Rock** and **Maul Rock** (to fit Guardian's Rock typing; Mangle is Bear, +2 rage). Wrath (Grass special, 45 power, lv6) and Solar Beam (Grass special, 90 power, 10 PP, lv40, no charge in Moonkin Form) assumed approved. **Moonfire is learnable by every Druid spec** (not form-gated). Every spec's secondary type should have a few moves of its own.
- **Starsurge** (Fairy special, 70 power, 15 PP, lv32, 20% +1 Sp. Atk to user) approved. **Celestial Alignment** (Fairy status, 1 PP, lv46): +2 Sp. Atk and +1 crit stage for 2 turns, then both are removed (Moonkin Form requirement unconfirmed).
- **Base Druid learnset (draft):** L1 Vine Whip, Growl; L4 Leech Seed; L6 Wrath; L8 Unshift; L10 Moonfire + Bear Form; L12 Razor Leaf; L14 Moonkin Form + Rejuvenation; L18 Cat Form; L20 Shred. (Bear and Moonkin Form levels swapped.)
- **Spec learnset split (draft):** Resto: Swiftmend 30, Wild Growth 38, Solar Beam 40, Tranquility 50. Feral: Rake 16, Ferocious Bite 24. Guardian: Maul 18, Thrash 22, Ironfur 26, Mangle 28, Frenzied Regeneration 34. Boomy: Starfire 26, Starsurge 32, Solar Beam 40, Celestial Alignment 46.
- **Filler policy (Charlie, 2026-11-18):** fill the gaps before the signature Druid moves with regular Pokemon moves instead of adding weaker custom versions, to avoid bloating the move list and keep harmony with the base game's design.
- **Filler moves (approved):** Resto: Mega Drain 16, Synthesis 20, Aromatherapy 24, Giga Drain 34, Ingrain 42. Feral: Quick Attack 12, Slash 22, Poison Jab 26, X-Scissor 32, Swords Dance 36. Guardian: Rock Throw 14, Bulk Up 20, Rock Slide 30, Body Press 32, Stone Edge 40, Earthquake 44. Boomy: Fairy Wind 12, Disarming Voice 18, Energy Ball 28, Dazzling Gleam 34, Calm Mind 38, Moonblast 44.
- **Stage 1 built (v0.1.28):** species ids 1589-1593 (Druid, Resto, Feral, Guard(ian), Boomy), palette-swapped Sunkern / Sudowoodo / Liepard / Torterra / Noctowl (script `/tmp/tools/druid_pal.py` is not in the repo; palettes are in graphics/pokemon/<dir>/druid_*.pal). Evolution assumed Moon->Resto, Shiny->Feral, Dawn->Guardian, Sun->Boomy. Base stats 65/55/70/70/70/60. Regular-move learnsets only. Pending: forms, combo points, bear rage, Efflorescence and other abilities, custom moves.
- **Form art system (Charlie, 2026-11-18):** the Druid's species art is its *base form*: Sunkern for the unevolved Druid, Sunflora for every evolved spec. Shifting changes the battle sprite. **Bear Form and Cat Form are available to all Druids**; Bear = Grotle (Torterra for Guardian), Cat = Purrloin (Liepard for Feral). Other specs only get the unevolved art, so each spec has something visibly special. **Tree Form (Resto only)** = Sudowoodo art; **Owlkin Form (Boomy only)** = Noctowl art (replaces the earlier general Moonkin Form, +1 Sp. Atk). Forms stay stage boosts. Needs: recolored Sunflora, Grotle, Purrloin; in-battle sprite swap (gfx-only, no stat change).
- **Form art decisions (2026-11-18):** all evolved specs share the same green Sunflora base. Tree Form and Owlkin Form are learned on evolution (level-0 learnset entries, supported by the engine). Fallback if per-spec form art is troublesome: give each spec its own special Bear/Cat form move.
- **Form art implementation plan:** gfx-only swap via `HandleSpeciesGfxDataChange` (Transform-style path with an override species); needs ~6 hidden form-only species entries for the art (Grotle, Torterra, Purrloin, Liepard, Sudowoodo, Noctowl, recolored), ~100 KB ROM. Cannot verify visually without an emulator.
- **Forms implemented (v0.1.30):** `volatiles.druidForm` (1 bear, 2 cat, 3 tree, 4 owlkin), `BS_DruidShift`, `BS_DruidUnshift` (hooked into the Protect script), art swap in `HandleSpeciesGfxDataChange` via `GetDruidFormSpecies`, 6 hidden form-species (ids 1594-1599). Tree Form heal boost in `ModifyDruidHealAmount`. Tests in `test/battle/ability/druid.c`. Sprite swap untested on screen.
- **Abilities implemented (v0.1.31):** Efflorescence (bloomTimer, switch-in, 3 turns of 1/16 heal), Predatory Swiftness (`predatorySwiftness` volatile set in `MoveEndChainLightning` hook, +1 priority), Survival Instincts (heal 60% once at <=30% HP, replaced Thick Hide; skips the Chain Lightning arc on the turn it triggers), Eclipse (+30% Grass on odd turns, Fairy on even; numbers unconfirmed).
- **Move management (decided):** moves stay constant across forms. A spec doesn't have to use its own form, so each spec can carry 3 spec moves plus a form move. A Druid trainer NPC with scroll menus to set loadouts comes later (added to docket).
- **Moves and levels:** drafting in progress (Moonkin, Bear, Cat Form, Shred done; Ferocious Bite proposed: Normal/Grass physical, 10 PP, ~lv24, spends all combo points, power 20 + 20 per point, Cat Form only (confirmed)).

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

### Druid combo points, bear rage and moves (v0.1.33)
- **Combo points (Feral):** `volatiles.comboPoints` (0-5), resets on switch-out, shown as a message after each change. Shred (Normal 40, +1, +2 on crit, always crits while `IsBattlersFirstTurn`, i.e. the turn after switching in or shifting), Rake (Grass 35, 100% poison, +1), Ferocious Bite (`EFFECT_FEROCIOUS_BITE`, Normal 20 +20 per point, spends all). All Cat Form only.
- **Bear rage (Guardian etc.):** `BattlerUsesRage()` = Warrior species, or a Druid in Bear Form. Shares `volatiles.warriorRage`. Maul (Rock 70, cost 3), Mangle (Rock 45, +2 rage), Ironfur (Grass, +2 Def, cost 4), Thrash (`MOVE_THRASH_DRUID`, Grass 50, both foes, +2 rage, 35% poison), Frenzied Regen (heals 60%, cost 5). All Bear Form only.
- Form gating lives in `GetMoveDruidFormRequirement()` (1 Bear, 2 Cat) and is checked in `CancelerMoveFailure`.
- **Survival Instincts** is now once per battle (`PartyState.survivalInstinctsUsed`).
- Maul was raised from 60 to 70 and Mangle lowered from 55 to 45 after review: Maul is the rage spender, Mangle the builder.
- Not yet: Boomy (Wrath, Starfire, Starsurge, Solar Beam, Celestial Alignment) and Resto (Rejuvenation, Swiftmend, Wild Growth, Tranquility) moves, Moonfire, Druid trainer NPC.

### Druid Boomy / Resto moves (v0.1.34)
- Celestial Alignment: `volatiles.celestialTimer` (2) + `bonusCritStages`, removed by `ENDTURN_CELESTIAL`. Species check (Boomy), not form check.
- Rejuvenation: `volatiles.rejuvTimer` (3), ticks in `ENDTURN_REJUVENATION`. Swiftmend clears it. Wild Growth / Tranquility share `BS_TryTeamHeal` + `BS_HealNextAlly` (loop in the battle script); Tranquility heals the bench directly in party data.
- Solar Beam skips its charge turn when `druidForm == 4` (Owlkin), in `CancelerCharging`.
- Open design question: per-form move loadouts (Druid has 4 move slots but many form moves). Proposal pending: store assigned moves per form, swap them on shift, edit via the Druid trainer NPC.

### Druid form loadouts (design, 2026-11-19)
- Every non-base form has 4 slots: **Unshift (fixed) + 3 assignable**. Base form uses the mon's own 4 moves.
- Learning a form-gated move auto-fills the first empty slot of its form. Past 3, it is learned but unassigned and needs the Druid trainer NPC (scroll menu). Moves usable in all forms (Moonfire, Wrath, Vine Whip...) can be assigned to any form.
- Shift moves (Bear, Cat, Tree, Owlkin Form) and Unshift stop being learnset moves and are granted automatically.
- Storage: SaveBlock3, keyed by personality, ~22 B per Druid. See [memory-budget.md](memory-budget.md).
- PP: form moves keep persistent PP per Druid (`pp` bytes in the loadout, 0xFF = full), refilled by `HealPlayerParty`. Implemented in v0.1.35 (`src/gjt_druid.c`).
- Implemented v0.1.35: affinity table `GetDruidMoveAffinity` (1 Bear, 2 Cat, 3 Tree, 4 Owlkin). Bear/Cat moves and Unshift are *exclusive* (skipped by level-up learning). Tree/Owlkin affinity moves are normal moves that also auto-fill those forms.
- Known gaps: the Druid trainer NPC; Bear Form is learned at 10 but Bear moves start at 18, so Bear Form shows only Unshift until then; Elixirs/Ethers do not restore form PP; a Druid knows no form moves in the base summary screen.

- Druid trainer (v0.1.36): `data/scripts/gjt_druid_trainer.inc` + `DruidTrainer_*` natives in `src/gjt_druid.c`. Uses dynamic multichoice menus (party mon, form, slot, move). `DRUID_SLOT_CLEARED` (0xFFFF) marks a deliberately empty slot. Reached from the test guide until it gets a real map spot.
