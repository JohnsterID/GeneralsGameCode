#!/bin/bash
# Wine + Xvfb Test Script for Crash Dialog Testing
# 
# This script sets up a virtual X server and tests the crash dialog
# using Wine on Linux (headless environment).
#
# Usage:
#   ./test-wine-xvfb.sh [build|test|clean]
#
# Requirements:
#   - Wine
#   - Xvfb
#   - MinGW-w64 cross-compiler
#   - CMake

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build-mingw"
DISPLAY_NUM=99
LOG_FILE="$SCRIPT_DIR/wine-crash-test.log"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

function print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

function print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

function print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

function print_error() {
    echo -e "${RED}❌ $1${NC}"
}

function check_dependencies() {
    print_header "Checking Dependencies"
    
    local missing=0
    
    if ! command -v wine &> /dev/null; then
        print_error "Wine not found"
        missing=1
    else
        print_success "Wine: $(wine --version)"
    fi
    
    if ! command -v Xvfb &> /dev/null; then
        print_error "Xvfb not found"
        missing=1
    else
        print_success "Xvfb: installed"
    fi
    
    if ! command -v x86_64-w64-mingw32-gcc &> /dev/null; then
        print_error "MinGW-w64 (64-bit) not found"
        missing=1
    else
        print_success "MinGW-w64: $(x86_64-w64-mingw32-gcc -dumpversion)"
    fi
    
    if ! command -v /usr/bin/cmake &> /dev/null; then
        print_error "CMake not found"
        missing=1
    else
        print_success "CMake: $(/usr/bin/cmake --version | head -1 || echo 'installed')"
    fi
    
    if [ $missing -eq 1 ]; then
        print_error "Missing dependencies. Please install them first."
        exit 1
    fi
    
    echo ""
}

function build_project() {
    print_header "Building with MinGW-w64"
    
    # Check if CMakeLists.txt exists
    if [ ! -f "$SCRIPT_DIR/CMakeLists.txt" ]; then
        print_error "CMakeLists.txt not found in $SCRIPT_DIR"
        exit 1
    fi
    
    # Check for toolchain file
    if [ ! -f "$SCRIPT_DIR/cmake/toolchain-mingw-w64.cmake" ]; then
        print_warning "Toolchain file not found, will attempt standard MinGW build"
        
        # Try using CMake presets if available
        if [ -f "$SCRIPT_DIR/CMakePresets.json" ]; then
            print_success "Found CMakePresets.json, checking for compatible preset..."
            /usr/bin/cmake --list-presets 2>/dev/null || true
        fi
    fi
    
    # Create build directory
    mkdir -p "$BUILD_DIR"
    
    # Configure (this might fail without proper toolchain, adjust as needed)
    print_success "Configuring build..."
    cd "$BUILD_DIR"
    
    # Try different configure methods
    if [ -f "$SCRIPT_DIR/cmake/toolchain-mingw-w64.cmake" ]; then
        /usr/bin/cmake .. \
            -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain-mingw-w64.cmake \
            -DCMAKE_BUILD_TYPE=Debug
    else
        print_warning "Attempting build with available presets or default configuration"
        /usr/bin/cmake .. -DCMAKE_BUILD_TYPE=Debug || {
            print_error "CMake configuration failed"
            print_warning "You may need to configure the build manually"
            exit 1
        }
    fi
    
    # Build
    print_success "Building project..."
    /usr/bin/cmake --build . --target generalszh || {
        print_error "Build failed"
        exit 1
    }
    
    print_success "Build completed successfully"
    echo ""
}

function test_crash_dialog() {
    print_header "Testing Crash Dialog with Wine + Xvfb"
    
    # Find the executable
    local exe_path=""
    if [ -f "$BUILD_DIR/bin/generalszh.exe" ]; then
        exe_path="$BUILD_DIR/bin/generalszh.exe"
    elif [ -f "$BUILD_DIR/generalszh.exe" ]; then
        exe_path="$BUILD_DIR/generalszh.exe"
    else
        print_error "Could not find generalszh.exe in build directory"
        print_warning "Build the project first with: $0 build"
        exit 1
    fi
    
    print_success "Found executable: $exe_path"
    
    # Test 1: Basic crash trigger
    print_header "Test 1: Running with -testcrash flag"
    
    print_success "Starting Xvfb on display :$DISPLAY_NUM..."
    Xvfb :$DISPLAY_NUM -screen 0 1024x768x24 &
    XVFB_PID=$!
    export DISPLAY=:$DISPLAY_NUM
    
    # Give Xvfb time to start
    sleep 2
    
    print_success "Running game with Wine..."
    print_warning "Expected: Game should crash and show dialog (check logs)"
    
    # Run with Wine and capture output
    WINEDEBUG=+messagebox,+dialog wine "$exe_path" -testcrash 2>&1 | tee "$LOG_FILE" || {
        print_warning "Game exited with crash (expected behavior)"
    }
    
    # Kill Xvfb
    kill $XVFB_PID 2>/dev/null || true
    
    print_success "Test completed, logs saved to: $LOG_FILE"
    
    # Check for expected crash files
    print_header "Checking for Crash Files"
    
    # Look for CrashInfo.txt in Wine's user directory
    local wine_home="$HOME/.wine"
    local wine_docs="$wine_home/drive_c/users/$USER/My Documents"
    
    if [ -d "$wine_docs" ]; then
        print_success "Searching for crash files in Wine documents..."
        find "$wine_docs" -name "CrashInfo.txt" -o -name "*.dmp" | while read -r file; do
            print_success "Found: $file"
        done
    else
        print_warning "Wine documents directory not found, crash files may be elsewhere"
    fi
    
    # Search in current directory
    if [ -f "./CrashInfo.txt" ]; then
        print_success "Found CrashInfo.txt in current directory"
        echo ""
        print_header "CrashInfo.txt Contents"
        head -50 ./CrashInfo.txt
    fi
    
    echo ""
    print_header "Test Summary"
    echo "Check $LOG_FILE for Wine/MessageBox output"
    echo "Look for MessageBox-related entries in the log"
    echo ""
}

function clean_build() {
    print_header "Cleaning Build Directory"
    
    if [ -d "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
        print_success "Build directory cleaned"
    else
        print_warning "Build directory does not exist"
    fi
    
    if [ -f "$LOG_FILE" ]; then
        rm -f "$LOG_FILE"
        print_success "Log file removed"
    fi
    
    echo ""
}

function show_usage() {
    echo "Usage: $0 [command]"
    echo ""
    echo "Commands:"
    echo "  deps     - Check dependencies"
    echo "  build    - Build project with MinGW-w64"
    echo "  test     - Run crash dialog test with Wine + Xvfb"
    echo "  clean    - Clean build directory"
    echo "  all      - Check deps, build, and test (default)"
    echo ""
}

# Main script
case "${1:-all}" in
    deps)
        check_dependencies
        ;;
    build)
        check_dependencies
        build_project
        ;;
    test)
        check_dependencies
        test_crash_dialog
        ;;
    clean)
        clean_build
        ;;
    all)
        check_dependencies
        build_project
        test_crash_dialog
        ;;
    help|--help|-h)
        show_usage
        ;;
    *)
        print_error "Unknown command: $1"
        echo ""
        show_usage
        exit 1
        ;;
esac

print_success "All operations completed"
