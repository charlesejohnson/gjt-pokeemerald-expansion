

[SPECIES_DEATHKNIGHT] =
{
   .baseHP        = 80,
   .baseAttack    = 85,
   .baseDefense   = 70,
   .baseSpeed     = 20,
   .baseSpAttack  = 65,
   .baseSpDefense = 75,
   .types = MON_TYPES(TYPE_GHOST),
   .catchRate = 200,
   .expYield = 255,
   .evYield_Attack  = 2,
   .genderRatio = MON_GENDERLESS,
   .eggCycles = 120,
   .friendship = 0,
   .growthRate = GROWTH_MEDIUM_SLOW,
   .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
   .abilities = { ABILITY_INSOMNIA, ABILITY_NONE, ABILITY_NONE },
   .bodyColor = BODY_COLOR_BLACK,
   .isLegendary = True,
   .perfectIVCount = 3,
   .levelUpLearnset = sDeathknightLevelUpLearnset,
   .teachableLearnset = sDeathknightTeachableLearnset,
   .cryId = CRY_AERODACTYL
   .natDexNum = NATIONAL_DEX_DEATHKNIGHT
   .categoryName = _("New Species")
   .height = 15
   .weight = 330
   .description = COMPOUND_STRING(
        "A spirit from a far\n"
        "away land. Commands \n"
        "death in its wake."),
    .pokemonScale = 256
    .pokemonOffset = 0
    .trainerScale = 290,
    .trainerOffset = 2,
    .frontPic = gMonFrontPic_Deathknight,
    .frontPicSize = MON_COORDS_SIZE(64, 64),
    .frontPicYOffset = 0
    .frontAnimFrames = ANIM_FRAMES(
        ANIMCMD_FRAME(0, 1),
    ),
    .frontAnimId = ANIM_GROW_VIBRATE,
    .frontAnimDelay = 15,
    .enemyMonElevation = 6,
    .backPic = gMonBackPic_Deathknight,
    .backPicSize = MON_COORDS_SIZE(64, 64),
    .backPicYOffset = 0,
    .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
    .palette = gMonPalette_Deathknight,
    .shinyPalette = gMonShinyPalette_Deathknight,
            .iconSprite = gMonIcon_Deathknight,
            .iconPalIndex = 2,
    FOOTPRINT(Deathknight)

},