@ GJT testing aid: an NPC in the player's bedroom that warps to the entrance of each finished gym.
@ Remove the two bedroom objects (LittlerootTown_*_2F map.json) before release.

GJT_TestWarp_EventScript_Guide::
	lock
	faceplayer
	message GJT_TestWarp_Text_WhereTo
	waitmessage
	dynmultipush GJT_TestWarp_Text_Rustboro, 0
	dynmultipush GJT_TestWarp_Text_Dewford, 1
	dynmultipush GJT_TestWarp_Text_Mauville, 2
	dynmultipush GJT_TestWarp_Text_Supplies, 3
	dynmultipush GJT_TestWarp_Text_WowMons, 4
	dynmultipush GJT_TestWarp_Text_Badges, 5
	dynmultipush GJT_TestWarp_Text_NeverMind, 6
	dynmultistack 0, 0, FALSE, 7, 0, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	switch VAR_RESULT
	case 0, GJT_TestWarp_EventScript_Rustboro
	case 1, GJT_TestWarp_EventScript_Dewford
	case 2, GJT_TestWarp_EventScript_Mauville
	case 3, GJT_TestWarp_EventScript_Supplies
	case 4, GJT_TestWarp_EventScript_WowMons
	case 5, GJT_TestWarp_EventScript_Badges
	release
	end

GJT_TestWarp_EventScript_Rustboro::
	warp MAP_RUSTBORO_CITY_GYM, 5, 18
	waitstate
	end

GJT_TestWarp_EventScript_Dewford::
	warp MAP_DEWFORD_TOWN_GYM, 8, 26
	waitstate
	end

GJT_TestWarp_EventScript_Mauville::
	warp MAP_MAUVILLE_CITY_GYM, 4, 19
	waitstate
	end

GJT_TestWarp_EventScript_Supplies::
	additem ITEM_MASTER_BALL, 10
	additem ITEM_RARE_CANDY, 99
	additem ITEM_FIRE_STONE, 5
	additem ITEM_WATER_STONE, 5
	additem ITEM_LEAF_STONE, 5
	additem ITEM_PROTEIN, 5
	additem ITEM_CALCIUM, 5
	additem ITEM_HP_UP, 5
	additem ITEM_ZINC, 5
	additem ITEM_IRON, 5
	additem ITEM_CARBOS, 5
	additem ITEM_TM_ROCK_TOMB
	additem ITEM_TM_BULK_UP
	additem ITEM_TM_SHOCK_WAVE
	playfanfare MUS_OBTAIN_ITEM
	msgbox GJT_TestWarp_Text_GaveSupplies, MSGBOX_DEFAULT
	waitfanfare
	release
	end

GJT_TestWarp_EventScript_WowMons::
	givemon SPECIES_DEATHKNIGHT, 5
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_NoMoreRoomForPokemon
	givemon SPECIES_MAGE, 5
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_NoMoreRoomForPokemon
	playfanfare MUS_OBTAIN_ITEM
	msgbox GJT_TestWarp_Text_GaveMons, MSGBOX_DEFAULT
	waitfanfare
	release
	end

GJT_TestWarp_EventScript_Badges::
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	msgbox GJT_TestWarp_Text_GaveBadges, MSGBOX_DEFAULT
	release
	end

GJT_TestWarp_Text_WhereTo:
	.string "Laddie! KHADGAR set up a wee\n"
	.string "shortcut fer testin'.\p"
	.string "Where tae?$"

GJT_TestWarp_Text_Rustboro:
	.string "RUSTBORO GYM$"

GJT_TestWarp_Text_Dewford:
	.string "DEWFORD GYM$"

GJT_TestWarp_Text_Mauville:
	.string "MAUVILLE GYM$"

GJT_TestWarp_Text_NeverMind:
	.string "NEVER MIND$"

GJT_TestWarp_Text_Supplies:
	.string "SUPPLIES$"

GJT_TestWarp_Text_WowMons:
	.string "CLASS POKéMON$"

GJT_TestWarp_Text_Badges:
	.string "BADGES 1-3$"

GJT_TestWarp_Text_GaveSupplies:
	.string "Here, laddie! 10 MASTER BALLS,\n"
	.string "99 RARE CANDIES, 5 each o' the\l"
	.string "evolution stones an' vitamins,\l"
	.string "an' the gym TMs!$"

GJT_TestWarp_Text_GaveMons:
	.string "A level 5 DEATH KNIGHT an' a\n"
	.string "level 5 MAGE are yers!$"

GJT_TestWarp_Text_GaveBadges:
	.string "The first three BADGES are yers.\p"
	.string "The level cap is now 29.$"
