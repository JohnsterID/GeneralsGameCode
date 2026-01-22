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

#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageMeshBase : public wxDialog
{
public:
    PropPageMeshBase() {}
    PropPageMeshBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_MESH")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_description = XRCCTRL(*this, "IDC_DESCRIPTION", wxStaticText);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_polygon_count = XRCCTRL(*this, "IDC_POLYGON_COUNT", wxStaticText);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_vertex_count = XRCCTRL(*this, "IDC_VERTEX_COUNT", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_user_text = XRCCTRL(*this, "IDC_USER_TEXT", wxTextCtrl);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_mesh_type_normal = XRCCTRL(*this, "IDC_MESH_TYPE_NORMAL", wxRadioButton);
        m_idc_mesh_type_collision_box = XRCCTRL(*this, "IDC_MESH_TYPE_COLLISION_BOX", wxRadioButton);
        m_idc_mesh_type_skin = XRCCTRL(*this, "IDC_MESH_TYPE_SKIN", wxRadioButton);
        m_idc_mesh_type_shadow = XRCCTRL(*this, "IDC_MESH_TYPE_SHADOW", wxRadioButton);
        m_idc_collision_type_physical = XRCCTRL(*this, "IDC_COLLISION_TYPE_PHYSICAL", wxCheckBox);
        m_idc_collision_type_projectile = XRCCTRL(*this, "IDC_COLLISION_TYPE_PROJECTILE", wxCheckBox);
        m_idc_hidden = XRCCTRL(*this, "IDC_HIDDEN", wxCheckBox);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_description;
    wxPanel *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxStaticText *m_idc_polygon_count;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_vertex_count;
    wxStaticText *m_idc_static_5;
    wxTextCtrl *m_idc_user_text;
    wxStaticBox *m_idc_static_6;
    wxRadioButton *m_idc_mesh_type_normal;
    wxRadioButton *m_idc_mesh_type_collision_box;
    wxRadioButton *m_idc_mesh_type_skin;
    wxRadioButton *m_idc_mesh_type_shadow;
    wxCheckBox *m_idc_collision_type_physical;
    wxCheckBox *m_idc_collision_type_projectile;
    wxCheckBox *m_idc_hidden;
};

// Derived class for event handlers and custom logic
class PropPageMesh : public PropPageMeshBase
{
public:
    PropPageMesh(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
