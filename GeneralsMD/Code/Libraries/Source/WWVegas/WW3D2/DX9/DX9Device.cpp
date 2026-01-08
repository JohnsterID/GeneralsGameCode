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

// TheSuperHackers @feature JohnsterID 08/01/2026 DirectX 9 device implementation
// Based on OpenW3D PR #17: https://github.com/w3dhub/OpenW3D/pull/17

#include "DX9Device.h"
#include "../dx8caps.h"
#include "matrix4.h"
#include "vector3.h"

DX9Device::DX9Device()
    : m_d3d(nullptr)
    , m_d3dDevice(nullptr)
    , m_caps(nullptr)
    , m_initialized(false)
    , m_displayWidth(0)
    , m_displayHeight(0)
    , m_displayBits(0)
    , m_windowed(true)
{
}

DX9Device::~DX9Device()
{
    Shutdown();
}

bool DX9Device::Init(bool lite)
{
    // TODO: Implement DX9 initialization
    // For now, stub implementation
    m_initialized = false;
    return m_initialized;
}

void DX9Device::Shutdown()
{
    if (m_initialized) {
        // TODO: Implement DX9 shutdown
        m_d3dDevice = nullptr;
        m_d3d = nullptr;
        m_initialized = false;
    }
}

bool DX9Device::Is_Initialized() const
{
    return m_initialized;
}

void* DX9Device::Get_D3D_Device()
{
    return m_d3dDevice;
}

void* DX9Device::Get_D3D_Interface()
{
    return m_d3d;
}

const DX8Caps* DX9Device::Get_Caps() const
{
    return m_caps;
}

unsigned DX9Device::Get_Render_Device_Count() const
{
    // TODO: Implement
    return 0;
}

const RenderDeviceDescClass* DX9Device::Get_Render_Device_Desc(unsigned index) const
{
    // TODO: Implement
    return nullptr;
}

bool DX9Device::Set_Render_Device(unsigned index)
{
    // TODO: Implement
    return false;
}

bool DX9Device::Set_Display_Mode(unsigned width, unsigned height, unsigned bits, bool windowed)
{
    m_displayWidth = width;
    m_displayHeight = height;
    m_displayBits = bits;
    m_windowed = windowed;
    
    // TODO: Implement DX9 display mode setting
    return false;
}

void DX9Device::Get_Display_Mode(unsigned& width, unsigned& height, unsigned& bits, bool& windowed) const
{
    width = m_displayWidth;
    height = m_displayHeight;
    bits = m_displayBits;
    windowed = m_windowed;
}

void DX9Device::Begin_Scene()
{
    if (m_d3dDevice) {
        m_d3dDevice->BeginScene();
    }
}

void DX9Device::End_Scene()
{
    if (m_d3dDevice) {
        m_d3dDevice->EndScene();
    }
}

void DX9Device::Present()
{
    if (m_d3dDevice) {
        m_d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
    }
}

void DX9Device::Clear(bool clear_color, bool clear_depth, const Vector3* color)
{
    if (!m_d3dDevice) return;
    
    DWORD flags = 0;
    if (clear_color) flags |= D3DCLEAR_TARGET;
    if (clear_depth) flags |= D3DCLEAR_ZBUFFER;
    
    D3DCOLOR clearColor = D3DCOLOR_XRGB(0, 0, 0);
    if (color) {
        clearColor = D3DCOLOR_XRGB(
            (int)(color->X * 255.0f),
            (int)(color->Y * 255.0f),
            (int)(color->Z * 255.0f)
        );
    }
    
    m_d3dDevice->Clear(0, nullptr, flags, clearColor, 1.0f, 0);
}

void DX9Device::Set_Texture(unsigned stage, void* texture)
{
    if (m_d3dDevice) {
        IDirect3DBaseTexture9* dx9Texture = static_cast<IDirect3DBaseTexture9*>(texture);
        m_d3dDevice->SetTexture(stage, dx9Texture);
    }
}

void DX9Device::Set_Transform(unsigned transform_type, const Matrix4& matrix)
{
    if (m_d3dDevice) {
        D3DMATRIX d3dMatrix;
        memcpy(&d3dMatrix, &matrix, sizeof(D3DMATRIX));
        m_d3dDevice->SetTransform((D3DTRANSFORMSTATETYPE)transform_type, &d3dMatrix);
    }
}

void DX9Device::Get_Transform(unsigned transform_type, Matrix4& matrix) const
{
    if (m_d3dDevice) {
        D3DMATRIX d3dMatrix;
        m_d3dDevice->GetTransform((D3DTRANSFORMSTATETYPE)transform_type, &d3dMatrix);
        memcpy(&matrix, &d3dMatrix, sizeof(Matrix4));
    }
}

void DX9Device::Set_Light(unsigned index, const void* light)
{
    if (m_d3dDevice && light) {
        // Note: Using native D3DLIGHT9 type - NO TYPEDEFS!
        const D3DLIGHT9* dx9Light = static_cast<const D3DLIGHT9*>(light);
        m_d3dDevice->SetLight(index, dx9Light);
    }
}

void DX9Device::Enable_Light(unsigned index, bool enable)
{
    if (m_d3dDevice) {
        m_d3dDevice->LightEnable(index, enable ? TRUE : FALSE);
    }
}

void DX9Device::Set_Material(const void* material)
{
    if (m_d3dDevice && material) {
        // Note: Using native D3DMATERIAL9 type - NO TYPEDEFS!
        const D3DMATERIAL9* dx9Material = static_cast<const D3DMATERIAL9*>(material);
        m_d3dDevice->SetMaterial(dx9Material);
    }
}

void DX9Device::Set_Viewport(const void* viewport)
{
    if (m_d3dDevice && viewport) {
        // Note: Using native D3DVIEWPORT9 type - NO TYPEDEFS!
        const D3DVIEWPORT9* dx9Viewport = static_cast<const D3DVIEWPORT9*>(viewport);
        m_d3dDevice->SetViewport(dx9Viewport);
    }
}

void DX9Device::Get_Viewport(void* viewport) const
{
    if (m_d3dDevice && viewport) {
        D3DVIEWPORT9* dx9Viewport = static_cast<D3DVIEWPORT9*>(viewport);
        m_d3dDevice->GetViewport(dx9Viewport);
    }
}

void DX9Device::Set_Render_State(unsigned state, unsigned value)
{
    if (m_d3dDevice) {
        m_d3dDevice->SetRenderState((D3DRENDERSTATETYPE)state, value);
    }
}

unsigned DX9Device::Get_Render_State(unsigned state) const
{
    if (m_d3dDevice) {
        DWORD value = 0;
        m_d3dDevice->GetRenderState((D3DRENDERSTATETYPE)state, &value);
        return value;
    }
    return 0;
}

void DX9Device::Set_Texture_Stage_State(unsigned stage, unsigned state, unsigned value)
{
    if (m_d3dDevice) {
        m_d3dDevice->SetTextureStageState(stage, (D3DTEXTURESTAGESTATETYPE)state, value);
    }
}

void DX9Device::Set_Stream_Source(unsigned stream, void* buffer, unsigned stride)
{
    if (m_d3dDevice && buffer) {
        IDirect3DVertexBuffer9* vb = static_cast<IDirect3DVertexBuffer9*>(buffer);
        // Note: DX9 API difference - no base offset parameter
        m_d3dDevice->SetStreamSource(stream, vb, 0, stride);
    }
}

void DX9Device::Set_Indices(void* buffer, unsigned base_vertex_index)
{
    if (m_d3dDevice && buffer) {
        IDirect3DIndexBuffer9* ib = static_cast<IDirect3DIndexBuffer9*>(buffer);
        // Note: DX9 API difference - SetIndices doesn't take base vertex index
        m_d3dDevice->SetIndices(ib);
        // Base vertex index handled in DrawIndexedPrimitive call
    }
}

void DX9Device::Draw_Primitive(unsigned primitive_type, unsigned start_vertex, unsigned primitive_count)
{
    if (m_d3dDevice) {
        m_d3dDevice->DrawPrimitive((D3DPRIMITIVETYPE)primitive_type, start_vertex, primitive_count);
    }
}

void DX9Device::Draw_Indexed_Primitive(unsigned primitive_type, unsigned min_index, unsigned num_vertices,
                                      unsigned start_index, unsigned primitive_count)
{
    if (m_d3dDevice) {
        // Note: DX9 API has different parameter order
        m_d3dDevice->DrawIndexedPrimitive(
            (D3DPRIMITIVETYPE)primitive_type,
            0,  // BaseVertexIndex
            min_index,
            num_vertices,
            start_index,
            primitive_count
        );
    }
}

void DX9Device::Reset_Statistics()
{
    // TODO: Implement statistics tracking for DX9
}
