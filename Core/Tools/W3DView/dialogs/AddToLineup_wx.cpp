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

#include "AddToLineup_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(AddToLineup, AddToLineupBase)

wxEND_EVENT_TABLE()

AddToLineup::AddToLineup(wxWindow *parent)
    : AddToLineupBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void AddToLineup::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void AddToLineup::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

bool AddToLineup::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool AddToLineup::TransferDataFromWindow()
{
    // No data members to extract - calling code accesses controls directly
    // List box selection can be retrieved via GetSelection() when needed
    return true;
}
