# Friend casting: replacing NPCs with Charlie's friends

Goal: replace Team Aqua/Magma members and other recurring characters with friends, then map where each appears. Counts are text boxes (`\p` page breaks), measured 2026-11-20 on the gjt branch. Only text with a speaker tag ("MAXIE:") is counted for the general list, so untagged NPC chatter is missing. FRLG maps are excluded.

## Process
1. Charlie lists his friends and the level of appearance each should have (cameo, recurring, boss).
2. Assign friends to slots below. Combining several NPCs into one friend is allowed, so a friend can show up more often and talk more.
3. Map the appearances (which map, which tile, which script).
4. Write the text, then replace the trainer name and sprite.

## Non-gym-leader characters by voice lines
| Character | Boxes | Notes |
|---|---|---|
| Brendan / May | 56 each | gender variants, you meet only one |
| Scott | 45 | already a friend (Norman cameo, Battle Frontier house) |
| Steven | 33 | |
| Wally | 27 | |
| Mr. Briney | 25 | |
| Mom | 24 | |
| Dad (Norman as dad) | 24 | |
| Archie | 21 | |
| Khadgar | 21 | all in the lab |
| Wallace | 20 | |
| Maxie | 19 | |
| Capt. Stern | 18 | |
| Mr. Stone | 15 | |
| Gabby | 14 | TV interviewer |
| Prof. Birch | 9 | |
| Ty | 7 | TV interviewer |

Mauville Old Man (53 boxes) is a minigame script, not real dialogue. TV show text (MC, Fans, Big Sis, Big Bro) is canned.

## Aqua and Magma: named members
| Member | Lines | Appearances |
|---|---|---|
| Archie | 21 | Seafloor Cavern (10), Mt. Chimney, Meteor Falls, Slateport Harbor, Route 128, Mt. Pyre, Sootopolis |
| Maxie | 19 | Space Center, Magma Hideout, Route 128, Mt. Chimney, Seafloor Cavern, Mt. Pyre, Sootopolis |
| Tabitha | 11 (battle text only) | Magma Hideout 4F, Mt. Chimney, Mossdeep Space Center (2v2 with Maxie) |
| Shelly | 12 (battle text only) | Weather Institute 2F, Seafloor Cavern Room 3 |
| Matt | 6 (battle text only) | Aqua Hideout B2F |
| Velithe (hack) | about 8 | Petalburg Woods |
| Polerodeo (hack) | 1 appearance | Rusturf Tunnel |
| Alms and Divinea (hack) | Alms 2 | Slateport museum pair |

Courtney is not in this game.

## Generic grunt slots (object events)
- Aqua, about 60: Slateport 18 (city, harbor, museum), Weather Institute 8, Aqua Hideout 12, Seafloor Cavern 10, Lilycove 5, Route 110 5, plus a few on Routes 119/121, Mt. Pyre, Mt. Chimney, Meteor Falls.
- Magma, about 40: Magma Hideout 14, Mt. Chimney 9, Mossdeep and Space Center 12, Jagged Pass 1, Route 112 2, Meteor Falls 2.
- Each grunt has one short battle text, so these are the cheapest slots.

## Replacement viability (Claude's judgment)
1. Maxie / Archie: best for close friends. Most appearances and lines (about 20 to rewrite each). Plot critical.
2. Tabitha, then Shelly: doable, 2 to 3 battles each.
3. Matt: one battle, cheap, little screen time.
4. Grunts: easiest. About 100 slots, one short battle text each. Good for friends with a cameo level of appearance.

## Friend list (Charlie, 2026-11-21), most frequent first
| Friend | Team | Class mon(s) | Favorites / notes |
|---|---|---|---|
| Sam | Magma (Maxie) | Blood Death Knight; Retribution Paladin in the final showdown | Loves Dragon types. Draft team: Garchomp, Salamence, Cloyster, Dragalge, Miltank |
| Ed | Aqua (Archie) | Brewmaster Monk; Arms Warrior in the final showdown | Loves "meta" picks |
| Vel | Bounces between teams | Frost Mage (switches spec every fight); Enhancement Shaman later | Unown. Already partly done (Velithe). Draft team: Venusaur, Weezing, Sinistcha, Breloom, Swampert |
| Tony | Neutral, replaces Steven (no team) | Marksmanship Hunter | Draft team: Indeedee, Primarina, Skeledirge, Eevee, Ampharos |
| Scott | Norman (done); joins Aqua later for the hideout | Beast Mastery Hunter + a pet (doubles fight is fine) | Already cast as Norman |
| Flynn | Magma | Arcane Mage | Gigalith, Swoobat, Leavanny |
| Div | Aqua (with Alms) | Paladin that later becomes Holy Paladin | Already partly done (Slateport museum pair) |
| Alms | Aqua (with Div) | Hunter that later becomes Beast Mastery | Already partly done |
| Markus | Magma | Elemental Shaman | Totodile, Treecko |
| Steve | Either | Retribution Paladin | Unknown |
| Dray | Either | Protection Paladin | Unknown |
| Tim | Magma (doubles pair with Meg) | Arcane Mage | Draft team: Tinkaton, Slaking, Ludicolo, Alolan Marowak, Blissey |
| Meg | Magma (doubles pair with Tim) | Restoration Druid | Draft team: Porygon-Z, Typhlosion, Scrafty, Volbeat, Jynx |
| Chase | Aqua | Frost Mage | Unknown |
| Austin | Unknown whether already used | n/a | Draft team: Dusknoir, Weavile, Chandelure, Hatterene, Snorlax |

Other draft league teams in Charlie's table (Charlie, Zoey, Malcolm, Adam) are unassigned; a fan-club "draft league" corner could host them later.

## Proposed slot assignment (Claude's draft, for Charlie to approve)
**Neutral:** Tony replaces Steven (33 lines, the biggest non-team slot after the rival). Marksmanship Hunter. Taken out of the Aqua/Magma split.

**Team Magma (5 friends):**
- Maxie: Sam (19 lines, plot critical, Dragon-heavy team fits the Hideout/Space Center boss role).
- Tabitha: Flynn (11 battle-text lines; Magma Hideout 4F, Mt. Chimney, Space Center).
- Magma Hideout / Mt. Chimney grunt slots: Markus (a few lines, can be combined across several grunt objects).
- Tim and Meg: a recurring doubles pair, best at the Mossdeep Space Center grunt cluster (12 grunts) and a Magma Hideout double battle. Same pattern as Alms and Div.

**Team Aqua (6 friends):**
- Archie: Ed (21 lines).
- Shelly: Chase (Weather Institute 2F, Seafloor Cavern Room 3).
- Matt: Steve (Aqua Hideout B2F, one battle) with an extra grunt cameo or two.
- Dray: Aqua grunt cluster (Slateport / Aqua Hideout), could also be a rival-style cameo.
- Div and Alms: keep the Slateport museum pair, add Aqua Hideout and Seafloor Cavern rematches.
- Scott: Norman now; joins Aqua for the hideout later.

**Vel:** Velithe appears on both sides (Petalburg Woods now, a Magma and an Aqua cameo later), so the Frost Mage's spec swap tells the story.
**Final showdown:** Sam gets a Retribution Paladin, Ed an Arms Warrior (needs the Elite Four / Champion arc to exist).

## Mandatory grunt slots (from `wow-tools/mandatory_trainers.py`, 2026-11-21)
Unavoidable fights found by path search (per map; story-forced rooms like the Space Center, Weather Institute and Mt. Chimney are one-way, so treat their grunts as forced too even though the tool lists them optional):
- **Magma Hideout:** 2F_1R grunts 5 and 3; 3F_1R grunts 9 and 16; 4F grunts 11, 12 and 13.
- **Aqua Hideout:** B2F grunts 6 and 8.
- **Seafloor Cavern:** Room 1 grunts 1 and 2; Room 3 grunt 5.
- **Forced by story (tool says optional):** Space Center 1F grunts 1-4, Weather Institute grunts 1 and 4, Mt. Chimney grunts 1 and 2.

Proposed friend placement (not yet built, waiting on Charlie):
- Markus: Magma Hideout 2F_1R grunt 5 (Elemental Shaman), plus Mt. Chimney grunt 2 as a repeat.
- Tim and Meg: Magma Hideout 3F_1R grunts 9 (Tim) and 16 (Meg) as back-to-back singles; their doubles fight at the Space Center grunt cluster (grunts 1 and 3).
- Dray: Aqua Hideout B2F grunt 6 (Protection Paladin) and Seafloor Cavern Room 1 grunt 1.
- Alms and Div: Seafloor Cavern Room 1 grunt 2 (Alms) and Room 3 grunt 5 (Div) as the Aqua rematches.
- Chase: Weather Institute grunt 4 before Shelly; the Shelly fight itself is the main Chase slot.
- Everything else stays a grunt (optional ones are the place for extra friend cameos or rematches).

## Decisions (Charlie, 2026-11-21)
- Slot assignment above is **approved**.
- Teams for the friends not in the draft table: Claude builds them (class mon plus favorites, rounded out).
- **Postgame area (later):** every friend appears there at their strongest.
- **Draft league place (later):** Austin and the other unlisted draft league members (Charlie, Zoey, Malcolm, Adam, others) get a slot in an in-game draft league venue. Candidate location: replace the Slateport beach challenge room. Not implemented yet.

## Mapping: Maxie (Sam) and Archie (Ed)
Ed also loves the **Blastoise line**, so Archie's ace is Blastoise. Levels below keep each fight's current level curve. Species names follow the repo (`SPECIES_DEATHKNIGHT_BLOOD`, `SPECIES_MONK_BREWMASTER`, ...). Teams are Claude's draft.

### Maxie → Sam (3 battles, 7 map appearances, about 19 lines)
| Order | Map | Script / trainer | Now | Draft team |
|---|---|---|---|---|
| 1 | Magma Hideout 4F | `MagmaHideout_4F_EventScript_Maxie`, `TRAINER_MAXIE_MAGMA_HIDEOUT` (5 text boxes) | Mightyena 37, Crobat 38, Camerupt 39 | Gabite 37, Blood Death Knight 38, Cloyster 39 |
| 2 | Mt. Chimney | `MtChimney_EventScript_Maxie`, `TRAINER_MAXIE_MT_CHIMNEY` (Archie cameo in the same map) | Mightyena 24, Zubat 24, Camerupt 25 | Bagon 24, Gible 24, Miltank 25 |
| 3 | Mossdeep Space Center 2F | `MossdeepCity_SpaceCenter_2F_EventScript_Maxie`, `TRAINER_MAXIE_MOSSDEEP` (2v2 with Tabitha, so Sam + Flynn) | Mightyena 42, Crobat 43, Camerupt 44 | Shelgon 42, Blood Death Knight 43, Dragalge 44 |
| cutscene | Mt. Pyre Summit, Route 128, Sootopolis City (also Seafloor Cavern, Meteor Falls cameos) | `MtPyre_Summit_*`, `Route128_*`, `SootopolisCity_EventScript_Maxie*` | no battle | text only |

Note: the Mt. Chimney fight comes first in the game's order (Mt. Chimney before the Hideout is how the story runs), so the L24 team is the earliest Sam sees; Salamence/Garchomp themselves wait for the postgame full team plus the Retribution Paladin.

### Archie → Ed (1 battle, 7 map appearances, about 21 lines)
| Order | Map | Script / trainer | Now | Draft team |
|---|---|---|---|---|
| cameo | Slateport Harbor | `SlateportCity_Harbor_EventScript_*Archie*` | text only | text only |
| cameo | Mt. Chimney, Meteor Falls 1F, Mt. Pyre Summit, Route 128, Sootopolis | various | text only | text only |
| 1 (only battle) | Seafloor Cavern Room 9 (14 labels, the longest chunk) | `SeafloorCavern_Room9_EventScript_ArchieAwakenKyogre`, `TRAINER_ARCHIE` | Mightyena 41, Crobat 41, Sharpedo 43 | Brewmaster Monk 41, a meta pick 41, Blastoise 43 |

Archie fights only once. Suggested fix: give Ed an earlier battle (Slateport Harbor or Meteor Falls, a Wartortle) so he is not just cutscenes until the cavern.

### What the swap changes in code and text
- Trainer rows: `src/data/trainers.party` (`Name:`, `Pic:`, party), then regenerate `trainers.h`.
- Text: the `*_Text_Maxie*` and `*_Text_Archie*` labels in each map's `scripts.inc`/`text.inc`.
- Pics: the trainer and overworld sprites need art for Sam and Ed (not done; ask Charlie).

### Built in v0.1.44 (Charlie approved: favorites + rain/sun spin, stand-in sprites, extra Archie battles)
Trainer names and speaker tags are now **SAM** and **ED** (other characters' dialogue was swapped too, 58 lines). Sprites are stand-ins (Maxie and Archie art).
- Sam (sun): Mt. Chimney L24-25 Bagon, Gible, Torkoal (Drought), Miltank. Magma Hideout L37-39 Torkoal (Drought), Gabite, Miltank, Blood DK, Cloyster. Mossdeep multi L42-44 Torkoal (Drought), Blood DK, Dragalge.
- Ed (rain): Seafloor Cavern L41-44 Pelipper (Drizzle), Kingdra, Barraskewda, Brew Monk, Blastoise (Rain Dish).
- New Ed battles: Slateport Harbor (`TRAINER_ARCHIE_SLATEPORT`, Pelipper 25, Wartortle 27) and Meteor Falls (`TRAINER_ARCHIE_METEOR_FALLS`, Pelipper 31, Barraskewda 32, Wartortle 34). Trainer flag space has 7 spare ids left.
- Ed's meta picks (Kingdra, Barraskewda) are my guesses. Swap them if he has real favorites. Arms Warrior and Retribution Paladin are for the final showdown.
