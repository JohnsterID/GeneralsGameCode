# MinGW-w64 32-bit (i686) Toolchain File
# Use with: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64-i686.cmake

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

# Specify the cross compiler
set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)

# Target environment
set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)

# Adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Force 32-bit pointer size
set(CMAKE_SIZEOF_VOID_P 4)
