/*
**Command & Conquer Renegade(tm)
**Copyright 2025 Electronic Arts Inc.
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

#include "ColorSel_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(ColorSel, ColorSelBase)
    EVT_BUTTON(wxID_OK, ColorSel::OnOK)
    EVT_BUTTON(wxID_CANCEL, ColorSel::OnCancel)
    // Add more event handlers as needed
wxEND_EVENT_TABLE()

ColorSel::ColorSel(wxWindow *parent)
    : ColorSelBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void ColorSel::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void ColorSel::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}
