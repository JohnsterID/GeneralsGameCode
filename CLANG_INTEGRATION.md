# Clang Compiler Integration Plan

## Executive Summary

**Strategic Decision:** Add Clang support with **modern toolchains only**. Skip VC6-based configurations entirely.

**Rationale:** VC6 will be dropped in favor of VC2022 (confirmed in PR #931 discussion). No value in developing new VC6-based build solutions.

**Recommended Configurations:**
1. ✅ **Clang-CL + Modern MSVC (C++20)** - Windows, ~1-2 days effort
2. ✅ **Linux Clang → Win32 i686 cross-compilation** - Linux to Windows, ~3-5 days effort

**Timeline:** ~1 month for complete implementation including variants and testing.

---

## Current State

### Existing CMake Presets (mingw-w64-build branch)

The project currently supports:

1. **VC6 Presets** (`vc6`, `vc6-debug`, `vc6-profile`)
   - Visual Studio 6 compiler
   - 32-bit Windows, pre-C++11
   - Single-config generator (Ninja)

2. **Win32 MSVC Presets** (`win32`, `win32-debug`, `win32-profile`)
   - Modern Visual Studio toolchain
   - 32-bit Windows, C++20 support
   - Multi-config generator (Ninja Multi-Config)

3. **MinGW-w64 Presets** (`mingw-w64-i686`, variants)
   - Linux → Windows 32-bit cross-compilation
   - Uses GCC toolchain with MinGW-w64
   - Custom ReactOS ATL + widl for COM support

### Key Infrastructure

- **cmake/compilers.cmake**: Compiler detection (`IS_VS6_BUILD`, `IS_MINGW_BUILD`)
- **cmake/mingw.cmake**: MinGW-specific flags and Windows library linking
- **cmake/toolchains/mingw-w64-i686.cmake**: Cross-compilation toolchain
- **Dependencies**: DirectX 8, Miles, Bink fetched via FetchContent

---

## Context: PR #931 (Merged Aug 2025)

**Change:** Moved VC6 toolchain source from private AWS S3 to public **itsmattkc/MSVC600** repository.

**Key Facts:**
- Public VC6 SP6 portable installation now available
- Repository: https://github.com/itsmattkc/MSVC600
- Pinned commit: `001c4bafdcf2ef4b474d693acccd35a91e848f40`
- Validated: Replay CRC tests pass (identical binaries)
- Contains: Compiler, linker, headers, libraries (no MASM, no IDE)

**Confirmed Long-term Plan:**
> "The long-term plan is probably to drop VC6 altogether and move forward with VC2022" - Skaronator
> "yes, therefore we shouldn't bother making our own fork/clone of the vc6 portable repo" - barefootlogician

**Impact:** While VC6 headers/libs are now publicly accessible, developing new VC6-based toolchains has no value since VC6 is transitional.

---

## Recommended Clang Configurations

### 1. Clang-CL + Modern MSVC for C++20 ⭐ HIGH PRIORITY

**Description:** Use `clang-cl` (LLVM's MSVC-compatible driver) with modern MSVC runtime and Windows SDK.

**Why This Matters:**
- ✅ Future-proof - aligns with VC2022 direction
- ✅ Full C++20 support (often better than MSVC)
- ✅ Better diagnostics and error messages
- ✅ Potential optimization improvements
- ✅ Drop-in replacement for `win32` presets

**Use Cases:**
- Developers who prefer Clang tooling
- CI builds with Clang sanitizers
- Performance comparison vs MSVC
- Modern C++ feature validation

**Implementation Effort:** LOW (~1-2 days)

#### Implementation Steps

**A. Add Preset (inherits from win32)**

Add to `CMakePresets.json`:
```json
{
    "name": "clang-cl-cpp20",
    "displayName": "Windows 32bit Clang-CL C++20",
    "inherits": "win32",
    "cacheVariables": {
        "CMAKE_C_COMPILER": "clang-cl",
        "CMAKE_CXX_COMPILER": "clang-cl"
    }
}
```

Add variants:
```json
{
    "name": "clang-cl-cpp20-debug",
    "inherits": "clang-cl-cpp20",
    "displayName": "Windows 32bit Clang-CL C++20 Debug",
    "cacheVariables": {
        "RTS_BUILD_OPTION_DEBUG": "ON"
    }
},
{
    "name": "clang-cl-cpp20-profile",
    "inherits": "clang-cl-cpp20",
    "displayName": "Windows 32bit Clang-CL C++20 Profile",
    "cacheVariables": {
        "RTS_BUILD_OPTION_PROFILE": "ON"
    }
}
```

**B. Update Compiler Detection**

Update `cmake/compilers.cmake`:
```cmake
# Detect Clang-CL (MSVC-compatible mode)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_CXX_SIMULATE_ID MATCHES "MSVC" OR MSVC)
        set(IS_CLANG_CL_BUILD TRUE)
        message(STATUS "Clang-CL detected (MSVC-compatible mode)")
    else()
        set(IS_CLANG_BUILD TRUE)
        message(STATUS "Clang detected (native mode)")
    endif()
endif()

# Treat clang-cl like MSVC for configuration
if(IS_CLANG_CL_BUILD AND NOT IS_VS6_BUILD)
    # Clang-CL supports C++20
    target_compile_features(core_config INTERFACE cxx_std_20)
    
    # Optional: Add clang-specific warnings or optimizations
    # add_compile_options(-Wno-unused-command-line-argument)
endif()
```

**C. Add Build and Workflow Presets**

Follow the same pattern as existing presets.

**D. Dependencies**
- LLVM/Clang with clang-cl (usually installed with LLVM on Windows)
- Visual Studio Build Tools or Windows SDK
- Modern MSVC runtime libraries

**Testing:**
```bash
# Configure
cmake --preset clang-cl-cpp20

# Build
cmake --build --preset clang-cl-cpp20

# Run and validate
```

---

### 2. Linux Clang → Win32 i686 Cross-Compilation ⭐ HIGH PRIORITY

**Description:** Use Clang on Linux to cross-compile to Windows 32-bit using MinGW-w64 headers/libraries.

**Why This Matters:**
- ✅ CI/CD efficiency (Linux runners faster/cheaper than Windows)
- ✅ Consistent build environment
- ✅ LLVM/LLD often faster than GCC/ld
- ✅ Better diagnostics than GCC
- ✅ Leverages recent MinGW-w64 work

**Use Cases:**
- GitHub Actions Linux runners
- Docker-based builds
- Developers working primarily on Linux
- Cross-platform CI pipelines

**Implementation Effort:** MEDIUM (~3-5 days)

#### Implementation Steps

**A. Create Toolchain File**

Create `cmake/toolchains/clang-mingw-w64-i686.cmake`:
```cmake
# Clang cross-compilation to Windows 32-bit (i686) using MinGW-w64
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

# Use Clang as the compiler
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# Tell Clang to target Windows i686
set(CMAKE_C_COMPILER_TARGET i686-w64-mingw32)
set(CMAKE_CXX_COMPILER_TARGET i686-w64-mingw32)

# Use MinGW-w64 binutils for resource compiler
set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)

# Optionally use LLVM tools (faster linking)
find_program(LLVM_AR llvm-ar)
find_program(LLVM_RANLIB llvm-ranlib)
if(LLVM_AR)
    set(CMAKE_AR ${LLVM_AR})
endif()
if(LLVM_RANLIB)
    set(CMAKE_RANLIB ${LLVM_RANLIB})
endif()

# Target environment (MinGW-w64 sysroot)
set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)

# Adjust find behavior
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Force 32-bit
set(CMAKE_SIZEOF_VOID_P 4)

# Clang-specific flags for Windows targeting
set(CMAKE_C_FLAGS_INIT "-target i686-w64-mingw32 -m32")
set(CMAKE_CXX_FLAGS_INIT "-target i686-w64-mingw32 -m32 -std=c++20")

# Use LLD linker (LLVM's linker) for better integration
set(CMAKE_EXE_LINKER_FLAGS_INIT "-target i686-w64-mingw32 -m32 -fuse-ld=lld")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-target i686-w64-mingw32 -m32 -fuse-ld=lld")

# Disable MFC-dependent tools (same as MinGW GCC)
set(RTS_BUILD_CORE_TOOLS OFF CACHE BOOL "Disable MFC tools for Clang MinGW" FORCE)
set(RTS_BUILD_GENERALS_TOOLS OFF CACHE BOOL "Disable MFC tools for Clang MinGW" FORCE)
set(RTS_BUILD_ZEROHOUR_TOOLS OFF CACHE BOOL "Disable MFC tools for Clang MinGW" FORCE)
```

**B. Create Clang-MinGW Configuration**

Create `cmake/clang-mingw.cmake`:
```cmake
# Clang + MinGW-w64 specific configuration
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "Configuring Clang + MinGW-w64 build settings")
    
    # Clang-specific optimizations
    add_compile_options(
        -fno-strict-aliasing
        -Wno-microsoft-exception-spec  # Suppress MSVC SEH warnings
    )
    
    # MSVC compatibility macros
    add_compile_definitions(
        __forceinline=inline\ __attribute__((always_inline))
        __int64=long\ long
        _int64=long\ long
        _USE_MATH_DEFINES
    )
    
    # Windows subsystem
    add_link_options(-mwindows)
    
    # Static linking of C++ runtime
    add_link_options(-static-libgcc -static-libstdc++)
    
    # Use LLD for faster linking (if not already set in toolchain)
    if(NOT CMAKE_EXE_LINKER_FLAGS MATCHES "fuse-ld=lld")
        add_link_options(-fuse-ld=lld)
    endif()
    
    # Link Windows libraries (same as GCC MinGW)
    link_libraries(
        uuid ole32 oleaut32 gdi32 user32 comctl32
        winmm vfw32 d3d8 dinput8 dsound imm32
    )
    
    # d3dx8 alias (same as GCC MinGW)
    if(NOT TARGET d3dx8)
        add_library(d3dx8 INTERFACE IMPORTED GLOBAL)
        set_target_properties(d3dx8 PROPERTIES
            INTERFACE_LINK_LIBRARIES "d3dx8d"
        )
        message(STATUS "Created d3dx8 -> d3dx8d alias for Clang MinGW")
    endif()
    
    message(STATUS "Clang + MinGW-w64 configuration complete")
endif()
```

**C. Update CMakeLists.txt**

Modify the MinGW section:
```cmake
# MinGW-w64 specific configuration
if(MINGW OR (CMAKE_SYSTEM_NAME MATCHES "Windows" AND CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        include(cmake/clang-mingw.cmake)
    else()
        include(cmake/mingw.cmake)
    endif()
    include(cmake/reactos-atl.cmake)
    include(cmake/widl.cmake)
endif()
```

**D. Update Compiler Detection**

Add to `cmake/compilers.cmake`:
```cmake
# Detect Clang + MinGW cross-compilation
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_SYSTEM_NAME MATCHES "Windows" AND NOT MSVC)
    message(STATUS "Clang + MinGW-w64 cross-compilation detected")
    set(IS_CLANG_MINGW_BUILD TRUE)
endif()
```

**E. Add CMake Preset**

Add to `CMakePresets.json`:
```json
{
    "name": "clang-mingw-w64-i686",
    "displayName": "Clang MinGW-w64 32-bit (i686) C++20",
    "generator": "Ninja",
    "hidden": false,
    "binaryDir": "${sourceDir}/build/${presetName}",
    "toolchainFile": "${sourceDir}/cmake/toolchains/clang-mingw-w64-i686.cmake",
    "cacheVariables": {
        "CMAKE_EXPORT_COMPILE_COMMANDS": "ON",
        "CMAKE_BUILD_TYPE": "Release"
    }
}
```

Add variants (debug, profile).

**F. Dependencies (Linux)**

```bash
# Ubuntu/Debian
sudo apt-get install clang llvm lld mingw-w64 mingw-w64-tools

# Verify
clang --version
i686-w64-mingw32-gcc --version  # MinGW-w64 sysroot
ld.lld --version                 # LLVM linker
```

**Testing:**
```bash
# Configure (on Linux)
cmake --preset clang-mingw-w64-i686

# Build
cmake --build --preset clang-mingw-w64-i686

# Copy to Windows and test
# OR test with Wine on Linux
```

---

## Implementation Timeline

### Phase 1: Clang-CL + Modern MSVC (Week 1)

**Day 1-2: Setup**
- [ ] Add `clang-cl-cpp20` preset and variants to `CMakePresets.json`
- [ ] Update `cmake/compilers.cmake` for clang-cl detection
- [ ] Test local build on Windows

**Day 3: Validation**
- [ ] Build all targets with clang-cl-cpp20
- [ ] Run functional tests
- [ ] Compare build output with win32 preset

**Day 4: Documentation & Cleanup**
- [ ] Update README with clang-cl presets
- [ ] Document any compiler warnings/differences
- [ ] Add troubleshooting notes

**Deliverable:** Working clang-cl presets, fully tested and documented.

---

### Phase 2: Linux Clang → Win32 (Week 2-3)

**Week 2: Toolchain Development**
- [ ] Create `cmake/toolchains/clang-mingw-w64-i686.cmake`
- [ ] Create `cmake/clang-mingw.cmake`
- [ ] Update `CMakeLists.txt` to include clang-mingw
- [ ] Update `cmake/compilers.cmake` for detection
- [ ] Add `clang-mingw-w64-i686` presets and variants

**Week 3: Testing & CI**
- [ ] Set up Linux environment with Clang + MinGW-w64
- [ ] Test cross-compilation locally (build on Linux)
- [ ] Verify binaries run on Windows
- [ ] Add Linux CI job to GitHub Actions workflow
- [ ] Document Linux build dependencies

**Deliverable:** Linux-to-Windows cross-compilation working locally and in CI.

---

### Phase 3: Polish & Variants (Week 4)

**For Each Preset:**
- [ ] Verify all build configurations (Release, Debug, Profile)
- [ ] Add corresponding build presets
- [ ] Add corresponding workflow presets
- [ ] Performance comparison vs existing toolchains
- [ ] Update all documentation

**Deliverable:** Complete preset families with full documentation.

---

## Testing Strategy

### For Each New Configuration

**1. Configuration Test**
```bash
cmake --preset <preset-name>
```
- ✓ No configuration errors
- ✓ Compiler detected correctly
- ✓ Dependencies found

**2. Build Test**
```bash
cmake --build --preset <preset-name>
```
- ✓ Compiles without errors
- ✓ Note warnings for review
- ✓ Build completes successfully

**3. Functional Test**
- Run the executable
- Test basic game functionality
- Verify no crashes or major issues

**4. Comparison Test**
- Compare binary sizes
- Compare exported symbols (if applicable)
- Performance testing (frame rates, load times)

**5. CI Integration**
- Add to GitHub Actions workflow
- Verify clean environment builds
- Check caching works correctly

---

## Benefits Summary

| Configuration | Setup Effort | Value | Future-Proof | CI Benefit |
|--------------|--------------|-------|--------------|------------|
| **Clang-CL + Modern MSVC** | LOW (1-2 days) | HIGH | ✅ Yes | Medium |
| **Linux Clang → Win32** | MEDIUM (3-5 days) | HIGH | ✅ Yes | High |
| ~~Clang-CL + VC6~~ | HIGH | LOW | ❌ No | None |

**Clang-CL + Modern MSVC Benefits:**
- Better error messages than MSVC
- Often better optimization
- Clang-specific tools (clang-tidy, sanitizers)
- Future-proof (aligns with VC2022)

**Linux Clang Cross-Compilation Benefits:**
- Cheaper CI (Linux runners < Windows runners)
- Faster builds (Clang/LLD performance)
- Reproducible Linux environment
- Docker-friendly

---

## Files to Create/Modify

### New Files
- `cmake/toolchains/clang-mingw-w64-i686.cmake` (Linux cross-compilation)
- `cmake/clang-mingw.cmake` (Clang-specific MinGW settings)

### Modified Files
- `CMakePresets.json` (add clang-cl and clang-mingw presets)
- `cmake/compilers.cmake` (add Clang detection)
- `CMakeLists.txt` (include clang-mingw when appropriate)
- `.github/workflows/build-toolchain.yml` (optional: add Clang CI jobs)
- `README.md` (document new presets)

---

## Migration Path (When VC6 is Dropped)

When the project removes VC6:

1. **Remove VC6 presets** from `CMakePresets.json`
2. **Remove VC6-specific code** from `cmake/compilers.cmake` (`IS_VS6_BUILD` checks)
3. **Remove STLPort dependency** (only needed for VC6)
4. **Update CI** to remove VC6 build jobs
5. **Archive VC6 documentation**

**Clang configurations remain unaffected** - they target modern toolchains only.

---

## Next Steps

### Immediate Actions
1. **Confirm approach** with project maintainers
2. **Set up environment** (install Clang/LLVM)
3. **Start Phase 1** (Clang-CL + Modern MSVC preset)

### Success Criteria
- ✅ clang-cl-cpp20 preset builds successfully
- ✅ Generated executables run correctly
- ✅ clang-mingw-w64-i686 cross-compiles from Linux
- ✅ CI integration working
- ✅ Documentation complete

### Questions to Resolve
- Should we add Clang builds to CI immediately or wait for validation?
- Do we want to use LLD linker by default or make it optional?
- Should we enable Clang-specific sanitizers in debug builds?

---

## Conclusion

**Strategic Focus:** Two forward-compatible Clang configurations that provide real value and will remain relevant after VC6 removal.

**Timeline:** ~1 month for complete implementation including all variants, testing, and documentation.

**Value:** Better developer experience, improved CI efficiency, and future-proof toolchain diversity.

**No wasted effort** on deprecated VC6 configurations. Everything built will continue to be useful long-term.

Ready to proceed with Phase 1! 🚀
