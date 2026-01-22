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

// TheSuperHackers: wxWidgets view implementation for W3DView

#include "w3dviewview_wx.h"
#include "w3dviewdoc_wx.h"
#include "w3dviewapp_wx.h"
#include "w3dviewframe_wx.h"
#include "w3dviewtree_wx.h"

#include <wx/sizer.h>

wxIMPLEMENT_DYNAMIC_CLASS(W3DViewView, wxView);

W3DViewView::W3DViewView()
    : m_frame(nullptr)
    , m_renderPanel(nullptr)
{
}

W3DViewView::~W3DViewView()
{
    // TODO: Shutdown W3D rendering engine if initialized
}

bool W3DViewView::OnCreate(wxDocument *doc, long WXUNUSED(flags))
{
    W3DViewApp& app = wxGetApp();
    W3DViewFrame *mainFrame = app.GetMainFrame();
    
    if (!mainFrame)
        return false;

    // Get the splitter window
    wxSplitterWindow *splitter = mainFrame->GetSplitter();
    
    if (!splitter)
        return false;

    // Create native panel for W3D rendering (replaces wxGLCanvas)
    // W3D engine will use the native window handle (HWND on Windows)
    m_renderPanel = new wxPanel(splitter, wxID_ANY);
    
    // TODO: Initialize W3D rendering engine with native window handle
    // Example (Windows):
    //   HWND hwnd = (HWND)m_renderPanel->GetHandle();
    //   wxSize size = m_renderPanel->GetClientSize();
    //   WW3D::Set_Render_Device(deviceIndex, size.GetWidth(), size.GetHeight(), bitsPerPixel, windowed);

    // Create the tree view
    W3DViewTreeCtrl *treeView = new W3DViewTreeCtrl(splitter, wxID_ANY);

    // Split the window
    splitter->SplitVertically(treeView, m_renderPanel, 250);

    m_frame = mainFrame;

    return true;
}

void W3DViewView::OnDraw(wxDC *WXUNUSED(dc))
{
    if (!m_renderPanel)
        return;

    // TODO: Render the 3D scene here using W3D rendering engine
    // The W3D engine handles its own rendering loop and buffer swapping
    // Example: ViewerScene::Render() or similar
}

void W3DViewView::OnUpdate(wxView *WXUNUSED(sender), wxObject *WXUNUSED(hint))
{
    if (m_renderPanel)
        m_renderPanel->Refresh();
}

bool W3DViewView::OnClose(bool deleteWindow)
{
    if (!GetDocument()->Close())
        return false;

    Activate(false);

    if (deleteWindow)
    {
        GetFrame()->Destroy();
        SetFrame(nullptr);
    }

    return true;
}
