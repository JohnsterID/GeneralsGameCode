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

// TheSuperHackers: Compatibility layer for W3D engine dependencies

#pragma once

#include <string>

// Phase 3A.2: Include engine types needed by dialog headers
// CRITICAL: Undefine CString before including engine headers
#ifdef CString
#undef CString
#endif

#include "vector2.h"
#include "vector3.h"

// Redefine CString for wxWidgets compatibility
#define CString wxString

// Forward declarations for other engine types
class SphereClass;
class ViewerSceneClass;
class ViewerAssetMgrClass;
class AssetInfoClass;
class RenderObjClass;
class CameraClass;
class ParticleEmitterClass;

// ============================================================================
// Phase 3A: Helper Functions for Dialog Integration
// ============================================================================

// Forward declarations
class W3DViewDoc;
class wxTextCtrl;
class wxSpinCtrl;

// Document access helper for wxWidgets dialogs
// Note: MFC code uses GetCurrentDocument() which returns CW3DViewDoc*
// wxWidgets dialogs should use this function which returns W3DViewDoc*
W3DViewDoc* GetCurrentDocument_wx();

// Control helper functions (wxWidgets equivalents of MFC helpers)
float GetDlgItemFloat(wxTextCtrl* ctrl);
void SetDlgItemFloat(wxTextCtrl* ctrl, float value);
void Initialize_Spinner(wxSpinCtrl* spin, float value, float min, float max);

// ============================================================================
// Phase 4: Engine Integration Macros (for .cpp files)
// ============================================================================

// Common engine macros that may not be available when including engine headers
// from wxWidgets context. These match MFC patterns.

// Reference-counted pointer release (from refcount.h)
// MFC usage: REF_PTR_RELEASE(SoundObj);
#ifndef REF_PTR_RELEASE
#define REF_PTR_RELEASE(x)  { if (x) x->Release_Ref(); x = nullptr; }
#endif

// ============================================================================
// Pattern for Engine Integration in Dialog .cpp Files
// ============================================================================
//
// When including engine headers in dialog .cpp files, use this pattern:
//
//   #include "YourDialog_wx.h"
//   #include <wx/...>  // All wxWidgets includes first
//
//   // Phase 4: Engine integration includes
//   #ifdef CString
//   #undef CString
//   #endif
//
//   #include "engine_header1.h"
//   #include "engine_header2.h"
//   // ... more engine includes ...
//
//   #define CString wxString  // Restore after engine includes
//
//   // Rest of implementation...
//
// The #undef/#define pattern is necessary because:
// 1. wxWidgets needs #define CString wxString for MFC compatibility
// 2. Engine headers may define/use CString differently
// 3. We must undefine before engine includes, redefine after
//
// ============================================================================
