# Elite Four environmental hazards

Code: `src/gjt_elite_four.c`. Hazards apply only in in-game trainer battles against the listed trainer id.

| Member | Boss | Hazard | Status |
|---|---|---|---|
| Sidney | N'Zoth | Rumors of the Deep: player switch-ins alternate confusion (first), then a Whirlpool bind credited to N'Zoth's active mon | built v0.1.51 |
| Phoebe | Y'shaarj | The Sha: physical = Taunt on user; status = 1/8 max HP; special = -1 crit stage (stacking) | built v0.1.51 |
| Glacia | Yogg-Saron | Memories of Betrayal: 1/8 power copy of your last move echoed back at end of turn; status moves 50% fail to harm you | built v0.1.52 |
| Drake | Xal'atath | Her Master Plan: whenever your stats are raised, her active mon gets the same raises | built v0.1.52 |
| Champion | Dimensius | Singularity: a Pokemon of yours that stays in two turns running takes 1/8 max HP at end of turn; switching resets it (no trap) | built v0.1.52 |

Echo details: damaging echo = 1/8 of the damage dealt (ignored if under 8); status echo = 1/8 max HP, 50% fizzle. Black Hole lasts the whole fight and reapplies silently.

Open choices: lead counts as the first switch-in (confusion); Own Tempo/Safeguard still block N'Zoth's confusion; Sha effects ignore abilities.

## Teams (level 58-60, ace last)
- Sidney (DOUBLES, Trick Room): Malamar (sets room), Tentacruel, Octillery, Dhelmise (all slow: 0 Spe IV, Brave/Quiet), Darkrai, Palkia (fast closers)
- Phoebe: Mesprit (leads, Calm Mind), Kleavor (Stone Axe), Scizor, Genesect, Hydreigon, Yveltal
- Glacia: Froslass (Froslassite, Snow Warning), Zoroark-Hisui, Mimikyu, Weavile, Kyurem, Guzzlord
- Drake: Gothitelle (Shadow Tag), Sableye, Kartana, Tyranitar, Mewtwo (Mewtwonite Y), Giratina
- Wallace/Dimensius: Dusknoir (Trick Room lead), Deoxys, Dialga, Lunala, Necrozma, Eternatus (ace)

Movesets and items live in `src/data/trainers.party` (control-leaning pass: ~3 attacks + 1 utility).
