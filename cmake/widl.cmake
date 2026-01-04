# WIDL (Wine IDL Compiler) detection and configuration
# Used as MIDL replacement for MinGW-w64 builds

if(MINGW)
    # Find widl executable
    find_program(WIDL_EXECUTABLE
        NAMES widl
        DOC "Wine IDL compiler for MinGW-w64"
    )
    
    if(WIDL_EXECUTABLE)
        message(STATUS "Found widl: ${WIDL_EXECUTABLE}")
        set(IDL_COMPILER ${WIDL_EXECUTABLE})
        set(IDL_COMPILER_FOUND TRUE)
    else()
        message(WARNING "widl not found. Install with: apt-get install wine-dev (Linux) or mingw-w64-tools (Windows)")
        set(IDL_COMPILER_FOUND FALSE)
    endif()
    
    # WIDL command function (compatible with MIDL)
    function(add_idl_file target_name idl_file)
        get_filename_component(idl_basename ${idl_file} NAME_WE)
        get_filename_component(idl_dir ${idl_file} DIRECTORY)
        
        set(header_file "${CMAKE_CURRENT_BINARY_DIR}/${idl_basename}.h")
        set(iid_file "${CMAKE_CURRENT_BINARY_DIR}/${idl_basename}_i.c")
        
        # Use widl with its own preprocessor but define DECLSPEC_ALIGN as empty
        # This allows widl to handle Wine IDL imports correctly
        add_custom_command(
            OUTPUT ${header_file}
            COMMAND ${IDL_COMPILER}
                --win32
                -I${idl_dir}
                -I/usr/include/wine/wine/windows
                -I/usr/include/wine/wine
                -I/usr/include/wine
                -D__WIDL__
                -DDECLSPEC_ALIGN\(x\)=
                -h -o ${header_file}
                ${idl_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS ${idl_file}
            COMMENT "Compiling IDL to header with widl: ${idl_file}"
            VERBATIM
        )
        
        add_custom_command(
            OUTPUT ${iid_file}
            COMMAND ${IDL_COMPILER}
                --win32
                -I${idl_dir}
                -I/usr/include/wine/wine/windows
                -I/usr/include/wine/wine
                -I/usr/include/wine
                -D__WIDL__
                -DDECLSPEC_ALIGN\(x\)=
                -u -o ${iid_file}
                ${idl_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS ${idl_file}
            COMMENT "Compiling IDL to IID with widl: ${idl_file}"
            VERBATIM
        )
        
        # Return output files to parent scope
        set(${target_name}_HEADER ${header_file} PARENT_SCOPE)
        set(${target_name}_IID ${iid_file} PARENT_SCOPE)
    endfunction()
    
elseif(MSVC)
    # MSVC uses midl.exe
    find_program(MIDL_EXECUTABLE
        NAMES midl.exe midl
        DOC "Microsoft IDL compiler"
    )
    
    if(MIDL_EXECUTABLE)
        message(STATUS "Found midl: ${MIDL_EXECUTABLE}")
        set(IDL_COMPILER ${MIDL_EXECUTABLE})
        set(IDL_COMPILER_FOUND TRUE)
    else()
        # midl.exe is usually in PATH with Visual Studio
        set(IDL_COMPILER "midl.exe")
        set(IDL_COMPILER_FOUND TRUE)
        message(STATUS "Using midl.exe from PATH")
    endif()
    
    # MIDL command function
    function(add_idl_file target_name idl_file)
        get_filename_component(idl_basename ${idl_file} NAME_WE)
        
        set(header_file "${CMAKE_CURRENT_BINARY_DIR}/${idl_basename}.h")
        set(iid_file "${CMAKE_CURRENT_BINARY_DIR}/${idl_basename}_i.c")
        
        # Convert forward slashes to backslashes for MIDL
        file(TO_NATIVE_PATH ${idl_file} idl_file_native)
        
        add_custom_command(
            OUTPUT ${header_file} ${iid_file}
            COMMAND ${IDL_COMPILER} "${idl_file_native}" /header ${idl_basename}.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS ${idl_file}
            COMMENT "Compiling IDL file ${idl_file} with midl"
            VERBATIM
        )
        
        # Return output files to parent scope
        set(${target_name}_HEADER ${header_file} PARENT_SCOPE)
        set(${target_name}_IID ${iid_file} PARENT_SCOPE)
    endfunction()
else()
    message(WARNING "No IDL compiler configured for this platform")
    set(IDL_COMPILER_FOUND FALSE)
endif()
