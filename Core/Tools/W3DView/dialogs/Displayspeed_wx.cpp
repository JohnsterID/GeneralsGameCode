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
// Implemented from MFC AnimationSpeed.cpp

#include "Displayspeed_wx.h"
#include "../w3dviewdoc_wx.h"
#include "../GraphicView_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(Displayspeed, DisplayspeedBase)
    EVT_SLIDER(XRCID("IDC_SPEED_SLIDER"), Displayspeed::OnHscroll)  // Horizontal scroll (slider)
    EVT_WINDOW_DESTROY(Displayspeed::OnDestroy)  // Window destruction
    EVT_CHECKBOX(XRCID("IDC_BLEND"), Displayspeed::OnBlend)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_COMPRESSQ"), Displayspeed::OnCompressq)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_16BIT"), Displayspeed::On16bit)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_8BIT"), Displayspeed::On8bit)  // Button/Checkbox click
wxEND_EVENT_TABLE()

Displayspeed::Displayspeed(wxWindow *parent, W3DViewDoc *doc, CGraphicView *view)
    : DisplayspeedBase(parent)
    , m_doc(doc)
    , m_view(view)
    , m_initialSpeed(1.0f)
{
    // MFC Reference: AnimationSpeed.cpp:48-56
    // Initialize dialog and center
    
    // Save initial animation speed for restore on cancel (MFC: AnimationSpeed.cpp:117-128)
    if (m_view)
    {
        m_initialSpeed = m_view->GetAnimationSpeed();
    }
    
    // Transfer data to controls
    TransferDataToWindow();
    Centre();
}

void Displayspeed::OnOK(wxCommandEvent &event)
{
    // Validate and close (keep current settings)
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void Displayspeed::OnCancel(wxCommandEvent &event)
{
    // MFC Reference: AnimationSpeed.cpp (MainFrm.cpp:990-1002)
    // On cancel: restore initial animation speed
    if (m_view)
    {
        m_view->SetAnimationSpeed(m_initialSpeed);
    }
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers - MFC AnimationSpeed.cpp matching implementation
// ============================================================================

void Displayspeed::OnHscroll(wxCommandEvent &event)
{
    // MFC Reference: AnimationSpeed.cpp:144-170 (OnHScroll)
    // Slider value changed - update animation speed in real-time
    
    if (!m_view || !m_idc_speed_slider) return;
    
    // Get slider position (1-200 percent)
    int sliderPos = m_idc_speed_slider->GetValue();
    
    // Convert percent to speed (0.01-2.00)
    float speed = static_cast<float>(sliderPos) / 100.0f;
    
    // Set animation speed immediately (MFC: AnimationSpeed.cpp:163)
    m_view->SetAnimationSpeed(speed);
}

void Displayspeed::OnDestroy(wxWindowDestroyEvent &event)
{
    // MFC Reference: AnimationSpeed.cpp:176-182 (OnDestroy)
    // Dialog being destroyed - cleanup if needed
    event.Skip(); // Allow default handling
}

void Displayspeed::OnBlend(wxCommandEvent &event)
{
    // MFC Reference: AnimationSpeed.cpp:188-201 (OnBlend)
    // Toggle animation blend setting
    
    if (!m_doc || !m_idc_blend) return;
    
    // Get checkbox state and update document
    bool blend = m_idc_blend->GetValue();
    m_doc->SetAnimationBlend(blend);
}

void Displayspeed::OnCompressq(wxCommandEvent &event)
{
    // MFC Reference: AnimationSpeed.cpp:203-226 (OnCompressq)
    // NOTE(MFC-Match): This method is COMMENTED OUT in MFC AnimationSpeed.cpp!
    // The code exists but is wrapped in /* */ comments - intentionally not implemented here.
    //   Original behavior: Would toggle channel Q compression and enable/disable radio buttons
    //   Would require: pCDoc->SetChannelQCompression(b_compress)
    //   Enable state: GetDlgItem(IDC_16BIT/IDC_8BIT)->EnableWindow(b_compress)
    //   Impact: LOW - feature is unused in MFC
    //   Decision: Leave unimplemented to match MFC behavior exactly
    
    // Empty implementation matches MFC (commented out code)
}

void Displayspeed::On16bit(wxCommandEvent &event)
{
    // MFC Reference: AnimationSpeed.cpp:228-234 (On16bit)
    // NOTE(MFC-Match): This method is COMMENTED OUT in MFC AnimationSpeed.cpp!
    // Intentionally not implemented here to match MFC behavior.
    //   Original behavior: Would set Q bytes to 2 (16-bit compression)
    //   Would require: pCDoc->SetChannelQnBytes(2); QnBytes = 2;
    //   Impact: LOW - feature is unused in MFC
    //   Decision: Leave unimplemented to match MFC behavior exactly
    
    // Empty implementation matches MFC (commented out code)
}

void Displayspeed::On8bit(wxCommandEvent &event)
{
    // MFC Reference: AnimationSpeed.cpp:236-243 (On8bit)
    // NOTE(MFC-Match): This method is COMMENTED OUT in MFC AnimationSpeed.cpp!
    // Intentionally not implemented here to match MFC behavior.
    //   Original behavior: Would set Q bytes to 1 (8-bit compression)
    //   Would require: pCDoc->SetChannelQnBytes(1); QnBytes = 1;
    //   Impact: LOW - feature is unused in MFC
    //   Decision: Leave unimplemented to match MFC behavior exactly
    
    // Empty implementation matches MFC (commented out code)
}


// ============================================================================
// Dialog Infrastructure - Data Transfer
// ============================================================================

bool Displayspeed::TransferDataToWindow()
{
    // MFC Reference: AnimationSpeed.cpp:89-138 (OnInitDialog)
    // Initialize all controls from document and view state
    
    if (!m_doc || !m_view) return false;
    
    // 1. Set animation blend checkbox (MFC: AnimationSpeed.cpp:104)
    if (m_idc_blend)
    {
        m_idc_blend->SetValue(m_doc->GetAnimationBlend());
    }
    
    // 2. Set compression checkbox (MFC: AnimationSpeed.cpp:105)
    // NOTE: Compression features are commented out in MFC dialog handlers
    if (m_idc_compressq)
    {
        m_idc_compressq->SetValue(m_doc->GetChannelQCompression());
    }
    
    // 3. Set 16bit/8bit radio buttons (MFC: AnimationSpeed.cpp:106)
    // NOTE: Radio button logic is commented out in MFC dialog handlers
    if (m_idc_16bit && m_idc_8bit)
    {
        int qBytes = m_doc->GetChannelQnBytes();
        m_idc_16bit->SetValue(qBytes == 2);
        m_idc_8bit->SetValue(qBytes == 1);
    }
    
    // 4. Enable/disable radio buttons based on compression (MFC: AnimationSpeed.cpp:107-113)
    bool compressEnabled = m_doc->GetChannelQCompression();
    if (m_idc_16bit) m_idc_16bit->Enable(compressEnabled);
    if (m_idc_8bit) m_idc_8bit->Enable(compressEnabled);
    
    // 5. Set animation speed slider (MFC: AnimationSpeed.cpp:125-136)
    if (m_idc_speed_slider)
    {
        // Get current animation speed (0.01-2.00)
        float animSpeed = m_view->GetAnimationSpeed();
        
        // Convert to percentage (1-200)
        int percent = static_cast<int>(animSpeed * 100.0f);
        
        // Set slider range and position (MFC: SetRange(1, 200))
        // NOTE: MFC uses range 1-200, not 1-100 as documented in earlier TODO
        m_idc_speed_slider->SetRange(1, 200);
        m_idc_speed_slider->SetValue(percent);
    }
    
    return true;
}

bool Displayspeed::TransferDataFromWindow()
{
    // Settings are applied in real-time by event handlers
    // OnHscroll updates animation speed immediately
    // OnBlend updates animation blend immediately
    // No additional transfer needed
    return true;
}
