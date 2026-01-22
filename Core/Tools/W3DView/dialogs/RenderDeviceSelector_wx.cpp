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

#include "RenderDeviceSelector_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(RenderDeviceSelector, RenderDeviceSelectorBase)
EVT_COMBOBOX(XRCID("IDC_RENDER_DEVICE_COMBO"), RenderDeviceSelector::OnSelchangeRenderDeviceCombo)  // Combobox selection change
wxEND_EVENT_TABLE()

RenderDeviceSelector::RenderDeviceSelector(wxWindow *parent)
    : RenderDeviceSelectorBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void RenderDeviceSelector::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void RenderDeviceSelector::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void RenderDeviceSelector::OnSelchangeRenderDeviceCombo(wxCommandEvent &event)
{
    // TODO: Implement OnSelchangeRenderDeviceCombo
    // Control ID: IDC_RENDER_DEVICE_COMBO
}
