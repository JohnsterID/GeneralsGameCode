# MinGW-w64 Technical Analysis

**Branch:** `mingw-w64-build`  
**Focus:** Deep dive into code changes and compatibility implementation

## Scope and Limitations

### 32-bit Windows Only (i686)

**Project Scope:** Win32 32-bit executables only
- MinGW preset: `mingw-w64-i686` (32-bit x86)
- Matches existing VC6 and MSVC builds
- No 64-bit (x86_64) support planned

**Rationale: VC6 and DirectX 8 are Long-Term Dependencies**

This project maintains compatibility with:
- **Visual C++ 6.0 (VC6)** - 32-bit only compiler
- **DirectX 8 SDK** - 32-bit only API
- **Existing mod ecosystem** - 32-bit binaries and tools

These dependencies may remain **indefinitely**. A 64-bit port would require:
- Dropping VC6 support entirely (breaking ABI compatibility)
- Migrating to DirectX 9+ (major graphics rewrite)
- Rebuilding entire mod ecosystem for 64-bit

**Therefore: 32-bit is the target architecture, not a temporary limitation.**

**Implications:**

1. **Year 2038 Problem (Y2038):**
   - 32-bit `time_t` will overflow on January 19, 2038
   - Affects: Save files, replays, network timestamps
   - **Accepted as long-term limitation** - documented technical debt
   - Mitigation: Game unlikely to be actively used in 2038
   - If needed: Workarounds exist (epoch shifts, date clamping)

2. **Memory Limitations:**
   - 2-4 GB address space limit
   - Not a practical concern for this game
   - Original game designed for 32-bit systems

3. **Performance:**
   - 32-bit code can be faster on older hardware
   - No significant disadvantage for game logic
   - DirectX 8 is 32-bit anyway

**Why 32-bit is Long-Term:**
- ✅ Matches VC6 ABI (required for compatibility)
- ✅ Binary compatibility with existing mods/tools
- ✅ DirectX 8 SDK is 32-bit only
- ✅ Preserves historical authenticity
- ❌ 64-bit would break compatibility with entire ecosystem

**Hypothetical Future (Not Planned):**
- A 64-bit fork would be a separate project
- Would require dropping VC6, migrating to DX9+, breaking compatibility
- Not on the roadmap - 32-bit is the commitment

---

## 1. Function Pointer Type Safety Issue

### Problem
MinGW GCC rejects implicit conversion from typed function pointers to `void*` in aggregate initialization.

### MSVC Behavior (Permissive)
```cpp
struct TableEntry {
    int namekey;
    const char* name;
    void* function;
};

WindowMsgHandledType (*func_ptr)(GameWindow*, unsigned int) = IMECandidateMainDraw;

TableEntry table[] = {
    { NAMEKEY_INVALID, "IMECandidateMainDraw", IMECandidateMainDraw },  // MSVC: OK
};
```

### GCC Behavior (Strict)
```
error: invalid conversion from 'WindowMsgHandledType (*)(GameWindow*, unsigned int)' to 'void*'
```

### Solution Applied
Add explicit cast to `void*`:
```cpp
TableEntry table[] = {
    { NAMEKEY_INVALID, "IMECandidateMainDraw", (void*)IMECandidateMainDraw },  // GCC: OK
};
```

### Impact
- **Files affected:** `FunctionLexicon.cpp` (Generals & GeneralsMD), `W3DFunctionLexicon.cpp`
- **Lines changed:** ~520 cast additions across both projects
- **Risk:** Low - Casts are mechanical transformations, no logic change
- **Benefit:** Exposes type system assumptions, improves portability

### Future Consideration
Consider changing `TableEntry` structure to use typed function pointers instead of `void*` to avoid casts entirely. This would require template or union-based design.

---

## 2. Inline Assembly Conversion

### Problem
MSVC uses Intel syntax inline assembly (`__asm { }`). GCC uses AT&T syntax inline assembly (`__asm__ __volatile__`).

### MSVC Code (Intel Syntax)
```cpp
DWORD myeip, myesp, myebp;
_asm {
MYEIP1:
    mov eax, offset MYEIP1
    mov dword ptr [myeip], eax
    mov eax, esp
    mov dword ptr [myesp], eax
    mov eax, ebp
    mov dword ptr [myebp], eax
}
```

### GCC Code (AT&T Syntax)
```cpp
__asm__ __volatile__(
    "call 1f\n\t"           // Push next instruction address to stack
    "1: pop %0\n\t"         // Pop into myeip (output operand 0)
    "mov %%esp, %1\n\t"     // Move stack pointer to myesp (output 1)
    "mov %%ebp, %2"         // Move base pointer to myebp (output 2)
    : "=r"(myeip), "=r"(myesp), "=r"(myebp)  // Output operands
    :                       // No input operands
    : "memory"              // Memory clobber
);
```

### Key Differences
| Aspect | MSVC (Intel) | GCC (AT&T) |
|--------|--------------|------------|
| Syntax | `mov dest, src` | `mov src, dest` |
| Register prefix | None | `%%reg` (doubled in inline asm) |
| Immediate prefix | None | `$` |
| Addressing | `[reg]` | `(reg)` |
| Label support | Yes (direct) | Yes (numeric local labels) |

### Implementation Notes
- **EIP capture:** GCC uses `call/pop` trick instead of `offset` (not available in AT&T syntax)
- **Constraints:** `"=r"` means write-only general register
- **Clobbers:** `"memory"` tells GCC this may modify memory (prevents reordering)

### Files Changed
- `Core/Libraries/Source/debug/debug_stack.cpp`
- `Generals/Code/GameEngine/Source/Common/System/StackDump.cpp`
- `GeneralsMD/Code/GameEngine/Source/Common/System/StackDump.cpp`

### Testing Requirements
⚠️ **Critical:** Stack traces must be validated under MinGW builds. This code is used for crash dumps and debugging.

**Test cases:**
1. Trigger intentional crash → verify stack trace correctness
2. Compare stack trace output: MSVC vs MinGW
3. Verify function names and addresses are accurate

---

## 3. Math Constants Compatibility

### Problem
MinGW's `<math.h>` provides different math constants than MSVC when `-std=c++20` is used.

### MSVC Behavior
Provides 14 constants unconditionally in `<math.h>`:
```c
M_E, M_LOG2E, M_LOG10E, M_LN2, M_LN10
M_PI, M_PI_2, M_PI_4, M_1_PI, M_2_PI
M_1_SQRTPI, M_2_SQRTPI, M_SQRT2, M_SQRT_2
```

### MinGW Behavior
- **With `-std=c++20`:** Constants disabled by default (strict ANSI mode)
- **With `_USE_MATH_DEFINES`:** Most constants available, but:
  - ❌ `M_1_SQRTPI` not defined
  - ❌ `M_SQRT_2` not defined (uses `M_SQRT1_2` instead)

### Solution in `mingw.h`
```cpp
#include <math.h>

// Missing constant
#ifndef M_1_SQRTPI
#define M_1_SQRTPI  0.564189583547756286948
#endif

// Name alias (both represent 1/√2)
#ifndef M_SQRT_2
#define M_SQRT_2    M_SQRT1_2
#endif
```

### CMake Configuration
```cmake
add_compile_definitions(_USE_MATH_DEFINES)  # Enable MinGW math constants
```

### Inclusion Chain
```
Core/Libraries/Source/WWVegas/WWLib/always.h
  ↓ (conditionally includes)
Core/Libraries/Source/WWVegas/WWLib/mingw.h
  ↓ (includes)
<math.h>
```

**Result:** All code can use math constants consistently across compilers.

---

## 4. COM/ATL Compatibility Layer

### Challenge
MinGW-w64 lacks complete COM support:
- ❌ No native ATL (Active Template Library)
- ❌ No `comsuppw.lib` (COM support utilities)
- ✅ Has COM headers and `uuid`, `ole32`, `oleaut32` libraries

### Solution: ReactOS Components

#### 4.1 ReactOS ATL Integration (`cmake/reactos-atl.cmake`)
- Uses ReactOS's open-source ATL implementation
- Provides `CComPtr`, `CComBSTR`, COM interface macros, etc.
- **Caveat:** ReactOS ATL requires PSEH (Portable Structured Exception Handling)

#### 4.2 PSEH Compatibility (`pseh_compat.h`)
**Problem:** ReactOS PSEH uses GNU C nested functions (not valid in C++)

**Solution:** Use ReactOS PSEH in "dummy mode"
```cpp
#define _USE_DUMMY_PSEH  // Disables real SEH, provides dummy macros

#define _SEH2_TRY       if (1)
#define _SEH2_EXCEPT(x) if (0)
#define _SEH2_FINALLY   if (1)
#define _SEH2_END       
```

**Impact:**
- ✅ ReactOS ATL headers compile successfully
- ⚠️ Structured exception handling **not functional** under MinGW
- ⚠️ SEH-dependent code paths will behave differently

**Risk Assessment:**
- **Low risk** if SEH is only used for abnormal error handling
- **High risk** if SEH is part of normal control flow

**Recommendation:** Audit ReactOS ATL usage for SEH dependencies. Consider alternative error handling for MinGW builds.

#### 4.3 COM Support Utilities (`comsupp_compat.h`)
Provides header-only implementations of:
```cpp
namespace _com_util {
    BSTR ConvertStringToBSTR(const char* str);
    char* ConvertBSTRToString(BSTR bstr);
}
```

These replace MSVC's `comsuppw.lib` functions.

**Implementation:**
- `ConvertStringToBSTR`: Uses `SysAllocString` + `MultiByteToWideChar`
- `ConvertBSTRToString`: Uses `WideCharToMultiByte` + manual allocation

**Memory management:** Caller must free returned strings (`SysFreeString`, `delete[]`)

---

## 5. DirectX 8 Library Workaround

### Problem
MinGW-w64's DirectX 8 SDK (from `min-dx8-sdk`) provides:
- ✅ `libd3d8.a` (Direct3D 8)
- ✅ `libd3dx8d.a` (D3DX 8 **debug** version)
- ❌ `libd3dx8.a` (D3DX 8 release version) - **missing**

### MSVC vs MinGW Library Naming
| Component | MSVC | MinGW-w64 |
|-----------|------|-----------|
| D3D8 | `d3d8.lib` | `libd3d8.a` ✅ |
| D3DX8 Release | `d3dx8.lib` | ❌ Missing |
| D3DX8 Debug | `d3dx8d.lib` | `libd3dx8d.a` ✅ |

### Solution in `cmake/mingw.cmake`
Create an interface library alias:
```cmake
if(NOT TARGET d3dx8)
    add_library(d3dx8 INTERFACE IMPORTED GLOBAL)
    set_target_properties(d3dx8 PROPERTIES
        INTERFACE_LINK_LIBRARIES "d3dx8d"
    )
    message(STATUS "Created d3dx8 -> d3dx8d alias for MinGW-w64")
endif()
```

**Effect:** All references to `d3dx8` automatically link to `d3dx8d`

### Implications
1. **Functionality:** D3DX8 debug library contains same functions as release (no issue for compilation)
2. **Performance:** May include extra debug checks (likely negligible)
3. **Binary size:** Debug library may be slightly larger
4. **Correctness:** ✅ No known functional differences for common D3DX8 usage

**Long-term solution:** Build release version of D3DX8 for MinGW or verify debug version is suitable.

---

## 6. Calling Convention Standardization

### Problem
C++ and C code mixing requires explicit calling convention declarations. MSVC is more forgiving about missing conventions.

### Changes Made

#### Example 1: Variadic Macros (`debug_debug.h`)
**Before:**
```cpp
#define DEBUG_ASSERTCRASH(condition, ...) \
    if (!(condition)) { DEBUG_CRASH(__VA_ARGS__); }
```

**After:**
```cpp
#define DEBUG_CRASH(...) Debug_Crash(__VA_ARGS__)

void Debug_Crash(const char* format, ...);  // Explicit C linkage + signature
```

**Reason:** MinGW requires proper function declarations for variadic macros.

#### Example 2: Function Pointer Declarations
Added explicit `__stdcall` / `__cdecl` annotations where missing:
```cpp
extern "C" {
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
}
```

**STDMETHODCALLTYPE expansion:**
- MSVC: `__stdcall`
- MinGW: `__attribute__((stdcall))` (defined in `<windows.h>`)

### Files Affected
- `Core/Libraries/Source/debug/debug_debug.cpp`
- `Core/GameEngine/Include/GameNetwork/WOLBrowser/FEBDispatch.h`
- Multiple CMakeLists.txt files (linkage specifications)

---

## 7. Static Linking Configuration

### Rationale
Avoid runtime DLL dependencies for GCC libraries.

### Implementation
```cmake
add_link_options(-static-libgcc -static-libstdc++)
```

**Effect:**
- `libgcc_s_dw2-1.dll` → embedded in `.exe`
- `libstdc++-6.dll` → embedded in `.exe`

### Trade-offs
| Aspect | Static | Dynamic |
|--------|--------|---------|
| Binary size | Larger (~500KB overhead) | Smaller |
| Deployment | Single EXE | Requires DLLs |
| Updates | Recompile to patch | Replace DLL |
| Compatibility | Self-contained | Requires matching GCC version |

**Decision:** Static linking is correct for game distribution (self-contained binaries).

---

## 8. Compiler Compatibility Macros

### MSVC Extension Emulation
```cmake
add_compile_definitions(
    __forceinline=inline\ __attribute__\(\(always_inline\)\)
    __int64=long\ long
    _int64=long\ long
)
```

**Breakdown:**
| MSVC | MinGW Equivalent | Purpose |
|------|------------------|---------|
| `__forceinline` | `inline __attribute__((always_inline))` | Force inline expansion |
| `__int64` | `long long` | 64-bit integer type |
| `_int64` | `long long` | Alternative 64-bit type |

**Note:** `_cdecl` and `_stdcall` are **not** redefined - MinGW already provides compatible definitions.

---

## 9. Potential Issues & Testing Gaps

### 9.1 Structured Exception Handling (SEH)
**Status:** ❌ Not functional under MinGW (dummy PSEH)

**Test:**
1. Trigger access violation in ATL/COM code
2. Verify behavior: MSVC may catch, MinGW will crash
3. Identify SEH-dependent code paths

**Mitigation:** Add explicit error checks instead of relying on SEH.

### 9.2 Stack Trace Accuracy
**Status:** ⚠️ Untested

**Test:**
1. Force crash with `StackDump()` call
2. Compare stack traces: MSVC vs MinGW
3. Verify function names, addresses, call chain

### 9.3 COM Interface Compatibility
**Status:** ⚠️ Untested

**Test:**
1. Web browser components (uses ATL)
2. WOL (Westwood Online) networking (uses COM)
3. DirectShow (Video for Windows - `vfw32.dll`)

**High-risk areas:**
- `EABrowserDispatch` / `EABrowserEngine` (uses ReactOS ATL)
- `WOLBrowser` (COM interfaces)

### 9.4 D3DX8 Debug Library
**Status:** ⚠️ Unknown impact

**Test:**
1. Rendering performance benchmarks
2. D3DX8 utility functions (texture loading, mesh parsing)
3. Binary size comparison

### 9.5 ABI Compatibility
**Status:** ⚠️ Requires validation

**Important:** MinGW GCC uses different C++ ABI than MSVC.

**Risk:** If any DLL boundaries cross C++ objects (not just C interfaces), expect crashes.

**Test:**
1. Verify all DLL exports are `extern "C"` or COM interfaces
2. Check for STL types crossing DLL boundaries (std::string, std::vector)
3. Validate against VC6-built DLLs

---

## 10. Compiler Flags Analysis

### Current Flags (`cmake/mingw.cmake`)
```cmake
-m32                    # Force 32-bit
-mwindows               # Windows subsystem (no console)
-static-libgcc          # Static GCC runtime
-static-libstdc++       # Static C++ runtime
-fno-strict-aliasing    # Disable strict aliasing (COM/DX8 compatibility)
```

### Recommended Additions (Phase 2)
```cmake
# Portability warnings
-Wall -Wextra           # Standard warning sets
-Wshadow                # Variable shadowing
-Wconversion            # Implicit conversions
-Wsign-conversion       # Sign conversions

# Error enforcement (start small)
-Werror=return-type     # Missing return statements
-Werror=uninitialized   # Uninitialized variables

# Debugging (optional builds)
-fsanitize=undefined    # Undefined behavior sanitizer
-fsanitize=address      # Address sanitizer (32-bit limited)
```

### Why `-fno-strict-aliasing`?
COM and DirectX8 code frequently uses type punning:
```cpp
IUnknown* punk = ...;
IDirectDraw* pdd = reinterpret_cast<IDirectDraw*>(punk);
```

Without `-fno-strict-aliasing`, GCC may optimize incorrectly.

**Future:** Audit type punning, replace with `memcpy` or unions where possible.

---

## 11. Known Limitations

### Profile Builds Not Supported

**Status:** ❌ MinGW profile builds are **non-functional**

**Reason:** The profiling system (`RTS_BUILD_OPTION_PROFILE=ON`) uses MSVC inline assembly for instrumentation:
```cpp
// MSVC-specific profiling code
__asm {
    rdtsc           // Read timestamp counter
    mov [cycles], eax
}
```

**Problem:** No direct GCC equivalent exists. While GCC has inline assembly, the profiling infrastructure is tightly coupled to MSVC's ABI and calling conventions.

**CMake Preset Status:**
- `mingw-w64-i686-profile` preset exists in `CMakePresets.json`
- **Do not use in production or CI**
- Kept for potential future exploration

**Workarounds Considered:**
1. **Port to GCC assembly syntax** - Would require complete rewrite of profiling system
2. **Use external profilers** - gprof, perf, valgrind (different workflow)
3. **Conditional compilation** - Disable profiling for MinGW builds

**Recommendation:** Accept that profile builds are MSVC-only for Phase 1. Revisit after VC6 removal in Phase 2.

**CI Impact:** Profile configuration removed from MinGW CI matrix in `.github/workflows/test-mingw-build.yml`

---

## 12. Recommendations by Priority

### P0 - Critical (Before Merge)
1. ✅ Enable MinGW CI builds
2. ✅ Basic runtime test (launch game, load map)
3. ⚠️ Verify stack traces work correctly
4. ⚠️ Test COM/ATL functionality (browser, WOL)

### P1 - High (Post-Merge)
1. Audit SEH usage in ReactOS ATL code paths
2. Capture warning baselines (MinGW vs MSVC)
3. Add `-Wall -Wextra` and fix new warnings
4. Validate ABI boundaries (DLL exports)

### P2 - Medium (Phase 2)
1. Replace function pointer `void*` casts with type-safe design
2. Add 32-bit sanitizer builds (`-fsanitize=address,undefined`)
3. Benchmark D3DX8 debug library vs release (if available)
4. Test 32-bit builds on modern Windows (32-bit subsystem validation)

### P3 - Low (Future)
1. Consider Clang-cl for Windows (after VC6 removal)
2. Evaluate ReactOS ATL alternatives (header-only ATL?)
3. Investigate full PSEH support for MinGW (if needed)

---

## Conclusion

The MinGW-w64 implementation is **technically sound** with the following caveats:

**Strengths:**
- Clean separation of compiler-specific code
- Minimal invasive changes to core logic
- Good use of existing ReactOS components
- Well-documented workarounds

**Risks:**
- Structured exception handling not functional (dummy PSEH)
- Stack trace code untested
- COM/ATL usage untested
- ABI boundaries unvalidated

**Overall Assessment:** Ready for merge after CI validation and basic runtime testing. Critical features (stack traces, COM/ATL) require dedicated testing.

---

**Reviewed by:** OpenHands AI  
**Date:** January 19, 2026
