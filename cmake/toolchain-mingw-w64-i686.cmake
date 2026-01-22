# CMake toolchain file for MinGW-w64 i686 (32-bit Windows) cross-compilation
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-mingw-w64-i686.cmake ..

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

# Specify the cross compilers
set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)

# Specify the target environment
set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Make sure we're building for Win32
set(WIN32 1)
set(MINGW 1)

# Set compiler flags for Windows
set(CMAKE_C_FLAGS_INIT "-D_WIN32 -DWIN32")
set(CMAKE_CXX_FLAGS_INIT "-D_WIN32 -DWIN32")

# Enable static linking to avoid DLL dependencies
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static-libgcc -static-libstdc++")
