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

#include "Resolution_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(Resolution, ResolutionBase)
EVT_LIST_ITEM_ACTIVATED(XRCID("IDC_RESOLUTION_LIST_CTRL"), Resolution::OnDblclkResolutionListCtrl)  // List item double-click
wxEND_EVENT_TABLE()

Resolution::Resolution(wxWindow *parent)
    : ResolutionBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void Resolution::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void Resolution::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void Resolution::OnDblclkResolutionListCtrl(wxListEvent &event)
{
    // TODO: Implement OnDblclkResolutionListCtrl
    // Control ID: IDC_RESOLUTION_LIST_CTRL
}
