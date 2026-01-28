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

// StringClass bug fixed in rddesc.h (Session 40 Part 4) - can now include!
#include "ww3d.h"
#include "rddesc.h"

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
    
    // Configure the list control
    m_idc_resolution_list_ctrl->SetSingleStyle(wxLC_REPORT);
    m_idc_resolution_list_ctrl->InsertColumn(0, "Resolution");
    m_idc_resolution_list_ctrl->InsertColumn(1, "Bit Depth");
    
    // Size the columns
    wxRect rect = m_idc_resolution_list_ctrl->GetClientRect();
    m_idc_resolution_list_ctrl->SetColumnWidth(0, (rect.GetWidth() >> 1) - 4);
    m_idc_resolution_list_ctrl->SetColumnWidth(1, (rect.GetWidth() >> 1) - 4);
    
    // Get current device and resolution information
    int curr_width, curr_height, curr_bpp;
    bool curr_windowed_state;
    WW3D::Get_Device_Resolution(curr_width, curr_height, curr_bpp, curr_windowed_state);
    
    // Get device description to enumerate available resolutions
    int device_index = WW3D::Get_Render_Device();
    const RenderDeviceDescClass &device_info = WW3D::Get_Render_Device_Desc(device_index);
    
    // Get resolution array from device
    const DynamicVectorClass<ResolutionDescClass> &res_array = device_info.Enumerate_Resolutions();
    
    // Populate list control with all available resolutions
    long selected_index = -1;
    for (int i = 0; i < res_array.Count(); i++) {
        const ResolutionDescClass &res = res_array[i];
        
        // Format resolution string: "WIDTHxHEIGHT"
        wxString res_string = wxString::Format("%dx%d", res.Width, res.Height);
        wxString bpp_string = wxString::Format("%d", res.BitDepth);
        
        // Add to list
        long list_index = m_idc_resolution_list_ctrl->InsertItem(i, res_string);
        m_idc_resolution_list_ctrl->SetItem(list_index, 1, bpp_string);
        
        // Store resolution index in item data for retrieval on OK
        m_idc_resolution_list_ctrl->SetItemData(list_index, i);
        
        // Check if this is the current resolution
        if (res.Width == curr_width && res.Height == curr_height && res.BitDepth == curr_bpp) {
            selected_index = list_index;
        }
    }
    
    // Select the current resolution in the list
    if (selected_index >= 0) {
        m_idc_resolution_list_ctrl->SetItemState(selected_index, 
                                                 wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED,
                                                 wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
        m_idc_resolution_list_ctrl->EnsureVisible(selected_index);
    }
    
    // Set fullscreen checkbox to current windowed state
    curr_windowed = curr_windowed_state;
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
    
    // Get selected list item
    long selected_item = m_idc_resolution_list_ctrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    
    if (selected_item >= 0) {
        // Get resolution index from item data
        long res_index = m_idc_resolution_list_ctrl->GetItemData(selected_item);
        
        // Get device description to access resolution array
        int device_index = WW3D::Get_Render_Device();
        const RenderDeviceDescClass &device_info = WW3D::Get_Render_Device_Desc(device_index);
        const DynamicVectorClass<ResolutionDescClass> &res_array = device_info.Enumerate_Resolutions();
        
        if (res_index >= 0 && res_index < res_array.Count()) {
            const ResolutionDescClass &selected_res = res_array[res_index];
            
            // Cache to wxConfig (MFC: WriteProfileInt("Config", "Device*"))
            wxConfigBase *config = wxConfigBase::Get();
            config->Write("/Config/DeviceWidth", selected_res.Width);
            config->Write("/Config/DeviceHeight", selected_res.Height);
            config->Write("/Config/DeviceBitsPerPix", selected_res.BitDepth);
            config->Flush();
            
            // Set globals (MFC: Resolution.cpp:138-140)
            // These are defined in Globals.h/Globals.cpp
            extern int g_iWidth, g_iHeight, g_iBitsPerPixel;
            g_iWidth = selected_res.Width;
            g_iHeight = selected_res.Height;
            g_iBitsPerPixel = selected_res.BitDepth;
        }
    }
    
    // Save fullscreen checkbox state
    wxConfigBase *config = wxConfigBase::Get();
    bool fullscreen = m_idc_fullscreen_check->GetValue();
    config->Write("/Config/Windowed", !fullscreen);
    config->Flush();
    curr_windowed = !fullscreen;
    
    // Apply fullscreen setting (MFC: ResolutionDialog.cpp:214)
    // Get_Graphic_View() is declared in Utils.h, implemented in Utils.cpp (line 873)
    // Set_Fullscreen() is implemented in GraphicView_wx.cpp (line 248)
    CGraphicView *graphic_view = Get_Graphic_View();
    if (graphic_view)
    {
        graphic_view->Set_Fullscreen(fullscreen);
    }
    
    return true;
}
