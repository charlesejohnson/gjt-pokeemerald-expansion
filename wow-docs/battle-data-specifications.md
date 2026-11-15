# Pokémon Battle Data Specifications Documentation

## Overview

This document outlines the comprehensive data architecture and connections between files that specify data about Pokémon species, moves, abilities, and their effects in battle through scripting documents in the Pokeemerald Expansion project.

**⚠️ Important Note: Always reference the codebase for authoritative information about Pokémon moves, types, and effects. External sources (websites, wikis, etc.) may be outdated or incorrect. The codebase contains the definitive, current implementation.**

## Authoritative Data Sources

**Always use the codebase as the definitive source for Pokémon data:**

- **Move Information:** `src/data/moves_info.h` contains the complete, current move definitions
- **Type Information:** Move types are defined in the `MoveInfo` structure, not external sources
- **Effect Information:** Battle effects are implemented in `src/data/battle_move_effects.h`
- **Species Data:** All species information is in `src/data/pokemon/species_info.h`
- **Ability Data:** Complete ability definitions are in `src/data/abilities.h`

**Why the codebase is authoritative:**
- External sources (wikis, websites) may be outdated or incorrect
- The codebase contains the actual implementation that runs in the game
- Custom modifications and expansions are only reflected in the code
- Type changes, effect modifications, and balance adjustments are in the code

**Example of code-first approach:**
```c
// ✅ Correct: Check the actual move definition
[MOVE_FIRE_BLAST] = {
    .type = TYPE_FIRE,           // Actual type in code
    .power = 110,                // Actual power in code
    .accuracy = 85,              // Actual accuracy in code
    .effect = EFFECT_BURN,       // Actual effect in code
}

// ❌ Incorrect: Relying on external sources
// "Fire Blast is Fire-type with 110 power" (may be outdated)
```

## Core Data Structures

### 1. Pokémon Species Data (`SpeciesInfo`)

**Location:** `include/pokemon.h` (lines 352-481)

The `SpeciesInfo` structure contains comprehensive data for each Pokémon species:

```c
struct SpeciesInfo {
    // Base Stats
    u8 baseHP;
    u8 baseAttack;
    u8 baseDefense;
    u8 baseSpeed;
    u8 baseSpAttack;
    u8 baseSpDefense;
    
    // Type and Catch Data
    u8 types[2];
    u8 catchRate;
    u16 expYield;
    
    // EV Yields
    u16 evYield_HP:2;
    u16 evYield_Attack:2;
    u16 evYield_Defense:2;
    u16 evYield_Speed:2;
    u16 evYield_SpAttack:2;
    u16 evYield_SpDefense:2;
    
    // Items and Breeding
    u16 itemCommon;
    u16 itemRare;
    u8 genderRatio;
    u8 eggCycles;
    u8 friendship;
    u8 growthRate;
    u8 eggGroups[2];
    
    // Abilities
    u16 abilities[NUM_ABILITY_SLOTS]; // Supports 3 abilities
    
    // Move Data
    const struct LevelUpMove *levelUpLearnset;
    const u16 *teachableLearnset;
    const u16 *eggMoveLearnset;
    const struct Evolution *evolutions;
    const u16 *formSpeciesIdTable;
    const struct FormChange *formChangeTable;
    
    // Graphics and Display Data
    const u32 *frontPic;
    const u32 *backPic;
    const u32 *palette;
    const u32 *shinyPalette;
    const u8 *iconSprite;
    
    // Flags and Special Properties
    u32 isLegendary:1;
    u32 isMythical:1;
    u32 isUltraBeast:1;
    u32 isParadox:1;
    // ... additional flags
};
```

**Data Sources:**
- `src/data/pokemon/species_info.h` - Main species data table
- `src/data/pokemon/species_info/gen_*.h` - Generation-specific data
- `src/data/pokemon/level_up_learnsets/` - Level-up move data
- `src/data/pokemon/teachable_learnsets.h` - TM/HM learnable moves
- `src/data/pokemon/egg_moves.h` - Egg move data
- `src/data/pokemon/form_change_tables.h` - Form change data

### 2. Move Data (`MoveInfo`)

**Location:** `include/move.h` (lines 40-139)

The `MoveInfo` structure defines all move properties and effects:

```c
struct MoveInfo {
    // Basic Information
    const u8 *name;
    const u8 *description;
    u16 effect;
    u16 type:5;
    u16 category:2; // Physical/Special/Status
    u16 power:9;
    u16 accuracy:7;
    u16 target:9;
    u8 pp;
    
    // Z-Move Data
    union {
        u8 effect;
        u8 powerOverride;
    } zMove;
    
    // Priority and Critical Hit
    s32 priority:4;
    u32 recoil:7;
    u32 strikeCount:4;
    u32 criticalHitStage:2;
    bool32 alwaysCriticalHit:1;
    
    // Move Properties (Flags)
    bool32 makesContact:1;
    bool32 ignoresProtect:1;
    bool32 magicCoatAffected:1;
    bool32 snatchAffected:1;
    bool32 punchingMove:1;
    bool32 bitingMove:1;
    bool32 pulseMove:1;
    bool32 soundMove:1;
    bool32 ballisticMove:1;
    bool32 powderMove:1;
    bool32 danceMove:1;
    bool32 windMove:1;
    bool32 slicingMove:1;
    bool32 healingMove:1;
    // ... additional flags
    
    // Ban Flags
    bool32 gravityBanned:1;
    bool32 mirrorMoveBanned:1;
    bool32 meFirstBanned:1;
    bool32 mimicBanned:1;
    bool32 metronomeBanned:1;
    bool32 copycatBanned:1;
    bool32 assistBanned:1;
    bool32 sleepTalkBanned:1;
    bool32 instructBanned:1;
    bool32 encoreBanned:1;
    bool32 parentalBondBanned:1;
    bool32 skyBattleBanned:1;
    bool32 sketchBanned:1;
    
    // Effect Arguments
    union {
        struct {
            u16 stringId;
            u16 status;
        } twoTurnAttack;
        struct {
            u16 side;
            u16 property;
        } protect;
        u32 status;
        u16 moveProperty;
        u16 holdEffect;
        u16 type;
        u16 fixedDamage;
        u16 absorbPercentage;
    } argument;
    
    // Additional Effects
    const struct AdditionalEffect *additionalEffects;
    
    // Contest Data
    u8 contestEffect;
    u8 contestCategory:3;
    u8 contestComboStarterId;
    u8 contestComboMoves[MAX_COMBO_MOVES];
    
    // Battle Animation
    const u8 *battleAnimScript;
};
```

**Data Sources:**
- `src/data/moves_info.h` - Complete move data table
- `data/battle_anim_scripts.s` - Battle animation scripts
- `src/data/battle_move_effects.h` - Move effect definitions

### 3. Ability Data (`Ability`)

**Location:** `include/pokemon.h` (lines 483-495)

The `Ability` structure defines ability properties:

```c
struct Ability {
    u8 name[ABILITY_NAME_LENGTH + 1];
    const u8 *description;
    s8 aiRating;
    u8 cantBeCopied:1;
    u8 cantBeSwapped:1;
    u8 cantBeTraced:1;
    u8 cantBeSuppressed:1;
    u8 cantBeOverwritten:1;
    u8 breakable:1;
    u8 failsOnImposter:1;
};
```

**Data Sources:**
- `src/data/abilities.h` - Complete ability data table

### 4. Battle Move Effects (`BattleMoveEffect`)

**Location:** `include/move.h` (lines 9-18)

The `BattleMoveEffect` structure links moves to their battle script implementations:

```c
struct BattleMoveEffect {
    const u8 *battleScript;  // Points to battle script implementation
    u16 battleTvScore:3;
    u16 encourageEncore:1;
    u16 twoTurnEffect:1;
    u16 semiInvulnerableEffect:1;
    u16 usesProtectCounter:1;
    u16 padding:9;
};
```

**Data Sources:**
- `src/data/battle_move_effects.h` - Effect-to-script mapping table

## Custom Resource Systems

### Case Study: Runic Power Implementation

The runic power system demonstrates how to extend the battle system with custom resource mechanics by leveraging existing infrastructure.

#### **System Architecture**

**Resource Storage:**
```c
// Reuses existing DisableStruct fields
struct DisableStruct {
    u8 stockpileCounter;        // Runic power counter (0-3)
    s8 stockpileDef;           // Stat tracking for runic effects
    s8 stockpileSpDef;         // Stat tracking for runic effects
    s8 stockpileBeforeDef;     // Original stats before runic power
    s8 stockpileBeforeSpDef;   // Original stats before runic power
}
```

**Resource Generation:**
```c
// MOVE_EFFECT_RUNICPOWER in additional effects
.additionalEffects = ADDITIONAL_EFFECTS({
    .moveEffect = MOVE_EFFECT_RUNICPOWER,
    .chance = 100,
}),
```

**Resource Consumption:**
```c
// Uses existing stockpile damage scaling
BattleScript_EffectSpender::
    stockpiletobasedamage BattleScript_SpitUpFail  // Validates and scales damage
    goto BattleScript_HitFromAtkAnimation
```

#### **Implementation Components**

**1. Custom Battle Script Command:**
```assembly
.macro runicpower id:req
    callnative BS_RunicPower
```

**2. Native C Implementation:**
```c
void BS_RunicPower(void)
{
    CMD_ARGS(u8 id);
    
    switch (cmd->id)
    {
    case 0: // Generate runic power
        if (gDisableStructs[gBattlerAttacker].stockpileCounter >= 3)
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CANT_RUNIC_POWER;
        }
        else
        {
            gDisableStructs[gBattlerAttacker].stockpileCounter++;
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_RUNIC_POWERED;
        }
        break;
    case 1: // Consume runic power (for damage scaling)
        if (gDisableStructs[gBattlerAttacker].stockpileCounter > 0)
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_USED_RUNIC_POWER;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_FAILED_RUNIC_POWER;
        }
        break;
    case 2: // Save stat changes for runic power effects
        // Track stat changes for runic power consumption
        break;
    }
}
```

**3. Validation and Error Handling:**
```c
// Automatic validation through stockpile system
static void Cmd_stockpiletobasedamage(void)
{
    if (gDisableStructs[gBattlerAttacker].stockpileCounter == 0)
    {
        gBattlescriptCurrInstr = failInstr;  // "But it failed!"
        return;
    }
    // Proceed with damage calculation
}
```

#### **Best Practices for Custom Resource Systems**

**1. Reuse Existing Infrastructure:**
- **Storage:** Use existing struct fields when possible
- **Validation:** Leverage existing validation systems
- **Scaling:** Use existing damage/effect scaling mechanisms
- **UI:** Integrate with existing string and message systems

**2. Proper Error Handling:**
- **Graceful failure:** Moves should fail with appropriate messages
- **State validation:** Check resource availability before consumption
- **Edge case handling:** Consider all possible battle states

**3. Clear Naming and Documentation:**
- **Descriptive effect names:** `MOVE_EFFECT_RUNIC_GENERATE` vs `MOVE_EFFECT_RUNICPOWER`
- **Consistent naming:** Use the same pattern for related effects
- **Documentation:** Explain the resource system and its interactions

**4. Balance and Thematic Consistency:**
- **Resource costs:** Generation should have some cost or limitation
- **Strategic depth:** Multiple ways to generate and consume resources
- **Thematic integration:** Resource mechanics should fit the Pokémon's theme

**5. Battle Script Command System:**
- **Use existing commands:** Leverage built-in battle script commands like `stockpile`
- **Command registration:** Custom commands must be properly registered in the command table
- **Function call chain:** Battle script → Command table → C function
- **Parameter validation:** Ensure command parameters match expected function signatures

#### **Learnset Management Best Practices**

**1. Preserve Existing Moves:**
- **Never remove existing moves** when adding new moves to learnsets
- **When level conflicts occur:** Keep both moves at the same level or move existing moves to different levels
- **Multiple moves per level:** Pokémon can learn multiple moves at the same level
- **Documentation:** Update CSV files to reflect all moves, not just new ones

**2. Learnset Update Guidelines:**
```c
// ✅ Correct: Preserve existing moves
static const struct LevelUpMove sMageLevelUpLearnset[] = {
    LEVEL_UP_MOVE( 1, MOVE_POUND),
    LEVEL_UP_MOVE( 1, MOVE_CONFUSION),
    LEVEL_UP_MOVE( 6, MOVE_EMBER),
    LEVEL_UP_MOVE( 9, MOVE_POWDER_SNOW),
    LEVEL_UP_MOVE( 10, MOVE_TELEPORT),        // Existing move preserved
    LEVEL_UP_MOVE( 10, MOVE_ARCANE_MISSILES), // New move added
    LEVEL_UP_MOVE( 12, MOVE_DOUBLE_TEAM),
    LEVEL_UP_MOVE( 14, MOVE_FIRE_SPIN),
    LEVEL_UP_MOVE( 18, MOVE_ICY_WIND),        // Existing move preserved
    LEVEL_UP_MOVE( 18, MOVE_ARCANE_INTELLECT), // New move added
    LEVEL_UP_MOVE( 22, MOVE_PSYBEAM),
    LEVEL_UP_END
};

// ❌ Incorrect: Removing existing moves
static const struct LevelUpMove sMageLevelUpLearnset[] = {
    LEVEL_UP_MOVE( 1, MOVE_POUND),
    LEVEL_UP_MOVE( 1, MOVE_CONFUSION),
    LEVEL_UP_MOVE( 6, MOVE_EMBER),
    LEVEL_UP_MOVE( 9, MOVE_POWDER_SNOW),
    LEVEL_UP_MOVE( 10, MOVE_ARCANE_MISSILES), // Only new move, removed TELEPORT
    LEVEL_UP_MOVE( 12, MOVE_DOUBLE_TEAM),
    LEVEL_UP_MOVE( 14, MOVE_FIRE_SPIN),
    LEVEL_UP_MOVE( 18, MOVE_ARCANE_INTELLECT), // Only new move, removed ICY_WIND
    LEVEL_UP_MOVE( 22, MOVE_PSYBEAM),
    LEVEL_UP_END
};
```

**3. Level Conflict Resolution:**
- **Option 1:** Keep both moves at the same level (recommended)
- **Option 2:** Move existing move to a different level (if thematic progression requires it)
- **Option 3:** Add new move at a different level to avoid conflict

**4. Documentation Updates:**
- **CSV Files:** Update all move entries, not just new ones
- **PP Values:** Include PP capacity for all moves
- **Implementation Status:** Mark moves as implemented (x) or script needed (s)
- **Level Learned:** Document the exact level each move is learned

#### **Debugging Battle Script Systems**

**1. Command Registration Issues:**
```c
// ❌ Problem: Undefined command causes freeze
BattleScript_EffectRunicPower::
    runicpower 0  // Not registered in command table
    printfromtable gRunicPowerUsedStringIds

// ✅ Solution: Use existing registered command
BattleScript_EffectRunicPower::
    stockpile 0    // Properly registered command
    printfromtable gRunicPowerUsedStringIds
```

## Unit Testing Battle Systems

### Test Infrastructure

**Location:** `test/battle/move_effect/` directory contains all move effect tests

**Key Files:**
- `test/battle.h` - Main test framework header
- `test/battle/move_effect/*.c` - Individual move effect test files
- `Makefile` - Test build configuration

### Test Execution

**Correct Commands:**
```bash
# Run all tests
make check

# Run specific test files
make check TEST_FILTER=fire_mage_moves
make check TEST_FILTER=scourge_strike

# Run tests with specific patterns
make check TEST_FILTER=blast_wave
```

**❌ Incorrect:** `make test` (doesn't exist)
**✅ Correct:** `make check` (proper test target)

### Test File Structure

**Required Header:**
```c
#include "test/battle.h"  // ✅ Correct
// #include "test/battle/test.h"  // ❌ Incorrect
```

**Test Structure:**
```c
ASSUMPTIONS {
    ASSUME(gMovesInfo[MOVE_MOVE_NAME].effect == EFFECT_HIT);
    ASSUME(gMovesInfo[MOVE_MOVE_NAME].power == 50);
    ASSUME(gMovesInfo[MOVE_MOVE_NAME].type == TYPE_FIRE);
}

SINGLE_BATTLE_TEST("Test description") {
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MOVE_NAME); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MOVE_NAME, player);
        HP_BAR(opponent);
        // Additional scene expectations
    } THEN {
        // State verification
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
    }
}
```

### Test Categories

#### 1. **Basic Move Testing**
```c
SINGLE_BATTLE_TEST("Move deals damage and applies effect") {
    GIVEN { PLAYER(SPECIES_WOBBUFFET); OPPONENT(SPECIES_WOBBUFFET); }
    WHEN { TURN { MOVE(player, MOVE_BLAST_WAVE); } }
    SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLAST_WAVE, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("Foe Wobbuffet's Speed fell!");
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
    }
}
```

#### 2. **Two-Turn Move Testing**
```c
SINGLE_BATTLE_TEST("Two-turn move charges then attacks") {
    GIVEN { PLAYER(SPECIES_WOBBUFFET); OPPONENT(SPECIES_WOBBUFFET); }
    WHEN {
        TURN { MOVE(player, MOVE_PYROBLAST); }
        TURN { SKIP_TURN(player); }
    } SCENE {
        MESSAGE("Wobbuffet is charging a massive fireball!");
        NOT MESSAGE("Wobbuffet used Pyroblast!");
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_PYROBLAST, player);
        NOT HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(player->status2, STATUS2_CHARGING);
    }
}
```

#### 3. **Double Battle Testing**
```c
SINGLE_BATTLE_TEST("Move hits both targets in double battle") {
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET); PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET); OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BLAST_WAVE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BLAST_WAVE, playerLeft);
        HP_BAR(opponentLeft); HP_BAR(opponentRight);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
        MESSAGE("Foe Wobbuffet's Speed fell!");
        MESSAGE("Foe Wynaut's Speed fell!");
    } THEN {
        EXPECT_EQ(opponentLeft->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
        EXPECT_EQ(opponentRight->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
    }
}
```

#### 4. **Status Effect Testing**
```c
SINGLE_BATTLE_TEST("Move increases critical hit stage") {
    GIVEN { PLAYER(SPECIES_WOBBUFFET); OPPONENT(SPECIES_WOBBUFFET); }
    WHEN { TURN { MOVE(player, MOVE_PHOENIX_FLAMES); } }
    SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PHOENIX_FLAMES, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(player->status2 & STATUS2_FOCUS_ENERGY, STATUS2_FOCUS_ENERGY);
    }
}
```

### Test Best Practices

#### 1. **ASSUMPTIONS Section**
- Verify move data matches implementation
- Check power, type, accuracy, effects
- Ensure critical hit stages are set correctly

#### 2. **GIVEN/WHEN/SCENE/THEN Structure**
- **GIVEN:** Set up battle conditions and Pokémon
- **WHEN:** Execute the move(s) being tested
- **SCENE:** Verify animations, messages, and visual effects
- **THEN:** Check final state (stat stages, status flags, etc.)

#### 3. **Message and Animation Testing**
```c
SCENE {
    ANIMATION(ANIM_TYPE_MOVE, MOVE_MOVE_NAME, player);  // Move animation
    HP_BAR(opponent);                                   // Damage dealt
    ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);  // Stat change
    MESSAGE("Foe Wobbuffet's Speed fell!");            // Status message
}
```

#### 4. **State Verification**
```c
THEN {
    EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
    EXPECT_TRUE(gMovesInfo[MOVE_MOVE_NAME].windMove);
    EXPECT_EQ(gMovesInfo[MOVE_MOVE_NAME].battleAnimScript, gBattleAnimMove_SolarBeam);
}
```

### Common Test Patterns

#### **Accuracy Testing**
```c
SINGLE_BATTLE_TEST("Move has correct accuracy") {
    GIVEN { PLAYER(SPECIES_WOBBUFFET); OPPONENT(SPECIES_WOBBUFFET); }
    WHEN { TURN { MOVE(player, MOVE_MOVE_NAME); } }
    SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MOVE_NAME, player);
        HP_BAR(opponent);
    } THEN {
        // Test will pass if hit, fail if miss (based on accuracy)
    }
}
```

#### **Property Verification**
```c
SINGLE_BATTLE_TEST("Move has correct properties") {
    GIVEN { PLAYER(SPECIES_WOBBUFFET); OPPONENT(SPECIES_WOBBUFFET); }
    WHEN { TURN { MOVE(player, MOVE_MOVE_NAME); } }
    SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MOVE_NAME, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_TRUE(gMovesInfo[MOVE_MOVE_NAME].validApprenticeMove);
        EXPECT_EQ(gMovesInfo[MOVE_MOVE_NAME].contestCategory, CONTEST_CATEGORY_COOL);
        EXPECT_EQ(gMovesInfo[MOVE_MOVE_NAME].contestEffect, CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS);
    }
}
```

### Debugging Test Issues

#### **"Nothing to be done for 'test'" Error**
- **Cause:** Using `make test` instead of `make check`
- **Solution:** Use `make check` or `make check TEST_FILTER=pattern`

#### **Test File Not Found**
- **Cause:** Incorrect include path (`#include "test/battle/test.h"`)
- **Solution:** Use `#include "test/battle.h"`

#### **Compilation Errors**
- **Check:** Move constants are defined in `include/constants/moves.h`
- **Check:** Effect constants are defined in `include/constants/battle.h`
- **Check:** Animation scripts are properly referenced

#### **Message Pattern Mismatches**
- **Issue:** Tests fail with "Unmatched MESSAGE" errors
- **Solution:** Check actual message strings in `src/battle_message.c`
- **Example:** `STRINGID_PKMNCHARGINGPOWER` maps to "{B_ATK_NAME_WITH_PREFIX} began charging power!"
- **Best Practice:** Use existing test files as reference for correct message patterns

#### **Animation Testing Issues**
- **Issue:** Tests expect no animation but animation plays
- **Solution:** For two-turn moves, allow animations on first turn (charging animations)
- **Pattern:** Use `NONE_OF` for messages/effects that shouldn't appear, but don't block animations
- **Example:** 
```c
NONE_OF {
    MESSAGE("Wobbuffet used Pyroblast!");
    HP_BAR(opponent);
    // Don't include ANIMATION here - charging animations are normal
}
```

#### **Double Battle Message Patterns**
- **Issue:** "Foe" vs "The opposing" message patterns
- **Solution:** Use "The opposing [Pokémon]'s [stat] fell!" format
- **Reference:** Check existing double battle tests for correct patterns

### Test Coverage Guidelines

#### **Essential Tests for New Moves:**
1. **Basic Functionality:** Damage, accuracy, targeting
2. **Special Effects:** Status changes, stat modifications
3. **Two-Turn Mechanics:** Charging, execution
4. **Double Battle:** Multi-target behavior
5. **Edge Cases:** Zero resources, invalid states
6. **Properties:** Contest data, apprentice moves, animations

#### **Regression Prevention:**
- Test move data integrity (power, type, accuracy)
- Verify effect implementations
- Check animation and message systems
- Validate contest and apprentice move properties