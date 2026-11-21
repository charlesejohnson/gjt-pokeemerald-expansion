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
	dynmultipush GJT_TestWarp_Text_Lavaridge, 7
	dynmultipush GJT_TestWarp_Text_Petalburg, 8
	dynmultipush GJT_TestWarp_Text_Fortree, 9
	dynmultipush GJT_TestWarp_Text_Mossdeep, 10
	dynmultipush GJT_TestWarp_Text_Sootopolis, 11
	dynmultipush GJT_TestWarp_Text_Supplies, 3
	dynmultipush GJT_TestWarp_Text_WowMons, 4
	dynmultipush GJT_TestWarp_Text_Badges, 5
	dynmultipush GJT_TestWarp_Text_DruidTrainer, 12
	dynmultipush GJT_TestWarp_Text_NeverMind, 6
	dynmultistack 0, 0, FALSE, 7, 0, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	switch VAR_RESULT
	case 0, GJT_TestWarp_EventScript_Rustboro
	case 1, GJT_TestWarp_EventScript_Dewford
	case 2, GJT_TestWarp_EventScript_Mauville
	case 7, GJT_TestWarp_EventScript_Lavaridge
	case 8, GJT_TestWarp_EventScript_Petalburg
	case 9, GJT_TestWarp_EventScript_Fortree
	case 10, GJT_TestWarp_EventScript_Mossdeep
	case 11, GJT_TestWarp_EventScript_Sootopolis
	case 3, GJT_TestWarp_EventScript_Supplies
	case 4, GJT_TestWarp_EventScript_WowMons
	case 5, GJT_TestWarp_EventScript_Badges
	case 12, GJT_DruidTrainer_EventScript_Start
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

GJT_TestWarp_EventScript_Lavaridge::
	warp MAP_LAVARIDGE_TOWN_GYM_1F, 13, 17
	waitstate
	end

GJT_TestWarp_EventScript_Petalburg::
	@ Skip the Wally tutorial: put the gym in its "ready for the leader" state
	goto_if_ge VAR_PETALBURG_GYM_STATE, 6, GJT_TestWarp_EventScript_PetalburgWarp
	setvar VAR_PETALBURG_GYM_STATE, 6
	call Common_EventScript_ReadyPetalburgGymForBattle
GJT_TestWarp_EventScript_PetalburgWarp::
	warp MAP_PETALBURG_CITY_GYM, 4, 110
	waitstate
	end

GJT_TestWarp_EventScript_Fortree::
	warp MAP_FORTREE_CITY_GYM, 15, 23
	waitstate
	end

GJT_TestWarp_EventScript_Mossdeep::
	warp MAP_MOSSDEEP_CITY_GYM, 4, 29
	waitstate
	end

GJT_TestWarp_EventScript_Sootopolis::
	warp MAP_SOOTOPOLIS_CITY_GYM_1F, 8, 24
	waitstate
	end

GJT_TestWarp_EventScript_Supplies::
	additem ITEM_MASTER_BALL, 10
	additem ITEM_RARE_CANDY, 99
	additem ITEM_FIRE_STONE, 5
	additem ITEM_WATER_STONE, 5
	additem ITEM_LEAF_STONE, 5
	additem ITEM_MOON_STONE, 5
	additem ITEM_SUN_STONE, 5
	additem ITEM_SHINY_STONE, 5
	additem ITEM_DAWN_STONE, 5
	additem ITEM_PROTEIN, 5
	additem ITEM_CALCIUM, 5
	additem ITEM_HP_UP, 5
	additem ITEM_ZINC, 5
	additem ITEM_IRON, 5
	additem ITEM_CARBOS, 5
	additem ITEM_PARCEL
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
	givemon SPECIES_WARRIOR, 5
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_NoMoreRoomForPokemon
	givemon SPECIES_SHAMAN, 5
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_NoMoreRoomForPokemon
	givemon SPECIES_DRUID, 5
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_NoMoreRoomForPokemon
	givemon SPECIES_MONK, 5
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_NoMoreRoomForPokemon
	playfanfare MUS_OBTAIN_ITEM
	msgbox GJT_TestWarp_Text_GaveMons, MSGBOX_DEFAULT
	waitfanfare
	release
	end

GJT_TestWarp_EventScript_Badges::
	message GJT_TestWarp_Text_WhichBadge
	waitmessage
	dynmultipush GJT_TestWarp_Text_Badge1, 0
	dynmultipush GJT_TestWarp_Text_Badge2, 1
	dynmultipush GJT_TestWarp_Text_Badge3, 2
	dynmultipush GJT_TestWarp_Text_Badge4, 3
	dynmultipush GJT_TestWarp_Text_Badge5, 4
	dynmultipush GJT_TestWarp_Text_Badge6, 5
	dynmultipush GJT_TestWarp_Text_Badge7, 6
	dynmultipush GJT_TestWarp_Text_Badge8, 7
	dynmultipush GJT_TestWarp_Text_AllBadges, 8
	dynmultipush GJT_TestWarp_Text_ClearBadges, 9
	dynmultipush GJT_TestWarp_Text_Back, 10
	dynmultistack 0, 0, FALSE, 7, 0, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	switch VAR_RESULT
	case 0, GJT_TestWarp_EventScript_ToggleBadge1
	case 1, GJT_TestWarp_EventScript_ToggleBadge2
	case 2, GJT_TestWarp_EventScript_ToggleBadge3
	case 3, GJT_TestWarp_EventScript_ToggleBadge4
	case 4, GJT_TestWarp_EventScript_ToggleBadge5
	case 5, GJT_TestWarp_EventScript_ToggleBadge6
	case 6, GJT_TestWarp_EventScript_ToggleBadge7
	case 7, GJT_TestWarp_EventScript_ToggleBadge8
	case 8, GJT_TestWarp_EventScript_AllBadges
	case 9, GJT_TestWarp_EventScript_ClearBadges
	release
	end

GJT_TestWarp_EventScript_ToggleBadge1::
	buffernumberstring STR_VAR_1, 1
	goto_if_set FLAG_BADGE01_GET, GJT_TestWarp_EventScript_ClearBadge1
	setflag FLAG_BADGE01_GET
	msgbox GJT_TestWarp_Text_BadgeOn, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ClearBadge1::
	clearflag FLAG_BADGE01_GET
	msgbox GJT_TestWarp_Text_BadgeOff, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ToggleBadge2::
	buffernumberstring STR_VAR_1, 2
	goto_if_set FLAG_BADGE02_GET, GJT_TestWarp_EventScript_ClearBadge2
	setflag FLAG_BADGE02_GET
	msgbox GJT_TestWarp_Text_BadgeOn, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ClearBadge2::
	clearflag FLAG_BADGE02_GET
	msgbox GJT_TestWarp_Text_BadgeOff, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ToggleBadge3::
	buffernumberstring STR_VAR_1, 3
	goto_if_set FLAG_BADGE03_GET, GJT_TestWarp_EventScript_ClearBadge3
	setflag FLAG_BADGE03_GET
	msgbox GJT_TestWarp_Text_BadgeOn, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ClearBadge3::
	clearflag FLAG_BADGE03_GET
	msgbox GJT_TestWarp_Text_BadgeOff, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ToggleBadge4::
	buffernumberstring STR_VAR_1, 4
	goto_if_set FLAG_BADGE04_GET, GJT_TestWarp_EventScript_ClearBadge4
	setflag FLAG_BADGE04_GET
	msgbox GJT_TestWarp_Text_BadgeOn, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ClearBadge4::
	clearflag FLAG_BADGE04_GET
	msgbox GJT_TestWarp_Text_BadgeOff, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ToggleBadge5::
	buffernumberstring STR_VAR_1, 5
	goto_if_set FLAG_BADGE05_GET, GJT_TestWarp_EventScript_ClearBadge5
	setflag FLAG_BADGE05_GET
	msgbox GJT_TestWarp_Text_BadgeOn, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ClearBadge5::
	clearflag FLAG_BADGE05_GET
	msgbox GJT_TestWarp_Text_BadgeOff, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ToggleBadge6::
	buffernumberstring STR_VAR_1, 6
	goto_if_set FLAG_BADGE06_GET, GJT_TestWarp_EventScript_ClearBadge6
	setflag FLAG_BADGE06_GET
	msgbox GJT_TestWarp_Text_BadgeOn, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ClearBadge6::
	clearflag FLAG_BADGE06_GET
	msgbox GJT_TestWarp_Text_BadgeOff, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ToggleBadge7::
	buffernumberstring STR_VAR_1, 7
	goto_if_set FLAG_BADGE07_GET, GJT_TestWarp_EventScript_ClearBadge7
	setflag FLAG_BADGE07_GET
	msgbox GJT_TestWarp_Text_BadgeOn, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ClearBadge7::
	clearflag FLAG_BADGE07_GET
	msgbox GJT_TestWarp_Text_BadgeOff, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ToggleBadge8::
	buffernumberstring STR_VAR_1, 8
	goto_if_set FLAG_BADGE08_GET, GJT_TestWarp_EventScript_ClearBadge8
	setflag FLAG_BADGE08_GET
	msgbox GJT_TestWarp_Text_BadgeOn, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ClearBadge8::
	clearflag FLAG_BADGE08_GET
	msgbox GJT_TestWarp_Text_BadgeOff, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_AllBadges::
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_BADGE08_GET
	msgbox GJT_TestWarp_Text_AllBadgesOn, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_EventScript_ClearBadges::
	clearflag FLAG_BADGE01_GET
	clearflag FLAG_BADGE02_GET
	clearflag FLAG_BADGE03_GET
	clearflag FLAG_BADGE04_GET
	clearflag FLAG_BADGE05_GET
	clearflag FLAG_BADGE06_GET
	clearflag FLAG_BADGE07_GET
	clearflag FLAG_BADGE08_GET
	msgbox GJT_TestWarp_Text_AllBadgesOff, MSGBOX_DEFAULT
	goto GJT_TestWarp_EventScript_Badges

GJT_TestWarp_Text_WhereTo:
	.include "data/text/gjt_version.inc"
	.string "\p"
	.string "Laddie! KHADGAR set up a wee\n"
	.string "shortcut fer testin'.\p"
	.string "Where tae?$"

GJT_TestWarp_Text_Rustboro:
	.string "RUSTBORO GYM$"

GJT_TestWarp_Text_Dewford:
	.string "DEWFORD GYM$"

GJT_TestWarp_Text_Petalburg:
	.string "PETALBURG GYM$"

GJT_TestWarp_Text_Fortree:
	.string "FORTREE GYM$"

GJT_TestWarp_Text_Mossdeep:
	.string "MOSSDEEP GYM$"

GJT_TestWarp_Text_Sootopolis:
	.string "SOOTOPOLIS GYM$"

GJT_TestWarp_Text_Lavaridge:
	.string "LAVARIDGE GYM$"

GJT_TestWarp_Text_Mauville:
	.string "MAUVILLE GYM$"

GJT_TestWarp_Text_DruidTrainer:
	.string "DRUID TRAINER$"

GJT_TestWarp_Text_NeverMind:
	.string "NEVER MIND$"

GJT_TestWarp_Text_Supplies:
	.string "SUPPLIES$"

GJT_TestWarp_Text_WowMons:
	.string "CLASS POKéMON$"

GJT_TestWarp_Text_Badges:
	.string "BADGES$"

GJT_TestWarp_Text_GaveSupplies:
	.string "Here, laddie! 10 MASTER BALLS,\n"
	.string "99 RARE CANDIES, 5 each o' the\l"
	.string "evolution stones an' vitamins,\l"
	.string "an' the gym TMs!$"

GJT_TestWarp_Text_GaveMons:
	.string "A level 5 DEATH KNIGHT, MAGE,\n"
	.string "WARRIOR, SHAMAN an' DRUID are yers!$"

GJT_TestWarp_Text_WhichBadge:
	.string "Which BADGE should I flip, laddie?$"

GJT_TestWarp_Text_Badge1:
	.string "BADGE 1$"

GJT_TestWarp_Text_Badge2:
	.string "BADGE 2$"

GJT_TestWarp_Text_Badge3:
	.string "BADGE 3$"

GJT_TestWarp_Text_Badge4:
	.string "BADGE 4$"

GJT_TestWarp_Text_Badge5:
	.string "BADGE 5$"

GJT_TestWarp_Text_Badge6:
	.string "BADGE 6$"

GJT_TestWarp_Text_Badge7:
	.string "BADGE 7$"

GJT_TestWarp_Text_Badge8:
	.string "BADGE 8$"

GJT_TestWarp_Text_AllBadges:
	.string "GIVE ALL 8$"

GJT_TestWarp_Text_ClearBadges:
	.string "CLEAR ALL$"

GJT_TestWarp_Text_Back:
	.string "BACK$"

GJT_TestWarp_Text_BadgeOn:
	.string "BADGE {STR_VAR_1} is now ON.$"

GJT_TestWarp_Text_BadgeOff:
	.string "BADGE {STR_VAR_1} is now OFF.$"

GJT_TestWarp_Text_AllBadgesOn:
	.string "All eight BADGES are ON.$"

GJT_TestWarp_Text_AllBadgesOff:
	.string "All BADGES are OFF.$"
