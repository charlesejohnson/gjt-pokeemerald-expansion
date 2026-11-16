LavaridgeTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_PokemonCenter_1F_OnFrame
	.byte 0

LavaridgeTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_LAVARIDGE_TOWN
	call Common_EventScript_UpdateBrineyLocation
	setflag FLAG_GJT_HIDE_LAVARIDGE_MAGNI
	call_if_eq VAR_GJT_LAVARIDGE_SCENE, 1, LavaridgeTown_PokemonCenter_1F_EventScript_ShowMagni
	end

LavaridgeTown_PokemonCenter_1F_EventScript_ShowMagni::
	clearflag FLAG_GJT_HIDE_LAVARIDGE_MAGNI
	return

LavaridgeTown_PokemonCenter_1F_OnFrame:
	map_script_2 VAR_GJT_LAVARIDGE_SCENE, 1, LavaridgeTown_PokemonCenter_1F_EventScript_FlannerySaved
	.2byte 0

@ GJT: Flannery has just been carried in after the Ragnaros fight.
LavaridgeTown_PokemonCenter_1F_EventScript_FlannerySaved::
	lockall
	delay 30
	msgbox LavaridgeTown_PokemonCenter_1F_Text_NurseTakesFlannery, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	delay 60
	fadescreen FADE_FROM_BLACK
	applymovement LOCALID_LAVARIDGE_MAGNI, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LavaridgeTown_PokemonCenter_1F_Text_MagniFlanneryIsStable, MSGBOX_DEFAULT
	closemessage
	message LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_WHITEOUT_TO_LAVARIDGE
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_BADGE04_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setvar VAR_LAVARIDGE_TOWN_STATE, 1
	call LavaridgeTown_Gym_1F_EventScript_GiveOverheat
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox LavaridgeTown_Gym_1F_Text_RegisteredFlannery, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_FLANNERY_MATCH_CALL
	setvar VAR_GJT_LAVARIDGE_SCENE, 2
	msgbox LavaridgeTown_PokemonCenter_1F_Text_MagniParting, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_GJT_HIDE_LAVARIDGE_MAGNI
	removeobject LOCALID_LAVARIDGE_MAGNI
	releaseall
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Magni::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_MagniParting, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_Text_NurseTakesFlannery:
	.string "NURSE JOY: Oh my goodness!\n"
	.string "Burns like these…\p"
	.string "Bring her through, quickly!\n"
	.string "I'll take her from here.$"

LavaridgeTown_PokemonCenter_1F_Text_MagniFlanneryIsStable:
	.string "MAGNI: She's stable, lad.\n"
	.string "Aye, she'll live.\p"
	.string "NURSE JOY says the burns are deep,\n"
	.string "but she's tough as the mountain.\p"
	.string "An' ye did that. Ye freed her.\p"
	.string "A promise is a promise, CHAMPION.\n"
	.string "Time for yer LOOT.$"

LavaridgeTown_PokemonCenter_1F_Text_MagniParting:
	.string "MAGNI: The molten lord is bested,\n"
	.string "but there're more o' them out there.\p"
	.string "Go on, {PLAYER}. I'll stay by her side\n"
	.string "until she wakes.$"

LavaridgeTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_LAVARIDGE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Youngster::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Woman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo, MSGBOX_NPC
	end

LavaridgeTown_PokemonCenter_1F_Text_TrainersPokemonSpendTimeTogether:
	.string "I think POKéMON get closer to their\n"
	.string "TRAINERS if they spend time together.\p"
	.string "The longer the better.\n"
	.string "That's what I think.$"

LavaridgeTown_PokemonCenter_1F_Text_HotSpringCanInvigorate:
	.string "It's sort of magical how just sitting\n"
	.string "in a hot-spring pool can invigorate.\p"
	.string "I wish I could let my POKéMON\n"
	.string "soak, too.$"

LavaridgeTown_PokemonCenter_1F_Text_TrainersShouldRestToo:
	.string "Hohoho! Hey, kid, you can reach\n"
	.string "the hot springs from here.\p"
	.string "If POKéMON are getting rest, so too\n"
	.string "should their TRAINERS.$"

