@ GJT Specialization Stone: use on a class Pokémon, pick a spec, evolve into it.
@ Works as first specialization and as respec. See wow-docs/design/vitamins-and-rewards.md

GJT_EventScript_UseSpecStone::
	lockall
	msgbox GJT_Text_SpecStoneWho, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, GJT_EventScript_SpecStoneEnd
	special GjtSpecStonePrepare
	goto_if_eq VAR_RESULT, 0, GJT_EventScript_SpecStoneNoEffect
	copyvar VAR_0x8006, VAR_RESULT
	msgbox GJT_Text_SpecStoneWhich, MSGBOX_DEFAULT
	goto_if_eq VAR_0x8006, 4, GJT_EventScript_SpecStoneMenu4
	dynmultipush gStringVar1, 0
	dynmultipush gStringVar2, 1
	dynmultipush gStringVar3, 2
	dynmultipush gText_Cancel, 3
	dynmultistack 0, 0, FALSE, 4, FALSE, 0, NULL
	goto GJT_EventScript_SpecStonePicked

GJT_EventScript_SpecStoneMenu4::
	dynmultipush gStringVar1, 0
	dynmultipush gStringVar2, 1
	dynmultipush gStringVar3, 2
	dynmultipush gStringVar4, 3
	dynmultipush gText_Cancel, 4
	dynmultistack 0, 0, FALSE, 5, FALSE, 0, NULL
GJT_EventScript_SpecStonePicked::
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, GJT_EventScript_SpecStoneEnd
	copyvar VAR_0x8005, VAR_RESULT
	@ Cancel is the entry after the last spec
	goto_if_ge VAR_0x8005, VAR_0x8006, GJT_EventScript_SpecStoneEnd
	special GjtSpecStoneApply
	goto_if_eq VAR_RESULT, FALSE, GJT_EventScript_SpecStoneAlready
	waitstate
	releaseall
	end

GJT_EventScript_SpecStoneAlready::
	msgbox GJT_Text_SpecStoneAlready, MSGBOX_DEFAULT
	releaseall
	end

GJT_EventScript_SpecStoneNoEffect::
	msgbox GJT_Text_SpecStoneNoEffect, MSGBOX_DEFAULT
GJT_EventScript_SpecStoneEnd::
	releaseall
	end

GJT_Text_SpecStoneWho:
	.string "Use the Spec Stone on which\n"
	.string "Pokémon?$"

GJT_Text_SpecStoneWhich:
	.string "Choose a specialization.$"

GJT_Text_SpecStoneAlready:
	.string "It already has that\n"
	.string "specialization.$"

GJT_Text_SpecStoneNoEffect:
	.string "It won't have any effect.$"

GJT_Text_SpecStoneGift:
	.string "Take this, you earned it.\p"
	.string "It's a Spec Stone. Use it on a\n"
	.string "class Pokémon to choose its path.\p"
	.string "You can use more Stones later\n"
	.string "to change your mind.$"

GJT_EventScript_GiveSpecStone::
	msgbox GJT_Text_SpecStoneGift, MSGBOX_DEFAULT
	giveitem ITEM_SPECIALIZATION_STONE
	return

GJT_Text_SpecStoneGift2:
	.string "Here, a second Spec Stone.\n"
	.string "Spend it on a new class Pokémon,\l"
	.string "or change a path you regret.$"

GJT_EventScript_GiveSpecStone2::
	msgbox GJT_Text_SpecStoneGift2, MSGBOX_DEFAULT
	giveitem ITEM_SPECIALIZATION_STONE
	return
