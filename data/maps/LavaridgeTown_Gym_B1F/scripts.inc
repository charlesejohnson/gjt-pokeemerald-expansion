LavaridgeTown_Gym_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_B1F_OnTransition
	.byte 0

LavaridgeTown_Gym_B1F_OnTransition:
	call LavaridgeTown_Gym_B1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_B1F_EventScript_CheckBuryTrainers
	end

@ Jeff removed (Firelands redesign). Temp var 9 kept unused.
LavaridgeTown_Gym_B1F_EventScript_SetTrainerTempVars::
	setvar VAR_TEMP_7, 0
	setvar VAR_TEMP_8, 0
	setvar VAR_TEMP_9, 0
	setvar VAR_TEMP_A, 0
	goto_if_defeated TRAINER_KEEGAN, LavaridgeTown_Gym_B1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_7, 1
LavaridgeTown_Gym_B1F_EventScript_EndSetTrainerTempVars::
	return

LavaridgeTown_Gym_B1F_EventScript_CheckBuryTrainers::
	goto_if_defeated TRAINER_KEEGAN, LavaridgeTown_Gym_B1F_EventScript_EndCheckBuryTrainers
	setobjectmovementtype LOCALID_KEEGAN, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_B1F_EventScript_EndCheckBuryTrainers::
	return
