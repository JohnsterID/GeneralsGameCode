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

#include "PropPageMesh_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(PropPageMesh, PropPageMeshBase)
    // MFC ON_WM_CLOSE() → wxWidgets EVT_CLOSE
    // EVT_CLOSE(PropPageMesh::OnClose)  // Uncomment and implement OnClose() if needed
wxEND_EVENT_TABLE()

PropPageMesh::PropPageMesh(wxWindow *parent)
    : PropPageMeshBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageMesh::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageMesh::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

bool PropPageMesh::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageMesh::TransferDataFromWindow()
{
    // No data members to extract - mesh properties managed by parent form
    // Control values can be retrieved directly when needed
    return true;
}
