/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// GraphicView_wx.cpp : wxWidgets implementation of GraphicView

#include "GraphicView_wx.h"
#include "w3dviewdoc_wx.h"
#include <wx/dcclient.h>

// Global instance pointer for Get_Graphic_View()
static CGraphicView* g_pGraphicView = nullptr;

wxBEGIN_EVENT_TABLE(CGraphicView, wxPanel)
    EVT_PAINT(CGraphicView::OnPaint)
    EVT_SIZE(CGraphicView::OnSize)
    EVT_LEFT_DOWN(CGraphicView::OnLeftDown)
    EVT_LEFT_UP(CGraphicView::OnLeftUp)
    EVT_RIGHT_DOWN(CGraphicView::OnRightDown)
    EVT_RIGHT_UP(CGraphicView::OnRightUp)
    EVT_MOTION(CGraphicView::OnMouseMove)
    EVT_TIMER(wxID_ANY, CGraphicView::OnTimer)
    EVT_ERASE_BACKGROUND(CGraphicView::OnEraseBackground)
wxEND_EVENT_TABLE()

/////////////////////////////////////////////////////////////////////////////
// Constructor / Destructor

CGraphicView::CGraphicView(wxWindow* parent, wxWindowID id,
                           const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE)
    , m_bInitialized(false)
    , m_bActive(true)
    , m_timer(this, wxID_ANY)
    , m_pCamera(nullptr)
    , m_pLightMesh(nullptr)
    , m_bLightMeshInScene(false)
    , m_bMouseDown(false)
    , m_bRMouseDown(false)
    , m_iWindowed(1)
    , m_UpdateCounter(0)
    , m_CameraDistance(100.0f)
    , m_ParticleCountUpdate(0)
    , m_CameraBonePosX(false)
    , m_dwLastFrameUpdate(0)
    , m_animationSpeed(1.0f)
    , m_animationState(AnimStopped)
    , m_objectRotation(NoRotation)
    , m_LightRotation(NoRotation)
    , m_allowedCameraRotation(FreeRotation)
{
    // Set as global instance
    g_pGraphicView = this;
    
    // TODO: Phase 3 - Initialize rendering context
    SetBackgroundStyle(wxBG_STYLE_PAINT);  // For custom painting
}

CGraphicView::~CGraphicView()
{
    if (m_timer.IsRunning()) {
        m_timer.Stop();
    }
    
    // TODO: Phase 3 - Cleanup rendering resources
    if (m_pCamera) {
        delete m_pCamera;
        m_pCamera = nullptr;
    }
    
    if (g_pGraphicView == this) {
        g_pGraphicView = nullptr;
    }
}

/////////////////////////////////////////////////////////////////////////////
// Initialization

bool CGraphicView::InitializeGraphicView()
{
    // TODO: Phase 3 - Initialize OpenGL/D3D rendering context
    // For now, just mark as initialized
    m_bInitialized = true;
    
    // Start update timer (30 FPS)
    m_timer.Start(33);
    
    return true;
}

/////////////////////////////////////////////////////////////////////////////
// Display Methods

void CGraphicView::Reset_Camera_To_Display_Sphere(SphereClass &sphere)
{
    // TODO: Phase 3 - Implement camera positioning for sphere
    m_ViewedSphere = sphere;
}

void CGraphicView::Reset_Camera_To_Display_Object(RenderObjClass &physObject)
{
    // TODO: Phase 3 - Implement camera positioning for object
}

void CGraphicView::Reset_Camera_To_Display_Emitter(ParticleEmitterClass &emitter)
{
    // TODO: Phase 3 - Implement camera positioning for emitter
}

void CGraphicView::Load_Default_Dat()
{
    // TODO: Phase 3 - Load default data file
}

void CGraphicView::UpdateDisplay()
{
    // TODO: Phase 3 - Update 3D scene
    Refresh(false);  // Request repaint
}

void CGraphicView::RepaintView(bool bUpdateAnimation, unsigned long ticks_to_use)
{
    // TODO: Phase 3 - Render 3D scene with animation update
    Refresh(false);
}

void CGraphicView::SetActiveUpdate(bool bActive)
{
    m_bActive = bActive;
    
    if (!m_bActive) {
        if (m_timer.IsRunning()) {
            m_timer.Stop();
        }
    } else {
        m_dwLastFrameUpdate = wxGetLocalTimeMillis().GetLo();
        if (!m_timer.IsRunning()) {
            m_timer.Start(33);  // 30 FPS
        }
    }
}

void CGraphicView::Allow_Update(bool onoff)
{
    // TODO: Phase 3 - Implement update control
    m_UpdateCounter = onoff ? 0 : 1;
}

/////////////////////////////////////////////////////////////////////////////
// Animation Methods

void CGraphicView::SetAnimationState(ANIMATION_STATE animationState)
{
    m_animationState = animationState;
    
    if (animationState == AnimPlaying) {
        SetActiveUpdate(true);
    } else if (animationState == AnimStopped) {
        SetActiveUpdate(false);
    }
    // AnimPaused keeps timer running but doesn't advance animation
}

/////////////////////////////////////////////////////////////////////////////
// Camera Methods

void CGraphicView::SetAllowedCameraRotation(CAMERA_ROTATION cameraRotation)
{
    m_allowedCameraRotation = cameraRotation;
}

void CGraphicView::SetCameraPos(CAMERA_POS cameraPos)
{
    // TODO: Phase 3 - Set camera to predefined position
}

void CGraphicView::Set_Camera_Distance(float dist)
{
    m_CameraDistance = dist;
    // TODO: Phase 3 - Update camera position based on distance
    Refresh(false);
}

/////////////////////////////////////////////////////////////////////////////
// Object Rotation Methods

void CGraphicView::ResetObject()
{
    m_objectRotation = NoRotation;
    // TODO: Phase 3 - Reset object transform
    Refresh(false);
}

void CGraphicView::RotateObject(OBJECT_ROTATION rotation)
{
    m_objectRotation = rotation;
    Refresh(false);
}

void CGraphicView::Rotate_Object()
{
    // TODO: Phase 3 - Apply rotation to object based on m_objectRotation
}

void CGraphicView::Rotate_Light()
{
    // TODO: Phase 3 - Apply rotation to light based on m_LightRotation
}

/////////////////////////////////////////////////////////////////////////////
// Fullscreen Methods

void CGraphicView::Set_Fullscreen(bool fullscreen)
{
    m_iWindowed = fullscreen ? 0 : 1;
    InitializeGraphicView();
}

/////////////////////////////////////////////////////////////////////////////
// FOV Methods

void CGraphicView::Set_FOV(double hfov, double vfov, bool force)
{
    // TODO: Phase 3 - Set field of view for camera
}

void CGraphicView::Reset_FOV()
{
    // TODO: Phase 3 - Reset field of view to default
}

/////////////////////////////////////////////////////////////////////////////
// wxWidgets Event Handlers

void CGraphicView::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    
    if (!m_bInitialized) {
        // Draw placeholder until initialized
        dc.SetBrush(*wxBLACK_BRUSH);
        dc.DrawRectangle(GetClientRect());
        
        dc.SetTextForeground(*wxWHITE);
        dc.DrawText("3D View - Initializing...", 10, 10);
        return;
    }
    
    // TODO: Phase 3 - Render 3D scene
    // For now, just draw a black background
    dc.SetBrush(*wxBLACK_BRUSH);
    dc.DrawRectangle(GetClientRect());
    
    dc.SetTextForeground(*wxGREEN);
    dc.DrawText("3D View - Ready (Rendering not yet implemented)", 10, 10);
}

void CGraphicView::OnSize(wxSizeEvent& event)
{
    // TODO: Phase 3 - Resize rendering viewport
    event.Skip();
    Refresh(false);
}

void CGraphicView::OnLeftDown(wxMouseEvent& event)
{
    m_bMouseDown = true;
    m_lastPoint = event.GetPosition();
    CaptureMouse();
}

void CGraphicView::OnLeftUp(wxMouseEvent& event)
{
    if (m_bMouseDown) {
        m_bMouseDown = false;
        if (HasCapture()) {
            ReleaseMouse();
        }
    }
}

void CGraphicView::OnRightDown(wxMouseEvent& event)
{
    m_bRMouseDown = true;
    m_lastPoint = event.GetPosition();
    CaptureMouse();
}

void CGraphicView::OnRightUp(wxMouseEvent& event)
{
    if (m_bRMouseDown) {
        m_bRMouseDown = false;
        if (HasCapture()) {
            ReleaseMouse();
        }
    }
}

void CGraphicView::OnMouseMove(wxMouseEvent& event)
{
    if (!m_bMouseDown && !m_bRMouseDown) {
        return;
    }
    
    wxPoint currentPoint = event.GetPosition();
    int deltaX = currentPoint.x - m_lastPoint.x;
    int deltaY = currentPoint.y - m_lastPoint.y;
    
    // TODO: Phase 3 - Implement camera/object rotation based on mouse movement
    // Left mouse: rotate object
    // Right mouse: rotate camera
    
    m_lastPoint = currentPoint;
    Refresh(false);
}

void CGraphicView::OnTimer(wxTimerEvent& event)
{
    if (!m_bActive) {
        return;
    }
    
    // TODO: Phase 3 - Update animation and render
    if (m_animationState == AnimPlaying) {
        // Update animation frame
    }
    
    Refresh(false);
}

void CGraphicView::OnEraseBackground(wxEraseEvent& event)
{
    // Don't erase background - we'll paint everything in OnPaint
    // This prevents flickering
}

/////////////////////////////////////////////////////////////////////////////
// Global Accessor Function

CGraphicView* Get_Graphic_View()
{
    return g_pGraphicView;
}
