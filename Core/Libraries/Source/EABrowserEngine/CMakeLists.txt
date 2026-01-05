add_library(core_browserengine INTERFACE)

if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    if(MINGW AND IDL_COMPILER_FOUND)
        # Use widl for MinGW builds
        add_idl_file(browserengine_idl "${CMAKE_CURRENT_LIST_DIR}/BrowserEngine.idl")
        add_library(core_browserenginewin STATIC ${browserengine_idl_IID} ${browserengine_idl_HEADER})
    elseif(MSVC)
        # Use midl for MSVC builds
        add_custom_command(
            OUTPUT BrowserEngine_i.c BrowserEngine.h
            COMMAND midl.exe "${CMAKE_CURRENT_LIST_DIR}\\BrowserEngine.idl" /header BrowserEngine.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            DEPENDS "${CMAKE_CURRENT_LIST_DIR}/BrowserEngine.idl"
            VERBATIM
        )
        add_library(core_browserenginewin STATIC BrowserEngine_i.c)
    endif()
    
    set_target_properties(core_browserenginewin PROPERTIES OUTPUT_NAME browserenginewin)
    target_link_libraries(core_browserengine INTERFACE core_browserenginewin)
endif()

target_include_directories(core_browserengine INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/..)
