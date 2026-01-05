# ReactOS ATL headers for MinGW-w64 builds
# Provides ATL/COM support without MSVC dependencies
# Uses ReactOS PSEH in C++-compatible dummy mode (_USE_DUMMY_PSEH)
# because MinGW-w64's PSEH uses GNU C nested functions which don't work in C++

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
        
        # Add ReactOS ATL and PSEH include directories with SYSTEM to suppress warnings
        # ReactOS PSEH must come BEFORE system includes to override MinGW's pseh2.h
        # (MinGW's pseh2.h uses GNU C nested functions which don't work in C++)
        # NOTE: Do NOT include ReactOS CRT headers - use MinGW-w64's CRT instead
        target_include_directories(reactos_atl SYSTEM INTERFACE 
            "${reactos_atl_SOURCE_DIR}/sdk/lib/pseh/include"
            "${reactos_atl_SOURCE_DIR}/sdk/lib/atl"
        )
        
        # Create ReactOS COM support library (comsupp)
        # Provides _com_util::ConvertStringToBSTR and ConvertBSTRToString
        # Uses ReactOS's comsupp.cpp implementation from sdk/lib/comsupp
        add_library(reactos_comsupp STATIC
            "${reactos_atl_SOURCE_DIR}/sdk/lib/comsupp/comsupp.cpp"
        )
        target_compile_definitions(reactos_comsupp PRIVATE
            WIN32_NO_STATUS
            _INC_WINDOWS
        )
        target_include_directories(reactos_comsupp PRIVATE
            "${reactos_atl_SOURCE_DIR}/sdk/include/psdk"
            "${reactos_atl_SOURCE_DIR}/sdk/include/crt"
        )
        # Link comsupp to oleaut32 for SysAllocString, SysFreeString, etc.
        target_link_libraries(reactos_comsupp PRIVATE oleaut32 ole32)
        
        # Note: reactos_comsupp is NOT added globally via link_libraries()
        # to avoid export conflicts with external dependencies like binkstub.
        # Instead, it should be linked explicitly to targets that need COM support.
        # This is automatically done for game targets via mingw.cmake's link_libraries().
        
        # Add required ATL defines for MinGW compatibility
        # NOTE: Do NOT define _ATL_NO_AUTOMATIC_NAMESPACE
        # The codebase uses ATL types (CComModule, CComObject, CString, etc.)
        # without ATL:: qualification and relies on automatic 'using namespace ATL;'
        #
        # _USE_DUMMY_PSEH: Use ReactOS PSEH's C++-compatible "dummy" mode
        # which provides simple macros instead of GNU C nested functions
        target_compile_definitions(reactos_atl INTERFACE
            _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
            _ATL_NO_DEBUG_CRT
            ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW
            ATL_NO_DEFAULT_LIBS
            _USE_DUMMY_PSEH
        )
        
        message(STATUS "ReactOS ATL headers: ${reactos_atl_SOURCE_DIR}/sdk/lib/atl")
        message(STATUS "ReactOS PSEH headers: ${reactos_atl_SOURCE_DIR}/sdk/lib/pseh/include")
        message(STATUS "ReactOS COM support (comsupp): ${reactos_atl_SOURCE_DIR}/sdk/lib/comsupp/comsupp.cpp")
        message(STATUS "Using ReactOS PSEH in C++-compatible dummy mode (_USE_DUMMY_PSEH)")
        message(STATUS "Using MinGW-w64 CRT headers (NOT ReactOS CRT)")
    endif()
else()
    # Create dummy target for non-MinGW builds
    add_library(reactos_atl INTERFACE)
endif()
