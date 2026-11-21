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
| Tony | Magma | Marksmanship Hunter | Draft team: Indeedee, Primarina, Skeledirge, Eevee, Ampharos |
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
**Team Magma (6 friends):**
- Maxie: Sam (19 lines, plot critical, Dragon-heavy team fits the Hideout/Space Center boss role).
- Tabitha: Tony (11 battle-text lines; Magma Hideout 4F, Mt. Chimney, Space Center).
- Magma Hideout / Mt. Chimney grunt slots: Flynn and Markus (a few lines each, can be combined across several grunt objects).
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

## Open questions for Charlie
1. Teams for Flynn, Markus, Steve, Dray, Chase, Div and Alms (they are not in the draft table). Default: their class mon plus their favorites, rounded out by Claude.
2. Austin: assign a slot, or keep him out?
3. Approve the slot draft above, or reassign.
