@ Druid trainer: assign known moves to each Druid form (Bear, Cat, Tree, Owlkin).
@ Reached from the test guide for now; becomes a real NPC when a town is chosen.
@ Variables: VAR_0x8004 party slot, 0x8005 form, 0x8006 slot, 0x8007 move.

GJT_DruidTrainer_EventScript_Start::
	msgbox GJT_DruidTrainer_Text_Intro, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, GJT_DruidTrainer_EventScript_End
	callnative DruidTrainer_Begin
	goto_if_eq VAR_RESULT, FALSE, GJT_DruidTrainer_EventScript_NotDruid
GJT_DruidTrainer_EventScript_FormMenu::
	message GJT_DruidTrainer_Text_WhichForm
	waitmessage
	callnative DruidTrainer_PushForms
	dynmultistack 0, 0, FALSE, 5, 0, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, GJT_DruidTrainer_EventScript_End
	goto_if_eq VAR_RESULT, 0, GJT_DruidTrainer_EventScript_End
	copyvar VAR_0x8005, VAR_RESULT
GJT_DruidTrainer_EventScript_SlotMenu::
	message GJT_DruidTrainer_Text_WhichSlot
	waitmessage
	callnative DruidTrainer_PushSlots
	dynmultistack 0, 0, FALSE, 4, 0, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, GJT_DruidTrainer_EventScript_FormMenu
	goto_if_eq VAR_RESULT, 0, GJT_DruidTrainer_EventScript_FormMenu
	copyvar VAR_0x8006, VAR_RESULT
	message GJT_DruidTrainer_Text_WhichMove
	waitmessage
	callnative DruidTrainer_PushMoves
	dynmultistack 0, 0, FALSE, 7, 0, 0, DYN_MULTICHOICE_CB_NONE
	closemessage
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, GJT_DruidTrainer_EventScript_SlotMenu
	copyvar VAR_0x8007, VAR_RESULT
	callnative DruidTrainer_Assign
	msgbox GJT_DruidTrainer_Text_Set, MSGBOX_DEFAULT
	goto GJT_DruidTrainer_EventScript_SlotMenu

GJT_DruidTrainer_EventScript_NotDruid::
	msgbox GJT_DruidTrainer_Text_NotDruid, MSGBOX_DEFAULT
GJT_DruidTrainer_EventScript_End::
	release
	end

GJT_DruidTrainer_Text_Intro:
	.string "Druid training! I'll set which\n"
	.string "moves each form uses.\p"
	.string "Which Druid?$"

GJT_DruidTrainer_Text_WhichForm:
	.string "Which form?$"

GJT_DruidTrainer_Text_WhichSlot:
	.string "Which slot?$"

GJT_DruidTrainer_Text_WhichMove:
	.string "Which move?$"

GJT_DruidTrainer_Text_Set:
	.string "Done! Unshift is always kept\n"
	.string "in the last slot.$"

GJT_DruidTrainer_Text_NotDruid:
	.string "That's not a Druid.$"
