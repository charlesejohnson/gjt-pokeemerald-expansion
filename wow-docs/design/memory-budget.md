# Memory budget (measured 2026-11-19, build v0.1.34)

Numbers come from the built ELF and a compile of the real structs, not estimates, unless marked *est.*

## ROM (32 MiB = 33,554,432 B)
- Used: 26,733,348 B (79.7%). **Free: 6,821,084 B (6.5 MiB).**
- Biggest consumers: overworld sprites 1.5 MB, mon front pics 1.5 MB, mon icons 1.4 MB, back pics 0.9 MB, battle anims 0.45 MB, fonts 0.4 MB, species info table 0.41 MB (264 B per species), tilesets 0.35 MB, metatiles 0.26 MB, trainer slides 0.26 MB.
- Per-item costs (*est.*, from average symbol sizes):
  - Recolored species (reuses existing art): ~0.6 KB (info 264 B, learnset ~120 B, name and dex text ~150 B, two palettes ~80 B).
  - Fully new-art species: ~3.3 KB (adds front pic ~1.05 KB, back pic ~0.6 KB, icon ~1.0 KB).
  - Move: ~0.15 KB data plus 0.1 to 0.3 KB script or code. Ability: similar.
- Remaining classes (Hunter, Priest, Rogue, Paladin, Warlock, Demon Hunter, Evoker, Monk): about 15 to 20 KB each if recolored, up to about 50 KB each with all-new art. **Worst case for all 8: ~0.4 MB (6% of free).**
- That leaves ≥ 6.1 MiB for maps, tilesets, bosses, trainer pics, music, text and cutscenes. ROM is not the constraint for classes.

## Species, move and ability IDs
- Species: custom ids run 1581 to 1599. Box mons store species in 11 bits, so the cap is 2047: **~448 species left** (each also costs 264 B in gSpeciesInfo). Remaining classes need roughly 50 to 90.
- Moves: 928 used, 2047 cap (11 bits). Abilities: 333 used.

## Save data (per slot; 14 sectors of 3,968 B plus a 116 B SaveBlock3 chunk each)
| Block | Used | Capacity | Free |
|---|---|---|---|
| SaveBlock1 (4 sectors) | 15,572 | 15,872 | **300 B** |
| SaveBlock2 (1 sector) | 3,884 | 3,968 | **84 B** |
| PokemonStorage (9 sectors) | 34,144 | 35,712 | **1,568 B** |
| SaveBlock3 (14 x 116 B) | 4 | 1,624 | **~1,620 B** |

SaveBlock1 and 2 are nearly full, so new persistent data goes in SaveBlock3. Boxed mons have only about 19 spare bits total, so per-Pokémon extras (like Druid loadouts) cannot live in the mon itself.

## RAM
- EWRAM (256 KiB): 227,224 B static, of which the heap is 115,968 B. **Free static: ~34.9 KB.** Battle structs (gBattleStruct etc.) come from the heap; peak heap use in battle is not measured (no emulator here).
- IWRAM (32 KiB): 28,380 B used. **Free: ~4.4 KB, and the stack lives in it.** Treat as full. New statics must be `EWRAM_DATA`. (Three statics from v0.1.33/34 were IWRAM by default and were moved, v0.1.35.)
- Battle volatiles are bit-packed into gBattleMons (144 B per battler); the class volatiles added so far total about 25 bits.

## Druid loadout cost (implemented v0.1.35)
- Per Druid: 40 B (key 4 B, 12 move slots x 2 B, 12 PP bytes). 20 entries = 800 B + 1 B of SaveBlock3, leaving ~820 B for other classes. The pool of known moves is derived from the learnset, so only assignments and PP are stored.
- Code: ~3 to 4 KB ROM (shift hook, auto-fill, menu).
