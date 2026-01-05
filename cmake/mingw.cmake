# MinGW-w64 specific compiler and linker configurations

if(MINGW)
    message(STATUS "Configuring MinGW-w64 build settings")
    
    # Detect if this is 32-bit or 64-bit MinGW
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(IS_MINGW32 TRUE)
        message(STATUS "MinGW-w64 32-bit (i686) detected")
    else()
        set(IS_MINGW32 FALSE)
        message(STATUS "MinGW-w64 64-bit (x86_64) detected")
    endif()
    
    # Base compiler flags for MinGW
    if(IS_MINGW32)
        # Force 32-bit compilation
        add_compile_options(-m32)
        add_link_options(-m32)
    endif()
    
    # Windows subsystem
    add_link_options(-mwindows)
    
    # Compatibility flags for legacy code
    add_compile_options(
        -fno-strict-aliasing        # Avoid type-punning issues with DX8/COM
    )
    
    # MSVC compatibility macros for MinGW
    # Note: MinGW already defines _cdecl and _stdcall correctly, so we only add __forceinline
    add_compile_definitions(
        __forceinline=inline\ __attribute__\(\(always_inline\)\)
        __int64=long\ long
        _int64=long\ long
    )
    
    # Math constants for MinGW (not defined by default in C++ mode)
    add_compile_definitions(
        M_PI=3.14159265358979323846
        M_PI_2=1.57079632679489661923
        M_PI_4=0.785398163397448309616
    )
    
    # Ensure proper calling conventions are defined
    # MinGW-w64 should define these, but verify they exist
    include(CheckCXXSymbolExists)
    check_cxx_symbol_exists(STDMETHODCALLTYPE "windows.h" HAVE_STDMETHODCALLTYPE)
    if(NOT HAVE_STDMETHODCALLTYPE)
        add_compile_definitions(
            STDMETHODCALLTYPE=__stdcall
            STDMETHODIMP=HRESULT\ __stdcall
        )
    endif()
    
    # Required Windows libraries for DX8 + COM
    link_libraries(
        uuid        # COM GUIDs
        ole32       # COM runtime
        oleaut32    # COM automation
        gdi32       # GDI
        user32      # User interface
        comctl32    # Common controls
        winmm       # Multimedia (timeGetTime, etc.)
        d3d8        # Direct3D 8
        dinput8     # DirectInput 8
        dsound      # DirectSound
    )
    
    # Optional: Add d3dx8 if available from min-dx8-sdk
    # Note: MinGW only provides libd3dx8d.a (debug), so we link to the 
    # d3dx8.lib from min-dx8-sdk via the dx8.cmake FetchContent
    
    message(STATUS "MinGW-w64 configuration complete")
endif()
