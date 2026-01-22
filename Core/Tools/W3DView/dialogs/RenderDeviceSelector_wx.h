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

#pragma once

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class RenderDeviceSelectorBase : public wxDialog
{
public:
    RenderDeviceSelectorBase() {}
    RenderDeviceSelectorBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_RENDER_DEVICE_SELECTOR")) {
            return false;
        }

        // Get references to controls
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idc_render_device_combo = XRCCTRL(*this, "IDC_RENDER_DEVICE_COMBO", wxComboBox);
        m_idc_colordepth_24 = XRCCTRL(*this, "IDC_COLORDEPTH_24", wxCheckBox);
        m_idc_colordepth_16 = XRCCTRL(*this, "IDC_COLORDEPTH_16", wxCheckBox);
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_device_name_static = XRCCTRL(*this, "IDC_DEVICE_NAME_STATIC", wxStaticText);
        m_idc_device_vendor_static = XRCCTRL(*this, "IDC_DEVICE_VENDOR_STATIC", wxStaticText);
        m_idc_device_platform_static = XRCCTRL(*this, "IDC_DEVICE_PLATFORM_STATIC", wxStaticText);
        m_idc_driver_name_static = XRCCTRL(*this, "IDC_DRIVER_NAME_STATIC", wxStaticText);
        m_idc_driver_vendor_static = XRCCTRL(*this, "IDC_DRIVER_VENDOR_STATIC", wxStaticText);
        m_idc_driver_version_static = XRCCTRL(*this, "IDC_DRIVER_VERSION_STATIC", wxStaticText);
        m_idc_hardware_name_static = XRCCTRL(*this, "IDC_HARDWARE_NAME_STATIC", wxStaticText);
        m_idc_hardware_vendor_static = XRCCTRL(*this, "IDC_HARDWARE_VENDOR_STATIC", wxStaticText);
        m_idc_hardware_chipset_static = XRCCTRL(*this, "IDC_HARDWARE_CHIPSET_STATIC", wxStaticText);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_11 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_12 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_driver_name = XRCCTRL(*this, "IDC_DRIVER_NAME", wxStaticText);

        return true;
    }

protected:
    wxButton *m_idok;
    wxComboBox *m_idc_render_device_combo;
    wxCheckBox *m_idc_colordepth_24;
    wxCheckBox *m_idc_colordepth_16;
    wxStaticText *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_static_5;
    wxStaticText *m_idc_static_6;
    wxStaticText *m_idc_static_7;
    wxStaticText *m_idc_static_8;
    wxStaticText *m_idc_static_9;
    wxStaticText *m_idc_device_name_static;
    wxStaticText *m_idc_device_vendor_static;
    wxStaticText *m_idc_device_platform_static;
    wxStaticText *m_idc_driver_name_static;
    wxStaticText *m_idc_driver_vendor_static;
    wxStaticText *m_idc_driver_version_static;
    wxStaticText *m_idc_hardware_name_static;
    wxStaticText *m_idc_hardware_vendor_static;
    wxStaticText *m_idc_hardware_chipset_static;
    wxPanel *m_idc_static_10;
    wxStaticText *m_idc_static_11;
    wxStaticText *m_idc_static_12;
    wxStaticText *m_idc_driver_name;
};

// Derived class for event handlers and custom logic
class RenderDeviceSelector : public RenderDeviceSelectorBase
{
public:
    RenderDeviceSelector(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
private:
    // Event handlers (Phase 2)
void OnSelchangeRenderDeviceCombo(wxCommandEvent &event);  // Combobox selection change
};
