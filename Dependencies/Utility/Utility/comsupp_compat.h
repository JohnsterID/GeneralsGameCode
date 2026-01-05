/**
 * @file comsupp_compat.h
 * @brief COM Support compatibility layer for MinGW-w64 with ReactOS
 *
 * Provides _com_util::ConvertStringToBSTR() and ConvertBSTRToString()
 * using ReactOS comsupp implementation. MinGW-w64 provides COM error
 * handling in comdef.h but lacks the string conversion utilities.
 */

#pragma once

#ifndef COMSUPP_COMPAT_H
#define COMSUPP_COMPAT_H

#ifdef __MINGW32__

// Include COM definitions first
#include <comdef.h>

// ReactOS provides _com_util::ConvertStringToBSTR and ConvertBSTRToString
// in sdk/lib/comsupp/comsupp.cpp which is built as reactos_comsupp library
// and linked to MinGW targets via cmake/mingw.cmake

// Declare the functions that ReactOS comsupp provides
namespace _com_util
{
    BSTR WINAPI ConvertStringToBSTR(const char *pSrc);
    char* WINAPI ConvertBSTRToString(BSTR pSrc);
}

#endif // __MINGW32__

#endif // COMSUPP_COMPAT_H
