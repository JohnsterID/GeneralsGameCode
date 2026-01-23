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

#pragma once

// GraphicView_wx.h : wxWidgets version of GraphicView
// Provides the main 3D rendering view for W3DView application

#include <wx/wx.h>
#include <wx/timer.h>
#include "w3dcompat_wx.h"

// Forward declarations
class ParticleEmitterClass;

/////////////////////////////////////////////////////////////////
//
//  Constants (from original GraphicView.h)
//
#define ROTATION_X      0x01
#define ROTATION_Y      0x02
#define ROTATION_Z      0x04
#define ROTATION_X_BACK 0x08
#define ROTATION_Y_BACK 0x10
#define ROTATION_Z_BACK 0x20

/////////////////////////////////////////////////////////////////////////////
// CGraphicView - wxWidgets version

class CGraphicView : public wxPanel
{
public:
    /////////////////////////////////////////////////
    //
    //  Public Data Types
    //
    typedef enum
    {
        AnimInvalid = -1,
        AnimPlaying = 0,
        AnimStopped = 1,
        AnimPaused = 2
    } ANIMATION_STATE;

    typedef enum
    {
        CameraFront = -1,
        CameraBack = 0,
        CameraTop = 1,
        CameraBottom = 2,
        CameraLeft = 3,
        CameraRight = 4
    } CAMERA_POS;

    typedef enum
    {
        NoRotation = 0,
        RotateX = ROTATION_X,
        RotateY = ROTATION_Y,
        RotateZ = ROTATION_Z,
        RotateXBack = ROTATION_X_BACK,
        RotateYBack = ROTATION_Y_BACK,
        RotateZBack = ROTATION_Z_BACK
    } OBJECT_ROTATION;

    typedef enum
    {
        FreeRotation = 0,
        OnlyRotateX = ROTATION_X,
        OnlyRotateY = ROTATION_Y,
        OnlyRotateZ = ROTATION_Z
    } CAMERA_ROTATION;

    /////////////////////////////////////////////////
    //
    //  Constructor / Destructor
    //
    CGraphicView(wxWindow* parent, wxWindowID id = wxID_ANY,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize);
    virtual ~CGraphicView();

    /////////////////////////////////////////////////
    //
    //  Public Methods
    //
    
    bool InitializeGraphicView();

    //
    //  Initial display methods
    //
    void Reset_Camera_To_Display_Sphere(SphereClass &sphere);
    void Reset_Camera_To_Display_Object(RenderObjClass &physObject);
    void Reset_Camera_To_Display_Emitter(ParticleEmitterClass &emitter);
    void Load_Default_Dat();

    void UpdateDisplay();
    void RepaintView(bool bUpdateAnimation = true, unsigned long ticks_to_use = 0);
    void SetActiveUpdate(bool bActive);
    void Allow_Update(bool onoff);

    //
    // Animation methods
    //
    float GetAnimationSpeed() const { return m_animationSpeed; }
    void SetAnimationSpeed(float animationSpeed) { m_animationSpeed = animationSpeed; }
    ANIMATION_STATE GetAnimationState() const { return m_animationState; }
    void SetAnimationState(ANIMATION_STATE animationState);

    //
    // Camera Methods
    //
    void SetAllowedCameraRotation(CAMERA_ROTATION cameraRotation);
    CAMERA_ROTATION GetAllowedCameraRotation() const { return m_allowedCameraRotation; }
    void SetCameraPos(CAMERA_POS cameraPos);
    class CameraClass* GetCamera() const { return m_pCamera; }

    float Get_Camera_Distance() const { return m_CameraDistance; }
    void Set_Camera_Distance(float dist);

    void Set_Camera_Bone_Pos_X(bool onoff) { m_CameraBonePosX = onoff; }
    bool Is_Camera_Bone_Pos_X() const { return m_CameraBonePosX; }

    //
    // Object rotation methods
    //
    void ResetObject();
    void RotateObject(OBJECT_ROTATION rotation);
    OBJECT_ROTATION GetObjectRotation() const { return m_objectRotation; }

    //
    // Light rotation methods
    //
    void Rotate_Light(OBJECT_ROTATION rotation) { m_LightRotation = rotation; }
    OBJECT_ROTATION Get_Light_Rotation() const { return m_LightRotation; }

    //
    //  Fullscreen mode
    //
    bool Is_Fullscreen() const { return !m_iWindowed; }
    void Set_Fullscreen(bool fullscreen);

    //
    //  Misc
    //
    RenderObjClass* Get_Light_Mesh() const { return m_pLightMesh; }
    Vector3& Get_Object_Center() { return m_ObjectCenter; }

    //
    //  FOV methods
    //
    void Set_FOV(double hfov, double vfov, bool force = false);
    void Reset_FOV();

protected:
    /////////////////////////////////////////////////
    //
    //  Protected methods
    //
    void Rotate_Object();
    void Rotate_Light();

    /////////////////////////////////////////////////
    //
    //  wxWidgets Event Handlers
    //
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnRightDown(wxMouseEvent& event);
    void OnRightUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnEraseBackground(wxEraseEvent& event);

private:
    /////////////////////////////////////////////////
    //
    //  Private Member Data
    //
    bool m_bInitialized;
    bool m_bActive;
    wxTimer m_timer;
    CameraClass* m_pCamera;
    RenderObjClass* m_pLightMesh;
    bool m_bLightMeshInScene;
    Vector3 m_ObjectCenter;
    SphereClass m_ViewedSphere;

    bool m_bMouseDown;
    bool m_bRMouseDown;
    wxPoint m_lastPoint;
    int m_iWindowed;
    int m_UpdateCounter;
    float m_CameraDistance;
    unsigned long m_ParticleCountUpdate;
    bool m_CameraBonePosX;

    // Animation data
    unsigned long m_dwLastFrameUpdate;
    float m_animationSpeed;
    ANIMATION_STATE m_animationState;
    OBJECT_ROTATION m_objectRotation;
    OBJECT_ROTATION m_LightRotation;
    CAMERA_ROTATION m_allowedCameraRotation;

    wxDECLARE_EVENT_TABLE();
};

/////////////////////////////////////////////////////////////////////////////
// Global accessor function (wxWidgets version)
CGraphicView* Get_Graphic_View();

