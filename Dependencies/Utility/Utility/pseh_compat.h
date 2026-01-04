/**
 * @file pseh_compat.h
 * @brief PSEH compatibility for MinGW-w64 with ReactOS ATL
 *
 * ReactOS ATL headers include <pseh/pseh2.h>. This header ensures
 * that MinGW-w64's PSEH implementation is used instead of ReactOS PSEH.
 * MinGW-w64 provides its own PSEH headers at /usr/i686-w64-mingw32/include/pseh/
 */

#pragma once

#ifndef PSEH_COMPAT_H
#define PSEH_COMPAT_H

#ifdef __MINGW32__

// Suppress PSEH-related warnings from MinGW-w64 PSEH headers
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

// Include MinGW-w64's PSEH2 implementation
// This provides proper structured exception handling for GCC
#include <pseh/pseh2.h>

// Restore compiler warnings after PSEH includes
#define PSEH_COMPAT_RESTORE_WARNINGS() \
    _Pragma("GCC diagnostic pop")

#else
// Non-MinGW platforms use native SEH or don't need PSEH
#define PSEH_COMPAT_RESTORE_WARNINGS()
#endif // __MINGW32__

#endif // PSEH_COMPAT_H
