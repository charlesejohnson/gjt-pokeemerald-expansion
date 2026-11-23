SootopolisCity_Gym_B1F_MapScripts::
	.byte 0

SootopolisCity_Gym_B1F_EventScript_Andrea::
	trainerbattle_single TRAINER_ANDREA, SootopolisCity_Gym_B1F_Text_AndreaIntro, SootopolisCity_Gym_B1F_Text_AndreaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AndreaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Crissy::
	trainerbattle_single TRAINER_CRISSY, SootopolisCity_Gym_B1F_Text_CrissyIntro, SootopolisCity_Gym_B1F_Text_CrissyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_CrissyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Brianna::
	trainerbattle_single TRAINER_BRIANNA, SootopolisCity_Gym_B1F_Text_BriannaIntro, SootopolisCity_Gym_B1F_Text_BriannaDefeat, SootopolisCity_Gym_B1F_EventScript_DaelinDefeated
	msgbox SootopolisCity_Gym_B1F_Text_BriannaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_DaelinDefeated::
	goto_if_set FLAG_RECEIVED_DAELIN_VITAMINS, SootopolisCity_Gym_B1F_EventScript_DaelinVitaminsGiven
	msgbox SootopolisCity_Gym_B1F_Text_DaelinReward, MSGBOX_DEFAULT
	giveitem ITEM_PROTEIN, 5
	giveitem ITEM_CALCIUM, 5
	giveitem ITEM_HP_UP, 5
	giveitem ITEM_ZINC, 5
	giveitem ITEM_IRON, 5
	giveitem ITEM_CARBOS, 5
	setflag FLAG_RECEIVED_DAELIN_VITAMINS
SootopolisCity_Gym_B1F_EventScript_DaelinVitaminsGiven::
	release
	end

SootopolisCity_Gym_B1F_EventScript_Connie::
	trainerbattle_single TRAINER_CONNIE, SootopolisCity_Gym_B1F_Text_ConnieIntro, SootopolisCity_Gym_B1F_Text_ConnieDefeat
	msgbox SootopolisCity_Gym_B1F_Text_ConniePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET, SootopolisCity_Gym_B1F_Text_BridgetIntro, SootopolisCity_Gym_B1F_Text_BridgetDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA, SootopolisCity_Gym_B1F_Text_OliviaIntro, SootopolisCity_Gym_B1F_Text_OliviaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY, SootopolisCity_Gym_B1F_Text_TiffanyIntro, SootopolisCity_Gym_B1F_Text_TiffanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_TiffanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bethany::
	trainerbattle_single TRAINER_BETHANY, SootopolisCity_Gym_B1F_Text_BethanyIntro, SootopolisCity_Gym_B1F_Text_BethanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BethanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Annika::
	trainerbattle_single TRAINER_ANNIKA, SootopolisCity_Gym_B1F_Text_AnnikaIntro, SootopolisCity_Gym_B1F_Text_AnnikaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AnnikaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Daphne::
	trainerbattle_single TRAINER_DAPHNE, SootopolisCity_Gym_B1F_Text_DaphneIntro, SootopolisCity_Gym_B1F_Text_DaphneDefeat
	msgbox SootopolisCity_Gym_B1F_Text_DaphnePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_Text_AndreaIntro:
	.string "MEKKATORQUE: Ah, a visitor!\n"
	.string "Excellent timing!\p"
	.string "My latest prototype is fully tested!\n"
	.string "Ninety percent tested! Okay, forty.$"

SootopolisCity_Gym_B1F_Text_AndreaDefeat:
	.string "MEKKATORQUE: Fascinating! The\n"
	.string "explosion was supposed to be\l"
	.string "smaller. I'll note that.$"

SootopolisCity_Gym_B1F_Text_AndreaPostBattle:
	.string "MEKKATORQUE: Taelia's ahead. She's\n"
	.string "wonderful.\p"
	.string "Her armor does not have a safety\n"
	.string "feature either.$"

SootopolisCity_Gym_B1F_Text_CrissyIntro:
	.string "I can summon a feast out of\n"
	.string "nothing. Sadly, this won't be one.$"

SootopolisCity_Gym_B1F_Text_CrissyDefeat:
	.string "I'm keeping the sandwiches I\n"
	.string "conjured. You can't have them.$"

SootopolisCity_Gym_B1F_Text_CrissyPostBattle:
	.string "They're good sandwiches, too.\n"
	.string "Ham. Possibly.$"

SootopolisCity_Gym_B1F_Text_DaphneIntro:
	.string "KUL TIRAS never loses at sea.\p"
	.string "We also never go back on dry\n"
	.string "land. This ice is a compromise.$"

SootopolisCity_Gym_B1F_Text_DaphneDefeat:
	.string "I blame the ice. Not me.\n"
	.string "The ice.$"

SootopolisCity_Gym_B1F_Text_DaphnePostBattle:
	.string "I'd prefer the sea. It doesn't\n"
	.string "crack when I step on it.$"

SootopolisCity_Gym_B1F_Text_ConnieIntro:
	.string "TAELIA: Jaina is just ahead. I'm to\n"
	.string "make sure you're ready for her.\p"
	.string "I'm very fond of you already.\n"
	.string "I'm still not going to go easy.$"

SootopolisCity_Gym_B1F_Text_ConnieDefeat:
	.string "TAELIA: Oh, well fought! Truly!\p"
	.string "I mean it. I'm a little bit\n"
	.string "proud of you.$"

SootopolisCity_Gym_B1F_Text_ConniePostBattle:
	.string "TAELIA: Jaina has a lot on her mind.\n"
	.string "Her father most of all.\p"
	.string "Be kind, and be careful.$"

SootopolisCity_Gym_B1F_Text_BridgetIntro:
	.string "The ADMIRAL said to hold the line.\n"
	.string "I've held it for three hours.\p"
	.string "My arms are tired.$"

SootopolisCity_Gym_B1F_Text_BridgetDefeat:
	.string "That's it. I'm going to go\n"
	.string "swab something.$"

SootopolisCity_Gym_B1F_Text_BridgetPostBattle:
	.string "Three hours. I'd like that\n"
	.string "noted somewhere.$"

SootopolisCity_Gym_B1F_Text_OliviaIntro:
	.string "Your team looks a bit dull.\n"
	.string "Let me enchant them.\p"
	.string "By which I mean beat them.$"

SootopolisCity_Gym_B1F_Text_OliviaDefeat:
	.string "Fine. Take the compliment. Your\n"
	.string "team is shinier than I thought.$"

SootopolisCity_Gym_B1F_Text_OliviaPostBattle:
	.string "Honestly, the shine is mostly\n"
	.string "the enchantment. Mine.$"

SootopolisCity_Gym_B1F_Text_TiffanyIntro:
	.string "Oh! A visitor! JAINA says no one\n"
	.string "gets past the ice.\p"
	.string "I've been practicing the speech\n"
	.string "for weeks.$"

SootopolisCity_Gym_B1F_Text_TiffanyDefeat:
	.string "Does a defeat count as practice?\n"
	.string "Please say yes.$"

SootopolisCity_Gym_B1F_Text_TiffanyPostBattle:
	.string "I'll get the speech right next\n"
	.string "time. Probably.$"

SootopolisCity_Gym_B1F_Text_BethanyIntro:
	.string "I studied ten years at KIRIN TOR.\n"
	.string "Ten! Do you know how many of those\l"
	.string "involved ice floors? Zero.$"

SootopolisCity_Gym_B1F_Text_BethanyDefeat:
	.string "I'd like to file a formal complaint\n"
	.string "with the floor.$"

SootopolisCity_Gym_B1F_Text_BethanyPostBattle:
	.string "The KIRIN TOR never covered\n"
	.string "this in the curriculum.$"

SootopolisCity_Gym_B1F_Text_AnnikaIntro:
	.string "Halt! No one passes the ADMIRAL\n"
	.string "without going through me.\p"
	.string "Also the mages. They're not very\n"
	.string "reliable.$"

SootopolisCity_Gym_B1F_Text_AnnikaDefeat:
	.string "Well done. Mind the ice on your\n"
	.string "way up. Or don't. I won't be\l"
	.string "there.$"

SootopolisCity_Gym_B1F_Text_AnnikaPostBattle:
	.string "The ADMIRAL is below. Be polite.\n"
	.string "Or don't. He won't be.$"

SootopolisCity_Gym_B1F_Text_DaelinReward:
	.string "DAELIN: My supplies. Salted, stale,\n"
	.string "and mine. Take them.\p"
	.string "Perhaps they will do you more good\n"
	.string "than they did my fleet.$"

SootopolisCity_Gym_B1F_Text_BriannaIntro:
	.string "DAELIN: You fell. Into MY hold.\n"
	.string "Most would have stayed down.\p"
	.string "Let me teach you what the sea does\n"
	.string "to the stubborn.$"

SootopolisCity_Gym_B1F_Text_BriannaDefeat:
	.string "DAELIN: Hmph. The sea favors you\n"
	.string "today.\p"
	.string "Do not mistake that for respect.$"

SootopolisCity_Gym_B1F_Text_BriannaPostBattle:
	.string "DAELIN: Take it, and go. A man pays\n"
	.string "what he owes. Even a bad one.$"

