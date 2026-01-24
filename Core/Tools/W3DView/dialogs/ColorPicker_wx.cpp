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

#include "ColorPicker_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(ColorPicker, ColorPickerBase)
EVT_BUTTON(XRCID("IDC_RESET"), ColorPicker::OnReset)  // Button/Checkbox click
wxEND_EVENT_TABLE()

ColorPicker::ColorPicker(wxWindow *parent)
    : ColorPickerBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void ColorPicker::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void ColorPicker::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void ColorPicker::OnReset(wxCommandEvent &event)
{
    // Reset color to default
    // Color picker panels handle their own reset logic
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

bool ColorPicker::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ColorPicker::TransferDataFromWindow()
{
    // Color picker uses custom panels that handle their own data
    // No extraction needed - data is managed by the color picker controls
    return true;
}
