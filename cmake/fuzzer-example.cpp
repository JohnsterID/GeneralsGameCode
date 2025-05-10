// Example fuzzer target for GeneralsGameCode
// This is a template that can be adapted for specific components

#include <cstdint>
#include <cstddef>
#include <string>

// Include the headers for the component you want to fuzz
// #include "YourComponent.h"

// The fuzzer entry point - this function will be called by LibFuzzer
// with different inputs to test your code
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // Skip empty inputs
    if (Size == 0) {
        return 0;
    }

    // Convert the raw data to a format your component can use
    // For example, if your component processes strings:
    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Call the function or component you want to test
    // For example:
    // YourComponent component;
    // component.process(input);
    
    // Or if you're testing a parser:
    // try {
    //     Parser parser;
    //     parser.parse(input);
    // } catch (const std::exception& e) {
    //     // Catching exceptions is important to continue fuzzing
    //     // But don't log them as that would slow down fuzzing
    // }

    // Return 0 to indicate successful execution
    // LibFuzzer will detect crashes automatically
    return 0;
}

// To compile this fuzzer:
// cmake -B build -DRTS_BUILD_OPTION_FUZZER=ON -DRTS_BUILD_OPTION_FUZZER_COVERAGE=ON
// cmake --build build
//
// To run the fuzzer:
// ./fuzzer_executable corpus_dir