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

#include "PropPageSphereColor_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(PropPageSphereColor, PropPageSphereColorBase)
EVT_WINDOW_DESTROY(PropPageSphereColor::OnDestroy)  // Window destruction
    EVT_CHECKBOX(XRCID("IDC_OPACITY_VECTOR_CHECK"), PropPageSphereColor::OnOpacityVectorCheck)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_INVERT_VECTOR_CHECK"), PropPageSphereColor::OnInvertVectorCheck)  // Button/Checkbox click
    EVT_INIT_DIALOG(PropPageSphereColor::OnInitDialog)
wxEND_EVENT_TABLE()

PropPageSphereColor::PropPageSphereColor(wxWindow *parent)
    : PropPageSphereColorBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageSphereColor::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageSphereColor::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void PropPageSphereColor::OnDestroy(wxWindowDestroyEvent &event)
{
    // MFC Reference: SphereColorPropPage.cpp (OnDestroy)
    // Function: Cleanup alpha vector data and property page resources
    //
    // MFC Implementation:
    //   int count = m_VectorBar->Get_Point_Count();
    //   for (int index = 0; index < count; index++) {
    //       AlphaVectorStruct *data = (AlphaVectorStruct *)m_VectorBar->Get_User_Data(index);
    //       if (data != nullptr) {
    //           delete data;
    //           m_VectorBar->Set_User_Data(index, 0L);
    //       }
    //   }
    //   CPropertyPage::OnDestroy();
    
    // TODO(Phase 3 - Rendering): Cleanup AlphaVectorStruct data
    //   Need to iterate through m_VectorBar points and delete AlphaVectorStruct instances
    //   This requires VectorBar integration (timeline control for particle alpha)
    //   Priority: HIGH - memory leak if not implemented
    
    event.Skip();  // Allow base class to process destruction
}

void PropPageSphereColor::OnOpacityVectorCheck(wxCommandEvent &event)
{
    // MFC Reference: SphereColorPropPage.cpp (OnOpacityVectorCheck)
    // Function: Enable/disable alpha vector controls and update render object
    //
    // MFC Implementation:
    //   bool is_checked = (IsDlgButtonChecked(IDC_OPACITY_VECTOR_CHECK) == 1);
    //   EnableWindow(GetDlgItem(IDC_VECTOR_BAR), is_checked);
    //   EnableWindow(GetDlgItem(IDC_INVERT_VECTOR_CHECK), is_checked);
    //   m_RenderObj->Set_Flag(SphereRenderObjClass::USE_ALPHA_VECTOR, is_checked);
    //   SetModified();
    
    bool is_checked = false;
    if (m_idc_opacity_vector_check)
    {
        is_checked = m_idc_opacity_vector_check->GetValue();
    }
    
    // Enable/disable alpha-vector timeline controls
    if (m_idc_vector_bar) m_idc_vector_bar->Enable(is_checked);
    if (m_idc_invert_vector_check) m_idc_invert_vector_check->Enable(is_checked);
    
    // TODO(Phase 3 - Rendering): Update render object flag
    //   MFC: m_RenderObj->Set_Flag(SphereRenderObjClass::USE_ALPHA_VECTOR, is_checked);
    //   Need to implement render object integration for sphere particles
    //   Priority: HIGH - required for correct particle rendering behavior
    
    // TODO(MFC-Match): Call SetModified() equivalent for property page
    //   Priority: LOW - functionality works, but Apply button state may not update
}

void PropPageSphereColor::OnInvertVectorCheck(wxCommandEvent &event)
{
    // MFC Reference: SphereColorPropPage.cpp (OnInvertVectorCheck)
    // Function: Update render object with inverted alpha setting
    //
    // MFC Implementation:
    //   bool is_checked = (IsDlgButtonChecked(IDC_INVERT_VECTOR_CHECK) == 1);
    //   m_RenderObj->Set_Flag(SphereRenderObjClass::USE_INVERSE_ALPHA, is_checked);
    //   SetModified();
    //
    // Note: This handler only updates render object, no UI changes
    
    bool is_checked = false;
    if (m_idc_invert_vector_check)
    {
        is_checked = m_idc_invert_vector_check->GetValue();
    }
    
    // TODO(Phase 3 - Rendering): Update render object flag
    //   MFC: m_RenderObj->Set_Flag(SphereRenderObjClass::USE_INVERSE_ALPHA, is_checked);
    //   Need to implement render object integration for sphere particles
    //   Priority: HIGH - required for correct particle rendering behavior
    
    // TODO(MFC-Match): Call SetModified() equivalent for property page
    //   Priority: LOW - functionality works, but Apply button state may not update
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageSphereColor::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Allow the base class to process this message
    // TODO: Convert: m_ColorBar		= ColorBarClass::Get_Color_Bar (::GetDlgItem (m_hWnd, IDC_COLOR_BAR));
    // TODO: Convert: m_OpacityBar	= ColorBarClass::Get_Color_Bar (::GetDlgItem (m_hWnd, IDC_OPACITY_BAR));
    // TODO: Convert: m_VectorBar		= ColorBarClass::Get_Color_Bar (::GetDlgItem (m_hWnd, IDC_VECTOR_BAR));
    //
    // Setup the color bars
    //
    // TODO: Convert: m_ColorBar->Set_Range (0, 1);
    // TODO: Convert: m_OpacityBar->Set_Range (0, 1);
    // TODO: Convert: m_VectorBar->Set_Range (0, 1);
    //
    //	Set-up the color bar
    //
    // TODO: Convert: int index;
    // TODO: Convert: m_ColorBar->Modify_Point (	index,
    // TODO: Convert: m_OrigColorChannel[index].Get_Time (),
    // TODO: Convert: m_OrigColorChannel[index].Get_Value ().X * 255,
    // TODO: Convert: m_OrigColorChannel[index].Get_Value ().Y * 255,
    // TODO: Convert: m_OrigColorChannel[index].Get_Value ().Z * 255);
    //
    //	Set-up the opacity bar
    //
    // TODO: Convert: m_OpacityBar->Modify_Point (	index,
    // TODO: Convert: m_OrigAlphaChannel[index].Get_Time (),
    // TODO: Convert: m_OrigAlphaChannel[index].Get_Value () * 255,
    // TODO: Convert: m_OrigAlphaChannel[index].Get_Value () * 255,
    // TODO: Convert: m_OrigAlphaChannel[index].Get_Value () * 255);
    //
    //	Set-up the vector bar
    //
    // TODO: Convert: m_VectorBar->Modify_Point (index,
    // TODO: Convert: m_OrigVectorChannel[index].Get_Time (),
    // TODO: Convert: 128,
    // TODO: Convert: 128,
    // TODO: Convert: 128);
    // TODO: Convert: AlphaVectorStruct *data = new AlphaVectorStruct (m_OrigVectorChannel[index].Get_Value ());
    // TODO: Convert: m_VectorBar->Set_User_Data (index, (ULONG)data);
    //
    //	Ensure our initial 'current' values are up-to-date
    //
    // TODO: Convert: Update_Colors ();
    // TODO: Convert: Update_Opacities ();
    // TODO: Convert: Update_Vectors ();
    //
    //	Ensure the disabled status of the dialog controls is correct
    //
    // TODO: Convert: CheckDlgButton (IDC_OPACITY_VECTOR_CHECK, (m_RenderObj->Get_Flags () & SphereRenderObjClass::USE_ALPHA_VECTOR) != 0);
    // TODO: Convert: CheckDlgButton (IDC_INVERT_VECTOR_CHECK, (m_RenderObj->Get_Flags () & SphereRenderObjClass::USE_INVERSE_ALPHA) != 0);
    // TODO: Convert: OnOpacityVectorCheck ();
	// MFC: return TRUE;

    event.Skip();
}

bool PropPageSphereColor::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageSphereColor::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Extract data from controls

    return true;
}
