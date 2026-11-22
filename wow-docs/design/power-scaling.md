# Power-level scaling plan (Elite Four and Champion)

Model: `wow-tools/power_model_stats.py` (parses base stats) then `wow-tools/power_model.py`. It is a rough relative rating, not a battle sim. Rerun it after any team change.

## Method
- Combat rating per mon: `sqrt(Offense x Bulk) x speed factor x utility`, from real level-58/60 stats.
  - Offense = best of Atk/SpA, times item (Life Orb 1.25, Specs/Band 1.3, others ~1.05-1.1).
  - Bulk = HP x sqrt(Def x SpD), times Leftovers/Sitrus/Assault Vest style factors.
  - Utility: +3% per control move (Taunt, Thunder Wave, Will-O-Wisp, Encore, Toxic, Protect, Trick Room, Dark Void), +6% per setup move.
- Enemy mons: IV 31, **EV 0**, neutral nature (as written in `trainers.party`).
- Boss hazard multiplier (my estimate of how much the hazard handicaps the player): N'Zoth 1.08, Y'shaarj 1.10, Yogg-Saron 1.08, Xal'atath 1.12, Dimensius 1.15.
- Player pool: every species in `pokemon-stages.csv` except "extremely rare", BST >= 470, plus the class species. Best six by rating at level 60.
- Player scenarios: **casual** (IV 22, no EVs, no nature, Leftovers), **informed** (IV 28, 252 HP + 252 offense, +10% nature, Life Orb), **optimized** (IV 31, same plus setup/control moves).

## Results (team rating, higher is stronger)
| Boss | Raw | With hazard | vs casual | vs informed | vs optimized |
|---|---|---|---|---|---|
| Sidney / N'Zoth | 380 | 410 | 1.17 | 0.82 | 0.76 |
| Glacia / Yogg-Saron | 363 | 392 | 1.12 | 0.79 | 0.73 |
| Drake / Xal'atath | 393 | 440 | 1.25 | 0.88 | 0.82 |
| Phoebe / Y'shaarj | 405 | 446 | 1.27 | 0.89 | 0.83 |
| Champion / Dimensius | 435 | 500 | 1.42 | 1.00 | 0.93 |

Player team rating at L60: casual 351, informed 499, optimized 539. A ratio above 1.0 means the boss is stronger than that player.

## Reading
- A casual player (no EV training) faces a real uphill fight everywhere, worst at the Champion (1.42).
- An informed player who trains EVs and picks natures **out-powers every Elite Four member** (0.79-0.89) and only ties the Champion. The EV/nature gap (about +40%) is the biggest lever in the game, because trainer mons currently have 0 EVs.
- The classes help but little in this rating: a class mon adds about +13 rating (+2.6% team) over the best non-class pick, so 2 and 3 class mons add about +5% and +8%. Class value is mostly in moves and mechanics (Runic Power, Rage, Seals, etc.) that this model does not capture.

## Recommendations (to decide together)
1. Give boss and gym mons EVs. Roughly +5% rating per 85 EVs on every stat. About 150-200 EVs each moves the Elite Four to 0.95-1.05 against the informed player, an even fight, while casual players stay well behind. This is the cheapest lever and does not change the teams.
2. Use the Champion as the true wall. He is already 1.00 against the informed player before EVs, so he needs fewer extra boosts than the Elite Four.
3. More than one WoW class is NOT necessary to reach the target difficulty. It is a gentle lever (+5% for a second class mon, +8% for a third). Use it as a reward or a second-playthrough option, not as the main balance tool.
4. Do not stack many levers at once: EVs on bosses plus a second class would swing a fight by 10% or more together.

## Caveats
Not modeled: type matchups, move choice and AI mistakes, player switching and healing items, the five-fight Elite Four gauntlet (attrition), real hazard impact, rival fights and player team availability by stage. The hazard multipliers are guesses and are the least trustworthy numbers. Playtest results should replace them.

## Status
- v0.1.57: boss EVs applied (170 each stat). Rerun the model and playtest to confirm the ratios.
