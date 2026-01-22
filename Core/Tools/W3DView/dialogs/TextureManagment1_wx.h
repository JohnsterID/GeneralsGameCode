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
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/treectrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class TextureManagment1Base : public wxDialog
{
public:
    TextureManagment1Base() {}
    TextureManagment1Base(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_TEXTURE_MANAGMENT1")) {
            return false;
        }

        // Get references to controls
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_tree1 = XRCCTRL(*this, "IDC_TREE1", wxTreeCtrl);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_texture_filename = XRCCTRL(*this, "IDC_TEXTURE_FILENAME", wxComboBox);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_advanced = XRCCTRL(*this, "IDC_ADVANCED", wxButton);
        m_idc_replace_texture = XRCCTRL(*this, "IDC_REPLACE_TEXTURE", wxButton);
        m_idc_restore_texture = XRCCTRL(*this, "IDC_RESTORE_TEXTURE", wxButton);

        return true;
    }

protected:
    wxButton *m_idok;
    wxButton *m_idcancel;
    wxStaticText *m_idc_static_1;
    wxStaticBitmap *m_idc_static_2;
    wxTreeCtrl *m_idc_tree1;
    wxStaticBox *m_idc_static_3;
    wxComboBox *m_idc_texture_filename;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_static_5;
    wxStaticText *m_idc_static_6;
    wxButton *m_idc_advanced;
    wxButton *m_idc_replace_texture;
    wxButton *m_idc_restore_texture;
};

// Derived class for event handlers and custom logic
class TextureManagment1 : public TextureManagment1Base
{
public:
    TextureManagment1(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
