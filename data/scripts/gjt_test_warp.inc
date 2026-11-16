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
	dynmultipush GJT_TestWarp_Text_NeverMind, 3
	dynmultistack 0, 0, FALSE, 4, 0, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	switch VAR_RESULT
	case 0, GJT_TestWarp_EventScript_Rustboro
	case 1, GJT_TestWarp_EventScript_Dewford
	case 2, GJT_TestWarp_EventScript_Mauville
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
