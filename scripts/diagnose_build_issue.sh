#!/bin/bash
# Diagnose the build issue that caused GitHub Actions to fail

set -x  # Show commands as they execute

echo "🔍 Diagnosing build configuration..."
echo ""

# Check if we're in the right directory
pwd
ls -la | head -20

# Check CMakeLists structure
echo ""
echo "📁 Checking CMakeLists.txt files..."
find . -name "CMakeLists.txt" -type f | head -10

# Check for W3DView files
echo ""
echo "📁 Checking W3DView files..."
ls -la Core/Tools/W3DView/*.txt 2>&1 | head -10
ls -la Core/Tools/W3DView/*.h 2>&1 | head -5
ls -la Core/Tools/W3DView/ui/*.xrc 2>&1 | wc -l
ls -la Core/Tools/W3DView/dialogs/*.h 2>&1 | wc -l

# Try to configure (just configuration, not build)
echo ""
echo "🔧 Testing CMake configuration..."
rm -rf /tmp/test_build
cmake -B /tmp/test_build -DBUILD_TOOLS=ON 2>&1 | tee /tmp/cmake_output.log

# Check the result
CMAKE_EXIT=$?
echo ""
echo "========================================"
if [ $CMAKE_EXIT -eq 0 ]; then
    echo "✅ CMake configuration succeeded!"
    
    # Check if W3DView target exists
    echo ""
    echo "🔍 Checking for W3DView target..."
    cmake --build /tmp/test_build --target help | grep -i w3dview
    
else
    echo "❌ CMake configuration failed with exit code $CMAKE_EXIT"
    echo ""
    echo "📋 Last 50 lines of output:"
    tail -50 /tmp/cmake_output.log
fi

exit $CMAKE_EXIT
