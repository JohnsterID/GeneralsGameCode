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
#include "../Utils.h"
#include "../GraphicView_wx.h"

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
    // TODO: Implement OnDblclkResolutionListCtrl
    // Control ID: IDC_RESOLUTION_LIST_CTRL
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void Resolution::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    //
    //	Configure the list control
    //
    // TODO: Convert: m_ListCtrl.SetExtendedStyle (LVS_EX_FULLROWSELECT);
    // TODO: Convert: m_ListCtrl.InsertColumn (0, "Resolution");
    // TODO: Convert: m_ListCtrl.InsertColumn (1, "Bit Depth");
    //
    //	Size the columns
    //
    // TODO: Convert: CRect rect;
    // TODO: Convert: m_ListCtrl.GetClientRect (&rect);
    // TODO: Convert: m_ListCtrl.SetColumnWidth (0, (rect.Width () >> 1) - 4);
    // TODO: Convert: m_ListCtrl.SetColumnWidth (1, (rect.Width () >> 1) - 4);
    //
    //	Get information about the current render device
    //
    // TODO: Convert: const RenderDeviceDescClass &device_info = WW3D::Get_Render_Device_Desc ();
    // TODO: Convert: const DynamicVectorClass<ResolutionDescClass> &res_list = device_info.Enumerate_Resolutions ();
    //
    //	Get the current resolution
    //
    // TODO: Declare: int curr_width			= 0;
    // TODO: Declare: int curr_height		= 0;
    // TODO: Declare: int curr_bpp			= 0;
    // TODO: Declare: bool curr_windowed	= false;
    // TODO: Convert: WW3D::Get_Device_Resolution (curr_width, curr_height, curr_bpp, curr_windowed);
    if (m_idc_fullscreen_check) {
        m_idc_fullscreen_check->SetValue(curr_windowed == false != 0);  // TODO: Verify boolean logic
    }
    //
    //	Loop over all the resolutions available to us
    //
    // TODO: Declare: bool found = false;
    // TODO: Declare: int index = res_list.Count ();
    // TODO: Declare: int width	= res_list[index].Width;
    // TODO: Declare: int height	= res_list[index].Height;
    // TODO: Declare: int bpp		= res_list[index].BitDepth;
    //
    //	Format description strings for this resolution
    //
    // TODO: Convert: CString resolution_string;
    // TODO: Convert: CString bit_depth_string;
    // TODO: Convert: resolution_string.Format ("%d x %d", width, height);
    // TODO: Convert: bit_depth_string.Format ("%d bpp (%d colors)", bpp, 1 << bpp);
    //
    //	Add this resolution to the list ctrl
    //
    // TODO: Declare: int list_index = m_ListCtrl.InsertItem (0, resolution_string, 0);
    // TODO: Convert: m_ListCtrl.SetItemText (list_index, 1, bit_depth_string);
    // TODO: Convert: m_ListCtrl.SetItemData (list_index, index);
    //
    //	Is this the current resolution?  If so,
    // select this entry as the default...
    //
    // TODO: Convert: if (	found == false &&
    // TODO: Convert: curr_width == width &&
    // TODO: Convert: curr_height == height &&
    // TODO: Convert: curr_bpp == bpp)
    // TODO: Convert: m_ListCtrl.SetItemState (list_index, LVIS_SELECTED, LVIS_SELECTED);
    // TODO: Convert: found = true;
    //
    //	Select the first entry by default (if necessary)
    //
    // TODO: Convert: m_ListCtrl.SetItemState (0, LVIS_SELECTED, LVIS_SELECTED);
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool Resolution::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool Resolution::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Convert: //
    // TODO: Convert: //	Get the current selection
    // TODO: Convert: //
    // TODO: Convert: int list_index = m_ListCtrl.GetNextItem (-1, LVNI_ALL | LVNI_SELECTED);
    // TODO: Convert: if (list_index >= 0) {
    // TODO: Convert: //
    // TODO: Convert: //	Index into the resolution list for this device...
    // TODO: Convert: //
    // TODO: Convert: int index = m_ListCtrl.GetItemData (list_index);
    // TODO: Convert: if (index >= 0) {
    // TODO: Convert: //
    // TODO: Convert: //	Lookup the selected resolution information
    // TODO: Convert: //
    // TODO: Convert: const RenderDeviceDescClass &device_info = WW3D::Get_Render_Device_Desc ();
    // TODO: Convert: const DynamicVectorClass<ResolutionDescClass> &res_list = device_info.Enumerate_Resolutions ();
    // TODO: Convert: g_iWidth				= res_list[index].Width;
    // TODO: Convert: g_iHeight			= res_list[index].Height;
    // TODO: Convert: g_iBitsPerPixel	= res_list[index].BitDepth;
    // TODO: Convert: //
    // TODO: Convert: // Cache this information in the registry
    // TODO: Convert: //
    // TODO: Convert: theApp.WriteProfileInt ("Config", "DeviceWidth", g_iWidth);
    // TODO: Convert: theApp.WriteProfileInt ("Config", "DeviceHeight", g_iHeight);
    // TODO: Convert: theApp.WriteProfileInt ("Config", "DeviceBitsPerPix", g_iBitsPerPixel);
    // TODO: Convert: //
    // TODO: Convert: //	Reset the display
    // TODO: Convert: //
    // TODO: Convert: bool fullscreen = (SendDlgItemMessage (IDC_FULLSCREEN_CHECK, BM_GETCHECK) == 1);
    // TODO: Convert: ::Get_Graphic_View ()->Set_Fullscreen (fullscreen);
    // TODO: Convert: }
    // TODO: Convert: }
    // TODO: Convert: return ;

    return true;
}
