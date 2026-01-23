////////////////////////////////////////////////////////////////////////////////
//                               W3D VIEWER
//
// Conditional string type for dual MFC/wxWidgets builds
//
// This file provides a unified string type that works with both:
// - MFC builds (VC6/MSVC): EngineString = CString
// - wxWidgets builds (MinGW/GCC): EngineString = wxString
//
// Engine classes (ViewerAssetMgr, AssetInfo, ViewerScene) use EngineString
// to avoid coupling to a specific UI framework.
//
// NOTE: This approach works now that wwstring.h has been fixed to handle
// UNICODE builds correctly (conditional compilation of WCHAR overloads).
////////////////////////////////////////////////////////////////////////////////

#ifndef W3DVIEW_ENGINE_STRING_H
#define W3DVIEW_ENGINE_STRING_H

#ifdef USE_WXWIDGETS
    //==========================================================================
    // wxWidgets Build
    //==========================================================================
    #include <wx/string.h>
    #include <string>
    
    typedef wxString EngineString;
    
    // CString-compatible wrapper functions
    inline size_t EngineStringGetLength(const EngineString& s) { return s.Length(); }
    
    // Conversion helpers for wxWidgets
    inline EngineString EngineStringFromStdString(const std::string& s) {
        return wxString::FromUTF8(s.c_str());
    }
    
    inline std::string EngineStringToStdString(const EngineString& s) {
        return std::string(s.utf8_str());
    }
    
    inline const char* EngineStringToCStr(const EngineString& s) {
        return s.utf8_str();
    }
    
#else
    //==========================================================================
    // MFC Build
    //==========================================================================
    #include <afx.h>
    #include <string>
    
    typedef CString EngineString;
    
    // Conversion helpers for MFC
    inline EngineString EngineStringFromStdString(const std::string& s) {
        return CString(s.c_str());
    }
    
    inline std::string EngineStringToStdString(const EngineString& s) {
        return std::string((LPCTSTR)s);
    }
    
    inline LPCTSTR EngineStringToCStr(const EngineString& s) {
        return (LPCTSTR)s;
    }
    
#endif

#endif // W3DVIEW_ENGINE_STRING_H
