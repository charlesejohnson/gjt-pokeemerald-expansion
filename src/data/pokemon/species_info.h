#include "constants/abilities.h"
#include "constants/teaching_types.h"
#include "species_info/shared_dex_text.h"
#include "species_info/shared_front_pic_anims.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }
#define CONDITIONS(...) ((const struct EvolutionParam[]) { __VA_ARGS__, {CONDITIONS_END} })

#define ANIM_FRAMES(...) (const union AnimCmd *const[]) { sAnim_GeneralFrame0, (const union AnimCmd[]) { __VA_ARGS__ ANIMCMD_END, }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
#define SHADOW(x, y, size)  .enemyShadowXOffset = x, .enemyShadowYOffset = y, .enemyShadowSize = size,
#define NO_SHADOW           .suppressEnemyShadow = TRUE,
#else
#define SHADOW(x, y, size)  .enemyShadowXOffset = 0, .enemyShadowYOffset = 0, .enemyShadowSize = 0,
#define NO_SHADOW           .suppressEnemyShadow = FALSE,
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if OW_POKEMON_OBJECT_EVENTS
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
#define OVERWORLD_PAL(...)                                  \
    .overworldPalette = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPalette = DEFAULT_2(NULL, __VA_ARGS__),
#if P_GENDER_DIFFERENCES
#define OVERWORLD_PAL_FEMALE(...)                                 \
    .overworldPaletteFemale = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPaletteFemale = DEFAULT_2(NULL, __VA_ARGS__),
#else
#define OVERWORLD_PAL_FEMALE(...)
#endif //P_GENDER_DIFFERENCES
#else
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE

#define OVERWORLD_DATA(picTable, _size, shadow, _tracks, _anims)                                                                     \
{                                                                                                                                       \
    .tileTag = TAG_NONE,                                                                                                                \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                                                            \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                                                                     \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                                                                         \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                                                                           \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                                                                          \
    .paletteSlot = PALSLOT_NPC_1,                                                                                                       \
    .shadowSize = shadow,                                                                                                               \
    .inanimate = FALSE,                                                                                                                 \
    .compressed = COMP,                                                                                                                 \
    .tracks = _tracks,                                                                                                                  \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64),                                             \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),                                                     \
    .anims = _anims,                                                                                                                    \
    .images = picTable,                                                                                                                 \
}

#define OVERWORLD(objEventPic, _size, shadow, _tracks, _anims, ...)                                 \
    .overworldData = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),                   \
    OVERWORLD_PAL(__VA_ARGS__)

#if P_GENDER_DIFFERENCES
#define OVERWORLD_FEMALE(objEventPic, _size, shadow, _tracks, _anims, ...)                          \
    .overworldDataFemale = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),             \
    OVERWORLD_PAL_FEMALE(__VA_ARGS__)
#else
#define OVERWORLD_FEMALE(...)
#endif //P_GENDER_DIFFERENCES

#else
#define OVERWORLD(...)
#define OVERWORLD_FEMALE(...)
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_POKEMON_OBJECT_EVENTS

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_PORYGON,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_TwoFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(QuestionMark)
        SHADOW(-1, 0, SHADOW_SIZE_M)
    #if OW_POKEMON_OBJECT_EVENTS
        .overworldData = {
            .tileTag = TAG_NONE,
            .paletteTag = OBJ_EVENT_PAL_TAG_SUBSTITUTE,
            .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
            .size = 512,
            .width = 32,
            .height = 32,
            .paletteSlot = PALSLOT_NPC_1,
            .shadowSize = SHADOW_SIZE_M,
            .inanimate = FALSE,
            .compressed = COMP,
            .tracks = TRACKS_FOOT,
            .oam = &gObjectEventBaseOam_32x32,
            .subspriteTables = sOamTables_32x32,
            .anims = sAnimTable_Following,
            .images = sPicTable_Substitute,
        },
    #endif
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .eggMoveLearnset = sNoneEggMoveLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    [SPECIES_DEATHKNIGHT] =
    {
    .speciesName = _("Death Knight"),
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
    .abilities = { ABILITY_HYPER_CUTTER, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sDeathknightLevelUpLearnset,
    .teachableLearnset = sDeathknightTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_DEATHKNIGHT,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A spirit from a far\n"
            "away land. Commands \n"
            "death in its wake."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 290,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Deathknight,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 1),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .frontAnimDelay = 15,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_Deathknight,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_Deathknight,
        .shinyPalette = gMonShinyPalette_Deathknight,
                .iconSprite = gMonIcon_Deathknight,
                .iconPalIndex = 2,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_DEATHKNIGHT_BLOOD},
            {EVO_ITEM, ITEM_FIRE_STONE, SPECIES_DEATHKNIGHT_FROST},
            {EVO_ITEM, ITEM_WATER_STONE, SPECIES_DEATHKNIGHT_UNHOLY}),
        FOOTPRINT(Deathknight)

    },
    [SPECIES_DEATHKNIGHT_FROST] =
    {
    .speciesName = _("Frost DK"),
    .baseHP        = 130,
    .baseAttack    = 150,
    .baseDefense   = 110,
    .baseSpeed     = 20,
    .baseSpAttack  = 75,
    .baseSpDefense = 90,
    .types = MON_TYPES(TYPE_GHOST, TYPE_ICE),
    .catchRate = 200,
    .expYield = 255,
    .evYield_Attack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_SNOW_WARNING, ABILITY_NONE, ABILITY_SNIPER },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sDeathknightFrostLevelUpLearnset,
    .teachableLearnset = sDeathknightTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_DEATHKNIGHT_FROST,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A spirit from a far\n"
            "away land. Commands \n"
            "death in its wake."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 290,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Bisharp,
        .frontPicSize = MON_COORDS_SIZE(48, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 1),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .frontAnimDelay = 15,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_Bisharp,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_DeathknightFrost,
        .shinyPalette = gMonShinyPalette_DeathknightFrost,
                .iconSprite = gMonIcon_Bisharp,
                .iconPalIndex = 2,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_DEATHKNIGHT_BLOOD},
            {EVO_ITEM, ITEM_WATER_STONE, SPECIES_DEATHKNIGHT_UNHOLY}),
        FOOTPRINT(Deathknight)
        

    },

    [SPECIES_DEATHKNIGHT_BLOOD] =
    {
    .speciesName = _("Blood DK"),
    .baseHP        = 170,
    .baseAttack    = 110,
    .baseDefense   = 105,
    .baseSpeed     = 20,
    .baseSpAttack  = 90,
    .baseSpDefense = 100,
    .types = MON_TYPES(TYPE_GHOST, TYPE_DARK),
    .catchRate = 200,
    .expYield = 255,
    .evYield_Attack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_WILL_OF_THE_NECROPOLIS, ABILITY_NONE, ABILITY_DARK_AURA },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sDeathknightBloodLevelUpLearnset,
    .teachableLearnset = sDeathknightTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_DEATHKNIGHT_BLOOD,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A spirit from a far\n"
            "away land. Commands \n"
            "death in its wake."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 290,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Bisharp,
        .frontPicSize = MON_COORDS_SIZE(48, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 1),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .frontAnimDelay = 15,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_Bisharp,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_Bisharp,
        .shinyPalette = gMonShinyPalette_Bisharp,
                .iconSprite = gMonIcon_Bisharp,
                .iconPalIndex = 2,
        .evolutions = EVOLUTION(
            {EVO_ITEM, ITEM_FIRE_STONE, SPECIES_DEATHKNIGHT_FROST},
            {EVO_ITEM, ITEM_WATER_STONE, SPECIES_DEATHKNIGHT_UNHOLY}),
        FOOTPRINT(Deathknight)
    

    },
    [SPECIES_DEATHKNIGHT_UNHOLY] =
    {
    .speciesName = _("Unholy DK"),
    .baseHP        = 130,
    .baseAttack    = 90,
    .baseDefense   = 90,
    .baseSpeed     = 20,
    .baseSpAttack  = 135,
    .baseSpDefense = 110,
    .types = MON_TYPES(TYPE_GHOST, TYPE_POISON),
    .catchRate = 200,
    .expYield = 255,
    .evYield_Attack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_POISON_TOUCH, ABILITY_NONE, ABILITY_PARENTAL_BOND },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sDeathknightUnholyLevelUpLearnset,
    .teachableLearnset = sDeathknightTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_DEATHKNIGHT_UNHOLY,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A spirit from a far\n"
            "away land. Commands \n"
            "death in its wake."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 290,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Bisharp,
        .frontPicSize = MON_COORDS_SIZE(48, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 1),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .frontAnimDelay = 15,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_Bisharp,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_DeathknightUnholy,
        .shinyPalette = gMonShinyPalette_DeathknightUnholy,
                .iconSprite = gMonIcon_Bisharp,
                .iconPalIndex = 2,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_DEATHKNIGHT_BLOOD},
            {EVO_ITEM, ITEM_FIRE_STONE, SPECIES_DEATHKNIGHT_FROST}),
        FOOTPRINT(Deathknight)

    },
    [SPECIES_MAGE] =
    {
    .speciesName = _("Mage"),
    .baseHP        = 55,
    .baseAttack    = 15,
    .baseDefense   = 30,
    .baseSpeed     = 90,
    .baseSpAttack  = 95,
    .baseSpDefense = 90,
    .types = MON_TYPES(TYPE_FIRE),
    .catchRate = 200,
    .expYield = 255,
    .evYield_SpAttack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_FROST_ARMOR, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sMageLevelUpLearnset,
    .teachableLearnset = sMageTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_MAGE,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A spirit from a far\n"
            "away land. Master \n"
            "of arcane energies."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 290,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Ralts,
        .frontPicSize = MON_COORDS_SIZE(24, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 15 : 12,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 1),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .frontAnimDelay = 15,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_Ralts,
        .backPicSize = MON_COORDS_SIZE(32, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_Ralts,
        .shinyPalette = gMonShinyPalette_Ralts,
                .iconSprite = gMonIcon_Ralts,
                .iconPalIndex = 2,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_MAGE_ARCANE},
            {EVO_ITEM, ITEM_FIRE_STONE, SPECIES_MAGE_FIRE},
            {EVO_ITEM, ITEM_WATER_STONE, SPECIES_MAGE_FROST}),
        FOOTPRINT(Ralts)

    },
    [SPECIES_MAGE_FROST] =
    {
    .speciesName = _("Frost Mage"),
    .baseHP        = 100,
    .baseAttack    = 20,
    .baseDefense   = 65,
    .baseSpeed     = 116,
    .baseSpAttack  = 128,
    .baseSpDefense = 125,
    .types = MON_TYPES(TYPE_FIRE, TYPE_ICE),
    .catchRate = 200,
    .expYield = 255,
    .evYield_SpAttack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_FROST_ARMOR, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sMageFrostLevelUpLearnset,
    .teachableLearnset = sMageTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_MAGE_FROST,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A spirit from a far\n"
            "away land. Master \n"
            "of arcane energies."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 290,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Gardevoir,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 1),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .frontAnimDelay = 15,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_Gardevoir,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(48, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 6,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_MageFrost,
        .shinyPalette = gMonShinyPalette_MageFrost,
                .iconSprite = gMonIcon_Gardevoir,
                .iconPalIndex = 1,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_MAGE_ARCANE},
            {EVO_ITEM, ITEM_FIRE_STONE, SPECIES_MAGE_FIRE},
            {EVO_ITEM, ITEM_WATER_STONE, SPECIES_MAGE_FROST}),
        FOOTPRINT(Froslass)

    },
    [SPECIES_MAGE_FIRE] =
    {
    .speciesName = _("Fire Mage"),
    .baseHP        = 95,
    .baseAttack    = 20,
    .baseDefense   = 45,
    .baseSpeed     = 126,
    .baseSpAttack  = 158,
    .baseSpDefense = 110,
    .types = MON_TYPES(TYPE_FIRE, TYPE_DRAGON),
    .catchRate = 200,
    .expYield = 255,
    .evYield_SpAttack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_FLASH_FIRE, ABILITY_NONE, ABILITY_HOT_STREAK },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sMageFireLevelUpLearnset,
    .teachableLearnset = sMageTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_MAGE_FIRE,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A spirit from a far\n"
            "away land. Master \n"
            "of arcane energies."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 290,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Gardevoir,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 1),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .frontAnimDelay = 15,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_Gardevoir,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(48, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 6,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_MageFire,
        .shinyPalette = gMonShinyPalette_MageFire,
                .iconSprite = gMonIcon_Gardevoir,
                .iconPalIndex = 1,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_MAGE_ARCANE},
            {EVO_ITEM, ITEM_FIRE_STONE, SPECIES_MAGE_FIRE},
            {EVO_ITEM, ITEM_WATER_STONE, SPECIES_MAGE_FROST}),
        FOOTPRINT(Delphox)

    },
    [SPECIES_MAGE_ARCANE] =
    {
    .speciesName = _("Arcane Mage"),
    .baseHP        = 80,
    .baseAttack    = 20,
    .baseDefense   = 45,
    .baseSpeed     = 136,
    .baseSpAttack  = 164,
    .baseSpDefense = 110,
    .types = MON_TYPES(TYPE_FIRE, TYPE_DRAGON),
    .catchRate = 200,
    .expYield = 255,
    .evYield_SpAttack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_MIRROR_ARMOR, ABILITY_NONE, ABILITY_MANA_BARRIER },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sMageArcaneLevelUpLearnset,
    .teachableLearnset = sMageTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_MAGE_FIRE,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A spirit from a far\n"
            "away land. Master \n"
            "of arcane energies."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 290,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Gardevoir,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 1),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .frontAnimDelay = 15,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_Gardevoir,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(48, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 6,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_MageArcane,
        .shinyPalette = gMonShinyPalette_MageArcane,
                .iconSprite = gMonIcon_Gardevoir,
                .iconPalIndex = 1,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_MAGE_ARCANE},
            {EVO_ITEM, ITEM_FIRE_STONE, SPECIES_MAGE_FIRE},
            {EVO_ITEM, ITEM_WATER_STONE, SPECIES_MAGE_FROST}),
        FOOTPRINT(Nihilego)

    },
    [SPECIES_WARRIOR] =
    {
    .speciesName = _("Warrior"),
    .baseHP        = 70,
    .baseAttack    = 70,
    .baseDefense   = 70,
    .baseSpeed     = 55,
    .baseSpAttack  = 30,
    .baseSpDefense = 40,
    .types = MON_TYPES(TYPE_FIGHTING),
    .catchRate = 200,
    .expYield = 255,
    .evYield_Attack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_GUTS, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sWarriorLevelUpLearnset,
    .teachableLearnset = sWarriorTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_WARRIOR,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A spirit from a far\n"
            "away land. Fights with\n"
            "unbending resolve."),
        .pokemonScale = 422,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Timburr,
        .frontPicSize = MON_COORDS_SIZE(48, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 20),
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 10),
        ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Timburr,
        .backPicSize = MON_COORDS_SIZE(64, 40),
        .backPicYOffset = 15,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_Timburr,
        .shinyPalette = gMonShinyPalette_Timburr,
        .iconSprite = gMonIcon_Timburr,
        .iconPalIndex = 1,
        FOOTPRINT(Timburr)
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_MOON_STONE, SPECIES_WARRIOR_ARMS},
            {EVO_ITEM, ITEM_SUN_STONE, SPECIES_WARRIOR_FURY},
            {EVO_ITEM, ITEM_SHINY_STONE, SPECIES_WARRIOR_PROTECTION}),
    },
    [SPECIES_WARRIOR_ARMS] =
    {
    .speciesName = _("Arms Warrior"),
    .baseHP        = 100,
    .baseAttack    = 140,
    .baseDefense   = 100,
    .baseSpeed     = 90,
    .baseSpAttack  = 45,
    .baseSpDefense = 70,
    .types = MON_TYPES(TYPE_FIGHTING, TYPE_STEEL),
    .catchRate = 200,
    .expYield = 255,
    .evYield_Attack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_SUDDEN_DEATH, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sWarriorArmsLevelUpLearnset,
    .teachableLearnset = sWarriorTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_WARRIOR_ARMS,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "A master of heavy\n"
            "weapons. Every blow\n"
            "is placed to kill."),
        .pokemonScale = 280,
        .pokemonOffset = 1,
        .trainerScale = 269,
        .trainerOffset = -1,
        .frontPic = gMonFrontPic_Machamp,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 11),
            ANIMCMD_FRAME(1, 11),
            ANIMCMD_FRAME(0, 11),
            ANIMCMD_FRAME(1, 11),
            ANIMCMD_FRAME(0, 11),
            ANIMCMD_FRAME(1, 11),
            ANIMCMD_FRAME(0, 11),
        ),
        .frontAnimId = ANIM_H_JUMPS,
        .backPic = gMonBackPic_Machamp,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 56) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 7,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_Machamp,
        .shinyPalette = gMonShinyPalette_Machamp,
        .iconSprite = gMonIcon_Machamp,
        .iconPalIndex = 0,
        FOOTPRINT(Machamp)

    },
    [SPECIES_WARRIOR_FURY] =
    {
    .speciesName = _("Fury Warrior"),
    .baseHP        = 90,
    .baseAttack    = 150,
    .baseDefense   = 75,
    .baseSpeed     = 125,
    .baseSpAttack  = 45,
    .baseSpDefense = 70,
    .types = MON_TYPES(TYPE_FIGHTING, TYPE_STEEL),
    .catchRate = 200,
    .expYield = 255,
    .evYield_Attack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_ENRAGE, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sWarriorFuryLevelUpLearnset,
    .teachableLearnset = sWarriorTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_WARRIOR_FURY,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "Twin blades and a\n"
            "furious temper. Hits\n"
            "faster as rage grows."),
        .pokemonScale = 265,
        .pokemonOffset = 2,
        .trainerScale = 262,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Mienshao,
        .frontPicSize = MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 4,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 50),
        ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Mienshao,
        .backPicSize = MON_COORDS_SIZE(56, 56),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_V_STRETCH,
        .palette = gMonPalette_Mienshao,
        .shinyPalette = gMonShinyPalette_Mienshao,
        .iconSprite = gMonIcon_Mienshao,
        .iconPalIndex = 2,
        FOOTPRINT(Mienshao)

    },
    [SPECIES_WARRIOR_PROTECTION] =
    {
    .speciesName = _("Prot Warrior"),
    .baseHP        = 140,
    .baseAttack    = 95,
    .baseDefense   = 150,
    .baseSpeed     = 55,
    .baseSpAttack  = 40,
    .baseSpDefense = 90,
    .types = MON_TYPES(TYPE_FIGHTING, TYPE_STEEL),
    .catchRate = 200,
    .expYield = 255,
    .evYield_Defense  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_SHIELD_SPECIALIZATION, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_BLACK,
    .perfectIVCount = 3,
    .levelUpLearnset = sWarriorProtectionLevelUpLearnset,
    .teachableLearnset = sWarriorTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_WARRIOR_PROTECTION,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "Stands before allies\n"
            "with a shield raised.\n"
            "Nothing gets past."),
        .pokemonScale = 272,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bastiodon,
        .frontPicSize = MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 10),
            ANIMCMD_FRAME(1, 25),
            ANIMCMD_FRAME(0, 30),
        ),
        .frontAnimId = ANIM_BACK_AND_LUNGE,
        .backPic = gMonBackPic_Bastiodon,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_Bastiodon,
        .shinyPalette = gMonShinyPalette_Bastiodon,
        .iconSprite = gMonIcon_Bastiodon,
        .iconPalIndex = 1,
        FOOTPRINT(Bastiodon)

    },
    [SPECIES_SHAMAN] =
    {
    .speciesName = _("Shaman"),
    .baseHP        = 65,
    .baseAttack    = 50,
    .baseDefense   = 75,
    .baseSpeed     = 60,
    .baseSpAttack  = 70,
    .baseSpDefense = 75,
    .types = MON_TYPES(TYPE_ELECTRIC),
    .catchRate = 200,
    .expYield = 255,
    .evYield_SpAttack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_STATIC, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_YELLOW,
    .perfectIVCount = 3,
    .levelUpLearnset = sShamanLevelUpLearnset,
    .teachableLearnset = sShamanTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_SHAMAN,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "Listens to the spirits of\n"
            "storm, flame and tide.\n"
            "Carries a totem pillar."),
        .pokemonScale = 422,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Timburr,
        .frontPicSize = MON_COORDS_SIZE(48, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 20),
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 10),
        ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Timburr,
        .backPicSize = MON_COORDS_SIZE(64, 40),
        .backPicYOffset = 15,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_Shaman,
        .shinyPalette = gMonShinyPalette_Shaman,
        .iconSprite = gMonIcon_Timburr,
        .iconPalIndex = 1,
        FOOTPRINT(Timburr)
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_MOON_STONE, SPECIES_SHAMAN_RESTORATION},
            {EVO_ITEM, ITEM_SUN_STONE, SPECIES_SHAMAN_ELEMENTAL},
            {EVO_ITEM, ITEM_SHINY_STONE, SPECIES_SHAMAN_ENHANCEMENT}),
    },
    [SPECIES_SHAMAN_RESTORATION] =
    {
    .speciesName = _("Resto Shaman"),
    .baseHP        = 120,
    .baseAttack    = 50,
    .baseDefense   = 115,
    .baseSpeed     = 85,
    .baseSpAttack  = 90,
    .baseSpDefense = 115,
    .types = MON_TYPES(TYPE_ELECTRIC, TYPE_WATER),
    .catchRate = 200,
    .expYield = 255,
    .evYield_SpDefense  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_STORM_DRAIN, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_YELLOW,
    .perfectIVCount = 3,
    .levelUpLearnset = sShamanRestorationLevelUpLearnset,
    .teachableLearnset = sShamanTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_SHAMAN_RESTORATION,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "Calls the tides to mend\n"
            "wounds. Water follows\n"
            "its every command."),
        .pokemonScale = 265,
        .pokemonOffset = 3,
        .trainerScale = 262,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Conkeldurr,
        .frontPicSize = MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(1, 45),
            ANIMCMD_FRAME(0, 10),
        ),
        .frontAnimId = ANIM_V_SHAKE_TWICE,
        .backPic = gMonBackPic_Conkeldurr,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_V_SHAKE_H_SLIDE,
        .palette = gMonPalette_ShamanResto,
        .shinyPalette = gMonShinyPalette_ShamanResto,
        .iconSprite = gMonIcon_Conkeldurr,
        .iconPalIndex = 1,
        FOOTPRINT(Conkeldurr)

    },
    [SPECIES_SHAMAN_ENHANCEMENT] =
    {
    .speciesName = _("Enh Shaman"),
    .baseHP        = 95,
    .baseAttack    = 125,
    .baseDefense   = 75,
    .baseSpeed     = 124,
    .baseSpAttack  = 70,
    .baseSpDefense = 75,
    .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FLYING),
    .catchRate = 200,
    .expYield = 255,
    .evYield_Speed  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_WINDFURY_WEAPON, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_YELLOW,
    .perfectIVCount = 3,
    .levelUpLearnset = sShamanEnhancementLevelUpLearnset,
    .teachableLearnset = sShamanTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_SHAMAN_ENHANCEMENT,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "Wields storm-charged\n"
            "weapons. Strikes ring\n"
            "out again and again."),
        .pokemonScale = 265,
        .pokemonOffset = 3,
        .trainerScale = 262,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Conkeldurr,
        .frontPicSize = MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(1, 45),
            ANIMCMD_FRAME(0, 10),
        ),
        .frontAnimId = ANIM_V_SHAKE_TWICE,
        .backPic = gMonBackPic_Conkeldurr,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_V_SHAKE_H_SLIDE,
        .palette = gMonPalette_ShamanEnh,
        .shinyPalette = gMonShinyPalette_ShamanEnh,
        .iconSprite = gMonIcon_Conkeldurr,
        .iconPalIndex = 1,
        FOOTPRINT(Conkeldurr)

    },
    [SPECIES_SHAMAN_ELEMENTAL] =
    {
    .speciesName = _("Ele Shaman"),
    .baseHP        = 100,
    .baseAttack    = 60,
    .baseDefense   = 80,
    .baseSpeed     = 120,
    .baseSpAttack  = 135,
    .baseSpDefense = 80,
    .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FIRE),
    .catchRate = 200,
    .expYield = 255,
    .evYield_SpAttack  = 2,
    .genderRatio = MON_GENDERLESS,
    .eggCycles = 120,
    .friendship = 0,
    .growthRate = GROWTH_MEDIUM_SLOW,
    .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    .abilities = { ABILITY_ELEMENTAL_OVERLOAD, ABILITY_NONE, ABILITY_NONE },
    .bodyColor = BODY_COLOR_YELLOW,
    .perfectIVCount = 3,
    .levelUpLearnset = sShamanElementalLevelUpLearnset,
    .teachableLearnset = sShamanTeachableLearnset,
    .cryId = CRY_AERODACTYL,
    .natDexNum = NATIONAL_DEX_SHAMAN_ELEMENTAL,
    .categoryName = _("New Species"),
    .height = 15,
    .weight = 330,
    .description = COMPOUND_STRING(
            "Commands lightning and\n"
            "lava. Every spell may\n"
            "echo back twice over."),
        .pokemonScale = 265,
        .pokemonOffset = 3,
        .trainerScale = 262,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Conkeldurr,
        .frontPicSize = MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 6,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(1, 45),
            ANIMCMD_FRAME(0, 10),
        ),
        .frontAnimId = ANIM_V_SHAKE_TWICE,
        .backPic = gMonBackPic_Conkeldurr,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_V_SHAKE_H_SLIDE,
        .palette = gMonPalette_ShamanEle,
        .shinyPalette = gMonShinyPalette_ShamanEle,
        .iconSprite = gMonIcon_Conkeldurr,
        .iconPalIndex = 1,
        FOOTPRINT(Conkeldurr)

    },

    /* You may add any custom species below this point based on the following structure: */

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        .frontPicFemale = gMonFrontPic_CircledQuestionMark,
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicFemale = gMonBackPic_CircledQuestionMarkF,
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .paletteFemale = gMonPalette_CircledQuestionMarkF,
        .shinyPaletteFemale = gMonShinyPalette_CircledQuestionMarkF,
        .iconSpriteFemale = gMonIcon_QuestionMarkF,
        .iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    */
};

const struct EggData gEggDatas[EGG_ID_COUNT] =
{
#include "egg_data.h"
};
