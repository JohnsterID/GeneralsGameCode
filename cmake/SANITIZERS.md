# Using Sanitizers with GeneralsGameCode

This document provides guidance on using sanitizers with the GeneralsGameCode project, specifically AddressSanitizer (ASan) and LibFuzzer.

## AddressSanitizer (ASan)

AddressSanitizer is a powerful tool for detecting memory errors such as use-after-free, heap buffer overflow, stack buffer overflow, and more.

### Enabling ASan

To enable AddressSanitizer, set the `RTS_BUILD_OPTION_ASAN` CMake option to `ON`:

```bash
cmake -B build -DRTS_BUILD_OPTION_ASAN=ON
```

### Known Issues with ASan on Win32

When using ASan with the Win32 version of the game, you may encounter several issues:

1. **Shadow Memory Collision**: ASan will fail to allocate memory in its preferred region because `binkw32.dll` claims a portion of that range first. You'll see an error like:

   ```
   ==19316==Shadow memory range interleaves with an existing memory mapping. ASan cannot proceed correctly. ABORTING.
   ```

   **Solution**: Rebase the address of `binkw32.dll` using the `editbin` tool:

   ```bash
   "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808\bin\Hostx64\x86\editbin.exe" /REBASE:BASE=0x40000000 BINKW32.DLL
   ```

   Note: For Generals (not Zero Hour), you cannot rebase the provided BINKW32.dll as it has been signed. Instead, copy the rebased Zero Hour version.

2. **Fault Tolerant Heap Collision**: Windows may enable the Fault Tolerant Heap (FTH) when compatibility mode is enabled for the executable, which collides with ASan.

   **Solution**: Remove compatibility mode through:
   - Registry: Delete the relevant key in `Computer\HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers`
   - Or disable compatibility in the properties of the executable

3. **Memory Limitations**: After just a few level loads, ASan may run out of memory and crash in 32-bit mode.

4. **Game Memory System**: The game memory system is automatically disabled when ASan is enabled. This is necessary because the game memory system overrides new/delete operators which interferes with ASan's memory tracking.

## LibFuzzer

LibFuzzer is a coverage-guided fuzzing library that can be used to find bugs and crashes caused by user-provided input.

### Enabling LibFuzzer

To enable LibFuzzer, set the `RTS_BUILD_OPTION_FUZZER` CMake option to `ON`:

```bash
cmake -B build -DRTS_BUILD_OPTION_FUZZER=ON
```

For best results, it's recommended to use LibFuzzer together with AddressSanitizer:

```bash
cmake -B build -DRTS_BUILD_OPTION_FUZZER=ON -DRTS_BUILD_OPTION_ASAN=ON
```

### Using LibFuzzer

To use LibFuzzer effectively:

1. Create a fuzz target function in your code:

```cpp
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // Use the data to test your code
    // For example, if you're testing a parser:
    MyParser parser;
    parser.parse(Data, Size);
    return 0;  // Non-zero return values are reserved for future use
}
```

2. Build your project with the fuzzer option enabled.

3. Run the resulting executable with a corpus directory:

```bash
./my_fuzzer_executable corpus_dir
```

### Additional Resources

- [LibFuzzer Documentation](https://llvm.org/docs/LibFuzzer.html)
- [OneFuzz Documentation](https://www.microsoft.com/research/project/project-onefuzz/)
- [OneFuzz GitHub Project](https://github.com/microsoft/onefuzz)

## Combining Sanitizers

When combining sanitizers (e.g., ASan and LibFuzzer), be aware that:

1. Each sanitizer adds runtime overhead
2. Some sanitizers may conflict with each other
3. The order of linking can matter

For the GeneralsGameCode project, the recommended combination is ASan + LibFuzzer:

```bash
cmake -B build -DRTS_BUILD_OPTION_ASAN=ON -DRTS_BUILD_OPTION_FUZZER=ON
```

This will:
- Enable both sanitizers
- Automatically disable the game memory system (due to ASan)
- Set up the necessary compiler and linker flags