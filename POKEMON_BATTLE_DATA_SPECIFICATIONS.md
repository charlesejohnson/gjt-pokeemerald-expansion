# Pokémon Battle Data Specifications Documentation

## Overview

This document outlines the comprehensive data architecture and connections between files that specify data about Pokémon species, moves, abilities, and their effects in battle through scripting documents in the Pokeemerald Expansion project.

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

#### **Key Design Principles**

**1. Leverage Existing Systems:**
- **Stockpile mechanics** for resource storage and scaling
- **Additional effects** for resource generation
- **Battle script commands** for custom logic
- **String system** for user feedback

**2. Proper Validation:**
- **Resource limits** (max 3 runic power)
- **Consumption validation** (fails gracefully when empty)
- **State tracking** (stat changes, battle history)

**3. Extensible Design:**
- **Multiple generation sources** (different moves can generate runic power)
- **Multiple consumption patterns** (damage, healing, status effects)
- **Configurable limits** (can be adjusted per Pokémon or form)

**4. Clear Naming Convention:**
- **Generic effects:** `EFFECT_RUNIC_CONSUME` for all runic power consumption
- **Descriptive messages:** Different messages for generation vs consumption
- **Consistent naming:** All runic power moves use the same effect system

#### **Integration Points**

**1. Move System Integration:**
```c
// Generation moves
[MOVE_SCOURGE_STRIKE] = {
    .additionalEffects = ADDITIONAL_EFFECTS({
        .moveEffect = MOVE_EFFECT_RUNICPOWER,
        .chance = 100,
    }),
}

// Consumption moves - ALL use the same generic effect
[MOVE_DEATH_STRIKE] = {
    .effect = EFFECT_RUNIC_CONSUME,  // Generic consumption
    .argument = { .absorbPercentage = 50 },
},
[MOVE_FROST_STRIKE] = {
    .effect = EFFECT_RUNIC_CONSUME,  // Generic consumption
    .criticalHitStage = 1,
},
```

**2. Battle Script Integration:**
```c
// Effect-to-script mapping - single entry for all runic consumption
[EFFECT_RUNIC_CONSUME] = {
    .battleScript = BattleScript_EffectSpender,
    .battleTvScore = 3,
    .encourageEncore = TRUE,
},
```

**3. String System Integration:**
```c
// Battle messages with clear naming
const u16 gRunicPowerUsedStringIds[] = {
    [B_MSG_RUNIC_POWERED]       = STRINGID_PKMNRUNICPOWERED,
    [B_MSG_CANT_RUNIC_POWER]    = STRINGID_PKMNCANTRUNICPOWER,
    [B_MSG_USED_RUNIC_POWER]    = STRINGID_PKMNUSEDRUNICPOWER,
    [B_MSG_FAILED_RUNIC_POWER]  = STRINGID_PKMNFAILEDTORUNICPOWER,
};
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

## Battle Scripting System

### Battle Script Commands

**Location:** `data/battle_scripts_1.s` and `data/battle_scripts_2.s`

Battle scripts are assembly-level implementations of move effects and battle mechanics. Each script is referenced by the `BattleMoveEffect` structure.

**Key Script Patterns:**
```assembly
BattleScript_EffectHit::
    attackcanceler
    accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
    attackstring
    ppreduce
    typecalc
    damagecalc
    damagevariation
    checkhitresult
    moveend
```

### Battle Script Command Implementation

**Location:** `src/battle_script_commands.c`

This file contains the C implementations of all battle script commands, providing the runtime execution logic for battle mechanics.

## Data Flow Architecture

### 1. Species → Move Learning

**Flow:** `SpeciesInfo.levelUpLearnset` → `LevelUpMove` arrays → Move IDs

```c
// In pokemon.c
const struct LevelUpMove *GetSpeciesLevelUpLearnset(u16 species) {
    return gSpeciesInfo[SanitizeSpeciesId(species)].levelUpLearnset;
}
```

### 2. Move → Effect → Battle Script

**Flow:** `MoveInfo.effect` → `BattleMoveEffect` → Battle Script

```c
// In battle_util.c
const struct BattleMoveEffect *GetBattleMoveEffect(u16 effect) {
    return &gBattleMoveEffects[effect];
}
```

### 3. Ability → Battle Effects

**Flow:** `Ability` data → Battle script commands → Runtime effects

Abilities are implemented through battle script commands that check ability flags and apply effects.

### 4. Form Changes and Evolution

**Flow:** `SpeciesInfo.formChangeTable` → `FormChange` → Target species

```c
// In pokemon.c
const struct FormChange *GetSpeciesFormChanges(u16 species) {
    return gSpeciesInfo[SanitizeSpeciesId(species)].formChangeTable;
}
```

## File Organization

### Data Definition Files

1. **Species Data:**
   - `src/data/pokemon/species_info.h` - Main species table
   - `src/data/pokemon/species_info/gen_*.h` - Generation-specific data
   - `src/data/pokemon/level_up_learnsets/` - Level-up moves by generation
   - `src/data/pokemon/teachable_learnsets.h` - TM/HM learnable moves
   - `src/data/pokemon/egg_moves.h` - Egg move data
   - `src/data/pokemon/form_change_tables.h` - Form change data

2. **Move Data:**
   - `src/data/moves_info.h` - Complete move definitions
   - `src/data/battle_move_effects.h` - Move effect to script mapping

3. **Ability Data:**
   - `src/data/abilities.h` - Complete ability definitions

### Script Implementation Files

1. **Battle Scripts:**
   - `data/battle_scripts_1.s` - Primary battle script implementations
   - `data/battle_scripts_2.s` - Additional battle scripts
   - `data/battle_anim_scripts.s` - Animation scripts

2. **Runtime Implementation:**
   - `src/battle_script_commands.c` - C implementations of script commands
   - `src/battle_util.c` - Battle utility functions
   - `src/pokemon.c` - Pokémon data access functions

### Header Files

1. **Structure Definitions:**
   - `include/pokemon.h` - Pokémon and ability structures
   - `include/move.h` - Move and effect structures
   - `include/battle.h` - Battle system structures

2. **Constants:**
   - `include/constants/species.h` - Species IDs
   - `include/constants/moves.h` - Move IDs
   - `include/constants/abilities.h` - Ability IDs
   - `include/constants/battle_move_effects.h` - Effect IDs

## Data Relationships

### 1. Species-to-Move Relationships

- **Level-up Moves:** `SpeciesInfo.levelUpLearnset` → `LevelUpMove` arrays
- **Teachable Moves:** `SpeciesInfo.teachableLearnset` → Move ID arrays
- **Egg Moves:** `SpeciesInfo.eggMoveLearnset` → Move ID arrays

### 2. Move-to-Effect Relationships

- **Primary Effect:** `MoveInfo.effect` → `BattleMoveEffect.battleScript`
- **Additional Effects:** `MoveInfo.additionalEffects` → `AdditionalEffect` arrays
- **Animation:** `MoveInfo.battleAnimScript` → Animation script

### 3. Ability-to-Battle Relationships

- **Ability Data:** `Ability` structure → Battle script commands
- **Ability Effects:** Implemented through conditional battle script commands
- **Ability Interactions:** Handled in battle script command implementations

### 4. Form Change Relationships

- **Form Data:** `SpeciesInfo.formChangeTable` → `FormChange` structures
- **Form Triggers:** Method-based form changes (item, move, etc.)
- **Form Effects:** Implemented through battle script commands

## Runtime Data Access

### 1. Species Data Access

```c
// Get species information
const struct SpeciesInfo *GetSpeciesInfo(u16 species);

// Get move learnsets
const struct LevelUpMove *GetSpeciesLevelUpLearnset(u16 species);
const u16 *GetSpeciesTeachableLearnset(u16 species);
const u16 *GetSpeciesEggMoves(u16 species);

// Get evolution data
const struct Evolution *GetSpeciesEvolutions(u16 species);

// Get form change data
const struct FormChange *GetSpeciesFormChanges(u16 species);
```

### 2. Move Data Access

```c
// Get move information
const struct MoveInfo *GetMoveInfo(u16 move);

// Get move properties
u32 GetMoveType(u16 move);
u32 GetMovePower(u16 move);
u32 GetMoveAccuracy(u16 move);
u32 GetMovePP(u16 move);

// Get move effects
const struct BattleMoveEffect *GetBattleMoveEffect(u16 effect);
```

### 3. Ability Data Access

```c
// Get ability information
const struct Ability *GetAbilityInfo(u16 ability);

// Get species abilities
u16 GetAbilityBySpecies(u16 species, u8 abilityNum);
```

## Battle Script Integration

### 1. Script Command System

Battle scripts use a command-based system where each command is implemented in `src/battle_script_commands.c`:

```c
// Example: accuracycheck command
void Cmd_accuracycheck(void) {
    CMD_ARGS(const u8 *failInstr, u16 move);
    // Implementation checks accuracy and branches to failInstr if missed
}
```

### 2. Effect-to-Script Mapping

The `gBattleMoveEffects` table maps effect IDs to their script implementations:

```c
const struct BattleMoveEffect gBattleMoveEffects[] = {
    [EFFECT_HIT] = {
        .battleScript = BattleScript_EffectHit,
        .battleTvScore = 1,
    },
    [EFFECT_SLEEP] = {
        .battleScript = BattleScript_EffectSleep,
        .battleTvScore = 1,
    },
    // ... additional effects
};
```

### 3. Move Effect Execution

When a move is used in battle:

1. **Move Selection:** `MoveInfo.effect` is retrieved
2. **Effect Lookup:** `gBattleMoveEffects[effect]` is found
3. **Script Execution:** `BattleMoveEffect.battleScript` is executed
4. **Command Processing:** Individual script commands are processed by `battle_script_commands.c`

## Data Validation and Constraints

### 1. Species Constraints

- Species IDs must be within valid range (0 to MAX_SPECIES)
- Form species IDs must reference valid base species
- Evolution chains must be acyclic
- Level-up moves must be in ascending level order

### 2. Move Constraints

- Move IDs must be within valid range (0 to MOVES_COUNT_ALL)
- Effect IDs must reference valid battle scripts
- Additional effects must have valid effect IDs
- Contest data must be consistent

### 3. Ability Constraints

- Ability IDs must be within valid range (0 to ABILITIES_COUNT)
- AI ratings should be reasonable values
- Flag combinations must be logical

## Extension Points

### 1. Adding New Species

1. Add species data to `src/data/pokemon/species_info.h`
2. Add level-up moves to appropriate generation file
3. Add teachable moves to `src/data/pokemon/teachable_learnsets.h`
4. Add egg moves to `src/data/pokemon/egg_moves.h`
5. Add form data if applicable

### 2. Adding New Moves

1. Add move data to `src/data/moves_info.h`
2. Add effect to `src/data/battle_move_effects.h`
3. Implement battle script in `data/battle_scripts_*.s`
4. Add animation script to `data/battle_anim_scripts.s`

### 3. Adding New Abilities

1. Add ability data to `src/data/abilities.h`
2. Implement ability effects in battle script commands
3. Add ability checks to relevant battle mechanics

### 4. Adding New Effects

1. Add effect ID to constants
2. Add effect data to `src/data/battle_move_effects.h`
3. Implement battle script in `data/battle_scripts_*.s`
4. Add command implementations to `src/battle_script_commands.c`

### 5. Adding Custom Resource Systems

1. **Identify existing infrastructure** that can be repurposed
2. **Create custom battle script commands** for resource logic
3. **Implement native C functions** for complex resource management
4. **Add appropriate validation** and error handling
5. **Integrate with existing systems** (string, AI, animations)
6. **Document the resource system** and its interactions

## Conclusion

This data architecture provides a comprehensive and extensible system for managing Pokémon battle data. The separation between data definition, script implementation, and runtime execution allows for modular development and easy maintenance. The strong typing and structured relationships ensure data consistency and enable powerful battle mechanics.

The system supports:
- Complex move effects through battle scripts
- Flexible ability implementations
- Dynamic form changes and evolutions
- Custom resource systems (like runic power)
- Extensible data structures for future generations
- Comprehensive validation and error handling

The runic power case study demonstrates how to properly extend the battle system by leveraging existing infrastructure while maintaining code clarity and system integrity. 