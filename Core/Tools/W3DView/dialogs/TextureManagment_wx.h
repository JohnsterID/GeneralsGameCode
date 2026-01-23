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
#include <wx/dialog.h>
#include <wx/listctrl.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class TextureManagmentBase : public wxDialog
{
public:
    TextureManagmentBase() {}
    TextureManagmentBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_TEXTURE_MANAGMENT")) {
            return false;
        }

        // Get references to controls
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_mesh_texture_list_ctrl = XRCCTRL(*this, "IDC_MESH_TEXTURE_LIST_CTRL", wxListCtrl);
        m_idc_toolbar_slot = XRCCTRL(*this, "IDC_TOOLBAR_SLOT", wxStaticText);

        return true;
    }

protected:
    wxButton *m_idok;
    wxButton *m_idcancel;
    wxStaticText *m_idc_static_1;
    wxStaticBitmap *m_idc_static_2;
    wxListCtrl *m_idc_mesh_texture_list_ctrl;
    wxStaticText *m_idc_toolbar_slot;
};

// Derived class for event handlers and custom logic
class TextureManagment : public TextureManagmentBase
{
public:
    TextureManagment(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
private:
    // Phase 2.5: Dialog infrastructure
    void OnInitDialog(wxInitDialogEvent& event);
    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

    // Event handlers (Phase 2)
void OnDblclkMeshTextureListCtrl(wxListEvent &event);  // Notification message (needs analysis)
    void OnKeydownMeshTextureListCtrl(wxListEvent &event);  // Notification message (needs analysis)
    void OnDestroy(wxWindowDestroyEvent &event);  // Window destruction
};
