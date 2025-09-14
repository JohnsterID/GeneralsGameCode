add_library(core_browserengine INTERFACE)

# Use widl (Wine IDL compiler) for cross-platform COM interface generation
if(WIN32)
    # On Windows, try to use midl.exe first, fall back to widl
    find_program(MIDL_EXECUTABLE midl.exe)
    if(MIDL_EXECUTABLE)
        add_custom_command(
            OUTPUT BrowserEngine_i.c BrowserEngine.h
            COMMAND ${MIDL_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}\\BrowserEngine.idl" /header BrowserEngine.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS "${CMAKE_CURRENT_LIST_DIR}/BrowserEngine.idl"
            VERBATIM
        )
    else()
        # Fall back to widl on Windows if midl.exe not found
        find_program(WIDL_EXECUTABLE widl REQUIRED)
        add_custom_command(
            OUTPUT BrowserEngine_i.c BrowserEngine.h
            COMMAND ${WIDL_EXECUTABLE} -h -H BrowserEngine.h "${CMAKE_CURRENT_LIST_DIR}/BrowserEngine.idl"
            COMMAND ${WIDL_EXECUTABLE} -c -o BrowserEngine_i.c "${CMAKE_CURRENT_LIST_DIR}/BrowserEngine.idl"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS "${CMAKE_CURRENT_LIST_DIR}/BrowserEngine.idl"
            VERBATIM
        )
    endif()
else()
    # On non-Windows platforms, use widl (Wine IDL compiler)
    find_program(WIDL_EXECUTABLE widl REQUIRED)
    add_custom_command(
        OUTPUT BrowserEngine_i.c BrowserEngine.h
        COMMAND ${WIDL_EXECUTABLE} -h -H BrowserEngine.h "${CMAKE_CURRENT_LIST_DIR}/BrowserEngine.idl"
        COMMAND ${WIDL_EXECUTABLE} -c -o BrowserEngine_i.c "${CMAKE_CURRENT_LIST_DIR}/BrowserEngine.idl"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/BrowserEngine.idl"
        VERBATIM
    )
endif()

# Build the COM interface library using MinGW cross-compiler for Windows API compatibility
find_program(MINGW_GCC i686-w64-mingw32-gcc)

if(MINGW_GCC)
    # Use MinGW cross-compiler to compile COM interface files
    message(STATUS "Using MinGW cross-compiler for COM interface compilation: ${MINGW_GCC}")
    
    # Create custom command to compile BrowserEngine_i.c with MinGW
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/BrowserEngine_i.o
        COMMAND ${MINGW_GCC} -c -I${CMAKE_CURRENT_BINARY_DIR} 
                ${CMAKE_CURRENT_BINARY_DIR}/BrowserEngine_i.c 
                -o ${CMAKE_CURRENT_BINARY_DIR}/BrowserEngine_i.o
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/BrowserEngine_i.c
        COMMENT "Compiling BrowserEngine_i.c with MinGW cross-compiler"
    )
    
    # Create library from the MinGW-compiled object file
    add_library(core_browserenginewin STATIC ${CMAKE_CURRENT_BINARY_DIR}/BrowserEngine_i.o)
    set_target_properties(core_browserenginewin PROPERTIES 
        OUTPUT_NAME browserenginewin
        LINKER_LANGUAGE C
    )
    
    target_link_libraries(core_browserengine INTERFACE core_browserenginewin)
    
else()
    # Fallback: try to compile with regular GCC and MinGW-w64 headers
    message(WARNING "MinGW cross-compiler not found. Attempting compilation with regular GCC and MinGW-w64 headers.")
    
    add_library(core_browserenginewin STATIC BrowserEngine_i.c)
    set_target_properties(core_browserenginewin PROPERTIES OUTPUT_NAME browserenginewin)
    
    # Add MinGW-w64 headers for Windows API compatibility
    find_path(MINGW_W64_INCLUDE_DIR windows.h
        HINTS
            /usr/i686-w64-mingw32/include
            /usr/x86_64-w64-mingw32/include
            /usr/include/mingw
        DOC "MinGW-w64 include directory for Windows API compatibility"
    )
    
    if(MINGW_W64_INCLUDE_DIR)
        target_include_directories(core_browserenginewin PRIVATE ${MINGW_W64_INCLUDE_DIR})
        message(STATUS "Using MinGW-w64 headers: ${MINGW_W64_INCLUDE_DIR}")
    endif()
    
    target_link_libraries(core_browserengine INTERFACE core_browserenginewin)
endif()

target_include_directories(core_browserengine INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/..)
