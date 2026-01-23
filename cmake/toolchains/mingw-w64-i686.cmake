# TheSuperHackers @build JohnsterID 05/01/2026 Add MinGW-w64 i686 cross-compilation toolchain
# MinGW-w64 32-bit (i686) Toolchain File
# Use with: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64-i686.cmake

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

# Specify the cross compiler
set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)
set(CMAKE_AR i686-w64-mingw32-ar)
set(CMAKE_RANLIB i686-w64-mingw32-ranlib)
set(CMAKE_DLLTOOL i686-w64-mingw32-dlltool)

# Target environment
set(CMAKE_FIND_ROOT_PATH 
    /usr/i686-w64-mingw32
    /opt/wxwidgets-3.2.9-mingw-i686
)

# Adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Force 32-bit pointer size
set(CMAKE_SIZEOF_VOID_P 4)

# Tool build flags (MFC tools disabled, wxWidgets tools enabled if wxWidgets found)
# W3DView and DebugWindow have wxWidgets alternatives and can be built with MinGW
set(RTS_BUILD_CORE_TOOLS OFF CACHE BOOL "Disable MFC-dependent core tools for MinGW" FORCE)
set(RTS_BUILD_GENERALS_TOOLS ON CACHE BOOL "Enable wxWidgets-based tools for MinGW" FORCE)
set(RTS_BUILD_ZEROHOUR_TOOLS ON CACHE BOOL "Enable wxWidgets-based tools for MinGW" FORCE)
