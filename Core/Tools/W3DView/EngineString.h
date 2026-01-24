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
// ENCODING STRATEGY:
// - Engine data is ANSI (char* in system codepage, typically Windows-1252)
// - wxWidgets is UNICODE (wxString stores UTF-16 internally)
// - Conversion: Use wxConvLocal for ANSI ↔ wxString at UI boundaries
////////////////////////////////////////////////////////////////////////////////

#ifndef W3DVIEW_ENGINE_STRING_H
#define W3DVIEW_ENGINE_STRING_H

#ifdef USE_WXWIDGETS
    //==========================================================================
    // wxWidgets Build (Unicode mode)
    //==========================================================================
    #include <wx/string.h>
    #include <wx/strconv.h>
    #include <string>
    
    typedef wxString EngineString;
    
    // CString-compatible wrapper functions
    inline size_t EngineStringGetLength(const EngineString& s) { return s.Length(); }
    
    // Conversion helpers for wxWidgets
    // NOTE: Engine data is ANSI (Windows codepage), not UTF-8!
    // Use wxConvLocal (system codepage) or wxCSConv("windows-1252")
    
    inline EngineString EngineStringFromAnsi(const char* ansiStr) {
        if (!ansiStr) return wxEmptyString;
        return wxString(ansiStr, wxConvLocal);
    }
    
    inline EngineString EngineStringFromStdString(const std::string& s) {
        return wxString(s.c_str(), wxConvLocal);
    }
    
    inline std::string EngineStringToStdString(const EngineString& s) {
        wxCharBuffer buf = s.mb_str(wxConvLocal);
        return std::string(buf.data());
    }
    
    // For temporary const char* (valid until next call or EngineString destruction)
    // WARNING: Returned pointer is temporary! Use immediately or copy.
    inline const char* EngineStringToCStr(const EngineString& s) {
        static thread_local wxCharBuffer buffer;
        buffer = s.mb_str(wxConvLocal);
        return buffer.data();
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
