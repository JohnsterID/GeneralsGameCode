/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// TheSuperHackers: wxWidgets application implementation for W3DView

#include "w3dviewapp_wx.h"
#include "w3dviewframe_wx.h"
#include "w3dviewdoc_wx.h"
#include "w3dviewview_wx.h"
#include "w3dcompat_wx.h"

#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_all.h>
#include <wx/docview.h>
#include <wx/docmdi.h>
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Stub functions for custom controls (wxWidgets versions to be implemented)
#ifdef _WIN32
void RegisterColorPicker(HINSTANCE hinst) { /* TODO: Implement custom control */ }
void RegisterColorBar(HINSTANCE hinst) { /* TODO: Implement custom control */ }
#else
void RegisterColorPicker(void* hinst) { /* Not needed on non-Windows */ }
void RegisterColorBar(void* hinst) { /* Not needed on non-Windows */ }
#endif

// Global variables
ViewerAssetMgrClass *_TheAssetMgr = nullptr;

const char *gAppPrefix = "w3_";
const char *g_strFile = "data/Generals.str";
const char *g_csfFile = "data/%s/Generals.csf";

// Stub for WWMath if not available
#ifndef USE_FULL_W3D_ENGINE
class WWMath {
public:
    static void Init() { /* Stub */ }
};
#else
#include "wwmath.h"
#endif

W3DViewApp::W3DViewApp()
    : m_frame(nullptr)
    , m_docManager(nullptr)
    , m_initialized(false)
{
}

W3DViewApp::~W3DViewApp()
{
    delete m_docManager;
}

bool W3DViewApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    SetAppName("W3DView");
    SetVendorName("Westwood Studios");

    // Initialize XML resource system
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->AddHandler(new wxUnknownWidgetXmlHandler);

    // Check if another instance is already running
#ifdef _WIN32
    HWND hprev = FindWindow(nullptr, "W3DView");
    if (hprev != nullptr)
    {
        ShowWindow(hprev, SW_NORMAL);
        BringWindowToTop(hprev);
        SetForegroundWindow(hprev);
        return false;
    }
#endif

    // Register custom controls
#ifdef _WIN32
    RegisterColorPicker((HINSTANCE)wxGetInstance());
    RegisterColorBar((HINSTANCE)wxGetInstance());
#else
    RegisterColorPicker(nullptr);
    RegisterColorBar(nullptr);
#endif

    // Initialize libraries
    WWMath::Init();

    // Disable 3DFX logo
#ifdef _WIN32
    _putenv("FX_GLIDE_NO_SPLASH=1");
#else
    setenv("FX_GLIDE_NO_SPLASH", "1", 1);
#endif

    // Create document manager
    m_docManager = new wxDocManager;

    // Create document template
    new wxDocTemplate(
        m_docManager,
        "W3D Files",
        "*.w3d",
        "",
        "w3d",
        "W3D Document",
        "W3D View",
        CLASSINFO(W3DViewDoc),
        CLASSINFO(W3DViewView)
    );

    // Allocate asset manager
    _TheAssetMgr = new ViewerAssetMgrClass;

    // Create main frame
    m_frame = new W3DViewFrame(m_docManager);
    m_frame->Show(true);
    SetTopWindow(m_frame);

    m_initialized = true;

    // Open file if specified on command line
    if (argc > 1)
    {
        m_docManager->CreateDocument(argv[1], wxDOC_SILENT);
    }

    return true;
}

int W3DViewApp::OnExit()
{
    ShutdownGraphicsSystem();

    if (_TheAssetMgr)
    {
        delete _TheAssetMgr;
        _TheAssetMgr = nullptr;
    }

    return wxApp::OnExit();
}

void W3DViewApp::InitializeGraphicsSystem()
{
    // Graphics system initialization will be handled by the view
}

void W3DViewApp::ShutdownGraphicsSystem()
{
    // Graphics system shutdown will be handled by the view
}

bool W3DViewApp::DoVersionCheck()
{
    // Version check can be implemented if needed
    return true;
}

wxIMPLEMENT_APP(W3DViewApp);
