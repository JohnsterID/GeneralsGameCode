// TheSuperHackers @build JohnsterID 05/01/2026 Add COM support utilities for MinGW-w64
/**
 * @file comsupp_compat.h
 * @brief COM Support compatibility layer for MinGW-w64
 *
 * Provides _com_util::ConvertStringToBSTR() and ConvertBSTRToString()
 * as header-only implementations. MinGW-w64 provides COM error
 * handling in comdef.h but lacks the string conversion utilities.
 */

#pragma once

#ifdef __MINGW32__

#include <windows.h>
#include <ole2.h>
#include <oleauto.h>
#include <comdef.h>

namespace _com_util
{

inline BSTR WINAPI ConvertStringToBSTR(const char *pSrc)
{
    DWORD cwch;
    BSTR wsOut = NULL;

    if (!pSrc)
        return NULL;

    // Compute the needed size with the NULL terminator
    cwch = MultiByteToWideChar(CP_ACP, 0, pSrc, -1, NULL, 0);
    if (cwch == 0)
        return NULL;

    // Allocate the BSTR (without the NULL terminator)
    wsOut = SysAllocStringLen(NULL, cwch - 1);
    if (!wsOut)
    {
        _com_issue_error(HRESULT_FROM_WIN32(ERROR_OUTOFMEMORY));
        return NULL;
    }

    // Convert the string
    if (MultiByteToWideChar(CP_ACP, 0, pSrc, -1, wsOut, cwch) == 0)
    {
        // We failed, clean everything up
        cwch = GetLastError();

        SysFreeString(wsOut);
        wsOut = NULL;

        _com_issue_error(!IS_ERROR(cwch) ? HRESULT_FROM_WIN32(cwch) : cwch);
    }

    return wsOut;
}

inline char* WINAPI ConvertBSTRToString(BSTR pSrc)
{
    DWORD cb, cwch;
    char *szOut = NULL;

    if (!pSrc)
        return NULL;

    // Retrieve the size of the BSTR with the NULL terminator
    cwch = SysStringLen(pSrc) + 1;

    // Compute the needed size with the NULL terminator
    cb = WideCharToMultiByte(CP_ACP, 0, pSrc, cwch, NULL, 0, NULL, NULL);
    if (cb == 0)
    {
        cwch = GetLastError();
        _com_issue_error(!IS_ERROR(cwch) ? HRESULT_FROM_WIN32(cwch) : cwch);
        return NULL;
    }

    // Allocate the string
    szOut = (char*)::operator new(cb * sizeof(char));
    if (!szOut)
    {
        _com_issue_error(HRESULT_FROM_WIN32(ERROR_OUTOFMEMORY));
        return NULL;
    }

    // Convert the string and NULL-terminate
    szOut[cb - 1] = '\0';
    if (WideCharToMultiByte(CP_ACP, 0, pSrc, cwch, szOut, cb, NULL, NULL) == 0)
    {
        // We failed, clean everything up
        cwch = GetLastError();

        ::operator delete(szOut);
        szOut = NULL;

        _com_issue_error(!IS_ERROR(cwch) ? HRESULT_FROM_WIN32(cwch) : cwch);
    }

    return szOut;
}

}

// Provide vtMissing global variable
// Use inline variable (C++17) to avoid multiple definition errors
inline _variant_t vtMissing(DISP_E_PARAMNOTFOUND, VT_ERROR);

#endif // __MINGW32__
