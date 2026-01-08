/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 TheSuperHackers
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

// TheSuperHackers @feature JohnsterID 08/01/2026 DirectX 8 device implementation

#pragma once

#include "../IGraphicsDevice.h"
#include <d3d8.h>

class DX8Caps;
class RenderDeviceDescClass;
class Matrix4;
class Vector3;

/**
 * DirectX 8 implementation of the graphics device interface.
 * 
 * This class uses native DirectX 8 types (D3DLIGHT8, D3DCAPS8, etc.)
 * without any conditional compilation or typedefs.
 */
class DX8Device : public IGraphicsDevice
{
public:
    DX8Device();
    virtual ~DX8Device();

    // IGraphicsDevice implementation
    virtual bool Init(bool lite = false) override;
    virtual void Shutdown() override;
    virtual bool Is_Initialized() const override;

    virtual void* Get_D3D_Device() override;
    virtual void* Get_D3D_Interface() override;
    
    virtual const DX8Caps* Get_Caps() const override;
    
    virtual unsigned Get_Render_Device_Count() const override;
    virtual const RenderDeviceDescClass* Get_Render_Device_Desc(unsigned index) const override;
    virtual bool Set_Render_Device(unsigned index) override;
    
    virtual bool Set_Display_Mode(unsigned width, unsigned height, unsigned bits, bool windowed) override;
    virtual void Get_Display_Mode(unsigned& width, unsigned& height, unsigned& bits, bool& windowed) const override;
    
    virtual void Begin_Scene() override;
    virtual void End_Scene() override;
    virtual void Present() override;
    virtual void Clear(bool clear_color, bool clear_depth, const Vector3* color = nullptr) override;
    
    virtual void Set_Texture(unsigned stage, void* texture) override;
    
    virtual void Set_Transform(unsigned transform_type, const Matrix4& matrix) override;
    virtual void Get_Transform(unsigned transform_type, Matrix4& matrix) const override;
    
    virtual void Set_Light(unsigned index, const void* light) override;
    virtual void Enable_Light(unsigned index, bool enable) override;
    
    virtual void Set_Material(const void* material) override;
    
    virtual void Set_Viewport(const void* viewport) override;
    virtual void Get_Viewport(void* viewport) const override;
    
    virtual void Set_Render_State(unsigned state, unsigned value) override;
    virtual unsigned Get_Render_State(unsigned state) const override;
    
    virtual void Set_Texture_Stage_State(unsigned stage, unsigned state, unsigned value) override;
    
    virtual void Set_Stream_Source(unsigned stream, void* buffer, unsigned stride) override;
    virtual void Set_Indices(void* buffer, unsigned base_vertex_index) override;
    
    virtual void Draw_Primitive(unsigned primitive_type, unsigned start_vertex, unsigned primitive_count) override;
    virtual void Draw_Indexed_Primitive(unsigned primitive_type, unsigned min_index, unsigned num_vertices, 
                                       unsigned start_index, unsigned primitive_count) override;
    
    virtual void Reset_Statistics() override;

    // DX8-specific accessors
    IDirect3DDevice8* Get_D3D8_Device() const { return m_d3dDevice; }
    IDirect3D8* Get_D3D8_Interface() const { return m_d3d; }

private:
    IDirect3D8* m_d3d;
    IDirect3DDevice8* m_d3dDevice;
    DX8Caps* m_caps;
    bool m_initialized;
    
    unsigned m_displayWidth;
    unsigned m_displayHeight;
    unsigned m_displayBits;
    bool m_windowed;
    
    // Helper methods
    bool Init_D3D8(bool lite);
    void Shutdown_D3D8();
};
