# GJT build changelog

The build version is shown at the very start of a new game (Khadgar's intro) and when you talk to the test NPC in the player's bedroom. Source: `data/text/gjt_version.inc`. ROM files are sent as `GJT-WoW-vX.Y.Z.gba` so a phone cannot reuse an older download with the same name. Bump the patch number for every ROM sent.

## v0.1.32
- Guardian's ability is now Survival Instincts (replaces Thick Hide): the first time its HP falls to 30% or less, it heals 60% for free (once per switch-in).

## v0.1.31
- Druid abilities live. Efflorescence (Resto): on switch-in, a bloom on your side heals every ally 1/16 max HP at the end of each of the next 3 turns. Predatory Swiftness (Feral): after a move that crits, the next move gains +1 priority. Thick Hide (Guardian): at half HP or less, takes 25% less damage. Eclipse (Boomy): Grass moves hit 30% harder on odd turns (1, 3, ...), Fairy moves on even turns.
- Numbers for Thick Hide and Eclipse were my picks; easy to tune.

## v0.1.30
- Druid forms live. Bear Form (+1 Def/Sp. Def), Cat Form (+1 Atk/Speed), Tree Form (Resto only: +1 Sp. Def, your healing moves 25% stronger), Owlkin Form (Boomy only: +1 Sp. Atk), Unshift (Protect that returns you to base form). Switching forms swaps the old boosts for the new ones and counts as switching in.
- Forms swap the battle sprite only: Bear = Grotle (Torterra for Guardian), Cat = Purrloin (Liepard for Feral), Tree = Sudowoodo, Owlkin = Noctowl. Evolved Druids are now the green Sunflora in their base form.
- Learnsets: Unshift 8, Bear Form 10, Cat Form 18 for everyone; Tree/Owlkin Form on evolution.
- Not yet: Efflorescence and other Druid abilities, combo points, bear rage, the custom Druid attacks/heals.

## v0.1.29
- Boomy Druid: Noctowl's brow tufts and eye band recolored blue (beak and talons pick up the blue too).

## v0.1.28
- Druid line (stage 1): Druid (Grass, Sunkern art), Resto (Sudowoodo art, orange wood), Feral (Grass/Normal, brown Liepard), Guardian (Grass/Rock, brown Torterra), Boomy (Grass/Fairy, Noctowl with blue eyes). Sheet stats; base Druid 65/55/70/70/70/60.
- Evolution (assumed): Moon -> Resto, Shiny -> Feral, Dawn -> Guardian, Sun -> Boomy.
- Abilities registered with no effect yet: Efflorescence, Predatory Swiftness, Thick Hide, Eclipse. Natural Cure on the base.
- Learnsets use regular Pokemon moves only so far (fillers); forms, combo points, bear rage and the custom Druid moves come next.
- Test NPC also hands out a Druid and Dawn Stones.

## v0.1.27
- Magma Totem: 30% chance to burn each foe it hits.
- Chain Lightning is a normal pick-your-target move again. After it hits, the lightning arcs to the other foe (doubles) for half of the damage it would have dealt there.

## v0.1.26
- Shaman stage 2: Windfury Weapon and Elemental Overload live (20% to repeat, chaining up to 5 repeats; shows as a multi-hit). Plain single-hit damaging moves only.
- Totems (4 turns, own side): Stoneskin (-25% physical damage taken), Searing (foes lose 1/8 per turn), Windfury (allies' physical hits can repeat), Healing Stream (team heals 1/16 per turn), Grounding (Light Screen + Mud Sport), Earthbind (foes' Speed held at -1 stage), Magma Totem (Lava Plume on foes at end of each of the 2 turns after the cast; no burn chance yet).
- New moves: Lava Burst (always crits a burned target), Riptide (12.5% now, 1/16 for 4 turns), Chain Lightning (main target full, other foe half; in doubles the first foe is main, no target menu), totems.
- Learnsets updated (Stoneskin 16, Searing 20, Earthbind 30, Grounding 46, Healing Wave 16, Stormstrike 20, Lava Burst 24, Riptide 28, Chain Lightning 32, Windfury Totem 42, Healing Stream 44, Magma Totem 44).
- All Warrior sprites recolored (Arms red, Fury orange, Protection steel blue, base bronze).

## v0.1.25
- Shaman line (stage 1): Shaman (Electric), Resto (Electric/Water), Enhancement (Electric/Flying), Elemental (Electric/Fire). Evolve with Moon/Shiny/Sun stones (Moon -> Resto, Shiny -> Enhancement, Sun -> Elemental). Placeholder Timburr/Conkeldurr sprites, recolored per spec.
- Abilities registered: Static, Storm Drain, Windfury Weapon and Elemental Overload (the last two have no effect yet).
- New moves: Lightning Bolt, Flame Shock, Stormstrike, Healing Wave (any friendly target, 40%), Earth Shock, Frost Shock, Bloodlust (+2 Atk/Sp. Atk to user and allies).
- Not yet in: Lava Burst, Riptide, Chain Lightning, all totems, the repeat-attack abilities.
- Test NPC now also hands out a Shaman.

## v0.1.24
- Spell Reflect now reflects the real damage the blocked special move would have dealt (1x, not Mirror Coat's 2x), instead of a flat 1/4 HP.

## v0.1.23
- Spell Reflect (Protection, Steel, 3 PP, priority +4): blocks special attacks this turn and throws them back, so the attacker loses 1/4 of its max HP. Not true Mirror Coat damage yet.
- Sweeping Strikes (Arms/Fury, 5 PP): for 4 turns, the user's single-target attacks hit every foe.
- Learned at 44 (Arms/Fury: Sweeping Strikes, Protection: Spell Reflect).
- Bleed confirmed absent from this codebase; Rend still poisons.

## v0.1.22
- Warrior rage display (interim): a battle message "<name>'s rage: N/10" whenever a Warrior's rage changes. A healthbox number or bar is still wanted but needs on-screen testing.

## v0.1.21
- Warrior rage (stage 2): new rage counter (max 10, resets on switch-out). Warriors gain 1 rage when they damage an opponent and 1 when an opponent damages them. Rage-cost moves fail if you can't afford them.
- New moves: Mortal Strike (4 rage, 60 power, heal block), Execute (spends all rage, 15 power per point), Charge! (first turn only, slows the foe, +5 rage), Victory Rush (heals 25% after a KO), Rampage (5 rage, 4 hits, +1 crit stage afterwards). Rend now costs 2 rage.
- Abilities live: Sudden Death (20% to refund a move's rage cost), Enrage (a KO raises Attack or Speed at random), Shield Specialization (20% to negate a physical hit).
- Not yet: Spell Reflect, Sweeping Strikes, rage display in battle, bleed (Rend/Whirlwind use poison/plain damage).

## v0.1.20
- Warrior line added (stage 1): Warrior (Fighting) evolves by Moon / Sun / Shiny Stone into Arms, Fury or Protection (all Fighting/Steel). Placeholder sprites: Timburr, Machamp, Mienshao, Bastiodon.
- New moves: Sunder Armor (-3 Def), Battle Shout, Command Shout (heal 40% self + ally), Colossus, Challenge (Warrior Taunt, Follow Me redirect), W. Whirlwind, Rend (poisons; bleed isn't implemented).
- New abilities registered (effects pending): Sudden Death, Enrage, Shield Specialization.
- Test NPC now also gives a level 5 Warrior and Moon/Sun/Shiny Stones.
- Not yet in: rage counter, rage-cost moves (Mortal Strike, Execute, Rampage, Charge, Victory Rush, Sweeping Strikes, Spell Reflect), ability effects.

## v0.1.19
- Sootopolis B1F filler texts rewritten (Dalaran mages Tiffany, Bethany, Crissy, Olivia; Kul Tiran sailors Bridget, Daphne, Annika).
- Warrior class design notes added (Arms ability: Sudden Death).

## v0.1.18
- Magni's Sootopolis Gym Guide texts (ice cracks then breaks, admiral warning, League foreshadowing).

## v0.1.17
- Jaina (Sootopolis) full text set: defeat, badge, TM, after-fight, Fortree reminder, plaque, rematch placeholders.
- Daelin's title is now ADMIRAL (new trainer class `TRAINER_CLASS_ADMIRAL`).

## v0.1.16 (2026-11-16)
- Daelin uses Drake's overworld and battle sprites. Jaina intro added (body swap with Juan; she keeps Juan's sprite).

## v0.1.15 (2026-11-16)
- Sootopolis: Taelia and Daelin texts, Daelin ace line (trainer slide), Daelin vitamin reward (5 of each, once, `FLAG_RECEIVED_DAELIN_VITAMINS`), Jaina's Articuno (Snow Warning) replacing Alolan Ninetales.

## v0.1.14 (2026-11-16)
- Mekkatorque ace line: trainer slide on his last switch-in (`sTrainerSlides` in `src/trainer_slide.c`, keyed by trainer constant `TRAINER_ANDREA`).

## v0.1.13 (2026-11-16)
- Sootopolis: Taelia moved to the left side of Jaina's room so she no longer blocks access to Jaina.

## v0.1.12 (2026-11-16)
- Sootopolis gym drafted: Jaina (dual weather), Mekkatorque (entrance, 1F), Taelia Fordragon (below Jaina, 1F), secret boss Daelin Proudmoore (top of B1F), seven Dalaran mage / Kul Tiran sailor fillers on B1F. Ice-floor puzzle kept. Trainer and Jaina texts are still vanilla. Test NPC: Sootopolis warp (entry 12). Magni no longer reintroduces himself after Rustboro.

## v0.1.11 (2026-11-16)
- Mossdeep gym texts: all six lieutenants (Nathanos, Varimathras, Arator, Turalyon, Rhonin, Vereesa), the Sylvanas + Alleria double battle, badge/TM text, Magni's guide lines, statue plaque and placeholder rematch lines. Saved in `design/mossdeep-texts.md`.

## v0.1.10 (2026-11-16)
- Mossdeep gym hall shortened (10x31) and decorated: side walls, center runner, statue pairs. Lieutenants now fight in back-to-back pairs two rows apart (Nathanos then Varimathras, Arator then Turalyon, Rhonin then Vereesa), so each pair feels like one chained encounter. Test NPC Mossdeep warp updated.

## v0.1.9 (2026-11-16)
- Mossdeep gym: statue tops added (metatile 516 sits above 524). Map renderer and layout script saved in `wow-docs/tools/`.

## v0.1.8 (2026-11-16)
- Mossdeep gym drafted: six lieutenants (Nathanos, Varimathras, Arator, Turalyon, Rhonin, Vereesa), Hunter's Mark text for opponent Dire Hit, and the Sylvanas + Alleria double battle (see `design/bosses.md`).
- Mossdeep gym map replaced with a straight hall (10x35): enter at the bottom, trainers alternate left and right walls, sisters at the top. Warp pads and rotating-tile puzzle removed. Trainer and sister texts are still the old vanilla texts.
- Test NPC: Mossdeep gym warp (entry 11).

## v0.1.7 (2026-11-16)
- Test NPC: warps for the Petalburg gym (skips the Wally tutorial by setting the gym ready state) and Fortree gym; supplies now include the Windseeker Binding for testing the Thunderaan seal.

## v0.1.6 (2026-11-16)
- Fortree boss-by-boss pass: Anshal (Sitrus Tropius, Castform sun), Nezir (hail: Delibird, Glalie, Alolan Sandslash, Swanna, Castform), Rohash (Shiftry Wind Rider, Castform rain), Faceless One (toned down, Octillery, Explosion Claydol, Will Suicide AI), Thunderaan (5 mons: Mega Pidgeot added, Altaria without Roost). AI test: Castform uses Weather Ball once weather is set.

## v0.1.5 (2026-11-16)
- Fortree gym draft (Prince Thunderaan, Conclave of the Wind, Faceless One), Windseeker Binding from the Ragnaros scene, sealing scene giving Thunderfury (placeholder item, no effect yet).

## v0.1.4 (2026-11-16)
- Petalburg gym first draft: Scott in Norman's body (humor cameo), 4-mon team, gym trainers swapped to Swimmer/Black Belt/Beauty with 2 mons each and "stunned by Scott" lines, Magni confused guide text, one-time vitamins from Scott.

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
