# GJT build changelog

The build version is shown at the very start of a new game (Khadgar's intro) and when you talk to the test NPC in the player's bedroom. Source: `data/text/gjt_version.inc`. ROM files are sent as `GJT-WoW-vX.Y.Z.gba` so a phone cannot reuse an older download with the same name. Bump the patch number for every ROM sent.

## v0.1.71
- **Leader EVs rebuilt by role.** The flat per-stat spread from v0.1.70 is gone. Roxanne, Brawly and Wattson are back to no EVs (their IV theming stands). Flannery 216, Norman 288, Winona 360, Tate and Liza 432 and Juan 480 EVs per mon (legal), put into two stats each to fit the mon: attackers get offense plus Speed, bulky mons get HP plus the matching defense, and slow Quiet Camerupt skips Speed.

## v0.1.70
- **(superseded by v0.1.71)** Gym leader first-fight EVs. Leader mons (`TRAINER_<LEADER>_1`) now carry EVs that rise with the gym, matching the vitamins a player has by then: Roxanne 0, Brawly 12, Wattson 24, Flannery 36, Norman 48, Winona 60, Tate and Liza 72, Juan 80 on every stat (total 72 to 480, legal; Elite Four use 85 each). Rematch tiers _2 to _5 are unchanged. This is a difficulty bump from gym 2 on, so watch it in playtest and lower a row if a gym spikes.

## v0.1.69
- Docs and housekeeping only. Counted the vitamins lying on Hoenn routes (34 stat vitamins, 340 EVs, about 23% on top of the gym schedule; see `design/vitamins-and-rewards.md`). Reserved spare flags 0x2F to 0x4F and three vars for the Void arc (`design/reserved-flags.md`). No game logic changed.

## v0.1.68
- **Evolution-stage pass on ordinary trainers.** Audit script compared every party mon's level with the level its evolution chain naturally needs. 100 mons were ahead of their stage; 29 non-boss ones that were 3 or more levels ahead were stepped down to the right stage (e.g. Machoke 22 to Machop, Tentacruel 27 to Tentacool, Aggron 29 to Aron). Left alone on purpose: leaders, Elite Four, Champion, Magma/Aqua leaders and any boss-AI trainers (they keep final forms), mons only 1 to 2 levels early, and parties that deliberately field a whole evolution line (e.g. Tentacool plus Tentacruel). Mons have no explicit movesets, so they use their natural learnset.

## v0.1.67
- **Rematch tiers 2 to 5 differentiated** for all eight leaders. EVs: tier 2 none, tier 3 84/84, tier 4 168/168, tier 5 252/252 in each mon's two main stats (504 total, legal). AI: tier 3 adds Smart Mon Choices, tier 4 adds Omniscient, tier 5 adds Ace Pokemon. Moves: tier 4 swaps one move per mon, tier 5 swaps a second (tier 5 keeps the tier 4 swap). Tier 2 is unchanged. Untested in play.

## v0.1.66
- **Thunderfury is now a real held item** (still `ITEM_GLIMMERING_CHARM`, moved from Key Items to Items, cannot be sold or tossed): the holder deals 10% more damage (`HOLD_EFFECT_GJT_THUNDERFURY` in `GetAttackerItemsModifier`) and each damaging attack from an opponent has a 10% chance to be parried ("X parried the attack with THUNDERFURY!"), handled just before the Protect check in `battle_move_resolution.c`. Untested in game.

## v0.1.65
- **Leader rematch pack.** All eight gym leaders now give their Mega Stone on their first rematch, and their rematch teams (`TRAINER_<LEADER>_2` to `_5`, 4 to 6 mons, same level ranges as before, IV 31) are rebuilt around that Mega: Roxanne/C'Thun Steelix, Brawly/Garrosh Falinks, Wattson/Lei Shen Manectric, Flannery/Ragnaros Camerupt, Norman/Scott Kangaskhan, Winona/Thunderaan Altaria, Tate and Liza/Windrunner Sableye, Juan/Jaina Slowbro. Leader names in the rematch teams now match the WoW names.
- **PokeNav calls** rewritten for all eight (they thank you for freeing them, say they are not ready yet, then offer the rematch). Placeholder-quality; edit freely in `data/text/match_call.inc`.
- **Badge-time stones removed** (gyms 5 to 8). Freed stones re-homed: Excadrite to the Meteor Falls ball, Gardevoirite to the New Mauville ball, Galladite to a Route 120 ball, Gyaradosite into the Aqua group (replacing Slowbronite), Cameruptite out of the Magma group (now Houndoominite, Charizardite X and Y).
- **Flannery returns to the Lavaridge gym** after the Petalburg badge so her rematch is reachable.
- New flags: `FLAG_RECEIVED_FLANNERY_MEGA`, `_NORMAN_`, `_WINONA_`, `_TATELIZA_`, `_JUAN_`.

## v0.1.64
- **Power TMs**: gym TMs upgraded (flags unchanged, texts updated): Rustboro Iron Tail (was Rock Tomb), Dewford Brick Break (was Bulk Up), Mauville Thunderbolt (was Shock Wave), Lavaridge Overheat (kept), Petalburg Facade (kept, Scott's gag), Fortree Earthquake (was Aerial Ace), Mossdeep Shadow Ball (was Calm Mind), Sootopolis Blizzard (was Water Pulse). Table in `wow-docs/design/vitamins-and-rewards.md`.
- **Mega Stones on rematches**: Roxanne's first rematch gives Excadrite, Brawly's gives Falinksite (flags `FLAG_RECEIVED_ROXANNE_MEGA`, `FLAG_RECEIVED_BRAWLY_MEGA`), joining Wattson's Manectite.

## v0.1.63
- **Mega Stones before the Mega Bracelet moved**: Manectite is now Wattson's first rematch reward (flag `FLAG_RECEIVED_WATTSON_MEGA`), Flannery gives none, and Charizardite X joins Y in the Magma Hideout group. Nothing is given before gym 5 now.

## v0.1.62
- **27 Mega Stones placed** (list in `wow-docs/design/mega-stones.md`): gyms 3 to 8 (Tate and Liza give two), a group of three after the Magma Hideout (Maxie) and another after the Aqua Hideout (Matt), five NPC bonus gifts, and nine replacing ordinary items on the ground or hidden. Scripts in `data/scripts/gjt_mega_stones.inc`. Untested in game.
- **Mega Bracelet**: the Mega Ring key item is renamed Mega Bracelet and Norman (gym 5) gives it. Mega Evolution needs it.

## v0.1.61
- **Specialization Stone** (new item "Spec Stone", 5,000): use it from the bag on a class Pokemon, pick the Pokemon, then pick a specialization from a menu (Druid shows four). Base and middle forms evolve into the chosen spec's middle form; final forms switch to the chosen final form. Same item for first spec and respec. Code: `src/gjt_spec_stone.c`, scripts: `data/scripts/gjt_spec_stone.inc`.
- **Where to get it**: Dewford gym guide (replaces the Fire/Water/Leaf stone gift), Lavaridge Pokemon Center after the Flannery badge (a second one, for flexibility), and Lilycove Department Store 3F (5,000, first on the list).
- All class evolution table entries that used Fire/Water/Leaf/Sun/Shiny/Moon/Dawn stones now point at the Spec Stone, so ordinary stones (Mauville mart, etc.) no longer evolve class Pokemon. Non-class Pokemon are unchanged. Untested in game.

## v0.1.60
- **Vitamin scarcity pass**: the Slateport market stall no longer sells vitamins (now Energy Powder, Energy Root, Heal Powder, Revival Herb). Ever Grande Pokemon Center has a vitamin clerk (the old woman NPC, default vitamin price) so players can catch a new team member up right before the League. All 21 mints now cost 5,000 (Lilycove 3F).

## v0.1.59
- **Vitamin reward schedule**: gyms now give 10, 10, 10, 15, 20, 25, 30, 30 vitamins (150 total, 25 of each type) with an even spread of all six types, replacing the old 30-each at gyms 1, 3, 5 and 8 only. Gyms 2, 4, 6 and 7 gained rewards (leader defeat scripts via `data/scripts/gjt_gym_vitamins.inc`).
- **Lilycove Department Store 3F** now sells mints (all 21) instead of vitamins. Design: `wow-docs/design/vitamins-and-rewards.md`.

## v0.1.58
- **Dimensius hazard changed to Singularity**: no more trap. Any of your Pokemon that stays on the field two turns in a row takes 1/8 max HP at end of turn; switching resets the count. Replaces the Black Hole (Magma Storm style) from v0.1.52.
- **Boss EVs made legal**: Elite Four and Champion mons now have 85 EVs in each stat (510 total, 0 Speed on Sidney's slow Trick Room mons), replacing the 170-each placeholder.

## v0.1.57
- **Boss EVs**: every Elite Four and Champion mon now has 170 EVs in each stat (0 Speed EVs on Sidney's slow Trick Room mons). Per `wow-docs/design/power-scaling.md`, this should make the E4 an even fight for an EV-trained player while casual players stay behind. Test and tune.

## v0.1.56
- **New trainer pics**: Drake (Xal'atath) is now an original elven void-sorceress sprite and the Champion (Dimensius) is an original horned void colossus over a consumed globe. Both are placeholder art generated procedurally (scripts in `wow-tools/sprites/`), 64x64, 16 colors, replacing `elite_four_drake.png` and `champion_wallace.png`. Drake/Champion names and intro text are unchanged.

## v0.1.55
- **All five Elite Four / Champion teams finalized** with a control-leaning moveset pass (about three attacks plus one utility: Taunt, Thunder Wave, Will-O-Wisp, Encore, Toxic, Protect). Sidney's Palkia is Origin Palkia (Lustrous Globe) and he has Protect on Dhelmise/Palkia. Phoebe: Focus Sash Kleavor, Mesprit Calm Mind. Glacia: Razor Claw Weavile, Swords Dance only on Mimikyu. Drake: Taunt/Foul Play on the whisperers, Night Slash Kartana. Champion Wallace (Dimensius): Dusknoir (Trick Room), Deoxys, Dialga, Lunala, Necrozma, Eternatus. Eternamax not used. Untested.

## v0.1.54
- **Sidney is now a double battle with a Trick Room team**: Malamar (sets the room), slow Tentacruel, Octillery, Dhelmise (0 Speed IVs, Speed-lowering natures), then fast closers Darkrai and Palkia. Toxic Spikes and Absol/Toxapex dropped. Phoebe's Mesprit now has Calm Mind instead of Trick Room.

## v0.1.53
- **Elite Four teams (first four)**, level 58-60, themed on their old gods. Sidney/N'Zoth: Malamar, Tentacruel, Octillery, Absol, Darkrai, Palkia. Phoebe/Y'shaarj: Mesprit (Trick Room), Kleavor (Stone Axe), Scizor, Genesect, Hydreigon, Yveltal. Glacia/Yogg-Saron: Mega Froslass lead, Hisuian Zoroark, Mimikyu, Weavile, Kyurem, Guzzlord. Drake/Xal'atath: Gothitelle, Sableye, Kartana, Tyranitar, Mega Mewtwo Y, Giratina. Champion still vanilla. Untested on emulator (Mega use by trainers unverified).

## v0.1.52
- **Elite Four hazards, part 2.** Glacia / Yogg-Saron "Memories of Betrayal": at end of turn an echo of your last move hits you for 1/8 of the damage it dealt; a status move echoes for 1/8 max HP but fizzles 50% of the time. Drake / Xal'atath "Her Master Plan": whenever your stats are raised, her active mon gets the same raises. Champion Wallace / Dimensius "Black Hole": a Magma Storm that never expires (1/8 HP per turn, traps your Pokemon, reapplies if broken). Untested on emulator.

## v0.1.51
- **Elite Four hazards, part 1** (`src/gjt_elite_four.c`, keyed to trainer id). Sidney / N'Zoth, "Rumors of the Deep": your Pokemon alternate on switch-in (lead included), first confusion, then a Whirlpool bind credited to N'Zoth's active mon. Phoebe / Y'shaarj, "The Sha": after your Pokemon uses a move, physical = Sha of Anger (you are Taunted), status = Sha of Pride (1/8 max HP), special = Sha of Violence (-1 crit stage, stacks, clears on switch). Untested on emulator. Design in `wow-docs/design/elite-four.md`.

## v0.1.50
- Encounter tables now stack about 9 distinct species over the 12 land slots (top species about 25%), closer to the hand-made early tables. Every species in the list still appears somewhere. Seafloor Cavern and Cave of Origin are rebuilt (no more Zubat-only), and Charmeleon is a rare Magma Hideout 4F night encounter. Tables regenerated, so slots shift again.

## v0.1.49
- Type balance: added Fairy (Snubbull, Spritzee), Electric (Plusle, Pachirisu) and Ice (Snorunt, Cubchoo) to the encounter list and worked them into routes 112-114 and 119-123, Jagged Pass and the Mauville/Shoal areas. Encounter tables were regenerated, so individual slots differ from v0.1.48.

## v0.1.48
- **Encounter tables rebuilt** from the new species/stage/rarity list (`wow-docs/data/pokemon-stages.csv`). Early routes keep their Day tables; mid and late routes, caves, Safari Zone and sea routes are rebuilt by theme. Rarity decides the slot (common on top, rare in the 4% slots, extremely rare only in hand-placed 1% slots: Mew, Jirachi, Landorus, Tornadus, Thundurus, Chi-Yu).
- **Day/night encounters on.** 70 maps got a `_Night` land table (more Dark/Ghost/Poison/Psychic). Morning and evening use the Day table. Needs a clock: if your emulator has no RTC, you'll only see one of the two tables.
- Details and per-map lists: `wow-docs/design/encounter-tables.md`; tool: `wow-tools/rebuild_encounters.py`.

## Tooling (no ROM): mandatory-trainer finder
- `wow-tools/mandatory_trainers.py` finds which trainers are unavoidable between a map's entrances/exits (path search that avoids sight lines). `MAP_X` for one map, `--all` writes `wow-docs/design/mandatory-trainers.md` (scan of every map). Limits: per-map only (multi-floor dungeons need manual chaining), ledges one-way, water/NPCs block, elevation and bridges ignored.

## v0.1.47
- **Trainer pass retuned (v0.1.46 was too hard).** Held items are now scarce: none below level 20; level 20-34 only some aces (Sitrus Berry/Leftovers); level 35+ aces get Life Orb/Leftovers, some unevolved mons Eviolite, a few Sitrus Berries. Extra mons now only go to trainers with 2 or fewer mons whose top level is 15+ (so early routes are unchanged).

## v0.1.46
- **Trainer difficulty pass.** 692 regular trainers (routes, class trainers, grunts, admins and their rematches) now carry held items and most gained one extra Pokémon (cap 6, only trainers with a mon at level 8+). Skipped: gym leaders, Elite Four, Champion, rivals, frontier heads, and every trainer that already had hand-picked items.
- Items: Eviolite on unevolved mons (level 10+); Oran/Sitrus Berry below level 20; at 20+ the ace gets Life Orb (strong attackers) or Leftovers (bulky), the lead gets Focus Sash, others Sitrus Berry/Leftovers.
- Extra mons are copied from another trainer of the same class at a similar level, at the party's top level. Script used: one-off, results are in `src/data/trainers.party`.
- Not done: gym leader/E4 retune, level bumps, middle-form usage by trainers.

## v0.1.45
- **Three-stage class evolutions.** Base + spec stone now gives a middle form (same name/art/ability as the final spec, BST about 465); middle evolves to the final at level 34. 25 new species (ids 1612-1636) covering DK, Mage, Warrior, Shaman, Druid, Monk, Paladin, Hunter.
- Druid/Warrior species checks go through `NormalizeClassSpecies` so middle forms behave like finals.
- **Save safety:** dex flag area fixed at 256 bytes (new species no longer shift the save). Added `VAR_GJT_SAVE_VERSION` stamped on load. NOTE: this changes the save layout once, so saves from v0.1.44 and earlier will not load correctly.

## v0.1.44
- **Maxie is now SAM, Archie is now ED** (stand-in sprites; names, speaker tags and mentions in other characters' text changed).
- Sam fields a sun team (Torkoal with Drought, Dragon line, Miltank, Cloyster, Blood DK). Ed fields a rain team (Pelipper with Drizzle, Kingdra, Barraskewda, Brew Monk, Blastoise).
- Two new Ed battles: Slateport Harbor and Meteor Falls (new trainers 855 and 856).

## v0.1.43
- **Tame Beast** (move 967, Beast Hunter learns it at 10): catch a wild Pokémon as your one pet. Odds are a Poké Ball's x1.5, no ball needed. The pet fights with +10% Atk/Def/SpA/SpD/Spe and Spirit Bond. Fails on trainers or if you already have a pet.

## v0.1.42
- **Hunter class added** (Accelgor art, recolored). Hunter (Bug, Compound Eyes), Beast Hunter (Spirit Bond), Marks Hunter (Trueshot Aura), Surv Hunter (Bug/Fighting, Relentless Hunter). Khadgar and the test guide hand out Hunter.
- New moves (954-966): Concussive Shot, Arcane Shot, Serpent Sting, Raptor Strike, Steady Shot, Immolation/Snake/Freezing Trap (consumed on first affected switch-in), Disengage, Kill Command, Sniper Shot, Mongoose Bite (needs a missed attack first), Chimaera Shot.
- **Tame Beast and forced doubles are not in yet.** Spirit Bond treats the doubles partner as the pet for now. Learnsets are drafts. Tests: `hunter.c` (11).

## v0.1.41
- **Paladin class added** (Bisharp art recolored by spec). Species: Paladin (Steel/Fairy, Justified), Prot Paladin (Devotion Aura), Holy Paladin (Concentration Aura), Ret Paladin (Steel/Fire, Retribution Aura). Khadgar and the test guide hand out Paladin.
- New moves (940-953): Avenger's Shield, Blessing of Kings/Wisdom/Might, Avenging Wrath, Holy Shock, Consecration, Repentance, Holy Strike, Seals of Light/Command/Justice, Judgement, plus a hidden Command Strike.
- Judgement consumes the active seal (my default, tell me if you'd rather it keep it). Learnsets are drafts. Tests: `paladin.c`.

## v0.1.40
- **Monk class added.** Four species on recolored Sawk art (sea-green skin; belt: brown base, white Mistweaver, orange Brewmaster, red Windwalker): Monk (Fairy, Limber), Mist Monk (Fairy), Brew Monk (Fire/Fairy), Wind Monk (Fairy/Fighting). Stats are the approved draft: Brewmaster 115/95/105/65/95/60, Windwalker 85/120/80/60/80/115. Evolve by Moon Stone (Mistweaver), Sun Stone (Brewmaster) or Shiny Stone (Windwalker). Khadgar and the test guide hand out Monk.
- New moves (ids 928-939): Tiger Palm, Rising Sun Kick (2 PP), Blackout Kick (2 hits, 20% per hit to refund a Rising Sun Kick PP), Spinning Crane Kick (one 60-power spread hit, because the engine can't multi-hit spread moves), Jade Lightning, Whirling Dragon (needs Rising Sun Kick and Blackout Kick used first, then resets both), Keg Smash (-1 accuracy, soaks the foe in liquor), Breath of Fire (35% burn, 100% and consumes the liquor), Purifying Brew, Celestial Brew, Life Cocoon (free Substitute + Aqua Ring, 1 PP), Ring of Peace (protect; physical attackers lose 1 Speed).
- New abilities: **Stagger** (Brewmaster: incoming damage -25%, each hit adds a stagger level up to 3, ticking 1/16, 1/8, 1/4 max HP per turn; the level eases down 1 per turn it isn't hit; level 3 gives +1 Atk and +1 Speed), **Soothing Mist** (Mistweaver: double Shell Bell that heals the lowest-HP party member, benched mons included), **Combo Strikes** (Windwalker: +20% damage when not repeating the previous move).
- Purifying Brew banks the stagger cleared (up to 3 stacks). Celestial Brew turns the stacks into a shield worth 25/50/100% max HP that absorbs damage until switch-out.
- Learnsets are first drafts. Tests: `monk.c` (11 tests).

## v0.1.39
- Warrior's Charge lost its exclamation point.

## v0.1.38
- Moonfire power 40 -> 20.
- Charge (Warrior) now has +1 priority. Still first turn only after switch-in, -1 foe Speed, +5 rage.
- A Druid trainer (Hiker, right wall at 12,5) now stands in the 1F of 15 Pokémon Centers using the standard layout (Oldale, Petalburg, Rustboro, Dewford, Slateport, Mauville, Verdanturf, Fallarbor, Fortree, Lilycove, Mossdeep, Sootopolis, Pacifidlog, Ever Grande, Battle Frontier). Lavaridge's center has its own layout and is not done.

## v0.1.37
- Khadgar's class picker now offers Warrior, Shaman and Druid alongside Death Knight and Mage.
- Druid forms have their own allowed-move lists (`IsMoveAllowedInDruidForm`). Each form takes its own affinity moves plus a shared list; Moonfire is open to all. Bear: Growl, Vine Whip, Bulk Up, Rock Throw, Rock Slide, Body Press, Stone Edge, Earthquake. Cat: Growl, Vine Whip, Razor Leaf, Quick Attack, Slash, Poison Jab, X-Scissor, Swords Dance. Tree: Leech Seed, Mega Drain, Synthesis, Aromatherapy, Giga Drain, Ingrain, Solar Beam. Owlkin: Leech Seed, Fairy Wind, Disarming Voice, Energy Ball, Dazzling Gleam, Calm Mind, Moonblast, Solar Beam. The trainer menu only lists allowed moves, and a disallowed stored move is skipped in battle.

## v0.1.36
- Druid trainer menu (test guide in the bedroom, new "DRUID TRAINER" option). Pick a Druid, a form (Bear, Cat, plus Tree for Resto and Owlkin for Boomy), a slot, then a move. Known moves = the Druid's learnset up to its level, minus the shift moves. "Clear slot" leaves a slot empty and it stays empty (no auto-fill). Picking a move already in another slot of that form moves it.
- Becomes a real NPC once a town is chosen.

## v0.1.35
- Druid form loadouts. Shifting swaps the move list: each form has up to 3 assigned moves plus Unshift (always last). Base form keeps the Pokémon's own moves.
- Bear and Cat moves (and Unshift) no longer take normal move slots. They are auto-assigned to their form as learned (first 3, in level order). A 4th one waits for the Druid trainer NPC (not built yet).
- Tree Form auto-fills with Resto's heals and Owlkin Form with Boomy's spells (Wrath, Starfire, Starsurge, Celestial Alignment). These are also normal moves.
- Form moves keep their own PP. It is saved per Druid in SaveBlock3 (20 Druids, 800 bytes) and refilled at a Pokémon Center. Base-move PP is untouched by shifting.
- To switch forms you now Unshift first (Unshift is in every form's list).
- Moved 3 class statics from IWRAM to EWRAM.

## v0.1.34
- Shared Druid moves: Wrath (Grass special, 45, lv6), Moonfire (Fairy special, 40, always burns, lv10). Rake moved to lv18.
- Boomy: Starfire (Grass special 80, 20% lower Sp. Def, lv26), Starsurge (Fairy special 70, 20% +1 Sp. Atk, lv32), Solar Beam (lv40, no charge turn in Owlkin Form), Celestial Alignment (lv46, Boomy only, 1 PP: +2 Sp. Atk and +1 crit stage for 2 turns, then both removed).
- Resto: Rejuvenation (lv14, self or ally, no upfront heal, 1/8 max HP at the end of each of 3 turns, stacks with the Efflorescence bloom), Swiftmend (lv30, consumes Rejuvenation, heals 50%, fails without it), Wild Growth (lv38, user and ally 25%), Solar Beam (lv40), Tranquility (lv50, whole team 35%, +1 Sp. Def, 1 PP).
- Tranquility's and Celestial Alignment's stat changes apply silently (no "rose" message yet).

## v0.1.33
- Feral combo points (cap 5, shown after each change). Shred (Normal, 40 power, +1 point, +2 on a crit, always crits the first turn after switching in or shifting form), Rake (Grass, 35 power, always poisons, +1), Ferocious Bite (Normal, 20 power +20 per point, spends all). All need Cat Form.
- Bear rage: a Druid in Bear Form builds rage exactly like the Warrior (+1 hitting, +1 being hit, cap 10). Maul (Rock, 70, costs 3), Mangle (Rock, 45, +2 rage), Ironfur (+2 Def, costs 4), Thrash (Grass, 50, hits both foes, +2 rage, 35% poison), Frenzied Regen (heals 60%, costs 5). All need Bear Form.
- Survival Instincts is now once per battle, not per switch-in.
- Learnsets: Feral Rake 16, Shred 20, Ferocious Bite 24. Guardian Maul 18, Thrash 22, Ironfur 26, Mangle 28, Frenzied Regen 34.
- Still to come: Boomy and Resto moves, Moonfire, Wrath.

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
