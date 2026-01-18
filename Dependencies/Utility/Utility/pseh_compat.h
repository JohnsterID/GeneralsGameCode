// TheSuperHackers @build JohnsterID 05/01/2026 Add PSEH compatibility for MinGW-w64
/**
 * @file pseh_compat.h
 * @brief PSEH compatibility for MinGW-w64 with ReactOS ATL
 *
 * ReactOS ATL headers include <pseh/pseh2.h>. This header ensures
 * that ReactOS PSEH is used in C++-compatible dummy mode (_USE_DUMMY_PSEH).
 * The cmake configuration (reactos-atl.cmake) adds ReactOS PSEH headers
 * to the include path before system headers, and defines _USE_DUMMY_PSEH.
 */

#pragma once

#ifdef __MINGW32__

// Suppress PSEH-related warnings from ReactOS PSEH headers
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-label"

// ReactOS PSEH headers will be included by ATL headers
// No need to include them explicitly here

// Restore compiler warnings after PSEH includes
#define PSEH_COMPAT_RESTORE_WARNINGS() \
    _Pragma("GCC diagnostic pop")

#else
// Non-MinGW platforms use native SEH or don't need PSEH
#define PSEH_COMPAT_RESTORE_WARNINGS()
#endif // __MINGW32__
