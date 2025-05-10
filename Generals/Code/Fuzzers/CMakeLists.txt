# Fuzzers for Generals code

if(RTS_BUILD_OPTION_FUZZER)
    # BIG File Fuzzer
    add_executable(big_file_fuzzer BIGFileFuzzer.cpp)
    
    # Link against required libraries
    target_link_libraries(big_file_fuzzer PRIVATE 
        core_config
        wwlib
        wwdebug
        wwvegas
    )
    
    # Set include directories
    target_include_directories(big_file_fuzzer PRIVATE
        ${CMAKE_SOURCE_DIR}/Generals/Code/GameEngine/Include
        ${CMAKE_SOURCE_DIR}/Generals/Code/GameEngineDevice/Include
        ${CMAKE_SOURCE_DIR}/Core/Libraries/Include
    )
    
    # Set output directory
    set_target_properties(big_file_fuzzer PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/fuzzers"
    )
    
    # Create a directory for fuzzer corpus
    add_custom_command(TARGET big_file_fuzzer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/fuzzers/corpus/big_file"
        COMMENT "Creating corpus directory for big_file_fuzzer"
    )
    
    # Create a simple seed file for the fuzzer
    add_custom_command(TARGET big_file_fuzzer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "BIGF" > "${CMAKE_BINARY_DIR}/bin/fuzzers/corpus/big_file/seed1"
        COMMENT "Creating seed file for big_file_fuzzer"
    )
    
    message(STATUS "Configured BIG file fuzzer")
endif()