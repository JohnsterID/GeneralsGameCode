/*
**Command & Conquer Renegade(tm)
**Copyright 2026 TheSuperHackers
**
**This program is free software: you can redistribute it and/or modify
**it under the terms of the GNU General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.
**
**This program is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**GNU General Public License for more details.
**
**You should have received a copy of the GNU General Public License
**along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Auto-generated from XRC by xrc2cpp.py
// Phase 3A.1: Complete manual implementation (NO infrastructure needed)

#include "Aboutbox_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(Aboutbox, AboutboxBase)
    EVT_BUTTON(XRCID("IDOK"), Aboutbox::OnOK)
wxEND_EVENT_TABLE()

Aboutbox::Aboutbox(wxWindow *parent)
    : AboutboxBase(parent)
{
    // Set the version text
    // MFC Reference: W3DView.cpp:317-361 (CAboutDlg::OnInitDialog)
    // MFC reads version from executable resource: GetFileVersionInfo/VerQueryValue
    // Format: IDS_VERSION string resource with major.minor (from dwFileVersionMS)
    // 
    // TODO(MFC-Match): Implement dynamic version reading from executable
    //   MFC Implementation:
    //     1. GetModuleFileName(nullptr, filename, MAX_PATH) - get exe path
    //     2. GetFileVersionInfoSize(filename, &dummy) - get version block size
    //     3. GetFileVersionInfo(filename, 0, size, pblock) - read version block
    //     4. VerQueryValue(pblock, "\\", &pVersionInfo, &len) - query VS_FIXEDFILEINFO
    //     5. Extract major.minor from dwFileVersionMS: (major >> 16), (major & 0xFFFF)
    //     6. Format using IDS_VERSION string resource: "W3DView Version %d.%d"
    //   wxWidgets Options:
    //     - MinGW: Can use Windows API (GetFileVersionInfo) if available
    //     - Cross-platform: Embed version in source/CMakeLists.txt
    //     - Hybrid: Try Windows API, fallback to embedded version
    //   Current: Hardcoded "W3DView Version 1.0" (default from MFC)
    //   Impact: MEDIUM - user convenience (shows actual build version)
    //   Note: MFC defaults to 1.0 if version resource missing, so current behavior valid
    if (m_idc_version)
    {
        m_idc_version->SetLabel("W3DView Version 1.0");
    }
    
    Centre();
}

void Aboutbox::OnOK(wxCommandEvent &event)
{
    // Simple OK button - just close the dialog
    EndModal(wxID_OK);
}
