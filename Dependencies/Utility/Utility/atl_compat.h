/**
 * @file atl_compat.h
 * @brief ATL compatibility layer for MinGW-w64 with ReactOS ATL
 *
 * Provides compatibility definitions and workarounds for using ReactOS ATL
 * headers with MinGW-w64 GCC compiler.
 */

#pragma once

#ifndef ATL_COMPAT_H
#define ATL_COMPAT_H

#ifdef __MINGW32__

// Suppress PSEH-related warnings when using ReactOS ATL headers
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wattributes"

// ReactOS ATL compatibility definitions
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

// MinGW-w64 specific ATL compatibility
#ifndef __ATLBASE_H__
// Provide minimal ATL base definitions if needed
#endif

// Restore compiler warnings after ATL includes
#define ATL_COMPAT_RESTORE_WARNINGS() \
    _Pragma("GCC diagnostic pop")

#else
// Non-MinGW platforms don't need these workarounds
#define ATL_COMPAT_RESTORE_WARNINGS()
#endif // __MINGW32__

#endif // ATL_COMPAT_H
