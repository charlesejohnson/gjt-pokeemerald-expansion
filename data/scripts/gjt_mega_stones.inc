@ GJT Mega Stone rewards. Placement list: wow-docs/design/mega-stones.md

GJT_Text_MegaGym:
	.string "They also press a strange, glittering\n"
	.string "stone into your hand.$"

GJT_Text_MegaNpc:
	.string "“Oh, and take this too. I found it\n"
	.string "once and never knew what it was for.”$"

GJT_Text_MegaMagma:
	.string "Among the scorched rubble, several\n"
	.string "glittering stones catch your eye.$"

GJT_Text_MegaAqua:
	.string "The Aqua crew left a crate behind.\n"
	.string "Inside are several glittering stones.$"

@ VAR_0x800A = stone item id
GJT_EventScript_MegaGymGive::
	msgbox GJT_Text_MegaGym, MSGBOX_DEFAULT
	giveitem VAR_0x800A
	return

GJT_EventScript_MegaNpcGive::
	msgbox GJT_Text_MegaNpc, MSGBOX_DEFAULT
	giveitem VAR_0x800A
	return

GJT_EventScript_MegaMagmaGroup::
	msgbox GJT_Text_MegaMagma, MSGBOX_DEFAULT
	giveitem ITEM_CAMERUPTITE
	giveitem ITEM_HOUNDOOMINITE
	giveitem ITEM_CHARIZARDITE_X
	giveitem ITEM_CHARIZARDITE_Y
	return

GJT_EventScript_MegaAquaGroup::
	msgbox GJT_Text_MegaAqua, MSGBOX_DEFAULT
	giveitem ITEM_SHARPEDONITE
	giveitem ITEM_SLOWBRONITE
	giveitem ITEM_STARMINITE
	return

GJT_Text_MegaBracelet:
	.string "“This Mega Bracelet resonates with\n"
	.string "the stones you carry. Use it well.”$"

GJT_EventScript_GiveMegaBracelet::
	msgbox GJT_Text_MegaBracelet, MSGBOX_DEFAULT
	giveitem ITEM_MEGA_RING
	return
