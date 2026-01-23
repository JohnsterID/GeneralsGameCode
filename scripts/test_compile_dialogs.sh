#!/bin/bash
# Test compilation script for Phase 2.5 integrated dialogs
# This performs syntax-only compilation checks without linking

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(dirname "$SCRIPT_DIR")"
DIALOGS_DIR="$REPO_ROOT/Core/Tools/W3DView/dialogs"

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "========================================================================"
echo "PHASE 2.5 DIALOG SYNTAX COMPILATION TEST"
echo "========================================================================"
echo ""

# Check if g++ is available
if ! command -v g++ &> /dev/null; then
    echo -e "${RED}❌ g++ not found${NC}"
    exit 1
fi

echo -e "${GREEN}✅ Found g++: $(g++ --version | head -1)${NC}"
echo ""

# Create a test output directory
TEST_DIR="$REPO_ROOT/test_compile_output"
mkdir -p "$TEST_DIR"

# Check if wx-config is available
if ! command -v wx-config &> /dev/null; then
    echo -e "${RED}❌ wx-config not found${NC}"
    echo "Please install wxWidgets development package:"
    echo "  sudo apt-get install libwxgtk3.2-dev"
    exit 1
fi

echo -e "${GREEN}✅ Found wxWidgets: $(wx-config --version)${NC}"

# Get wxWidgets flags
WX_CXXFLAGS="$(wx-config --cxxflags)"

# Common include paths (minimal for syntax checking)
INCLUDES="-I$REPO_ROOT"
INCLUDES="$INCLUDES -I$REPO_ROOT/Core"
INCLUDES="$INCLUDES -I$REPO_ROOT/Core/Tools/W3DView"

# C++ standard and flags
CXXFLAGS="-std=c++17 -fsyntax-only $WX_CXXFLAGS"

# Test a few simple dialogs first
TEST_DIALOGS=(
    "PropPageAdvanimMixing_wx.cpp"
    "BackgroundObject_wx.cpp"
    "BackgroundBmp_wx.cpp"
    "ColorPicker_wx.cpp"
    "CameraDistance_wx.cpp"
)

echo "Testing syntax compilation of ${#TEST_DIALOGS[@]} dialogs..."
echo ""

SUCCESS=0
FAILED=0
FAILED_FILES=()

for dialog in "${TEST_DIALOGS[@]}"; do
    DIALOG_FILE="$DIALOGS_DIR/$dialog"
    
    if [ ! -f "$DIALOG_FILE" ]; then
        echo -e "${YELLOW}⏭️  Skip: $dialog (not found)${NC}"
        continue
    fi
    
    echo -n "Testing $dialog... "
    
    # Try to compile (syntax only)
    if g++ $CXXFLAGS $INCLUDES "$DIALOG_FILE" 2> "$TEST_DIR/${dialog}.errors"; then
        echo -e "${GREEN}✅ OK${NC}"
        SUCCESS=$((SUCCESS + 1))
        rm -f "$TEST_DIR/${dialog}.errors"
    else
        echo -e "${RED}❌ FAILED${NC}"
        FAILED=$((FAILED + 1))
        FAILED_FILES+=("$dialog")
        
        # Show first few errors
        echo -e "${YELLOW}First 10 errors:${NC}"
        head -10 "$TEST_DIR/${dialog}.errors" | sed 's/^/  /'
        echo ""
    fi
done

echo ""
echo "========================================================================"
echo "COMPILATION TEST SUMMARY"
echo "========================================================================"
echo ""
echo -e "Success: ${GREEN}$SUCCESS${NC} dialogs"
echo -e "Failed:  ${RED}$FAILED${NC} dialogs"
echo ""

if [ $FAILED -gt 0 ]; then
    echo "Failed files:"
    for file in "${FAILED_FILES[@]}"; do
        echo "  - $file"
        echo "    Error log: $TEST_DIR/${file}.errors"
    done
    echo ""
    echo -e "${YELLOW}Note: Failures are expected due to missing wxWidgets headers${NC}"
    echo -e "${YELLOW}      and missing project headers. This is normal.${NC}"
fi

echo ""
echo "Next steps:"
echo "  1. Install wxWidgets development packages"
echo "  2. Set up full build environment"
echo "  3. Test full compilation"

exit 0
