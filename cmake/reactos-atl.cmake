# ReactOS ATL headers for MinGW-w64 builds
# Provides ATL/COM support without MSVC dependencies
# Uses MinGW-w64's PSEH implementation for exception handling

if(MINGW)
    message(STATUS "Setting up ReactOS ATL for MinGW-w64")
    
    FetchContent_Declare(
        reactos_atl
        GIT_REPOSITORY https://github.com/reactos/reactos.git
        GIT_TAG        0.4.15-release
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
        SOURCE_SUBDIR  sdk/lib/atl
    )
    
    FetchContent_GetProperties(reactos_atl)
    if(NOT reactos_atl_POPULATED)
        FetchContent_Populate(reactos_atl)
        
        # Create interface library for ReactOS ATL headers
        add_library(reactos_atl INTERFACE)
        
        # Add ONLY ReactOS ATL include directory with SYSTEM to suppress warnings
        # Do NOT include ReactOS PSEH - MinGW-w64 provides its own PSEH at
        # /usr/i686-w64-mingw32/include/pseh/ which will be found first
        target_include_directories(reactos_atl SYSTEM INTERFACE 
            "${reactos_atl_SOURCE_DIR}/sdk/lib/atl"
        )
        
        # Add required ATL defines for MinGW compatibility
        target_compile_definitions(reactos_atl INTERFACE
            _ATL_NO_AUTOMATIC_NAMESPACE
            _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
            _ATL_NO_DEBUG_CRT
            ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW
            ATL_NO_DEFAULT_LIBS
        )
        
        message(STATUS "ReactOS ATL headers: ${reactos_atl_SOURCE_DIR}/sdk/lib/atl")
        message(STATUS "Using MinGW-w64 PSEH (not ReactOS PSEH)")
    endif()
else()
    # Create dummy target for non-MinGW builds
    add_library(reactos_atl INTERFACE)
endif()
