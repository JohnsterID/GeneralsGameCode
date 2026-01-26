# LightSceneDialog TODO Analysis - Type 1 Dialog

**Dialog**: OnLightScene  
**Status**: Type 1 - Non-Functional Placeholder  
**Complexity**: HIGH (More complex than LightAmbient)  
**Estimated Effort**: 4-6 hours

---

## Classification: Type 1 (Non-Functional Placeholder)

Following Session 37's investigation methodology:
- ✅ Checked wxWidgets LightSceneDialog_wx.cpp
- ✅ Compared with MFC SceneLightDialog.cpp
- ✅ Result: **Type 1** - Extensive TODOs, no functional implementation

**Evidence**:
- OnCancel: Lines 51-74 - Full TODO explaining needed implementation
- OnHscroll: Lines 80-108 - Full TODO explaining slider handling
- OnGrayscaleCheck: Lines 110-130 - Full TODO explaining grayscale logic
- OnChannelBothRadio: Similar TODOs
- OnChannelDiffuseRadio: Similar TODOs
- OnChannelSpecularRadio: Similar TODOs
- OnAttenuationCheck: Similar TODOs

---

## Complexity Analysis

### Why This Is MORE Complex Than LightAmbient:

**LightAmbient** (Already Implemented):
- Single light property: Ambient Light (Vector3)
- 3 RGB sliders (0-100)
- Grayscale checkbox
- Real-time updates
- Cancel restores initial values

**LightScene** (Needs Implementation):
- **TWO color channels**: Diffuse + Specular (both Vector3)
- 3 RGB sliders (0-100) - shared for both channels!
- **Channel selection**: Radio buttons to choose Diffuse/Specular/Both
- **Intensity slider**: Separate intensity control (0-100)
- **Distance control**: Light position/distance from object
- **Attenuation controls**: Start/End range + enable checkbox
- Grayscale checkbox
- Real-time updates
- Cancel restores: diffuse, specular, intensity, attenuation, distance

---

## MFC Reference: SceneLightDialog.cpp

### OnInitDialog (Lines ~42-150):

```cpp
// Set slider ranges
m_redSlider.SetRange(0, 100);
m_greenSlider.SetRange(0, 100);
m_blueSlider.SetRange(0, 100);

// Get scene light
CW3DViewDoc *pCDoc = ::GetCurrentDocument();
if (pCDoc && pCDoc->GetScene()) {
    Vector3 diffuse;
    Vector3 specular;
    pCDoc->GetSceneLight()->Get_Diffuse(&diffuse);
    pCDoc->GetSceneLight()->Get_Specular(&specular);
    
    // Remember initial settings for cancel restore
    m_InitialRedDiffuse = int(diffuse.X * 100.0f);
    m_InitialGreenDiffuse = int(diffuse.Y * 100.0f);
    m_InitialBlueDiffuse = int(diffuse.Z * 100.0f);
    m_InitialRedSpecular = int(specular.X * 100.0f);
    m_InitialGreenSpecular = int(specular.Y * 100.0f);
    m_InitialBlueSpecular = int(specular.Z * 100.0f);
    
    Set_Color_Control_State(diffuse);  // Initialize sliders to diffuse
    
    // Get attenuation
    double start = 0, end = 0;
    pCDoc->GetSceneLight()->Get_Far_Attenuation_Range(start, end);
    BOOL atten_on = pCDoc->GetSceneLight()->Get_Flag(LightClass::FAR_ATTENUATION);
    SendDlgItemMessage(IDC_ATTENUATION_CHECK, BM_SETCHECK, (WPARAM)atten_on);
    
    // Get intensity
    float intensity = pCDoc->GetSceneLight()->Get_Intensity();
    
    // Calculate distance from light to object
    float distance = 0;
    if (pCDoc->GetDisplayedObject() != nullptr) {
        Vector3 light_pos = pCDoc->GetSceneLight()->Get_Position();
        Vector3 obj_pos = pCDoc->GetDisplayedObject()->Get_Position();
        distance = (light_pos - obj_pos).Length();
    }
    m_InitialDistance = distance;
    m_InitialIntensity = intensity;
    m_InitialStartAtten = start;
    m_InitialEndAtten = end;
    m_InitialAttenOn = atten_on;
}
```

### OnHScroll (Lines 188-242):

```cpp
void CSceneLightDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // Did the intensity slider send this message?
    if (pScrollBar == GetDlgItem(IDC_INTENSITY_SLIDER)) {
        float intensity = ((float)m_IntensitySlider.GetPos()) / 100.0f;
        ::GetCurrentDocument()->GetSceneLight()->Set_Intensity(intensity);
    } else {
        // RGB sliders
        
        // If grayscale is checked, sync all sliders
        if (SendDlgItemMessage(IDC_GRAYSCALE_CHECK, BM_GETCHECK)) {
            int iCurrentPos = 0;
            if (pScrollBar == GetDlgItem(IDC_SLIDER_RED)) {
                iCurrentPos = m_redSlider.GetPos();
            } else if (pScrollBar == GetDlgItem(IDC_SLIDER_GREEN)) {
                iCurrentPos = m_greenSlider.GetPos();
            } else {
                iCurrentPos = m_blueSlider.GetPos();
            }
            
            // Sync all sliders
            m_redSlider.SetPos(iCurrentPos);
            m_greenSlider.SetPos(iCurrentPos);
            m_blueSlider.SetPos(iCurrentPos);
        }
        
        // Build color vector
        Vector3 color;
        color.X = float(m_redSlider.GetPos()) / 100.0f;
        color.Y = float(m_greenSlider.GetPos()) / 100.0f;
        color.Z = float(m_blueSlider.GetPos()) / 100.0f;
        
        // Update the light based on current channel
        Update_Light(color);
    }
}
```

### OnCancel (Lines 250-281):

```cpp
void CSceneLightDialog::OnCancel(void)
{
    CW3DViewDoc *pCDoc = ::GetCurrentDocument();
    if (pCDoc && pCDoc->GetScene()) {
        Vector3 diffuse;
        diffuse.X = float(m_InitialRedDiffuse) / 100.0f;
        diffuse.Y = float(m_InitialGreenDiffuse) / 100.0f;
        diffuse.Z = float(m_InitialBlueDiffuse) / 100.0f;
        
        Vector3 specular;
        specular.X = float(m_InitialRedSpecular) / 100.0f;
        specular.Y = float(m_InitialGreenSpecular) / 100.0f;
        specular.Z = float(m_InitialBlueSpecular) / 100.0f;
        
        // Restore the scene light's color
        pCDoc->GetSceneLight()->Set_Diffuse(diffuse);
        pCDoc->GetSceneLight()->Set_Specular(specular);
        
        // Restore intensity, attenuation, and distance
        pCDoc->GetSceneLight()->Set_Intensity(m_InitialIntensity);
        pCDoc->GetSceneLight()->Set_Far_Attenuation_Range(m_InitialStartAtten, m_InitialEndAtten);
        pCDoc->GetSceneLight()->Set_Flag(LightClass::FAR_ATTENUATION, m_InitialAttenOn);
        Update_Distance(m_InitialDistance);
    }
    
    CDialog::OnCancel();
}
```

### Update_Light Helper (Lines 284-336):

```cpp
void CSceneLightDialog::Update_Light(const Vector3& color)
{
    CW3DViewDoc *pCDoc = ::GetCurrentDocument();
    if (pCDoc && pCDoc->GetScene()) {
        // Determine which channel to update based on radio buttons
        if (SendDlgItemMessage(IDC_CHANNEL_DIFFUSE_RADIO, BM_GETCHECK)) {
            // Update diffuse only
            pCDoc->GetSceneLight()->Set_Diffuse(color);
        } else if (SendDlgItemMessage(IDC_CHANNEL_SPECULAR_RADIO, BM_GETCHECK)) {
            // Update specular only
            pCDoc->GetSceneLight()->Set_Specular(color);
        } else {
            // Update both (default)
            pCDoc->GetSceneLight()->Set_Diffuse(color);
            pCDoc->GetSceneLight()->Set_Specular(color);
        }
    }
}
```

### Update_Distance Helper (Lines ~338-360):

```cpp
void CSceneLightDialog::Update_Distance(float distance)
{
    CW3DViewDoc *pCDoc = ::GetCurrentDocument();
    if (pCDoc && pCDoc->GetScene()) {
        RenderObjClass *render_obj = pCDoc->GetDisplayedObject();
        if (render_obj != nullptr) {
            // Get object position
            Vector3 obj_pos = render_obj->Get_Position();
            
            // Get current light position direction (normalized)
            Vector3 light_pos = pCDoc->GetSceneLight()->Get_Position();
            Vector3 direction = light_pos - obj_pos;
            direction.Normalize();
            
            // Calculate new light position at specified distance
            Vector3 new_pos = obj_pos + (direction * distance);
            pCDoc->GetSceneLight()->Set_Position(new_pos);
        }
    }
}
```

---

## Implementation Requirements

### Member Variables Needed:

```cpp
// For cancel restore
int m_InitialRedDiffuse;
int m_InitialGreenDiffuse;
int m_InitialBlueDiffuse;
int m_InitialRedSpecular;
int m_InitialGreenSpecular;
int m_InitialBlueSpecular;
float m_InitialIntensity;
float m_InitialDistance;
float m_InitialStartAtten;
float m_InitialEndAtten;
bool m_InitialAttenOn;

// For channel tracking
enum Channel { CHANNEL_BOTH, CHANNEL_DIFFUSE, CHANNEL_SPECULAR };
Channel m_CurrentChannel;
```

### Helper Methods Needed:

```cpp
void Update_Light(const Vector3& color);
void Update_Distance(float distance);
void Update_Attenuation();
void Set_Color_Control_State(const Vector3& color);
```

### Document Methods Required:

**Already Exist**:
- ✅ `LightClass* GetSceneLight()` - Already in w3dviewdoc_wx.h:157

**Need to Check**:
- ❓ LightClass methods (Get_Diffuse, Set_Diffuse, Get_Specular, Set_Specular, etc.)
- ❓ Do we need wrapper methods or can we access LightClass directly?

---

## Wrapper Methods Decision

### Question: Do we need wrappers for LightClass like we did for ViewerSceneClass?

**LightAmbient Pattern**:
- Problem: Including ViewerScene.h caused template errors
- Solution: Added GetAmbientLight()/SetAmbientLight() wrappers to W3DViewDoc
- Benefit: Dialogs don't include ViewerScene.h

**LightScene Consideration**:
- GetSceneLight() already exists and returns LightClass*
- Need to check if including light.h (LightClass) causes template errors
- If YES: Need wrappers for all LightClass methods
- If NO: Can access light->Set_Diffuse(), light->Set_Specular(), etc. directly

**Recommendation**: 
1. Try including light.h in dialog
2. If template errors occur, add wrapper methods to W3DViewDoc
3. Wrapper methods would be:
   ```cpp
   void SetSceneLightDiffuse(const Vector3& color);
   void SetSceneLightSpecular(const Vector3& color);
   Vector3 GetSceneLightDiffuse() const;
   Vector3 GetSceneLightSpecular() const;
   float GetSceneLightIntensity() const;
   void SetSceneLightIntensity(float intensity);
   // etc.
   ```

---

## Implementation Strategy

### Phase 1: Investigate Header Includes
1. Try including light.h in LightSceneDialog_wx.cpp
2. Attempt compilation
3. If template errors: Add wrapper methods (like LightAmbient)
4. If no errors: Access light directly

### Phase 2: Implement Core Functionality
1. Add member variables for initial state
2. Implement OnInitDialog
   - Get scene light
   - Save initial diffuse/specular/intensity/attenuation/distance
   - Initialize sliders and controls
3. Implement OnHScroll
   - Handle intensity slider
   - Handle RGB sliders with grayscale logic
   - Call Update_Light helper
4. Implement helper methods
   - Update_Light (apply to diffuse/specular/both)
   - Update_Distance (reposition light)
   - Update_Attenuation

### Phase 3: Implement Cancel Restore
1. OnCancel restores all initial values:
   - Diffuse color
   - Specular color
   - Intensity
   - Attenuation range
   - Attenuation flag
   - Distance

### Phase 4: Implement Channel Selection
1. OnChannelBothRadio
2. OnChannelDiffuseRadio
3. OnChannelSpecularRadio
4. Each updates m_CurrentChannel and calls Set_Color_Control_State

### Phase 5: Implement Other Controls
1. OnGrayscaleCheck - sync all RGB sliders
2. OnAttenuationCheck - enable/disable attenuation controls

---

## Estimated Effort

**Complexity Factors**:
- Two color channels (diffuse + specular)
- Channel selection logic
- Distance/position calculations
- Attenuation controls
- Multiple helper methods

**Comparison**:
- BackgroundColor: 2-3 hours (simple RGB sliders)
- LightAmbient: 2-3 hours (RGB sliders + wrapper methods)
- **LightScene: 4-6 hours** (dual channels + distance + attenuation + helpers)

---

## Recommendation

Following Session 37's pattern classification:

**Classification**: Type 1 - Non-Functional Placeholder  
**Action**: DEFER to future session  
**Reason**: High complexity, needs careful implementation

**Next Steps** (For Future Session):
1. Investigate remaining TODO(MFC-Verify) dialogs first
2. Classify them as Type 1 or Type 2
3. Implement simpler Type 1 dialogs first
4. Save LightScene for when we have more confidence with the pattern

**Current Session**: Document complexity and move to next dialog investigation

---

## User Guidance Application

Following "Be careful before removing TODOs, we may even need to add more":

**Action Taken**:
- ✅ Investigated LightSceneDialog thoroughly
- ✅ Compared with MFC implementation
- ✅ Classified as Type 1 (non-functional)
- ✅ **ADDED comprehensive TODO analysis** (this document!)
- ✅ Documented complexity (higher than LightAmbient)
- ✅ Created implementation strategy for future session

**Result**: Did NOT blindly implement - documented complexity first!

This document serves as comprehensive TODOs explaining exactly what needs to be done when this dialog is implemented in a future session.
