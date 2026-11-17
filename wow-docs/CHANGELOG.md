# GJT build changelog

The build version is shown at the very start of a new game (Khadgar's intro) and when you talk to the test NPC in the player's bedroom. Source: `data/text/gjt_version.inc`. ROM files are sent as `GJT-WoW-vX.Y.Z.gba` so a phone cannot reuse an older download with the same name. Bump the patch number for every ROM sent.

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
