FortreeCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
	.byte 0

FortreeCity_Gym_OnTransition:
	special RotatingGate_InitPuzzle
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower bc of rotating gates
	end

FortreeCity_Gym_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_3
FortreeCity_Gym_EventScript_InitRotatingGates::
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeCity_Gym_EventScript_Winona::
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_WinonaRematch
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, FortreeCity_Gym_EventScript_GiveAerialAce2
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_WinonaDefeated::
	@ GJT: seal Thunderaan with the Windseeker Binding, yielding Thunderfury
	checkitem ITEM_PARCEL
	call_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_SealThunderaan
	checkitem ITEM_GLIMMERING_CHARM
	call_if_eq VAR_RESULT, FALSE, FortreeCity_Gym_EventScript_GiveThunderfury
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_FORTREE_GYM
	setflag FLAG_BADGE06_GET
	call GJT_EventScript_GymVitamins6
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers
	call FortreeCity_Gym_EventScript_GiveAerialAce
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
	release
	end

FortreeCity_Gym_EventScript_SealThunderaan::
	msgbox FortreeCity_Gym_Text_SealThunderaan, MSGBOX_DEFAULT
	removeitem ITEM_PARCEL
	return

FortreeCity_Gym_EventScript_GiveThunderfury::
	giveitem ITEM_GLIMMERING_CHARM
	return

FortreeCity_Gym_EventScript_GiveAerialAce2::
	giveitem ITEM_TM_EARTHQUAKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce::
	giveitem ITEM_TM_EARTHQUAKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
	return

FortreeCity_Gym_EventScript_WinonaRematch::
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_DEFAULT
	goto_if_set FLAG_RECEIVED_WINONA_MEGA, FortreeCity_Gym_EventScript_WinonaRematchDone
	setvar VAR_0x800A, ITEM_ALTARIANITE
	call GJT_EventScript_MegaGymGive
	setflag FLAG_RECEIVED_WINONA_MEGA
FortreeCity_Gym_EventScript_WinonaRematchDone::
	release
	end

FortreeCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Edwardo::
	trainerbattle_single TRAINER_EDWARDO, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Ashley::
	trainerbattle_single TRAINER_ASHLEY, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Humberto::
	trainerbattle_single TRAINER_HUMBERTO, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_GymGuidePostVictory::
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_GymStatueCertified::
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_EventScript_GymStatue::
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_Text_GymGuideAdvice:
	.string "Hmm? CHAMPION!\p"
	.string "The FORTREE GYM is a tree-house maze\n"
	.string "wi' rotatin' doors, aye. Mind yer step.\p"
	.string "Guardin' it are the CONCLAVE OF THE\n"
	.string "WIND: ANSHAL, NEZIR an' ROHASH.\p"
	.string "An' somethin' else. Somethin' wi' no\n"
	.string "face. I dinnae like the look o' that.\p"
	.string "At the top is WINONA, taken by PRINCE\n"
	.string "THUNDERAAN, the bound prince o' air.\p"
	.string "Ye'll need that BINDIN' I gave ye. Keep\n"
	.string "it safe, lad!$"

FortreeCity_Gym_Text_GymGuidePostVictory:
	.string "Ye did it, lad! THUNDERAAN's bound\n"
	.string "again, an' WINONA's alright.\p"
	.string "Check yer TRAINER CARD. The FEATHER\n"
	.string "BADGE is recorded.\p"
	.string "An' that blade… THUNDERFURY. Och,\n"
	.string "that's a story tae tell yer grandkids.$"

FortreeCity_Gym_Text_JaredIntro:
	.string "ROHASH, of the WIND ITSELF.\p"
	.string "Blink, and I'll be gone.\n"
	.string "Blink twice, and you'll be down!$"

FortreeCity_Gym_Text_JaredDefeat:
	.string "Too slow… I was too slow…$"

FortreeCity_Gym_Text_JaredPostBattle:
	.string "The CONCLAVE stands as one wind.\n"
	.string "One of us broke. Another is waiting.$"

FortreeCity_Gym_Text_EdwardoIntro:
	.string "…\p"
	.string "You… should not… look…\p"
	.string "There is no face here…\n"
	.string "only the old thing that watches.\p"
	.string "It does not blink…\n"
	.string "It does not end…$"

FortreeCity_Gym_Text_EdwardoDefeat:
	.string "…It sees you now…$"

FortreeCity_Gym_Text_EdwardoPostBattle:
	.string "…\p"
	.string "Forget my face.\n"
	.string "There was no face.$"

FortreeCity_Gym_Text_AshleyIntro:
	.string "NEZIR, of the FROST WIND.\p"
	.string "Winter rides the high air.\n"
	.string "Feel the chill in your bones!$"

FortreeCity_Gym_Text_AshleyDefeat:
	.string "The frost… thins…$"

FortreeCity_Gym_Text_AshleyPostBattle:
	.string "Even the coldest gale warms in time.\n"
	.string "Go on. ROHASH awaits.$"

FortreeCity_Gym_Text_HumbertoIntro:
	.string "ANSHAL, of the NATURE WIND.\n"
	.string "Roots hold the earth. Leaves ride the sky.\p"
	.string "Let me show you how the forest\n"
	.string "breathes on the gale!$"

FortreeCity_Gym_Text_HumbertoDefeat:
	.string "The forest… bows…$"

FortreeCity_Gym_Text_HumbertoPostBattle:
	.string "The wind carries seeds far.\n"
	.string "Where they land, new groves rise.$"

FortreeCity_Gym_Text_WinonaIntro:
	.string "…the air…\n"
	.string "…it screams…\p"
	.string "WINONA… is not… here…\p"
	.string "I am THUNDERAAN, PRINCE OF AIR!\n"
	.string "Bow before the WINDSEEKER, little one!\p"
	.string "I shall carry you into the storm,\n"
	.string "and no sky will ever hold you again!$"

FortreeCity_Gym_Text_WinonaDefeat:
	.string "The storm leaves her like a held breath.\p"
	.string "WINONA drops to her knees, gasping,\n"
	.string "but whole.\p"
	.string "You raise the BINDING OF THE WINDSEEKER.\n"
	.string "Light spirals outward…\p"
	.string "and PRINCE THUNDERAAN is drawn into\n"
	.string "the metal, screaming, bound once more.$"

FortreeCity_Gym_Text_ReceivedFeatherBadge:
	.string "{PLAYER} received the FEATHER BADGE\n"
	.string "from WINONA.$"

FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis:
	.string "WINONA: …I don't remember much.\n"
	.string "Only wind. And a voice.\p"
	.string "But I remember you. Thank you.\p"
	.string "The FEATHER BADGE lets POKéMON use\n"
	.string "the HM move FLY outside of battle.\p"
	.string "All obedience up to Level 70, too.\n"
	.string "Please, take this as well.$"

FortreeCity_Gym_Text_ExplainAerialAce:
	.string "This TM contains EARTHQUAKE.\p"
	.string "Even the highest branches\n"
	.string "feel it.\p"
	.string "… … … … … …$"

FortreeCity_Gym_Text_RegisteredWinona:
	.string "Registered GYM LEADER WINONA\n"
	.string "in the POKéNAV.$"

FortreeCity_Gym_Text_WinonaPostBattle:
	.string "WINONA: I will watch the skies\n"
	.string "more carefully now.\p"
	.string "Thank you for freeing me, {PLAYER}.$"

FortreeCity_Gym_Text_GymStatue:
	.string "FORTREE CITY POKéMON GYM$"

FortreeCity_Gym_Text_GymStatueCertified:
	.string "FORTREE CITY POKéMON GYM\p"
	.string "WINONA'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

FortreeCity_Gym_Text_WinonaPreRematch:
	.string "WINONA: We humans can never escape\n"
	.string "gravity's pull on the ground.\p"
	.string "But by striving for excellence,\n"
	.string "we have the power to soar!\p"
	.string "You have scaled the pinnacle as\n"
	.string "the reigning CHAMPION.\p"
	.string "Please, allow me to see your power\n"
	.string "at full flight!$"

FortreeCity_Gym_Text_WinonaRematchDefeat:
	.string "I failed to reach your height again…$"

FortreeCity_Gym_Text_WinonaPostRematch:
	.string "WINONA: Even though I have lost,\n"
	.string "the wings of my heart remain unbroken.\p"
	.string "I can rise and soar again and\n"
	.string "yet again.\p"
	.string "I am convinced of it!$"

FortreeCity_Gym_Text_WinonaRematchNeedTwoMons:
	.string "WINONA: We humans can never escape\n"
	.string "gravity's pull on the ground.\p"
	.string "But by striving for excellence,\n"
	.string "we have the power to soar!\p"
	.string "You have scaled the pinnacle as\n"
	.string "the reigning CHAMPION.\p"
	.string "Please, allow me to see your power\n"
	.string "at full flight!\p"
	.string "Oh, no… Do you have but one\n"
	.string "POKéMON with you?\p"
	.string "Please return with two POKéMON\n"
	.string "at the very least.$"

FortreeCity_Gym_Text_SealThunderaan:
	.string "The BINDING hums in your hand.\p"
	.string "The storm folds into a single blade,\n"
	.string "crackling with quiet, proud fury.\p"
	.string "THUNDERFURY, BLESSED BLADE OF THE\n"
	.string "WINDSEEKER.$"
