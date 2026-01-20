# Compiler Warnings Baseline

**Purpose:** Track compiler warnings across different toolchains to identify portability issues  
**Date Created:** January 19, 2026  
**CI Run:** [#21151257423](https://github.com/TheSuperHackers/GeneralsGameCode/actions/runs/21151257423) (main branch, commit 5265436)

## Executive Summary

| Compiler | Configuration | Total Warnings | Unique Types | Status |
|----------|---------------|----------------|--------------|--------|
| VC6 | Release+t+e | 55 | 2 | ✅ Baseline captured |
| MSVC C++20 | win32 Release+t+e | 1,499 | 20+ | ✅ Baseline captured |
| MinGW-w64 GCC | i686 Release | 4,529 | 4+ | ✅ Baseline captured |

**IMPORTANT UPDATE:** All three compilers build successfully! MinGW-w64 produces working executables with 4,529 warnings (95% are offsetof on non-standard-layout types - conditionally-supported, not errors).

### Key Findings

1. **VC6 is remarkably clean** - Only 55 warnings, mostly macro redefinitions
2. **MSVC C++20 is MUCH stricter** - 1,499 warnings (27× more than VC6)
3. **MinGW-w64 GCC is MOST strict** - 4,529 warnings (3× more than MSVC, 82× more than VC6)
4. **95% of MinGW warnings are ONE issue** - offsetof on non-standard-layout types (4,305/4,529)
5. **GCC exposes what MSVC hides** - offsetof portability issues silently accepted by MSVC
6. **Windows SDK headers generate noise** - 993 MSVC warnings from Windows Kit headers alone (C4114)
7. **Deprecated API usage** - 51 swprintf, 9 gethostbyname, 8 GetVersionExA warnings (MSVC)
8. **Signed/unsigned mismatches** - 174 instances (C4018) - portability red flag (MSVC)
9. **Three-compiler strategy validated** - VC6 (55) | MSVC C++20 (1,499) | MinGW-w64 GCC (4,529) all build successfully

## Warning Categories

### Priority Classification

| Priority | Description | Action |
|----------|-------------|--------|
| **P0 - Must Fix** | Breaks MinGW or causes UB | Fix immediately |
| **P1 - Should Fix** | Real portability issues | Fix in Phase 2 |
| **P2 - Legacy Noise** | Accepted technical debt | Document and suppress locally |
| **P3 - External** | From Windows SDK or dependencies | Ignore (not our code) |

---

## VC6 Warnings Baseline

**Build:** `Generals / vc6+t+e` (Release with tools and extras)  
**Total Warnings:** 55  
**Build Status:** ✅ Success

### Warning Breakdown

| Count | Code | Description | Files | Priority |
|-------|------|-------------|-------|----------|
| 42 | C4005 | Macro redefinition: `NUM_ALPHA_TILES` | `WHeightMapEdit.h` | P2 |
| 12 | C4800 | `int` forced to `bool` | `GameText.cpp` | P1 |
| 1 | C4005 | Macro redefinition: `WIN32_LEAN_AND_MEAN` | `registry.cpp` | P2 |

### Detailed Analysis

#### C4005: Macro Redefinition (43 instances)

**File: `WHeightMapEdit.h:60`**
```cpp
warning C4005: 'NUM_ALPHA_TILES' : macro redefinition
```
**Occurrences:** 42 (WorldBuilder tool headers)

**Cause:** Header included multiple times with different preprocessor states

**Action:** P2 - Legacy noise from WorldBuilder tool (not core game)

**File: `registry.cpp:25`**
```cpp
warning C4005: 'WIN32_LEAN_AND_MEAN' : macro redefinition
```
**Occurrences:** 1

**Cause:** Windows header inclusion order issue

**Action:** P2 - Define only once, add include guards

---

#### C4800: Implicit int-to-bool Conversion (12 instances)

**Files:**
- `Core/Tools/Autorun/GameText.cpp:817`
- `Core/Tools/Autorun/GameText.cpp:1041`
- `Core/Tools/Autorun/GameText.cpp:1117`

**Pattern:**
```cpp
bool result = some_int_expression;  // Implicit conversion
```

**Reason:** VC6 warns about performance implications of int→bool coercion

**Action:** P1 - Use explicit comparison: `!= 0` or `== 0`

**MinGW Impact:** GCC will likely warn with `-Wconversion`

---

## MSVC C++20 Warnings Baseline

**Build:** `Generals / win32+t+e` (Release with tools and extras)  
**Total Warnings:** 1,499  
**Build Status:** ✅ Success

### Warning Breakdown (Top 20)

| Count | Code | Description | Priority |
|-------|------|-------------|----------|
| 993 | C4114 | Same type qualifier used more than once | P3 |
| 62 | C4180 | Qualifier applied to function type has no meaning | P3 |
| 174 | C4018 | Signed/unsigned mismatch (various operators) | P1 |
| 51 | C4996 | `swprintf` deprecated | P1 |
| 42 | C4005 | `NUM_ALPHA_TILES` macro redefinition | P2 |
| 65 | C5055 | Enum/float arithmetic deprecated | P0 |
| 28 | C4267 | `size_t` to smaller type conversion | P1 |
| 9 | C4996 | `gethostbyname` deprecated | P1 |
| 8 | C4996 | `GetVersionExA` deprecated | P1 |
| 8 | C4244 | `time_t` to `sint32` conversion | P1 |
| 4 | C4996 | `inet_addr` deprecated | P1 |
| 4 | C4477 | Format string issues with `sprintf` | P0 |
| 1 | C4535 | `_set_se_translator()` requires `/EHa` | P2 |
| 3 | C5287 | Enum type mismatch in GameSpy code | P3 |

### Detailed Analysis

#### P3 - External / Ignorable

##### C4114: Same Type Qualifier Used More Than Once (993 instances)
**Source:** Windows SDK headers (`ole2.h`, `rpcdcep.h`)

**Example:**
```cpp
// Windows Kit 10.0.26100.0 headers
C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\um\ole2.h(116)
warning C4114: same type qualifier used more than once
```

**Action:** IGNORE - Microsoft's SDK headers, not our code

**Suppression:** Already handled by SDK warning pragma wrappers

---

##### C4180: Qualifier Applied to Function Type (62 instances)
**Source:** Windows SDK headers (`rpcdcep.h`)

**Example:**
```cpp
C:\Program Files (x86)\Windows Kits\10\include\10.0.26100.0\shared\rpcdcep.h(844)
warning C4180: qualifier applied to function type has no meaning; ignored
```

**Action:** IGNORE - Microsoft's SDK headers

---

##### C5287: Enum Type Mismatch (3 instances)
**Source:** GameSpy SDK (`gpiconnect.c`, `gpisearch.c`, `sb_serverbrowsing.c`)

**Example:**
```cpp
build\win32\_deps\gamespy-src\src\gp\gpiconnect.c(427)
warning C5287: operands are different enum types '_GPIBool' and '_GPEnum'
```

**Action:** IGNORE - External dependency (GameSpy SDK)

---

#### P0 - Must Fix (Blocks MinGW or Causes UB)

**UPDATE:** MinGW-w64 builds successfully on `mingw-w64-build` branch! The P0 warnings below are **MSVC-specific** and do not block MinGW compilation. GCC handles these differently.

##### C5055: Enum/Float Arithmetic Deprecated (65 instances)

**Pattern:**
```cpp
EnumType value = 5.0f / SomeEnum::Value;  // Deprecated in C++20
EnumType value = SomeEnum::Value * 1.5f;  // Deprecated in C++20
EnumType value = SomeEnum::Value + 2.0f;  // Deprecated in C++20
```

**Distribution:**
- `/` (divide): 30 instances
- `*` (multiply): 30 instances
- `+` (add): 19 instances
- `-` (subtract): 6 instances

**Files:**
- `Generals/Code/Libraries/Source/WWVegas/WW3D2/ww3d.cpp(163)`
- Various 3D rendering and animation code

**Reason:** C++20 standard deprecated implicit arithmetic between enums and floating-point types

**MinGW Impact:** 🟢 **MinGW builds successfully** - GCC compiles without error (may warn with `-Wpedantic`)

**MSVC Impact:** ⚠️ MSVC C++20 warns (C5055) but compiles

**Fix (Optional for Warning Cleanup):**
```cpp
// Before
float result = SomeEnum::Value / 2.0f;

// After
float result = static_cast<float>(SomeEnum::Value) / 2.0f;
```

**Action:** P1 (downgraded from P0) - Add explicit casts to clean up MSVC warnings, not blocking MinGW

---

##### C4477: Format String Issues (4 instances)

**Pattern:**
```cpp
sprintf(buffer, "%d", some_value);  // Type mismatch with format specifier
```

**MinGW Impact:** 🟡 **GCC will warn with `-Wformat`** (not enabled by default in MinGW build)

**MSVC Impact:** ⚠️ MSVC warns (C4477)

**Action:** P1 - Fix format specifiers to match argument types when enabling strict warnings

---

#### P1 - Should Fix (Real Portability Issues)

##### C4018: Signed/Unsigned Mismatch (174 instances)

**Distribution by Operator:**
- `<` : 54 instances
- `>` : 48 instances
- `>=` : 37 instances
- `<=` : 13 instances
- (other): 22 instances

**Example Files:**
```
Generals\Code\Libraries\Source\WWVegas\WW3D2\ddsfile.cpp(102): '<='
Generals\Code\Libraries\Source\WWVegas\WW3D2\ddsfile.cpp(106): '>='
Core\Libraries\Source\WWVegas\WW3D2\textureloader.cpp(1329): '>='
Core\Libraries\Source\WWVegas\WW3D2\textureloader.cpp(1366): '>='
Core\Libraries\Source\profile\profile_result.cpp(222): '>'
Core\Libraries\Source\profile\profile_result.cpp(225): '>'
Core\Libraries\Source\debug\debug_io_con.cpp(90): '>'
Core\Libraries\Source\debug\debug_io_con.cpp(172): '<='
Core\Libraries\Source\debug\debug_debug.cpp(720): '<'
Core\Libraries\Source\debug\debug_debug.cpp(722): '<'
```

**MinGW Impact:** 🟡 **GCC will warn with `-Wsign-compare` (enabled by `-Wall`)**

**Pattern:**
```cpp
int signed_value = -1;
size_t unsigned_value = 10;
if (signed_value < unsigned_value) {  // WARNING: signed/unsigned mismatch
    // If signed_value is negative, it gets cast to huge unsigned value!
}
```

**Real Bug Example:**
```cpp
int offset = -5;
size_t length = strlen(str);
if (offset < length) {  // BUG! offset converts to ~4 billion
    // This branch NEVER executes for negative offsets!
}
```

**Action:** 
1. Review all 174 instances
2. Fix with explicit casts or type changes
3. Priority: Conditions involving negative values or loop indices

---

##### C4996: Deprecated Windows APIs (68 instances)

**swprintf (51 instances):**
```cpp
Core\Libraries\Source\WWVegas\WWLib\widestring.cpp(many)
warning C4996: 'swprintf': function has been changed to conform with the ISO C standard,
adding an extra character count parameter. To use the traditional Microsoft version,
set _CRT_NON_CONFORMING_SWPRINTFS.
```

**Fix:**
```cpp
// Before
wchar_t buffer[256];
swprintf(buffer, L"Value: %d", value);

// After (C99 standard)
wchar_t buffer[256];
swprintf(buffer, 256, L"Value: %d", value);
```

**gethostbyname (9 instances):**
```cpp
warning C4996: 'gethostbyname': Use getaddrinfo() or GetAddrInfoW() instead
```

**GetVersionExA (8 instances):**
```cpp
warning C4996: 'GetVersionExA': was declared deprecated
```

**inet_addr (4 instances):**
```cpp
warning C4996: 'inet_addr': Use inet_pton() or InetPton() instead
```

**MinGW Impact:** 🟢 MinGW likely won't warn (not CRT-specific)

**Action:** 
- P1 for `swprintf` (easy fix, 51 instances)
- P2 for network APIs (requires more refactoring, Windows XP compat concern)

---

##### C4267: size_t to Smaller Type Conversion (28 instances)

**Pattern:**
```cpp
size_t length = strlen(str);
UnsignedShort short_len = length;  // WARNING: possible data loss
UnsignedByte byte_len = length;    // WARNING: possible data loss
```

**MinGW Impact:** 🟡 **GCC will warn with `-Wconversion`**

**Action:** Add explicit casts after range validation

---

##### C4244: Type Conversion with Possible Data Loss (8+ instances)

**Pattern:**
```cpp
time_t timestamp = time(NULL);  // 64-bit on modern systems
sint32 int_time = timestamp;    // WARNING: 32-bit, overflows in 2038
```

**Files:**
```
Core\Libraries\Source\WWVegas\WWDownload\FTP.cpp(668)
```

**MinGW Impact:** 🟡 **This is a Y2038 bug!** 
- GCC may warn on 32-bit builds
- Affects save files, replays, network timestamps after Jan 19, 2038
- **All builds are 32-bit only (i686)** - project architecture decision to maintain original ABI with VC6

**Project Decision:** ✅ **Accept as long-term limitation**
- All builds are 32-bit: VC6, MSVC, MinGW
- Y2038 limitation applies equally to all compilers
- Documented technical debt for 32-bit architecture
- Not MinGW-specific
- **VC6 and DirectX 8 are long-term dependencies** (both 32-bit only)

**Rationale:**
- VC6 compatibility required (32-bit only compiler)
- DirectX 8 SDK is 32-bit only
- Mod ecosystem is 32-bit
- Game unlikely to be actively used in 2038
- If needed: Workarounds exist (epoch shifts, date clamping)

**Note:** A 64-bit port would require dropping VC6, migrating to DX9+, and breaking compatibility. Not planned.

---

#### P2 - Legacy Noise

##### C4535: _set_se_translator() Requires /EHa (1 instance)

**File:** `Core\Libraries\Source\debug\debug_debug.cpp(264)`

**Reason:** Using structured exception handling without async exception support flag

**MinGW Impact:** 🟢 Not applicable (SEH not supported in MinGW)

**Action:** P2 - Document that SEH is MSVC-only

---

---

## MinGW-w64 GCC Baseline (Pending)

**Status:** ⏳ Awaiting PR #2067 merge  
**Branch:** `mingw-w64-build`  
**Configuration:** i686-w64-mingw32-gcc, C++20, 32-bit

### Expected Warning Categories

Based on analysis of code changes, MinGW will likely report:

#### Expected MinGW-Specific Warnings

1. **Function Pointer Type Mismatches**
   - Status: ✅ Fixed in PR #2067 (explicit casts added)
   - Files: `FunctionLexicon.cpp` (~520 casts)

2. **Inline Assembly**
   - Status: ✅ Fixed in PR #2067 (converted to GCC syntax)
   - Files: `StackDump.cpp`

3. **Calling Convention Mismatches**
   - Status: ✅ Fixed in PR #2067
   - Files: Various

4. **Signed/Unsigned Comparisons** (`-Wsign-compare`)
   - Status: ⚠️ NOT FIXED
   - Expected: 174+ warnings (matches MSVC C4018)

5. **Enum/Float Arithmetic** (`-Wno-enum-float-conversion` NOT used)
   - Status: ⚠️ NOT FIXED
   - Expected: 65+ warnings (matches MSVC C5055)

6. **Type Conversions** (`-Wconversion`)
   - Status: ⚠️ NOT FIXED
   - Expected: 28+ warnings for size_t narrowing

### Recommended Initial MinGW Flags

**Phase 0 (Current - PR #2067):**
```cmake
# Default warnings only
# No strict flags yet
```

**Phase 1 (First iteration after merge):**
```cmake
-Wall                          # Standard warnings
-Wno-unknown-pragmas          # Ignore MSVC pragmas
-Wno-unused-parameter         # Reduce noise
-Wno-missing-field-initializers  # Common pattern
```

**Phase 2 (After baseline analysis):**
```cmake
-Wall -Wextra                 # Enable extended warnings
-Wsign-compare                # Catch signed/unsigned issues
-Werror=return-type           # Missing returns are bugs
-Werror=format                # Format string errors
```

**Phase 3 (Strict canary mode):**
```cmake
-Wall -Wextra -Wpedantic
-Wshadow                      # Variable shadowing
-Wconversion                  # Implicit conversions
-Wsign-conversion             # Sign conversions
-Werror=uninitialized         # Uninitialized variables
```

---

## MinGW-w64 GCC Warnings Baseline

**CI Run:** [Test MinGW-w64 Build #3](https://github.com/JohnsterID/GeneralsGameCode/actions/runs/21154815635)  
**Configuration:** mingw-w64-i686 (Release)  
**Total Warnings:** 4,529

### Warning Distribution

| Warning Type | Count | Percentage | Severity |
|--------------|-------|------------|----------|
| **offsetof on non-standard-layout** | 4,305 | 95.0% | P2 |
| operator new without throw() | 92 | 2.0% | P2 |
| enum/float arithmetic deprecated | 45 | 1.0% | P1 |
| Other (various) | 87 | 2.0% | P2-P3 |

### Primary Issue: offsetof on Non-Standard-Layout Types (4,305 warnings)

**Pattern:**
```cpp
warning: 'offsetof' within non-standard-layout type 'BoneFXUpdateModuleData' is conditionally-supported
warning: 'offsetof' within non-standard-layout type 'GlobalData' is conditionally-supported
```

**Top Offenders:**
```
495  BoneFXUpdateModuleData
339  GlobalData  
245  SpecialAbilityUpdateModuleData
222  TransitionDamageFXModuleData
132  SpawnBehaviorModuleData
111  ThingTemplate
100  InGameUI
... (50+ more types)
```

**Explanation:**
- C++11 standard: `offsetof` only guaranteed for standard-layout types
- Game engine uses inheritance/virtual functions in INI data structures
- Makes types non-standard-layout
- GCC warns but allows it ("conditionally-supported")
- **MSVC silently accepts** - doesn't warn at all

**Why This Matters:**
- **Portability risk**: May not work on non-x86 architectures
- **Standard compliance**: Relies on implementation-defined behavior
- **Deep in codebase**: INI parsing system architecture

**Root Cause:**
The game uses `offsetof` to serialize/deserialize INI files. Data structures inherit from base classes and have virtual functions, violating standard-layout requirements.

**Project Decision:** ✅ **Accept as baseline**
- Conditionally-supported, not an error
- Works on Windows x86 (32-bit target)
- Refactoring INI system out of scope
- Warnings document technical debt
- 32-bit architecture is long-term commitment

**Options (if addressing later):**
1. Suppress: `-Wno-invalid-offsetof` (reduces 4,529 → ~200 warnings)
2. Refactor INI system (high effort, high risk)
3. Accept as Windows-only code (current approach)

### Secondary Issues

**operator new (92 warnings):**
```cpp
warning: 'operator new' must not return NULL unless it is declared 'throw()' (or '-fcheck-new' is in effect)
```
- Missing throw specification
- Undefined behavior if allocation fails
- Fix: Add `std::nothrow` or exception spec

**enum/float arithmetic (45 warnings):**
- Same as MSVC C5055
- Deprecated in C++20
- Needs explicit casts

### MinGW Build Results

| Configuration | Warnings | Executable Size | Status |
|---------------|----------|-----------------|--------|
| GeneralsMD Release | 4,529 | 4.74 MB | ✅ Pass |
| Generals Release | 4,028 | 4.55 MB | ✅ Pass |
| Generals Debug | 4,063 | 56.6 MB | ✅ Pass |
| GeneralsMD Debug | 4,564 | 61.4 MB | ✅ Pass |

**All builds produce working Windows PE executables.**

### What GCC Catches That MSVC Doesn't

1. ✅ **offsetof on non-standard-layout types** - MSVC silent, GCC warns
2. ✅ **operator new return semantics** - Stricter throw specifications
3. ✅ **Standard compliance** - More pedantic about C++ standard

**This is EXACTLY why MinGW is valuable** - it exposes portability issues that MSVC hides!

---

## Comparison Matrix

### Warning Categories Across Compilers

| Category | VC6 | MSVC C++20 | MinGW GCC | Priority | Notes |
|----------|-----|------------|-----------|----------|-------|
| **offsetof non-standard-layout** | 0 | 0 | **4,305** | P2 | **GCC-only! MSVC silent** |
| Macro redefinition | 43 | 43 | <50 | P2 | Same issue in all compilers |
| Signed/unsigned mismatch | 0 | 174 | ~174 | P1 | MSVC C++20 and GCC strict |
| operator new semantics | 0 | 0 | 92 | P2 | GCC enforces throw specs |
| Enum/float arithmetic | 0 | 65 | 45 | P1 | C++20 deprecation (both warn) |
| Deprecated APIs | 0 | 68 | 0 | P1 | MSVC CRT specific |
| Type conversions | 0 | 28 | ~28 | P1 | Strict type checking |
| Int-to-bool conversion | 12 | 0 | 0 | P1 | VC6 specific |
| Windows SDK noise | 0 | 1055 | 0 | P3 | MSVC SDK specific |
| Function pointers | 0 | 0 | 0 | - | ✅ Fixed in PR #2067 |
| Inline assembly | 0 | 0 | 0 | - | ✅ Fixed in PR #2067 |
| **TOTAL** | **55** | **1,499** | **4,529** | - | **MinGW 3× stricter than MSVC** |

**Legend:**
- 🔴 Will warn/error
- 🟡 Will warn with `-Wextra`
- 🟢 Won't warn
- ✅ Already fixed
- ❓ Unknown (needs testing)

---

## Recommendations

### Immediate Actions (MinGW Builds Successfully!)

1. **Capture MinGW warning baseline:**
   ```bash
   # Run CI workflow: .github/workflows/test-mingw-build.yml
   # Or build locally:
   cmake --preset mingw-w64-i686 2>&1 | tee build_mingw_baseline.log
   cmake --build --preset mingw-w64-i686 2>&1 | tee -a build_mingw_baseline.log
   ```

2. **Update this document with MinGW statistics:**
   - Total warning count
   - Warning types and distribution
   - Compare with VC6 and MSVC baselines

3. **No P0 blocking issues** - MinGW compiles successfully ✅

### Phase 1 (Current - Three Compiler Strategy)

1. **Capture MinGW baseline:**
   ```bash
   cmake --preset mingw-w64-i686 2>&1 | tee build_mingw_baseline.log
   cmake --build --preset mingw-w64-i686 2>&1 | tee -a build_mingw_baseline.log
   ```

2. **Compare baselines:**
   - Identify MinGW-only warnings → likely real portability bugs
   - Identify MSVC-only warnings → MSVC-specific quirks
   - Identify shared warnings → common technical debt

3. **Fix MinGW-specific warnings first:**
   - These are NEW issues exposed by second compiler
   - Higher probability of being real bugs

### Phase 2 (Gradual Strictness)

1. **Enable `-Wall -Wextra` on MinGW**
2. **Fix signed/unsigned mismatches** (174 instances)
3. **Update deprecated APIs** (68 instances)
4. **Add `-Werror` for critical warnings** (return-type, format, uninitialized)

### Phase 3 (Canary Compiler)

1. **Make MinGW the strict compiler**
2. **Enable `-Wconversion`, `-Wshadow`**
3. **Suppress legacy warnings locally** with pragmas
4. **All new code must compile clean on MinGW**

---

## Baseline Refresh Protocol

### When to Refresh

- ✅ After significant warning-fix campaigns
- ✅ After MinGW merge (PR #2067)
- ✅ After compiler version upgrades
- ✅ Quarterly (to track drift)

### How to Refresh

1. **Download CI logs:**
   ```bash
   curl -L -H "Authorization: token $GITHUB_TOKEN" \
     "https://api.github.com/repos/TheSuperHackers/GeneralsGameCode/actions/runs/RUN_ID/logs" \
     -o ci_logs.zip
   unzip ci_logs.zip
   ```

2. **Extract warnings:**
   ```bash
   grep "warning C[0-9]" "Build Generals _ vc6+t+e.txt" > vc6_warnings.txt
   grep "warning C[0-9]" "Build Generals _ win32+t+e.txt" > msvc_warnings.txt
   # After MinGW merge:
   grep "warning:" "Build Generals _ mingw-w64-i686.txt" > mingw_warnings.txt
   ```

3. **Update this document** with new statistics

4. **Commit changes:**
   ```bash
   git add COMPILER_WARNINGS_BASELINE.md
   git commit -m "docs: Update compiler warnings baseline (CI run #XXXXX)"
   ```

---

## Appendix: Warning Code Reference

### MSVC Warning Codes

| Code | Description | Severity |
|------|-------------|----------|
| C4005 | Macro redefinition | Low |
| C4018 | Signed/unsigned mismatch | Medium |
| C4114 | Same type qualifier twice | Low (SDK) |
| C4180 | Qualifier on function type | Low (SDK) |
| C4244 | Type conversion, possible data loss | High |
| C4267 | size_t conversion | Medium |
| C4477 | Format string mismatch | High |
| C4535 | SEH requires /EHa | Low |
| C4800 | Forcing int to bool | Low |
| C4996 | Deprecated function | Medium |
| C5055 | Enum/float operation deprecated | High (C++20) |
| C5287 | Enum type mismatch | Medium |

### GCC Warning Flags (Expected)

| Flag | Description | Enabled By |
|------|-------------|------------|
| `-Wconversion` | Implicit type conversions | (manual) |
| `-Wsign-compare` | Signed/unsigned comparison | `-Wall` |
| `-Wsign-conversion` | Sign-changing conversions | (manual) |
| `-Wformat` | Printf format checking | `-Wall` |
| `-Wuninitialized` | Uninitialized variable use | `-Wall` |
| `-Wshadow` | Variable shadowing | (manual) |
| `-Wpedantic` | Non-ISO C++ usage | (manual) |
| `-Wextra` | Extra warnings | (manual) |

---

**Document Version:** 1.0  
**Last Updated:** January 19, 2026  
**Next Review:** After PR #2067 merge (MinGW baseline capture)
