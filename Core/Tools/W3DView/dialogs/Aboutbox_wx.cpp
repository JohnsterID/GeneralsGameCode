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
    // NOTE: MFC version reads from executable version resource (VS_VERSION_INFO).
    // wxWidgets equivalent would use platform-specific methods:
    //   Windows: GetFileVersionInfo/VerQueryValue
    //   Cross-platform: Parse custom resource or embed in source
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
