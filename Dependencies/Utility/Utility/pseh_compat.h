/**
 * @file pseh_compat.h
 * @brief PSEH (Portable Structured Exception Handling) compatibility for MinGW-w64
 *
 * ReactOS ATL uses PSEH (Portable Structured Exception Handling) which can
 * cause warnings and compatibility issues with MinGW-w64 GCC. This header
 * provides workarounds and compatibility definitions.
 */

#pragma once

#ifndef PSEH_COMPAT_H
#define PSEH_COMPAT_H

#ifdef __MINGW32__

// Suppress PSEH-related warnings from ReactOS headers
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

// PSEH compatibility definitions for MinGW-w64
#ifndef _SEH_ENABLE_TRACE
#define _SEH_ENABLE_TRACE 0
#endif

#ifndef _SEH_NO_NATIVE_NLG
#define _SEH_NO_NATIVE_NLG
#endif

// MinGW-w64 provides native SEH support through GCC extensions
// but PSEH may need additional compatibility shims
#ifndef __try
#define __try if (1)
#endif

#ifndef __except
#define __except(x) if (0)
#endif

#ifndef __finally
#define __finally
#endif

// PSEH2/PSEH3 compatibility macros
#ifndef _SEH2_TRY
#define _SEH2_TRY __try
#endif

#ifndef _SEH2_EXCEPT
#define _SEH2_EXCEPT __except
#endif

#ifndef _SEH2_FINALLY
#define _SEH2_FINALLY __finally
#endif

#ifndef _SEH2_END
#define _SEH2_END
#endif

// Exception handling compatibility
#ifndef EXCEPTION_EXECUTE_HANDLER
#define EXCEPTION_EXECUTE_HANDLER 1
#endif

#ifndef EXCEPTION_CONTINUE_SEARCH
#define EXCEPTION_CONTINUE_SEARCH 0
#endif

#ifndef EXCEPTION_CONTINUE_EXECUTION
#define EXCEPTION_CONTINUE_EXECUTION -1
#endif

// Restore compiler warnings after PSEH-related includes
#define PSEH_COMPAT_RESTORE_WARNINGS() \
    _Pragma("GCC diagnostic pop")

#else
// Non-MinGW platforms use native SEH or don't need these workarounds
#define PSEH_COMPAT_RESTORE_WARNINGS()
#endif // __MINGW32__

#endif // PSEH_COMPAT_H
