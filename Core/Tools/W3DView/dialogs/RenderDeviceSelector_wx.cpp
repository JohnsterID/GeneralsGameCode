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

// RenderDeviceSelector - Exact MFC to wxWidgets conversion
// MFC Reference: DeviceSelectionDialog.cpp

#include "RenderDeviceSelector_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/config.h>
#include "ww3d.h"
// #include "rddesc.h"  // TODO: RenderDeviceDescClass Get_*() methods have StringClass return type bug

wxBEGIN_EVENT_TABLE(RenderDeviceSelector, RenderDeviceSelectorBase)
    EVT_INIT_DIALOG(RenderDeviceSelector::OnInitDialog)
    EVT_COMBOBOX(XRCID("IDC_RENDER_DEVICE_COMBO"), RenderDeviceSelector::OnSelchangeRenderDeviceCombo)
wxEND_EVENT_TABLE()

// MFC: CDeviceSelectionDialog::CDeviceSelectionDialog(BOOL bLookupCachedInfo, CWnd* pParent)
RenderDeviceSelector::RenderDeviceSelector(wxWindow *parent, bool lookup_cached_info)
    : RenderDeviceSelectorBase(parent),
      m_lookup_cached_info(lookup_cached_info),
      m_device_index(0),
      m_bits_per_pixel(16),
      m_driver_name(wxEmptyString)
{
    Centre();
}

// MFC: CDeviceSelectionDialog::DoModal()
int RenderDeviceSelector::ShowModal()
{
    bool found_device = false;
    int result = wxID_OK;
    
    // Get the name of the last used device driver from the registry (wxConfig)
    wxConfig config("W3DView", "TheSuperHackers");
    m_driver_name = config.Read("/Config/DeviceName", wxEmptyString);
    
    // MFC: If cached info enabled, device name exists, and shift key not held
    if (m_lookup_cached_info && 
        !m_driver_name.IsEmpty() &&
        !(wxGetKeyState(WXK_SHIFT))) {
        
        // Loop through all devices to find the cached one
        // MFC: DeviceSelectionDialog.cpp:120-140
        int device_count = WW3D::Get_Render_Device_Count();
        for (int index = 0; (index < device_count) && !found_device; index++) {
            
            const char *name = WW3D::Get_Render_Device_Name(index);
            if (m_driver_name.CmpNoCase(name) == 0) {
                // Found the cached device - simulate showing dialog without actually showing it
                m_device_index = index;
                m_bits_per_pixel = config.Read("/Config/DeviceBitsPerPix", 16L);
                found_device = true;
            }
        }
    }
    
    // Show the dialog only if device not found in cache
    if (!found_device) {
        result = RenderDeviceSelectorBase::ShowModal();
    }
    
    return result;
}

// MFC: CDeviceSelectionDialog::OnInitDialog()
void RenderDeviceSelector::OnInitDialog(wxInitDialogEvent &event)
{
    // Loop through all the devices and add them to the combobox
    // MFC: DeviceSelectionDialog.cpp:42-79
    int device_count = WW3D::Get_Render_Device_Count();
    int selected_index = 0;
    
    for (int index = 0; index < device_count; index++) {
        // Get device name
        const char *name = WW3D::Get_Render_Device_Name(index);
        
        // Add to combobox
        int combo_index = m_idc_render_device_combo->Append(name);
        
        // Check if this matches the cached driver name
        if (m_driver_name.CmpNoCase(name) == 0) {
            selected_index = combo_index;
        }
        
        // Associate device index with combo item (store as client data)
        m_idc_render_device_combo->SetClientData(combo_index, reinterpret_cast<void*>(static_cast<intptr_t>(index)));
    }
    
    // Check the '16bpp' checkbox by default
    // MFC: SendDlgItemMessage(IDC_COLORDEPTH_16, BM_SETCHECK, TRUE)
    m_idc_colordepth_16->SetValue(true);
    m_idc_colordepth_24->SetValue(false);
    
    // Select the cached device (or first if none cached)
    m_idc_render_device_combo->SetSelection(selected_index);
    
    // Update the static controls to reflect the selected device
    UpdateDeviceDescription();
    
    event.Skip();
}

// MFC: CDeviceSelectionDialog::OnSelchangeRenderDeviceCombo()
void RenderDeviceSelector::OnSelchangeRenderDeviceCombo(wxCommandEvent &event)
{
    // MFC: DeviceSelectionDialog.cpp:153-163
    int index = m_idc_render_device_combo->GetSelection();
    if (index != wxNOT_FOUND) {
        // Update the static controls with the information from the device
        UpdateDeviceDescription();
    }
}

// MFC: CDeviceSelectionDialog::UpdateDeviceDescription()
void RenderDeviceSelector::UpdateDeviceDescription()
{
    // MFC: DeviceSelectionDialog.cpp:129-145
    // TODO(StringClass-Bug): RenderDeviceDescClass Get_*() methods have broken return types
    //   Issue: rddesc.h declares methods as `const char* Get_Device_Name() const`
    //          but implementation returns `StringClass` directly: `{ return DeviceName; }`
    //   Root Cause: StringClass has no implicit conversion to const char* in wxWidgets builds
    //   MFC Build: Works because MFC's StdAfx.h may add conversion operator or uses different StringClass
    //   wxWidgets Build: Compiler error "cannot convert 'const StringClass' to 'const char*'"
    //   
    //   Attempted fixes that failed:
    //   1. Call .Peek_Buffer() - not const, can't call from const method
    //   2. Call .str() - returns const TCHAR* (wchar_t*), still type mismatch
    //   3. Cast to wxString - can't construct from StringClass
    //   
    //   Proper solution (needs header change in rddesc.h):
    //   Option A: Change return type to `const StringClass&` (breaks MFC compatibility)
    //   Option B: Fix implementation to call .str(): `{ return DeviceName.str(); }`
    //            Then cast to wxString in calling code
    //   Option C: Add const version of Peek_Buffer to StringClass
    //   
    //   Current workaround: Skip device info display, focus on device selection functionality
    //   Device selection (combo box, checkboxes, registry) works without device_desc access
    //   
    //   MFC fields that would be populated (currently skipped):
    //   - IDC_DRIVER_NAME (m_driver_name) - driver name from registry
    //   - IDC_DEVICE_NAME_STATIC - device_desc.Get_Device_Name()
    //   - IDC_DEVICE_VENDOR_STATIC - device_desc.Get_Device_Vendor()
    //   - IDC_DEVICE_PLATFORM_STATIC - device_desc.Get_Device_Platform()
    //   - IDC_DRIVER_NAME_STATIC - device_desc.Get_Driver_Name()
    //   - IDC_DRIVER_VENDOR_STATIC - device_desc.Get_Driver_Vendor()
    //   - IDC_DRIVER_VERSION_STATIC - device_desc.Get_Driver_Version()
    //   - IDC_HARDWARE_NAME_STATIC - device_desc.Get_Hardware_Name()
    //   - IDC_HARDWARE_VENDOR_STATIC - device_desc.Get_Hardware_Vendor()
    //   - IDC_HARDWARE_CHIPSET_STATIC - device_desc.Get_Hardware_Chipset()
    //
    // For now: Set driver name only (from m_driver_name, not from device_desc)
    if (m_idc_driver_name) {
        m_idc_driver_name->SetLabelText(m_driver_name);
    }
    
    // TODO: Populate other device info fields once StringClass issue is resolved
    // Until then, these fields will show placeholder text from XRC dialog definition
}

void RenderDeviceSelector::OnOK(wxCommandEvent &event)
{
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void RenderDeviceSelector::OnCancel(wxCommandEvent &event)
{
    EndModal(wxID_CANCEL);
}

bool RenderDeviceSelector::TransferDataToWindow()
{
    // Data transfer handled in OnInitDialog
    return true;
}

// MFC: CDeviceSelectionDialog::OnOK()
bool RenderDeviceSelector::TransferDataFromWindow()
{
    // MFC: DeviceSelectionDialog.cpp:171-198
    
    // Get the selected device index from client data
    int sel = m_idc_render_device_combo->GetSelection();
    if (sel != wxNOT_FOUND) {
        m_device_index = static_cast<int>(reinterpret_cast<intptr_t>(
            m_idc_render_device_combo->GetClientData(sel)));
    }
    
    // Get bits per pixel from checkboxes
    // MFC: SendDlgItemMessage(IDC_COLORDEPTH_16, BM_GETCHECK) == TRUE ? 16 : 24
    m_bits_per_pixel = m_idc_colordepth_16->GetValue() ? 16 : 24;
    
    // Get device name string from combobox
    m_driver_name = m_idc_render_device_combo->GetStringSelection();
    
    // Cache this information in the registry (wxConfig)
    // MFC: theApp.WriteProfileString("Config", "DeviceName", stringDeviceName)
    // MFC: theApp.WriteProfileInt("Config", "DeviceBitsPerPix", m_iBitsPerPixel)
    wxConfig config("W3DView", "TheSuperHackers");
    config.Write("/Config/DeviceName", m_driver_name);
    config.Write("/Config/DeviceBitsPerPix", static_cast<long>(m_bits_per_pixel));
    config.Flush();
    
    return true;
}
