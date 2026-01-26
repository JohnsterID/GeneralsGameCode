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
#include <wx/config.h>
#include "../Utils.h"
#include "../GraphicView_wx.h"
#include "../Globals.h"

// BLOCKER TODO: rddesc.h inclusion causes StringClass/const char* conflicts with wxWidgets
// BLOCKER TODO: RenderDeviceDescClass inline methods return StringClass as const char*
// BLOCKER TODO: Need RenderDeviceDescClass, ResolutionDescClass, DynamicVectorClass for resolution enumeration
// BLOCKER TODO: Required for WW3D::Get_Render_Device_Desc() and device_info.Enumerate_Resolutions()
// BLOCKER TODO: This is an infrastructure issue affecting resolution enumeration dialogs
// #include "ww3d.h"
// #include "rddesc.h"

wxBEGIN_EVENT_TABLE(Resolution, ResolutionBase)
EVT_LIST_ITEM_ACTIVATED(XRCID("IDC_RESOLUTION_LIST_CTRL"), Resolution::OnDblclkResolutionListCtrl)  // List item double-click
    EVT_INIT_DIALOG(Resolution::OnInitDialog)
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
    // MFC: ResolutionDialog.cpp:228-236 (OnDblclkResolutionListCtrl)
    // Double-click on list item acts like OK button
    long list_index = m_idc_resolution_list_ctrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (list_index >= 0) {
        // Trigger OK behavior (works with current stub implementation)
        if (Validate() && TransferDataFromWindow()) {
            EndModal(wxID_OK);
        }
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void Resolution::OnInitDialog(wxInitDialogEvent& event)
{
    // MFC: ResolutionDialog.cpp:84-170 (OnInitDialog)
    // TODO(MFC-Infrastructure): Full implementation requires rddesc.h (blocker: StringClass conflicts)
    
    // Configure the list control
    m_idc_resolution_list_ctrl->SetSingleStyle(wxLC_REPORT);
    m_idc_resolution_list_ctrl->InsertColumn(0, "Resolution");
    m_idc_resolution_list_ctrl->InsertColumn(1, "Bit Depth");
    
    // Size the columns
    wxRect rect = m_idc_resolution_list_ctrl->GetClientRect();
    m_idc_resolution_list_ctrl->SetColumnWidth(0, (rect.GetWidth() >> 1) - 4);
    m_idc_resolution_list_ctrl->SetColumnWidth(1, (rect.GetWidth() >> 1) - 4);
    
    // TODO(MFC-Infrastructure): Re-enable after fixing rddesc.h include issue (see header)
    // MFC implementation:
    //   1. Get device info: WW3D::Get_Render_Device_Desc()
    //   2. Enumerate resolutions: device_info.Enumerate_Resolutions()
    //   3. Get current resolution: WW3D::Get_Device_Resolution(width, height, bpp, windowed)
    //   4. Populate list with all available resolutions
    //   5. Select current resolution in list
    //
    // Blocked by: rddesc.h contains inline methods returning StringClass as const char*
    // Required types: RenderDeviceDescClass, ResolutionDescClass, DynamicVectorClass<ResolutionDescClass>
    
    // Stub: Add a placeholder message
    long list_index = m_idc_resolution_list_ctrl->InsertItem(0, "Resolution enumeration blocked by rddesc.h");
    m_idc_resolution_list_ctrl->SetItem(list_index, 1, "See Resolution_wx.cpp");
    
    // Set fullscreen checkbox to current windowed state (from config)
    wxConfigBase *config = wxConfigBase::Get();
    curr_windowed = config->ReadBool("/Config/Windowed", true);
    if (m_idc_fullscreen_check) {
        m_idc_fullscreen_check->SetValue(!curr_windowed);
    }
    
    event.Skip();
}

bool Resolution::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool Resolution::TransferDataFromWindow()
{
    // MFC: ResolutionDialog.cpp:180-221 (OnOK)
    // TODO(MFC-Infrastructure): Full implementation requires rddesc.h (blocker: StringClass conflicts)
    
    // TODO(MFC-Infrastructure): Re-enable after fixing rddesc.h include issue
    // MFC implementation:
    //   1. Get selected list item index
    //   2. Get resolution index from item data
    //   3. Lookup resolution from WW3D::Get_Render_Device_Desc().Enumerate_Resolutions()[index]
    //   4. Set globals: g_iWidth, g_iHeight, g_iBitsPerPixel
    //   5. Cache to registry: WriteProfileInt("Config", "DeviceWidth/Height/BitsPerPix")
    //   6. Apply fullscreen setting: Get_Graphic_View()->Set_Fullscreen()
    //
    // Current implementation: Save fullscreen setting only (resolution enum blocked)
    
    // Save fullscreen checkbox state
    wxConfigBase *config = wxConfigBase::Get();
    bool fullscreen = m_idc_fullscreen_check->GetValue();
    config->Write("/Config/Windowed", !fullscreen);
    curr_windowed = !fullscreen;
    
    // TODO: Apply fullscreen setting when Get_Graphic_View()->Set_Fullscreen() is available
    
    return true;
}
