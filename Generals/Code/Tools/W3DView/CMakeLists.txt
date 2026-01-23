if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})

    add_executable(g_w3dview_wx WIN32)

    target_link_libraries(g_w3dview_wx PRIVATE
        core_config
        core_utility
        core_wwstub
        corei_w3dview_wx
        ${wxWidgets_LIBRARIES}
        d3d8
        d3d8lib
        d3dx8
        imm32
        milesstub
        version  # MinGW: libversion.a, MSVC: Version.lib (case-insensitive on Windows)
        vfw32
        winmm
        g_wwaudio
        g_wwvegas
    )

    target_include_directories(g_w3dview_wx PRIVATE
        ${wxWidgets_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Core/Tools/W3DView
    )

    target_compile_definitions(g_w3dview_wx PRIVATE
        ${wxWidgets_DEFINITIONS}
        USE_WXWIDGETS=1
    )

    if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
        set_target_properties(g_w3dview_wx PROPERTIES OUTPUT_NAME W3DViewV)
    else()
        set_target_properties(g_w3dview_wx PROPERTIES OUTPUT_NAME w3dviewv)
    endif()

    # XRC loading test executable (commented out - test file not on feat branch, not REQUIRED)
    # add_executable(test_xrc_loading
    #     ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Core/Tools/W3DView/test_xrc_loading.cpp
    #     ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Core/Tools/W3DView/W3DViewUI.cpp
    # )
    #
    # target_link_libraries(test_xrc_loading PRIVATE
    #     ${wxWidgets_LIBRARIES}
    # )
    #
    # target_include_directories(test_xrc_loading PRIVATE
    #     ${wxWidgets_INCLUDE_DIRS}
    #     ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Core/Tools/W3DView
    # )
    #
    # target_compile_definitions(test_xrc_loading PRIVATE
    #     ${wxWidgets_DEFINITIONS}
    # )

elseif(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    add_executable(g_w3dview WIN32)

    target_link_libraries(g_w3dview PRIVATE
        core_config
        core_utility
        core_wwstub # avoid linking GameEngine
        corei_w3dview # this interface gets the source files for the tool
        d3d8
        d3d8lib
        d3dx8
        imm32
        milesstub
        version  # MinGW: libversion.a, MSVC: Version.lib (case-insensitive on Windows)
        vfw32
        winmm
        g_wwaudio
        g_wwvegas
    )

    if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
        target_compile_definitions(g_w3dview PRIVATE _AFXDLL)
        set_target_properties(g_w3dview PROPERTIES OUTPUT_NAME W3DViewV)
    else()
        set_target_properties(g_w3dview PROPERTIES OUTPUT_NAME w3dviewv)
    endif()
endif()
