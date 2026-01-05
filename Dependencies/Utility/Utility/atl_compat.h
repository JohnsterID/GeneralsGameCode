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

// ReactOS ATL compatibility definitions
// TODO: Confirm if we shouldn't use _ATL_NO_AUTOMATIC_NAMESPACE and if this should be in mingw.cmake
#ifndef _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_NO_AUTOMATIC_NAMESPACE
#endif

#ifndef _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#endif

#ifndef _ATL_NO_DEBUG_CRT
#define _ATL_NO_DEBUG_CRT
#endif

#ifndef ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW
#endif

#ifndef ATL_NO_DEFAULT_LIBS
#define ATL_NO_DEFAULT_LIBS
#endif

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
