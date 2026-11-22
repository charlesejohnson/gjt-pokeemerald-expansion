@ GJT gym vitamin rewards. Totals per gym: 10,10,10,15,20,25,30,30 (150 total, 25 of each type).
@ See wow-docs/design/vitamins-and-rewards.md

GJT_EventScript_GymVitamins2::
	msgbox GJT_Text_GymVitamins, MSGBOX_DEFAULT
	giveitem ITEM_HP_UP 2
	giveitem ITEM_PROTEIN 2
	giveitem ITEM_IRON 1
	giveitem ITEM_CALCIUM 1
	giveitem ITEM_ZINC 2
	giveitem ITEM_CARBOS 2
	return

GJT_EventScript_GymVitamins4::
	msgbox GJT_Text_GymVitamins, MSGBOX_DEFAULT
	giveitem ITEM_HP_UP 3
	giveitem ITEM_PROTEIN 3
	giveitem ITEM_IRON 3
	giveitem ITEM_CALCIUM 2
	giveitem ITEM_ZINC 2
	giveitem ITEM_CARBOS 2
	return

GJT_EventScript_GymVitamins6::
	msgbox GJT_Text_GymVitamins, MSGBOX_DEFAULT
	giveitem ITEM_HP_UP 4
	giveitem ITEM_PROTEIN 4
	giveitem ITEM_IRON 4
	giveitem ITEM_CALCIUM 4
	giveitem ITEM_ZINC 4
	giveitem ITEM_CARBOS 5
	return

GJT_EventScript_GymVitamins7::
	msgbox GJT_Text_GymVitamins, MSGBOX_DEFAULT
	giveitem ITEM_HP_UP 5
	giveitem ITEM_PROTEIN 5
	giveitem ITEM_IRON 5
	giveitem ITEM_CALCIUM 5
	giveitem ITEM_ZINC 5
	giveitem ITEM_CARBOS 5
	return

GJT_Text_GymVitamins:
	.string "Take these vitamins with you.\n"
	.string "Spend them wisely on your team!$"
