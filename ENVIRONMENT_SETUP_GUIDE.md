# Environment Setup Guide for W3DView wxWidgets Development

**Date**: January 26, 2026  
**Purpose**: Setup complete build and testing environment per Xvfb.txt  
**Target**: MinGW-w64 i686 cross-compilation for Win32 + Wine testing

---

## Prerequisites

This guide follows `/workspace/project/Xvfb.txt` exactly for:
- MinGW-w64 cross-compilation (Win32 target)
- Wine for Windows binary testing
- Xvfb for headless GUI testing
- CMake build system

**⚠️ CRITICAL**: This builds **Windows binaries**, NOT Linux binaries!

---

## Quick Setup Script

```bash
#!/bin/bash
# Full environment setup for W3DView wxWidgets development
# Based on /workspace/project/Xvfb.txt

set -e

echo "═══════════════════════════════════════════════════════════"
echo "  W3DView wxWidgets Development Environment Setup"
echo "═══════════════════════════════════════════════════════════"
echo ""

# Step 1: Clean environment
echo "[1/7] Cleaning environment variables..."
unset LD_LIBRARY_PATH
unset LD_PRELOAD
export LD_LIBRARY_PATH=
echo "✓ Environment cleaned"
echo ""

# Step 2: Update package lists
echo "[2/7] Updating package lists..."
sudo apt-get update -qq
echo "✓ Package lists updated"
echo ""

# Step 3: Install base system packages
echo "[3/7] Installing base system packages..."
sudo apt-get install -y \
    xvfb \
    cabextract \
    libegl1 \
    libgl1-mesa-dri \
    pkg-config \
    wget \
    ca-certificates \
    xdpyinfo
echo "✓ Base packages installed"
echo ""

# Step 4: Enable 32-bit architecture for Wine
echo "[4/7] Enabling 32-bit architecture..."
sudo dpkg --add-architecture i386
echo "✓ i386 architecture enabled"
echo ""

# Step 5: Install WineHQ
echo "[5/7] Installing WineHQ..."
sudo mkdir -pm755 /etc/apt/keyrings
sudo wget -q -O /etc/apt/keyrings/winehq-archive.key \
    https://dl.winehq.org/wine-builds/winehq.key
sudo wget -q -NP /etc/apt/sources.list.d/ \
    https://dl.winehq.org/wine-builds/debian/dists/trixie/winehq-trixie.sources
sudo apt-get update -qq
sudo apt-get install -y --install-recommends \
    winehq-stable \
    wine32 \
    wine64 \
    libwine:i386 \
    libwine:amd64 \
    wine-stable-dev
echo "✓ Wine installed: $(wine --version)"
echo "✓ widl installed: $(widl --version)"
echo ""

# Step 6: Install MinGW-w64 toolchain
echo "[6/7] Installing MinGW-w64 toolchain..."
sudo apt-get install -y \
    mingw-w64 \
    cmake
echo "✓ MinGW-w64 installed: $(i686-w64-mingw32-gcc --version | head -1)"
echo "✓ CMake installed: $(cmake --version | head -1)"
echo ""

# Step 7: Setup Wine prefix
echo "[7/7] Setting up Wine prefix..."
export WINEARCH=win32
export WINEPREFIX=~/.wine32
wineboot -u
echo "✓ Wine prefix created: $WINEPREFIX"
echo ""

# Step 8: Start Xvfb
echo "[8/8] Starting Xvfb virtual display..."
Xvfb :99 -screen 0 1024x768x24 &
sleep 2
export DISPLAY=:99
if xdpyinfo -display :99 &>/dev/null; then
    echo "✓ Xvfb running on :99"
else
    echo "✗ Xvfb failed to start"
    exit 1
fi
echo ""

# Step 9: Install DirectX 9 (optional but recommended)
echo "[9/9] Installing DirectX 9 via winetricks..."
wget -q https://raw.githubusercontent.com/Winetricks/winetricks/master/src/winetricks \
    -O /tmp/winetricks
chmod +x /tmp/winetricks
DISPLAY=:99 WINEPREFIX=~/.wine32 /tmp/winetricks -q d3dx9 2>&1 | grep -v "^wine:" || true
echo "✓ DirectX 9 installed"
echo ""

echo "═══════════════════════════════════════════════════════════"
echo "  Environment Setup Complete!"
echo "═══════════════════════════════════════════════════════════"
echo ""
echo "Summary:"
echo "  ✓ Wine 11.0+ (wine32, wine64, widl)"
echo "  ✓ MinGW-w64 i686 cross-compiler"
echo "  ✓ CMake build system"
echo "  ✓ Xvfb virtual display (:99)"
echo "  ✓ Wine prefix (~/.wine32)"
echo "  ✓ DirectX 9 runtime"
echo ""
echo "Environment Variables:"
echo "  export WINEARCH=win32"
echo "  export WINEPREFIX=~/.wine32"
echo "  export DISPLAY=:99"
echo "  export CC=i686-w64-mingw32-gcc"
echo "  export CXX=i686-w64-mingw32-g++"
echo ""
echo "Next Steps:"
echo "  1. Build wxWidgets for MinGW (see section below)"
echo "  2. Build W3DView with CMake"
echo "  3. Test with Wine"
echo ""
```

---

## wxWidgets Cross-Compilation

**⚠️ IMPORTANT**: wxWidgets must be built SPECIFICALLY for MinGW Win32 target!

### Download and Extract
```bash
cd /tmp
wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.9/wxWidgets-3.2.9.tar.bz2
tar xjf wxWidgets-3.2.9.tar.bz2
cd wxWidgets-3.2.9
mkdir build-mingw
cd build-mingw
```

### Configure for MinGW Cross-Compilation
```bash
../configure \
    --host=i686-w64-mingw32 \
    --prefix=/opt/wxwidgets-3.2.9-mingw-i686 \
    --with-msw \
    --enable-shared \
    --disable-svg \
    --with-expat=builtin \
    --disable-webview \
    --disable-mediactrl
```

**Configuration Explanation:**
- `--host=i686-w64-mingw32`: Cross-compile for Win32
- `--prefix=/opt/wxwidgets-3.2.9-mingw-i686`: Install location
- `--with-msw`: Windows MSW (not GTK!)
- `--enable-shared`: Create DLLs
- `--disable-svg/webview/mediactrl`: Reduce dependencies

### Build and Install
```bash
make -j$(nproc)
sudo make install
```

**Time**: ~15 minutes on modern hardware

### Verification
```bash
ls -lh /opt/wxwidgets-3.2.9-mingw-i686/bin/*.dll | head -5
ls -lh /opt/wxwidgets-3.2.9-mingw-i686/lib/libwx*.a | head -5
```

Expected: 14-16 DLL files, multiple .a library files

---

## Building W3DView with CMake

### Configure Build
```bash
cd /workspace/project/GeneralsGameCode
mkdir -p build
cd build

cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/mingw-w64-i686.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DwxWidgets_ROOT_DIR=/opt/wxwidgets-3.2.9-mingw-i686
```

### Build W3DView
```bash
cmake --build . --target g_w3dview_wx -j$(nproc)
```

**Output**: `Generals/W3DViewV.exe` (59MB Win32 executable)

### Expected Build Time
- Clean build: ~2-3 minutes
- Incremental build: 4-6 seconds

---

## Testing with Wine

### Copy Required DLLs
```bash
cd /workspace/project/GeneralsGameCode/build/Generals

# Copy wxWidgets DLLs
cp /opt/wxwidgets-3.2.9-mingw-i686/bin/*.dll .

# Copy MinGW runtime DLLs
cp /usr/lib/gcc/i686-w64-mingw32/*/libgcc_s_dw2-1.dll .
cp /usr/lib/gcc/i686-w64-mingw32/*/libstdc++-6.dll .
```

### Run with Wine
```bash
export WINEARCH=win32
export WINEPREFIX=~/.wine32
export DISPLAY=:99

wine W3DViewV.exe
```

### Smoke Test
```bash
timeout 5 wine W3DViewV.exe &> /tmp/w3dview_test.log
EXIT_CODE=$?

if [ $EXIT_CODE -eq 124 ]; then
    echo "✅ SUCCESS: Application running (timeout)"
else
    echo "⚠️  Application exited with code $EXIT_CODE"
    tail -20 /tmp/w3dview_test.log
fi
```

---

## Environment Variables Reference

### Required for Building
```bash
export CC=i686-w64-mingw32-gcc
export CXX=i686-w64-mingw32-g++
export WINEARCH=win32
```

### Required for Testing
```bash
export WINEARCH=win32
export WINEPREFIX=~/.wine32
export DISPLAY=:99
```

### Optional (for debugging)
```bash
export WINEDEBUG=-all  # Suppress Wine debug output
export WINEPREFIX=~/.wine32  # or /opt/wineprefix32
```

---

## Verification Checklist

### Build Environment ✅
- [ ] cmake --version shows 3.31.6+
- [ ] i686-w64-mingw32-gcc --version shows GCC 14+
- [ ] wine --version shows Wine 11.0+
- [ ] widl --version shows widl 11.0+
- [ ] Xvfb running on :99 (xdpyinfo -display :99)

### wxWidgets Installation ✅
- [ ] /opt/wxwidgets-3.2.9-mingw-i686/bin/*.dll exists (14+ files)
- [ ] /opt/wxwidgets-3.2.9-mingw-i686/lib/libwx*.a exists (multiple files)
- [ ] /opt/wxwidgets-3.2.9-mingw-i686/include/wx-3.2/ exists

### Wine Environment ✅
- [ ] WINEPREFIX directory exists (~/.wine32 or /opt/wineprefix32)
- [ ] wine32 and wine64 both installed
- [ ] widl available (for RC compilation)
- [ ] DirectX 9 installed (d3dx9_*.dll in system32)

### Build Success ✅
- [ ] CMake configuration succeeds
- [ ] Build completes with 0 errors, 0 warnings
- [ ] W3DViewV.exe exists (59MB Win32 PE32 i386)
- [ ] file W3DViewV.exe shows "PE32 executable Intel 80386"

### Runtime Success ✅
- [ ] Wine launches W3DViewV.exe without immediate crash
- [ ] Application runs for 5+ seconds
- [ ] No missing DLL errors
- [ ] Window appears (if not headless)

---

## Troubleshooting

### Issue: cmake not found
**Solution**: Install CMake
```bash
sudo apt-get install -y cmake
```

### Issue: i686-w64-mingw32-gcc not found
**Solution**: Install MinGW-w64
```bash
sudo apt-get install -y mingw-w64
```

### Issue: Wine permission denied in /opt
**Solution**: Use user home directory
```bash
export WINEPREFIX=~/.wine32
```

### Issue: Xvfb not running
**Solution**: Start Xvfb manually
```bash
Xvfb :99 -screen 0 1024x768x24 &
export DISPLAY=:99
```

### Issue: Missing DLLs when running with Wine
**Solution**: Copy required DLLs to exe directory
```bash
cp /opt/wxwidgets-3.2.9-mingw-i686/bin/*.dll /path/to/exe/
cp /usr/lib/gcc/i686-w64-mingw32/*/lib*.dll /path/to/exe/
```

### Issue: CMake can't find wxWidgets
**Solution**: Specify wxWidgets root
```bash
cmake .. -DwxWidgets_ROOT_DIR=/opt/wxwidgets-3.2.9-mingw-i686
```

### Issue: Build fails with wx header errors
**Solution**: Ensure MinGW wxWidgets built (not Linux wxWidgets)
```bash
# Remove Linux wxWidgets confusion
# Rebuild wxWidgets with --host=i686-w64-mingw32
```

---

## Differences from Native Linux Development

### ❌ What NOT to Do
- Do NOT use native Linux GCC
- Do NOT build with system wxWidgets (libwxgtk3.2-dev)
- Do NOT try to run binaries natively on Linux
- Do NOT use vcpkg for wxWidgets (manual build required)

### ✅ What TO Do
- Use i686-w64-mingw32-gcc (MinGW cross-compiler)
- Build wxWidgets specifically for MinGW Win32
- Test binaries with Wine
- Follow Xvfb.txt exactly

### Why MinGW?
- W3DView uses DirectX 8/9 (Windows-only)
- Game engine uses Windows APIs
- MFC comparison requires Wine testing
- Native Linux port would require OpenGL conversion

---

## Time Estimates

| Task | Time | Frequency |
|------|------|-----------|
| Base system setup | 5 minutes | One-time |
| Wine installation | 10 minutes | One-time |
| MinGW installation | 2 minutes | One-time |
| Xvfb setup | 1 minute | One-time |
| wxWidgets build | 15 minutes | One-time |
| Initial CMake build | 3 minutes | One-time |
| Incremental builds | 4-6 seconds | Every compile |
| Wine smoke test | 30 seconds | Per test |

**Total Initial Setup**: ~35 minutes (one-time investment)

---

## Environment Persistence

### Add to ~/.bashrc for permanent setup
```bash
# W3DView Development Environment
export WINEARCH=win32
export WINEPREFIX=~/.wine32
export DISPLAY=:99
export CC=i686-w64-mingw32-gcc
export CXX=i686-w64-mingw32-g++

# Start Xvfb if not running
if ! xdpyinfo -display :99 &>/dev/null; then
    Xvfb :99 -screen 0 1024x768x24 &>/dev/null &
fi
```

---

## Testing Tools Integration (Optional)

After environment setup, testing tools from `dev/visual-testing-tools` can be used:

```bash
# Checkout testing tools
git fetch origin dev/visual-testing-tools
git checkout origin/dev/visual-testing-tools -- testing-tools/

# Run smoke test
cd testing-tools
chmod +x run_smoke_test.sh
./run_smoke_test.sh

# Compare screenshots
python3 screenshot_compare.py mfc_screenshot.png wx_screenshot.png -o diff.png
```

---

## Next Steps After Setup

1. **Verify Environment**
   - Run all checklist items
   - Test basic Wine launch
   - Confirm Xvfb display working

2. **Build W3DView**
   - Configure CMake with MinGW toolchain
   - Build g_w3dview_wx target
   - Verify 59MB Win32 executable created

3. **Smoke Test**
   - Copy required DLLs
   - Launch with Wine + Xvfb
   - Verify 5+ second runtime

4. **Continue Development**
   - Implement next features (Session 20: Wireframe toggle)
   - Test incrementally
   - Commit with proper authorship

---

**Setup Guide Complete**  
**Based on**: `/workspace/project/Xvfb.txt`  
**Status**: Ready for implementation
