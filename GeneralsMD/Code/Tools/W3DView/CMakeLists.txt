if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})

    add_executable(z_w3dview_wx WIN32)

    target_link_libraries(z_w3dview_wx PRIVATE
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
        Version
        vfw32
        winmm
        z_wwaudio
        z_wwvegas
    )

    target_include_directories(z_w3dview_wx PRIVATE
        ${wxWidgets_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../Core/Tools/W3DView
    )

    target_compile_definitions(z_w3dview_wx PRIVATE
        ${wxWidgets_DEFINITIONS}
        USE_WXWIDGETS=1
    )

    if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
        set_target_properties(z_w3dview_wx PROPERTIES OUTPUT_NAME W3DViewZH)
    else()
        set_target_properties(z_w3dview_wx PROPERTIES OUTPUT_NAME w3dviewzh)
    endif()

elseif(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    add_executable(z_w3dview WIN32)

    target_link_libraries(z_w3dview PRIVATE
        core_config
        core_utility
        core_wwstub # avoid linking GameEngine
        corei_w3dview # this interface gets the source files for the tool
        d3d8
        d3d8lib
        d3dx8
        imm32
        milesstub
        Version
        vfw32
        winmm
        z_wwaudio
        z_wwvegas
    )

    if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
        target_compile_definitions(z_w3dview PRIVATE _AFXDLL)
        set_target_properties(z_w3dview PROPERTIES OUTPUT_NAME W3DViewZH)
    else()
        set_target_properties(z_w3dview PROPERTIES OUTPUT_NAME w3dviewzh)
    endif()
endif()
