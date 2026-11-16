LavaridgeTown_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_1F_OnTransition
	.byte 0

LavaridgeTown_Gym_1F_OnTransition:
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers
	end

@ Cole, Gerald removed (Firelands redesign). Temp vars D/E kept for Axle/Danielle.
LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars::
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 0
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar
	setvar VAR_TEMP_D, 1
LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_E, 1
LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars::
	return

LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle
	setobjectmovementtype LOCALID_AXLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers
	setobjectmovementtype LOCALID_DANIELLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers::
	return

LavaridgeTown_Gym_1F_EventScript_Flannery::
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto_if_unset FLAG_RECEIVED_TM_OVERHEAT, LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostBattle, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated::
	@ GJT: Flannery is carried to the Pokemon Center; the rewards come from Magni there
	@ (LavaridgeTown_PokemonCenter_1F_EventScript_FlannerySaved).
	setflag FLAG_GJT_HIDE_LAVARIDGE_FLANNERY
	setvar VAR_GJT_LAVARIDGE_SCENE, 1
	closemessage
	delay 40
	warp MAP_LAVARIDGE_TOWN_POKEMON_CENTER_1F, 7, 5
	waitstate
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat2::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat::
	giveitem ITEM_TM_OVERHEAT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_OVERHEAT
	return

LavaridgeTown_Gym_1F_EventScript_FlanneryRematch::
	trainerbattle_rematch_double TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryPreRematch, LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat, LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostRematch, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_EventScript_CheckTrainerScript::
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	release
	special ShouldTryGetTrainerScript
	goto_if_eq VAR_RESULT, 1, EventScript_GotoTrainerScript
	end

LavaridgeTown_Gym_1F_EventScript_Axle::
	trainerbattle_lavaridge LOCALID_AXLE, TRAINER_AXLE, LavaridgeTown_Gym_1F_Text_AxleIntro, LavaridgeTown_Gym_1F_Text_AxleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_AxlePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Keegan::
	trainerbattle_lavaridge LOCALID_KEEGAN, TRAINER_KEEGAN, LavaridgeTown_Gym_B1F_Text_KeeganIntro, LavaridgeTown_Gym_B1F_Text_KeeganDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_KeeganPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Danielle::
	trainerbattle_lavaridge LOCALID_DANIELLE, TRAINER_DANIELLE, LavaridgeTown_Gym_1F_Text_DanielleIntro, LavaridgeTown_Gym_1F_Text_DanielleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_DaniellePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jace::
	trainerbattle_single TRAINER_JACE, LavaridgeTown_Gym_B1F_Text_JaceIntro, LavaridgeTown_Gym_B1F_Text_JaceDefeat
	msgbox LavaridgeTown_Gym_B1F_Text_JacePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Eli::
	trainerbattle_single TRAINER_ELI, LavaridgeTown_Gym_B1F_Text_EliIntro, LavaridgeTown_Gym_B1F_Text_EliDefeat
	msgbox LavaridgeTown_Gym_B1F_Text_EliPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox LavaridgeTown_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_GymStatueCertified::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_EventScript_GymStatue::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_Text_GymGuideAdvice:
	.string "CHAMPION! Ye've made it tae the\n"
	.string "LAVARIDGE GYM, aye!\p"
	.string "I'm MAGNI. KHADGAR sent me tae guide\n"
	.string "ye, an' ye'll want me wits here.\p"
	.string "The FIRELANDS 'ave spilled intae this\n"
	.string "gym, an' RAGNAROS himself has taken\l"
	.string "poor FLANNERY.\p"
	.string "His lieutenants stand in the way:\n"
	.string "BETH'TILAC, ALYSRAZOR, STAGHELM,\l"
	.string "an' RYOLITH's two feet.\p"
	.string "Bring somethin' tae cool 'em doon,\n"
	.string "an' mind the sun!\p"
	.string "When it's over, I'll meet ye at the\n"
	.string "POKéMON CENTER. Ye'll earn yer LOOT!$"

LavaridgeTown_Gym_1F_Text_GymGuidePostVictory:
	.string "Aye, I knew ye'd do it, lad!\n"
	.string "FLANNERY's on the mend.\p"
	.string "Check yer TRAINER CARD. The HEAT\n"
	.string "BADGE should be properly recorded.$"

LavaridgeTown_Gym_1F_Text_AxleIntro:
	.string "I am MAJORDOMO STAGHELM, Druid of\n"
	.string "the Flame.\p"
	.string "The Lord of Fire rewards those who\n"
	.string "burn the world's green to ash.\p"
	.string "Let me show you how fire feeds\n"
	.string "on growth!$"

LavaridgeTown_Gym_1F_Text_AxleDefeat:
	.string "The flame… goes out…$"

LavaridgeTown_Gym_1F_Text_AxlePostBattle:
	.string "The forest burns, and the forest\n"
	.string "returns.\p"
	.string "Do not mistake my defeat for\n"
	.string "RAGNAROS's.$"

LavaridgeTown_Gym_B1F_Text_KeeganIntro:
	.string "Tangled in the web, are you?\p"
	.string "BETH'TILAC weaves her silk over\n"
	.string "the sand. Every step you take\l"
	.string "tells her where you stand.$"

LavaridgeTown_Gym_B1F_Text_KeeganDefeat:
	.string "My threads… have been burned through.$"

LavaridgeTown_Gym_B1F_Text_KeeganPostBattle:
	.string "Climb on, little prey.\p"
	.string "There are more of us below, and\n"
	.string "RAGNAROS himself above.$"

LavaridgeTown_Gym_1F_Text_DanielleIntro:
	.string "ALYSRAZOR, herald of the\n"
	.string "firebird, takes wing!\p"
	.string "Burn bright, little one, or burn out!$"

LavaridgeTown_Gym_1F_Text_DanielleDefeat:
	.string "My feathers… are ash…$"

LavaridgeTown_Gym_1F_Text_DaniellePostBattle:
	.string "The phoenix always rises again.\p"
	.string "Go on. The molten lord is waiting.$"

LavaridgeTown_Gym_B1F_Text_JaceIntro:
	.string "LORD RYOLITH's LEFT FOOT stomps\n"
	.string "upon the earth!\p"
	.string "My brother and I move as one.\n"
	.string "Break one of us, and the other\l"
	.string "will crush you!$"

LavaridgeTown_Gym_B1F_Text_JaceDefeat:
	.string "The left foot… has fallen.$"

LavaridgeTown_Gym_B1F_Text_JacePostBattle:
	.string "We fall together, as we stood.\p"
	.string "Go. The Firelord is waiting.$"

LavaridgeTown_Gym_B1F_Text_EliIntro:
	.string "And LORD RYOLITH's RIGHT FOOT\n"
	.string "shakes the mountain!\p"
	.string "Together we are the Lord of\n"
	.string "Rocks, and you stand beneath\l"
	.string "our weight!$"

LavaridgeTown_Gym_B1F_Text_EliDefeat:
	.string "The right foot… cracks…$"

LavaridgeTown_Gym_B1F_Text_EliPostBattle:
	.string "The mountain trembles no more.\p"
	.string "Hurry. His patience wears thin.$"

LavaridgeTown_Gym_1F_Text_FlanneryIntro:
	.string "Too… soon…\p"
	.string "You… dare… enter… MY… domain…\p"
	.string "By FIRE… be… PURGED!\p"
	.string "I am RAGNAROS, the FIRELORD.\n"
	.string "Come, and be consumed!\p"
	.string "SULFURAS shall smash your\n"
	.string "worthless little world!$"

LavaridgeTown_Gym_1F_Text_FlanneryDefeat:
	.string "The lava recedes from her skin as\n"
	.string "SULFURAS clatters to the ground.\p"
	.string "Burns cover her skin, but she is\n"
	.string "breathing.\p"
	.string "Barely.$"

LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge:
	.string "{PLAYER} received the HEAT BADGE\n"
	.string "from MAGNI.$"

LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis:
	.string "Here, lad.\p"
	.string "With the HEAT BADGE, all POKéMON up\n"
	.string "tae Level 50, even those ye get in\l"
	.string "trades, will obey ye completely.\p"
	.string "An' it lets POKéMON use the HM move\n"
	.string "STRENGTH outside o' battle.\p"
	.string "FLANNERY wanted ye tae 'ave this too.$"

LavaridgeTown_Gym_1F_Text_ExplainOverheat:
	.string "That TM50 contains OVERHEAT.\p"
	.string "That move inflicts serious damage on\n"
	.string "the opponent.\p"
	.string "But it also sharply cuts the SP. ATK\n"
	.string "of the POKéMON using it. It might not\l"
	.string "be suitable for longer battles.$"

LavaridgeTown_Gym_1F_Text_RegisteredFlannery:
	.string "Registered GYM LEADER FLANNERY\n"
	.string "in the POKéNAV.$"

LavaridgeTown_Gym_1F_Text_FlanneryPostBattle:
	.string "Your power reminds me of someone…\p"
	.string "Oh! I know! You battle like NORMAN,\n"
	.string "the GYM LEADER of PETALBURG.$"

LavaridgeTown_Gym_1F_Text_GymStatue:
	.string "LAVARIDGE TOWN POKéMON GYM$"

LavaridgeTown_Gym_1F_Text_GymStatueCertified:
	.string "LAVARIDGE TOWN POKéMON GYM\p"
	.string "FLANNERY'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

LavaridgeTown_Gym_1F_Text_FlanneryPreRematch:
	.string "FLANNERY: Losing a battle isn't going\n"
	.string "to deflate me.\p"
	.string "I love POKéMON.\n"
	.string "I love to battle.\l"
	.string "And… I love this GYM!\p"
	.string "Let's exchange superhot moves\n"
	.string "in another battle!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat:
	.string "Whew!\n"
	.string "On the verge of eruption!$"

LavaridgeTown_Gym_1F_Text_FlanneryPostRematch:
	.string "FLANNERY: I lost the match,\n"
	.string "but I'm completely satisfied.\p"
	.string "It's not often I get to enjoy a battle\n"
	.string "this heated.\p"
	.string "Let's have another one like this\n"
	.string "again sometime!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons:
	.string "FLANNERY: Losing a battle isn't going\n"
	.string "to deflate me.\p"
	.string "I love POKéMON.\n"
	.string "I love to battle.\l"
	.string "And… I love this GYM!\p"
	.string "Let's exchange superhot moves\n"
	.string "in another battle!\p"
	.string "Oh, wait. Do you only have one POKéMON\n"
	.string "that can battle?\p"
	.string "I hate to say this, but when you come\n"
	.string "see me, bring at least two POKéMON.$"
