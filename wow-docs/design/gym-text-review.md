# Gym text review (Rustboro, Dewford, Mauville)

Written 2026-11-16 from `data/maps/*_Gym/scripts.inc`. Goal: compare the three finished gyms and list the text that still needs writing. Nothing here changes game text; the prompts are questions for the author.

## How the first two gyms read (the standard to match)

| | Rustboro (Ahn'Qiraj) | Dewford (Orgrimmar) |
|---|---|---|
| Gym Guide | Magni, Scottish voice, long WoW-lore intro, explains new-arrival premise | Magni, same voice, names Garrosh and the Iron Horde |
| Post-victory guide | Hands out loot | Explains the class stones |
| Boss intro | Short, in-character, one epithet ("Twin Emperor, guarded to magic") | Long speeches for Nazgrim and Garrosh |
| Leader | Possession device: Roxanne is controlled, then wakes and thanks you | Garrosh defeat line, then a narrated scene ("The WARCHIEF kneels in silence...") around the badge |
| Statue text | Boss/raid name | Boss/raid name plus "Siege of Orgrimmar" |
| Rematch lines | Vanilla | Vanilla |

Common devices: (1) a Scottish-voiced Magni who frames the gym as a WoW invasion, (2) bosses introduce themselves by name and role, (3) the vanilla leader is a victim of the boss, who is freed on defeat, (4) badge text is rewritten around that story.

## Mauville today

| Text | State | Notes |
|---|---|---|
| Gym Guide advice | **Vanilla** | Still Wattson's electric-type tips and "switch-controlled doors"; the puzzle is gone |
| Gym Guide post-victory | **Vanilla-ish** | "You've powered the door open!" refers to the removed door puzzle |
| Jin'Rokh (Kirk) | Custom | Intro is a one-liner in broken speech; defeat and post-battle are the same line |
| Ra-Den (Shawn) | Custom | Strong, grim intro; post-battle teases Lei Shen |
| Tortos (Angelo) | Placeholder | Intro "ROAAARRRRRR", defeat "...", post-battle is narration |
| Ben | Mixed | Intro is custom (sacrificed trainer); defeat is vanilla; post-battle still says "traps with switches" |
| Vivian | **Unused** | Text exists but the trainer is no longer in the gym |
| Lei Shen (Wattson) | Custom | Good intro; defeat line ends in a sad/proud note; badge scene follows the Dewford pattern |
| Post-battle Wattson, "go forth and endeavor" | **Vanilla** | Cheerful vanilla lines that clash with the possession tone |
| Rematch intro/defeat/post/two-mon lines | **Vanilla** | Same as the first two gyms |
| Statue | Custom | "The Throne of Thunder" |

## Fixed 2026-11-16: three unterminated strings

Three gym strings had no `$` end marker, so the game kept reading whatever came next in memory. **This is the likely cause of the playtest bug "some dialogue writes over itself in gyms"** (needs an in-game check): Rustboro `MarcDefeat`, Dewford `ExplainBulkUp`, Mauville `BenIntro`. All three now end with `$`.

## Small fixes that are obviously typos (not applied)

- Rustboro: Roxanne intro "Arleady" (should be "Already"); Roxanne post-battle "shell- shocked" has a stray space.
- Dewford: statue "HALLF OF FAME" and "SEIGE OF ORGRIMMAR"; "Hall of Fame" line also has a stray space in the guide post-victory ("class  !Use").
- Mauville: Ben intro "All The GYM", "Sacrifice And" (capitalisation), Wattson intro "I could not. / have asked for" (the sentence is cut: "could not" then "have asked").
- Several Mauville and Rustboro lines use `Defeated…` as defeat and post-battle placeholders.

## Prompts for new text (answer any, skip any)

**Gym Guide (Magni), Mauville**
1. What should Magni tell the player about the Thunder King's gym now that there is no switch puzzle? (What does he warn about electric types, Lei Shen, the Thunder King, his Pandaren/Mogu backstory?)
2. After victory, what is Magni's line? The Dewford one explains the class stones; should this one hand out something or just celebrate?

**Trainers**
3. *Jin'Rokh (Kirk):* Is he Lei Shen's servant or an independent storm-spirit-like boss? Give an intro that fits "Breaker of storms", plus a distinct defeat line and a post-battle line.
4. *Tortos (Angelo):* He is currently silent/"ROAAARRR". Do you want him to stay non-verbal (then make defeat and post-battle describe the scene) or speak?
5. *Ra-Den (Shawn):* The post-battle already teases Lei Shen. Keep it, or add something about "deluded heroes" being the player?
6. *Ben:* What is he, a sacrificed trainer or a witness? Rewrite his defeat and post-battle so they match the intro and drop the switch reference.
7. *Vivian:* Cut the text or give her a role (a spare slot for a future boss)?

**Lei Shen (Wattson)**
8. The vanilla post-battle (`WattsonPostBattle`) and `GoForthAndEndeavor` lines are cheerful. Should Wattson remain cheerful after he is freed, or be shaken like Roxanne and Brawly? Give one line each.
9. His defeat line currently ends the fight on Lei Shen's voice. Do you want Wattson to speak first (waking up), as Roxanne does?

**Cross-gym**
10. Rematch lines are vanilla in all three gyms. Do you want a short "boss returned" version for each leader, or should rematches be cut for this game?
11. Do you want the gym statues to name the raid consistently (Ahn'Qiraj, Siege of Orgrimmar, Throne of Thunder)? If so, add the raid to Rustboro's certified text too.

## How to hand text back

Reply with the lines in any order; I will drop them into the right `.string` blocks (keeping `\n`, `\l`, `\p` line widths) and build. Keep lines to about 36 characters per line when you write, or I will wrap them for you.
