# ReactOS ATL headers for MinGW-w64 builds
# Provides ATL/COM support without MSVC dependencies

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
        
        # Add ATL include directory
        target_include_directories(reactos_atl INTERFACE 
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
    endif()
else()
    # Create dummy target for non-MinGW builds
    add_library(reactos_atl INTERFACE)
endif()
