# Vitamin and reward schedule

Battle EV gain is OFF (`B_EV_CAP_TYPE = EV_CAP_NO_GAIN`). Vitamins give +10 EVs each (no 100 cap, up to 252). Mints change nature. This schedule is the main way players build their team, per `power-scaling.md`.

## Gym rewards (v0.1.59)
Even spread over all six vitamin types, totals rise through the game. Extras rotate so the run totals 25 of each type (150 vitamins, 1,500 EVs).

| Gym | Boss | Total | HP Up | Protein | Iron | Calcium | Zinc | Carbos | Where it is given |
|---|---|---|---|---|---|---|---|---|---|
| 1 | Roxanne | 10 | 2 | 2 | 2 | 2 | 1 | 1 | Gym guide, after victory |
| 2 | Brawly | 10 | 2 | 2 | 1 | 1 | 2 | 2 | Leader defeat script |
| 3 | Wattson | 10 | 1 | 1 | 2 | 2 | 2 | 2 | Gym guide, after victory |
| 4 | Flannery | 15 | 3 | 3 | 3 | 2 | 2 | 2 | Leader defeat (Lavaridge Pokemon Center) |
| 5 | Norman | 20 | 3 | 3 | 3 | 4 | 4 | 3 | Scott, after victory |
| 6 | Winona | 25 | 4 | 4 | 4 | 4 | 4 | 5 | Leader defeat script |
| 7 | Tate and Liza | 30 | 5 | 5 | 5 | 5 | 5 | 5 | Leader defeat script |
| 8 | Juan | 30 | 5 | 5 | 5 | 5 | 5 | 5 | Daelin in the Sootopolis gym |

Previously every gym with vitamins gave 30 (5 of each) at gyms 1, 3, 5 and 8 only.

## Shops
- **Lilycove Department Store (3F)**: vitamins removed, now sells all 21 mints (5,000 each).
- **Ever Grande Pokemon Center**: vitamin clerk (replaces the old woman NPC), engine default vitamin price, right before the Elite Four so a new team member can catch up.
- **Slateport market stall**: vitamins removed (sells Energy Powder, Energy Root, Heal Powder, Revival Herb).

## Specialization Stone (v0.1.61)
One universal item, "Spec Stone", for every class (Druid has four specs). Use on a class mon, choose the spec, it evolves. Base and middle forms go to the chosen middle form; final forms switch final form. Respec is only priced (no use limit): Lilycove 3F sells it at 5,000. Story copies: Dewford gym guide (replaces the Fire/Water/Leaf gift) and Lavaridge Pokemon Center after the Heat Badge. Class evolution tables now key on this item, so normal stones do not evolve class mons.

## Gym TMs (v0.1.64)
Only moves already in the TM list can be used without engine work. Rustboro Iron Tail, Dewford Brick Break, Mauville Thunderbolt, Lavaridge Overheat, Petalburg Facade, Fortree Earthquake, Mossdeep Shadow Ball, Sootopolis Blizzard. Power rises through the run. Moves like Stone Edge or Close Combat would need adding to `include/constants/tms_hms.h`, which renumbers TMs and is not save-safe, so they are left out.

## Targets (see power-scaling.md)
Gym rewards alone: about 150 vitamins. Spread evenly over 6 stats it rates near parity with Glacia and Sidney and below Drake, Phoebe and the Champion. Focused on two stats per mon it is closer to the middle bosses. The Ever Grande shop is the catch-up lever.

## Ground vitamins on routes (counted v0.1.69)
Hoenn item balls and hidden items already in the world (FRLG maps ignored, they are not reachable):
| Item | Count |
|---|---|
| HP Up | 5 |
| Protein | 6 |
| Iron | 5 |
| Calcium | 5 |
| Zinc | 7 |
| Carbos | 6 |
| **Stat vitamins total** | **34** (340 EVs) |
| Rare Candy | 16 |
| PP Up / PP Max | 10 / 1 |

Several sit behind Dive (Underwater routes 124/126/127/128), Artisan Cave (five) or Safari Zone, so they land late. They add about 23% on top of the 150 gym vitamins. No stat is bare: each vitamin type gets 5 to 7, so no single stat is favoured. These are kept as a bonus on top of the schedule, not counted in it. If balance feels high in playtest, trade some for PP Ups.

## Other rewards to schedule (not done)
Power TMs, held items (Thunderfury), Mega Stones and a universal Specialization item are to be placed alongside vitamins; see the questions in the chat.
