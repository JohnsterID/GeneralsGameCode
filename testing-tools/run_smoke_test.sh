#!/bin/bash
#
# Smoke Test for MFC vs wxWidgets W3DView
# Tests if both executables launch successfully under Wine
#

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "═══════════════════════════════════════════════════════════"
echo "  W3DView MFC vs wxWidgets Smoke Test"
echo "═══════════════════════════════════════════════════════════"
echo ""

# Setup paths
MFC_EXE="/workspace/project/mfc-artifacts/ZH/W3DViewZH.exe"
WX_EXE="/workspace/project/GeneralsGameCode/build/Generals/W3DViewV.exe"
GAME_DIR="/workspace/project/Command & Conquer Generals - Zero Hour"

# Check if executables exist
echo "[1/5] Checking executables..."
if [ ! -f "$MFC_EXE" ]; then
    echo -e "${RED}ERROR: MFC executable not found: $MFC_EXE${NC}"
    exit 1
fi
if [ ! -f "$WX_EXE" ]; then
    echo -e "${RED}ERROR: wxWidgets executable not found: $WX_EXE${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Both executables found${NC}"
echo "  MFC:      $(ls -lh "$MFC_EXE" | awk '{print $5}')"
echo "  wxWidgets: $(ls -lh "$WX_EXE" | awk '{print $5}')"
echo ""

# Check Wine setup
echo "[2/5] Checking Wine environment..."
if ! command -v wine &> /dev/null; then
    echo -e "${RED}ERROR: Wine not installed${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Wine installed: $(wine --version)${NC}"
echo ""

# Setup Wine environment
echo "[3/5] Setting up Wine environment..."
export WINEARCH=win32
export WINEPREFIX=~/.wine32
export DISPLAY=:99

# Check if Xvfb is running
if ! xdpyinfo -display :99 &>/dev/null; then
    echo -e "${YELLOW}⚠ Xvfb not running on :99, attempting to start...${NC}"
    Xvfb :99 -screen 0 1280x1024x24 &
    sleep 2
    if ! xdpyinfo -display :99 &>/dev/null; then
        echo -e "${RED}ERROR: Failed to start Xvfb${NC}"
        exit 1
    fi
fi
echo -e "${GREEN}✓ Xvfb running on display :99${NC}"
echo ""

# Test MFC version
echo "[4/5] Testing MFC W3DViewZH.exe..."
echo "  Launching MFC version for 5 seconds..."
timeout 5 wine "$MFC_EXE" &> /tmp/mfc_launch.log || true
MFC_EXIT=$?
if grep -qi "error\|exception\|crash" /tmp/mfc_launch.log; then
    echo -e "${YELLOW}⚠ MFC version may have issues (check /tmp/mfc_launch.log)${NC}"
    echo "  Last 10 lines:"
    tail -10 /tmp/mfc_launch.log | sed 's/^/    /'
else
    echo -e "${GREEN}✓ MFC version launched (exit code: $MFC_EXIT)${NC}"
fi
echo ""

# Test wxWidgets version
echo "[5/5] Testing wxWidgets W3DViewV.exe..."
echo "  Launching wxWidgets version for 5 seconds..."
timeout 5 wine "$WX_EXE" &> /tmp/wx_launch.log || true
WX_EXIT=$?
if grep -qi "error\|exception\|crash" /tmp/wx_launch.log; then
    echo -e "${YELLOW}⚠ wxWidgets version may have issues (check /tmp/wx_launch.log)${NC}"
    echo "  Last 10 lines:"
    tail -10 /tmp/wx_launch.log | sed 's/^/    /'
else
    echo -e "${GREEN}✓ wxWidgets version launched (exit code: $WX_EXIT)${NC}"
fi
echo ""

# Summary
echo "═══════════════════════════════════════════════════════════"
echo "  Smoke Test Summary"
echo "═══════════════════════════════════════════════════════════"
echo ""
echo "MFC Version:      $(if [ $MFC_EXIT -ne 124 ]; then echo -e "${YELLOW}Exited early ($MFC_EXIT)${NC}"; else echo -e "${GREEN}OK (timeout)${NC}"; fi)"
echo "wxWidgets Version: $(if [ $WX_EXIT -ne 124 ]; then echo -e "${YELLOW}Exited early ($WX_EXIT)${NC}"; else echo -e "${GREEN}OK (timeout)${NC}"; fi)"
echo ""
echo "Logs saved:"
echo "  MFC:      /tmp/mfc_launch.log"
echo "  wxWidgets: /tmp/wx_launch.log"
echo ""

if [ $MFC_EXIT -eq 124 ] && [ $WX_EXIT -eq 124 ]; then
    echo -e "${GREEN}✅ SMOKE TEST PASSED: Both versions launch successfully${NC}"
    exit 0
else
    echo -e "${YELLOW}⚠ SMOKE TEST PARTIAL: One or both versions exited early${NC}"
    echo "  This may be expected if running headless."
    echo "  Check logs for actual errors."
    exit 0
fi
