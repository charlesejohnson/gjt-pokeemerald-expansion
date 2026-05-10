# Design Document: *Pocket Japan* (working title)
> Based on `rh-hideout/pokeemerald-expansion:master`
> Personal fork: `charlesejohnson/gjt-pokeemerald-expansion`
> Last updated: 2026-05-09

---

## 1. High Concept

A Pokemon Emerald ROM hack reskinned as a real Japan trip taken by Charlie, Zoey, and Dana. The player chooses one of the three as their character. The core Pokemon loop (8 badges → champion) is replaced with collecting **8 Memories** across Japan before flying home. Pokemon battles are recontextualized as travel encounters — arguments, cultural moments, games, and social situations. The tone is warm, funny, and personal.


:: a couple top-level notes as we begin scoping more heavily. I think most of the effort here will be in building effective triggers and npc movement, good dialogue, fakemon design, and especially tileset creation and building. I want to really hammer down our process on these bfore we get started, as well as anything esle you think could sneak up on us. a pitch: we should have each of these as epics, and then we can sort my notes into these categories so then individual agents can work on them::

---

## 2. Playable Characters

Each character has a unique starter (fakemon TBD), slightly different dialogue throughout, and a few exclusive side events. The story beats are otherwise shared.

### Charlie
- **Starter:** TBD (table tennis / jazz themed? — open to suggestion) ::let's make it a diverging evolution based on an item gotten from the 2 special adventures, table tennis and jazz club extra. It will be a normal type sphere that becomes a music note (dark/fairy) or a table tennis ball w/ paddle (or stars or something, some way to make the ball identifiable) (normal/fighting).::
- **Exclusive events:** Table tennis minigame (Tokyo Day 2), Jazz bar (Tokyo Day 3), solo "extra adventures" that split from the group
- **Quirk mechanic:** Many NPCs speak only Japanese. Dialogue options are limited to "Nod politely." Over the course of the game, a hidden "Japanese comprehension" stat increases, unlocking more response options and richer NPC interactions. ::let's not change track any hidden stats here. we can make it more understandable as time goes on but that can be hardcoded::
- **Food restriction:** Cannot order soup. (Attempting to triggers a unique "Can't eat soup" scene.) ::I can eat soup, but it makes my clothes messy. Maybe it costs extra for a bib or something?::
- **Language flavor:** Some menus/signs appear partially in Japanese when playing as Charlie.

### Zoey
- **Starter:** Moss-type fakemon (mossy/plant themed, fits Moss Temple memory in Kyoto)
- **Exclusive events:** Shares most adventures with Dana; takes a nap + gets spaghetti (Tokyo Day 3)
- **Food restriction:** Can only purchase vegetarian food at Conbini/restaurants.
- **Quirk:** "Kakkoii koi" — Zoey has a special interaction at the Kyoto koi pond. ::this isn't really a quirk, more of a specific interaction I noted. I have several notes for just specific moments, similar to the mr/ms joke, that shoulnd't be a real mechanical change::

### Dana
- **Starter:** Arty fakemon (aesthetic/creative themed) OR the gacha bunny fakemon from Sapporo (⚑ confirm with Charles) ::definitely gacha bunny, it's cute and small and pink, and maybe it can evolve to be in its gacha ball. Wait I've got an even better idea -- it starts as a coin and becomes a gacha bunny thing by manually evolving it at the gacha place::
- **Exclusive events:** Shares most adventures with Zoey
- **Quirk mechanic:** "Mr/Ms" joke — recurring gag with NPCs misgendering/mis-titling Dana, played as a lighthearted running bit.  ::same note as zoey above::
- **Onsen surcharge:** Dana is charged extra at the onsen. This is a real mechanic (costs extra in-game currency).

---

## 3. Core Mechanic Changes (Skin Layer)

| Pokemon Emerald Concept | This Game's Equivalent |
|---|---|
| Gym Badges | Travel Memories (8 total) |
| Gym Leaders | Memorable Encounters / Experience Gatekeepers |
| Pokemon Champion | Flying home / clearing the airport gauntlet |
| Elite Four | Airport: luggage check → security → customs → gate (4 stages) |
| Pokemon Center (free heal) | **Removed** — healing only via: sleeping between days, onsen visits |
| Pokemart | Conbini (7-Eleven / Lawson) |
| Routes | City streets, train lines, temple paths | ::let's not do train lines as their own routes. Mostly, I'd expect we're on city streets, in buildings (stations or shops, such as kyoto station being gigantic). We will have train routes be connections between different parts of the game. Since it's more narratively driven, we'll lock these modes of transport behind achieving certain memories::
| HM Fly | Shinkansen / domestic flights (costs in-game yen) | ::no need to replace hms, we should just have these other modes of transportation availbale to move between maps::
| HM Surf | Taxi (costs in-game yen) |
| Rival | The other two characters (whichever two you didn't pick) |
| Professor | TBD — travel guide figure? Tour operator? | ::I think I have some broader ideas here -- we can make it a thing where none of us knew that upon showing up to japan, that the tourism board (whatever it's called) both released real pokemon (wow!) into the wild, and are demanding that all toursits get at least 8 memories before they leave the country. this is a funny, polite "in your best interest" very japanese-style thing The minister of tourism (idk the name in japan) would be the professor, in a joking-antagonistic role since he's preventing our leaving.
| Poke Ball | TBD — thematic reskin | ::no reskin to pokeballs needed:

### New Mechanics
- **Sake buff:** NPCs occasionally ask "Would you like to drink sake?" Accepting gives a battle buff but all Pokemon wake up next day at 80% HP.
- **Vending machines:** Scattered across maps, sell healing items cheaply.
- **Day/Night cycle:** Forced narratively. Days end automatically (you can't grind indefinitely in one day). Each new day starts with a Conbini breakfast prompt. ::I'm fine with infinite grinding in one day, but let's implement level caps, potentially remove them with an optional prompt at the beginning of the game?::
- **"Wait, these aren't our umbrellas"** — a recurring event/joke, probably a puzzle or item mix-up mechanic.
- **Plane intro:** On the flight to Japan, the game asks "Would you like to play Pokemon?" → triggers a random battle at 30,000 feet. Flavor text only, no real consequence. ::yes flavor only, but let's make it a real fight! kinda like the opening to pokemon colosseum, where it's just a fun little battle that's against a known trainer like Red, and all our guys are like lvl 60-80 and stronger than him, so it's an easy tutorial-style fight, but it's also a good piece of foreshadowing for what's going to happen, and narratively shows we're already into pokemon.::
- **Transylvanian family:** Optional battle — a Maushold (family of four) for extra pocket change.
- **Shiny Farfetch'd:** Labeled "Beautiful Duck." Rare encounter. ::not really a mechanic, just a note of an event that happens -- this will be on a route in kyoto::

---

## 4. Locations & Memory Structure

Memories are collected roughly in chronological order. Each location has sub-areas accessed via train/taxi.

---

### 🗼 ACT 1 — TOKYO (Days 1–4)

#### Tokyo Day 1 — Arrival
- **Narrative:** Plane lands. Rain. Navigate the airport, take the train into the city.
- **Intro event:** Plane battle (see mechanic above)
- **Sub-areas:** Airport, train platform, hotel district
- **Encounters:** Head massage/treatment parlor (healing event), rainy street NPCs
- **Memory #1:** ⚑ TBD — arrival/first impression memory ::first memory should be head massage::

#### Tokyo Day 2 — Exploration
- **Narrative:** Table tennis (Charlie exclusive), Folk museum, meet at cat cafe, thrift stores
- **Sub-areas:** Cat cafe, folk museum, thrift district
- **Key events:**
  - Cat cafe: healing event (cats restore your team's mood)
  - Thrift stores: buy cosmetic/flavor items ::I think we should have powerful stat raising items such as iron/protein to give EV's. Let's also remove the applicatino of EV's from any other method, so these items have particular value::
  - Table tennis (Charlie): minigame or trainer battle framed as a match ::definitely trainer battles, it's a place where we rotated opponents every 10 min or so. Very nice older people, who spoke almost entirely japanese. Just a casual and friendly place::
- **Memory #2:** ⚑ TBD — cat cafe / folk museum memory ::maybe we make the thrift stores a memory, since we all wound up getting some items we wore a lot the rest of the trip::

#### Tokyo Day 3 — Full Day
- **Narrative:** Yanaka district walk, snacks, cube bakery, lamp shop, old wood man, jewelers, Imperial Garden, Jazz club, onsen
- **Sub-areas:** Yanaka streets, Imperial Garden, Jazz bar, Onsen
- **Key NPCs:**
  - Old wood man (shop owner, sells rare item)
  - Jazz bar musician (battle? or healing event with sake offer)
- **Key items:** Cat tail snack, sweet potato snack (consumable buffs)
- **Zoey exclusive:** Takes a nap; gets spaghetti instead of Japanese food (flavor scene)
- **Charlie exclusive:** Jazz club performance/battle
- **Memory #3:** Jazz club OR Imperial Garden (⚑ confirm) ::definitely jazz club memory::

#### Tokyo Day 4 — Goodbye to Luggage
- **Narrative:** Fly to Sapporo. Send luggage ahead via 7-Eleven (a real Japan thing — luggage forwarding).
- **Event:** 7-Eleven Conbini goodbye scene. Luggage forwarding costs yen.
- **Transition:** Domestic flight to Sapporo (Shinkansen/HM Fly equivalent)

---

### 🍺 ACT 2 — SAPPORO (Days 4–5)

#### Sapporo Day 4 — Arrival Evening
- **Narrative:** Teppanyaki dinner (Zoey very hungry), gacha machines, communal bath
- **Sub-areas:** Teppanyaki restaurant, gacha arcade, hotel
- **Key events:**
  - Teppanyaki: dinner battle/encounter with chef NPC
  - Gacha: item lottery mechanic (spend yen, get random item/cosmetic)
  - "Took a bath together" — communal onsen scene (healing event) ::remove this, this was just about me n zoey taking a bath::
- **Dana mechanic:** Charged extra at onsen here

#### Sapporo Day 5 — Sightseeing
- **Narrative:** Mt. moriyama, Sapporo Beer Museum, wagyu ramen, "Love is Blind Ohio" (⚑ what is this?) ::love is blind is a tv show that our server at the ramen shop liked, and said she wanted to go to ohio because of this::, Milk Mura
- **Sub-areas:** Mt. moriyama ropeway, Beer Museum, ramen shop, Milk Mura
- **Key events:**
  - Mt. moriyama: route-style climb, encounter wild Pokemon, view at top = Memory ::we took a cable car up, but maybe we can add extra routes to walk up as an option, would be extra work here::
  - Beer Museum: sake/beer offer mechanic
  - Milk Mura: healing dairy items (restore HP generously)
- **Memory #4:** Mt. moriyama summit OR Beer Museum (⚑ confirm) ::let's do milk mura, I think it was equally memorable to the mountain and it happened at the end of the day. We can have a ::

---

### ⛩️ ACT 3 — KYOTO (Days 6–8 approx.)

#### Kyoto Day 1 — Thai Massage + Ryokan
- **Narrative:** Thai massage place (fighting-type trainer area), check into Matsumoto Ryokan (no bidet — this is noted as a hardship)
- **Sub-areas:** Thai massage parlor, Ryokan
- **Key mechanic:** Thai massage = "sub-gym." Defeating the fighting-type trainers earns a badge-equivalent with a forced Thai name.
- **NPCs:** Uru and Sai (noisy Japanese men — double battle?)
- **Memory #5:** Thai massage gym win

#### Kyoto Day 2 — Moss Temple + Silk Dying
- **Narrative:** Moss temple, calligraphy, donation box, walk around the circle, silk dying workshop
- **Sub-areas:** Moss temple grounds, calligraphy hall, silk workshop
- **Key NPCs:**
  - Shin-San / Mr. Shin (shop owner or guide)
  - Shova (⚑ who is this? fellow traveler?) ::translator for shin::
  - Maira — Israeli/British person met at some point (⚑ Kyoto or Sapporo?)
- **Wild encounters (Moss Temple):** Clodsire (in water), Yanma, Beetles, Crow, Spinarak, Butterfly Pokemon
- **Zoey starter connection:** Moss temple is where Zoey's starter feels most at home — special dialogue
- **Key event:** "Eigo wa ii desu ka" — NPC asks if English is okay (Charlie's comprehension mechanic moment) ::not quite what happened. A noisy tourist showed up and I was trying to help her understand how to ask if english is okay. She was just only speaking in english not even trying to communicate, which was hilarious to see her lack the social tact. Zoey talked to her for a while because they were both vegetarian::
- **Memory #6:** Moss temple / calligraphy memory ::let's do calligraphy as the memory, but we can have a miniboss at moss temple for fun since it was a big part of the day::

#### Kyoto Day 3 — Tenryuji + Bamboo Forest
- **Narrative:** Shinkansen ticket difficulty, sushi train at Kyoto station, Tenryuji temple, bamboo forest, Nenbutsu-ji temple, old town road, frog place, nice cafe
- **Sub-areas:** Kyoto Station (sushi train), Tenryuji, bamboo forest path, Nenbutsu-ji, cafe
- **Key events:**
  - Shinkansen tickets: puzzle/obstacle before fast travel unlocks
  - Sushi train: conveyor belt = item shop with rotating stock ::let's have this be a fight too -- you can pick a dish that gives a wild pokemoin encounter like tatsugiri, the sushi pokemon, or a vegetable thing for vegetarians::
  - Tenryuji tourist gauntlet: fight through waves of tourist NPCs to reach the garden ::there's also a big bee (mega beedrill? just a really strong beedrill?) in the shoe area before we enter the temple. Let's do a little event on that.
  - Singular red flower on outcropping (flavor landmark, maybe Memory trigger)
  - Bamboo forest: route with escalating difficulty the higher you climb (better rewards at top)
  - Poison ivy: status-inflicting tile on bamboo path
  - Nenbutsu-ji: beautiful gravestones, owl encounters
  - Frog place: (⚑ what is this exactly? Frog shrine? Figurine shop?) :::it's a shop, mostly ceramics that was on the route to the old street that had shops and nenbutsu-ji temple::
  - Dango + yuzu tea: consumable items at the cafe
- **Wild encounters:** Owls (Nenbutsu-ji), swallows (Tenryuji inside), bee (Tenryuji entrance)
- **Memory #7:** Bamboo forest summit OR Tenryuji garden

---

### 🗼 ACT 4 — TOKYO PART 2 (Days 9–11 approx.)

#### Tokyo 2 Day 1 — Split Party
- **Narrative:** Charlie goes to "gym" (table tennis rematch? or new gym). Zoey and Dana go to giant craft store in Ginza (⚑ get store name — Itoya? ::yes itoya::). Group reunites at 12F building (pens, souvenirs, rooftop cafe).
- **Sub-areas:** Ginza craft store, 12F building, Charlie's gym location
- **Key events:**
  - Charlie exclusive: gym/table tennis event
  - Zoey/Dana exclusive: craft store item shopping
  - Haircut + head spa (healing event), Uniqlo (item shop)

#### Tokyo 2 Day 2 — Anime + Night Out
- **Narrative:** Anime cafe, souvenir shopping, packing, pizza bar with foosball, karaoke
- **Sub-areas:** Anime cafe, souvenir district, pizza bar, karaoke venue
- **Key events:**
  - Anime cafe: flavor/cosmetic items
  - Karaoke: minigame? (⚑ optional) ::karaoke is after pizza bar, should be the memory::
  - Pizza bar foosball: minigame or trainer battle
- **Memory #8:** Final night out memory (karaoke? pizza bar?)

#### Tokyo 2 Day 3 — Flea Market + Airport
- **Narrative:** Morning flea market, then head to airport
- **Sub-areas:** Flea market (rotating item shop), airport
- **Airport Gauntlet (Elite Four equivalent):**
  1. Luggage check-in :: we had a suuuper long delay, me and zoey, so eprahps some crazy thing where we have to defeat diagla, the pokemon god of time::
  2. Security screening
  3. Customs
  4. Gate / boarding
- **Final scene:** Plane takes off. Credits roll over window view. 

---

## 5. Fakemon & Custom Species (Planned)

| Concept | Based On | Type Ideas | Notes |
|---|---|---|---|
| Charlie's starter | Table tennis / jazz | Normal? Sound? | TBD |
| Zoey's starter | Moss / plant | Grass | Fits Moss Temple arc |
| Dana's starter | Arty / gacha bunny | Fairy? Normal? | Gacha bunny from Sapporo |
| Gacha bunny | Sapporo gacha machine | Fairy | Could be Dana's starter OR wild encounter |
| Beautiful Duck | Shiny Farfetch'd reskin | Normal/Flying | Rare encounter, flavor rename only |
| Maushold (Transylvanian family) | Existing Pokemon | Normal | Optional fight for yen |
| Clodsire | Existing Pokemon | Poison/Ground | Moss temple water |

> ⚑ More fakemon ideas welcome — WoW project is reference for how to implement

---

## 6. Custom Moves & Abilities (Planned)

| Name | Type | Concept | Notes |
|---|---|---|---|
| Nod Politely | Normal | Does nothing / placeholder | Charlie's signature "move" in social battles |
| Sake Toast | Normal | Buff move, -20% HP next turn | Party-wide ATK up |
| Luggage Forward | Normal | Send away one Pokemon to "storage" early | 7-Eleven mechanic |
| ⚑ More TBD | — | — | — |

---

## 7. Open Questions (⚑ Needs Charles to Confirm)

1. What is "Love is Blind Ohio" in Sapporo? Fellow traveler? A joke reference?
2. Who is Shova? Fellow traveler met in Kyoto?
3. What is the "frog place" in Kyoto? Shrine? Shop?
4. Dana's starter — gacha bunny OR a different arty fakemon?
5. What is Memory #1? (Arrival feels right but what's the "win condition"?)
6. What is the craft store in Ginza? (Itoya? Tokyu Hands?)
7. Is Maira met in Kyoto or Sapporo? And is she a trainer battle or NPC? ::in kyoto teppanyaki dinner, with hiro-san the chef (who charlie does a drinking race with -- maybe mashing a button minigame for stretch)::
8. Does karaoke become a minigame or just a flavor scene? ::flavor scene with battles/boss for memory acquiring::
9. Working title — *Pocket Japan* placeholder, anything better? ::
10. Charlie's starter concept — any strong preferences?

---

## 8. Tone & Design Principles

- Warm, funny, and deeply personal — not a parody, but a love letter to the trip
- Japanese cultural moments are portrayed respectfully and with humor, never mockingly
- Character quirks are mechanical (food restrictions, surcharges) not just cosmetic
- Difficulty should be gentle — this is a story game first, Pokemon game second ::we can have decent difficulty, maybe a difficulty that can be easily implemented (different level caps) or complexly done::
- Every Memory should feel earned and emotionally resonant, not just a badge swap
