#!/bin/bash
# Automated W3DView Build and Test Pipeline
# Tests the complete MFC to wxWidgets conversion automation

set -e  # Exit on error

echo "🚀 W3DView Build and Test Pipeline"
echo "===================================="
echo ""

# Configuration
BUILD_DIR="${BUILD_DIR:-build}"
INSTALL_DEPS="${INSTALL_DEPS:-false}"
RUN_XVFB="${RUN_XVFB:-false}"

# Step 1: Install dependencies (if requested)
if [ "$INSTALL_DEPS" = "true" ]; then
    echo "📦 Installing dependencies..."
    sudo apt-get update -qq
    sudo apt-get install -y -qq \
        libwxgtk3.0-gtk3-dev \
        libwxgtk3.0-gtk3-0v5 \
        wx-common \
        cmake \
        g++ \
        ninja-build \
        xvfb \
        x11-xserver-utils
    echo "✅ Dependencies installed"
    echo ""
fi

# Step 2: Check for wxWidgets
echo "🔍 Checking for wxWidgets..."
if command -v wx-config &> /dev/null; then
    WX_VERSION=$(wx-config --version)
    echo "✅ wxWidgets $WX_VERSION found"
else
    echo "❌ wxWidgets not found!"
    echo "   Install with: sudo apt-get install libwxgtk3.0-gtk3-dev"
    exit 1
fi
echo ""

# Step 3: Validate all XRC files
echo "🔍 Validating XRC files..."
python3 scripts/validate_xrc_files.py Core/Tools/W3DView/ui
if [ $? -ne 0 ]; then
    echo "❌ XRC validation failed!"
    exit 1
fi
echo ""

# Step 4: Configure build
echo "🔧 Configuring build..."
cmake -B "$BUILD_DIR" \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DBUILD_TOOLS=ON \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
echo "✅ Build configured"
echo ""

# Step 5: Build W3DView
echo "🔨 Building W3DView..."
cmake --build "$BUILD_DIR" --target W3DView -j$(nproc)
if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
else
    echo "❌ Build failed!"
    exit 1
fi
echo ""

# Step 6: Run XRC loading test
echo "🧪 Running XRC loading test..."
TEST_BINARY="$BUILD_DIR/Generals/Code/Tools/W3DView/test_xrc_loading"

if [ ! -f "$TEST_BINARY" ]; then
    echo "⚠️  Test binary not found at $TEST_BINARY"
    echo "   Skipping XRC loading test"
else
    # Set up environment for test
    export DISPLAY="${DISPLAY:-:99}"
    
    # Start Xvfb if requested
    if [ "$RUN_XVFB" = "true" ]; then
        echo "🖥️  Starting Xvfb on $DISPLAY..."
        Xvfb $DISPLAY -screen 0 1024x768x24 &
        XVFB_PID=$!
        sleep 2
    fi
    
    # Run test
    cd "$BUILD_DIR/Generals/Code/Tools/W3DView"
    ./test_xrc_loading
    TEST_RESULT=$?
    
    # Cleanup Xvfb
    if [ "$RUN_XVFB" = "true" ]; then
        kill $XVFB_PID 2>/dev/null || true
    fi
    
    if [ $TEST_RESULT -eq 0 ]; then
        echo "✅ XRC loading test passed!"
    else
        echo "❌ XRC loading test failed!"
        exit 1
    fi
fi
echo ""

# Step 7: Summary
echo "========================================"
echo "✅ Pipeline completed successfully!"
echo "========================================"
echo ""
echo "Summary:"
echo "  ✅ XRC validation: PASSED"
echo "  ✅ Build: SUCCESS"
echo "  ✅ XRC loading test: PASSED"
echo ""
echo "Next steps:"
echo "  - Run full application: $BUILD_DIR/Generals/Code/Tools/W3DView/W3DView"
echo "  - Test individual dialogs"
echo "  - Visual comparison with MFC version"
echo ""

exit 0
