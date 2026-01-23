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

// Stub classes for W3D engine types when full engine is not available
// These allow compilation of the wxWidgets UI without requiring the full W3D engine

#ifndef USE_FULL_W3D_ENGINE

// Basic math types
class Vector2
{
public:
    Vector2() : X(0), Y(0) {}
    Vector2(float _x, float _y) : X(_x), Y(_y) {}
    float X, Y;
};

class Vector3
{
public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    float x, y, z;
};

class SphereClass
{
public:
    SphereClass() : radius(0) {}
    Vector3 center;
    float radius;
};

class CameraClass
{
public:
    CameraClass() {}
    virtual ~CameraClass() {}
    
    virtual void Set_Position(const Vector3& pos) {}
    virtual Vector3 Get_Position() const { return Vector3(); }
};

class RenderObjClass
{
public:
    RenderObjClass() {}
    virtual ~RenderObjClass() {}
    
    virtual void Render() {}
    virtual const char* Get_Name() const { return ""; }
};

class ViewerSceneClass
{
public:
    ViewerSceneClass() {}
    virtual ~ViewerSceneClass() {}
    
    virtual void Add_Render_Object(RenderObjClass* obj) {}
    virtual void Remove_Render_Object(RenderObjClass* obj) {}
    virtual void Render() {}
};

class AssetInfoClass
{
public:
    AssetInfoClass() : m_renderObj(nullptr) {}
    virtual ~AssetInfoClass() { delete m_renderObj; }
    
    const char* Get_Name() const { return m_name.c_str(); }
    void Set_Name(const char* name) { m_name = name; }
    
    RenderObjClass* Get_Render_Obj() { return m_renderObj; }
    void Set_Render_Obj(RenderObjClass* obj) { m_renderObj = obj; }
    
private:
    std::string m_name;
    RenderObjClass* m_renderObj;
};

class WW3DAssetManager
{
public:
    WW3DAssetManager() {}
    virtual ~WW3DAssetManager() {}
    
    virtual AssetInfoClass* Load_W3D_Asset(const char* filename) { return nullptr; }
    virtual int Get_Asset_Count() const { return 0; }
    virtual AssetInfoClass* Get_Asset_Info(int index) { return nullptr; }
};

// Stub for ViewerAssetMgrClass
class ViewerAssetMgrClass : public WW3DAssetManager
{
public:
    ViewerAssetMgrClass() {}
    virtual ~ViewerAssetMgrClass() {}
};

#else
// When using full W3D engine, include the real headers
#include "ViewerScene.h"
#include "ViewerAssetMgr.h"
#include "AssetInfo.h"
#endif // USE_FULL_W3D_ENGINE
