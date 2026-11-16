# Playtest feedback and design inspiration notes

Source: Google Sheet "WoP Playtest, Documentation & Feedback" (May 2025), tabs *Adam Feedback*, *Ed Feedback*, *Sam Feedback*, *Flynn Feedback*. Each tester had their own tab with the same layout. Only Adam's tab has results. The other three are still blank templates.

Columns to fill per boss: attempts, nuzlocke run?, difficulty 1-5, comments.

## Adam's results (nuzlocke: "eh" for all)

| Area | Boss | Attempts | Difficulty (1-5) | Comments |
|---|---|---|---|---|
| Petalburg Woods | Velithe | 2 | 3 | |
| Rustboro Gym | Twin Emperor 1 | 1 | 1 | Didn't feel like the tanky ones did anything. Their kit made him expect annoyance, but they "just kind of died and didnt attack me". |
| Rustboro Gym | Twin Emperor 2 | 1 | 1 | Both incentivised special moves, or non-contact physical. |
| Rustboro Gym | Princess Huhuran | 1 | 3 | |
| Rustboro Gym | Ossirian the Unscarred | 2 | 4 | |
| Rustboro Gym | C'Thun | 2 | 4 | Dislikes the stall Pokémon and wants Ancient Power removed (stated more bluntly in the sheet). |

Dewford, Slateport and Mauville bosses were not rated in any tab.

## Known bugs (from the sheet)

- Some dialogue writes over itself in gyms — likely cause found 2026-11-16: three gym strings lacked the `$` terminator (Marc defeat, Bulk Up explanation, Ben intro) and are now fixed; please confirm in-game and tell me if overlap remains
- Custom mons sometimes hover (display issue only) — **fixed 2026-11-15**: custom forms reusing Bisharp/Ralts/Froslass/Delphox/Nihilego sprites now copy that species' front/back size, Y offset and enemy elevation. Death Knight base form uses its own sprite and still needs checking in-game.

- Mauville Gym: stray pressed-switch tiles appear after beating Wattson, and two NPC lines still mention switches (see [../design/boss-and-gym-method.md](../design/boss-and-gym-method.md)); gym is completable

## Requested general feedback

The sheet asks testers for extra feedback on dialogue, encounters, "coolness factors", balance and bugs.

## Design inspiration notes per boss

Same notes as the *Inspiration notes* column in the sheets, kept here so the intent of each fight is recorded next to the feedback.

| Area | Boss (original) | Inspiration |
|---|---|---|
| Petalburg Woods | Velithe | Indecisive, has Fire and Water Pokémon, plus his favourite |
| Rustboro Gym | Twin Emperors (Tommy, Josh) | One has insane physical defence, one insane special defence. They also like to swap positions. |
| Rustboro Gym | Princess Huhuran (Marc) | High Poison and Bug damage, with crits |
| Rustboro Gym | Ossirian the Unscarred (Allen) | Pokémon that suit his boss arena: pillars and Egyptian gods |
| Rustboro Gym | C'Thun (Roxanne) | Rock Pokémon with a focus on darkness, sandstorms, confusion and Cosmic Power. Lots of variance; considered pulling back but it's very thematic. |
| Rusturf Tunnel | Polerodeo (grunt) | Favourite Pokémon: Abra and a cat |
| Dewford Gym | Nazgrim (Cristian) | Basic Fighting-type stuff |
| Dewford Gym | Blackfuse (Brenden) | Steel, Poison, playing unfair |
| Dewford Gym | Zaela (Lilith) | Dragons |
| Dewford Gym | Garrosh (Brawly) | "Big fight man". Granbull is the ace because of its tusks. |
| Slateport Museum | Alms (grunt 1), Div (grunt 2) | Water-focused teams somewhat based on themselves |
| Mauville Gym | Jin'Rokh (Kirk) | Interacts with puddles of water and electrocution; also a squirrely Mienfoo with Fake Out and U-turn |
| Mauville Gym | Tortos (Angelo) | A turtle. Uses turtles and stalls. |
| Mauville Gym | Ra-Den (Shawn) | One big guy: set up Electric Terrain, explode, send out a big guy |
| Mauville Gym | Lei Shen (Wattson) | Electric doubles battle focused on protecting Raikou |

## How to use this file going forward

When a new playtester or run is recorded, add a `## <Name>'s results` section in the same format instead of creating another tab.

## Death Knight sprites (2026-11-15)
- Base Death Knight: Pawniard art. Blood: Bisharp (red). Frost: Bisharp recolored light blue. Unholy: Bisharp recolored green.
- Done as palette swaps only (`graphics/pokemon/deathknight/{frost,unholy}_{normal,shiny}.pal`); pixel art is shared with Bisharp.
- Shinies: Blood keeps Bisharp's purple, Frost shiny is red, Unholy shiny is orange.
- Party/PC icons still use Bisharp's shared icon palette (red-ish); recoloring needs a custom icon palette slot.

## Mage sprites (2026-11-16)
- Base Mage: Ralts (green). Frost / Fire / Arcane: Gardevoir recolored light blue / orange / light purple (green slots swapped; palettes in `graphics/pokemon/gardevoir/*_mage_*.pal`).
- Shinies: Frost = original green, Fire = yellow, Arcane = Gardevoir's own shiny (teal).
- Evolved forms now use Gardevoir's size/offset values (previously copied from Froslass/Delphox/Nihilego).
- Icons use Gardevoir's shared icon palette (green); recoloring needs custom icon palettes.
