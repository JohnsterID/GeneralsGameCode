/**
 * @file atl_compat.h
 * @brief ATL compatibility layer for MinGW-w64 with ReactOS ATL
 *
 * Provides compatibility definitions for using ReactOS ATL headers
 * with MinGW-w64 GCC compiler. ReactOS ATL headers will use MinGW-w64's
 * PSEH implementation for exception handling.
 */

#pragma once

#ifndef ATL_COMPAT_H
#define ATL_COMPAT_H

#ifdef __MINGW32__

// Include PSEH compatibility first (uses MinGW-w64 PSEH)
#include "pseh_compat.h"

// Suppress additional warnings from ReactOS ATL headers
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wattributes"

// NOTE: ReactOS ATL compile definitions are set in cmake/reactos-atl.cmake:
//   - _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
//   - _ATL_NO_DEBUG_CRT
//   - ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW
//   - ATL_NO_DEFAULT_LIBS
// These are applied via target_compile_definitions() on the reactos_atl target.
// Any target linking to reactos_atl will automatically inherit these definitions.
//
// IMPORTANT: _ATL_NO_AUTOMATIC_NAMESPACE is NOT defined because the codebase
// uses ATL types (CComModule, CComObject, CString, etc.) without namespace
// qualification and relies on the automatic 'using namespace ATL;' from ATL headers.

// Restore compiler warnings after ATL includes
#define ATL_COMPAT_RESTORE_WARNINGS() \
    do { \
        _Pragma("GCC diagnostic pop") \
        PSEH_COMPAT_RESTORE_WARNINGS() \
    } while(0)

#else
// Non-MinGW platforms don't need these workarounds
#define ATL_COMPAT_RESTORE_WARNINGS()
#endif // __MINGW32__

#endif // ATL_COMPAT_H
