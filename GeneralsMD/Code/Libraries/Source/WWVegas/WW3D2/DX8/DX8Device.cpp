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

#include "DX8Device.h"
#include "../dx8caps.h"
#include "../dx8wrapper.h"  // Temporary during transition
#include "matrix4.h"
#include "vector3.h"

DX8Device::DX8Device()
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

DX8Device::~DX8Device()
{
    Shutdown();
}

bool DX8Device::Init(bool lite)
{
    // Temporary: Delegate to existing DX8Wrapper during transition
    // TODO: Move implementation here once callers are updated
    m_initialized = DX8Wrapper::Init(lite);
    if (m_initialized) {
        m_d3dDevice = DX8Wrapper::_Get_D3D_Device8();
        m_d3d = DX8Wrapper::_Get_D3D8();
    }
    return m_initialized;
}

void DX8Device::Shutdown()
{
    if (m_initialized) {
        // Temporary: Delegate to existing DX8Wrapper
        DX8Wrapper::Shutdown();
        m_d3dDevice = nullptr;
        m_d3d = nullptr;
        m_initialized = false;
    }
}

bool DX8Device::Is_Initialized() const
{
    return m_initialized;
}

void* DX8Device::Get_D3D_Device()
{
    return m_d3dDevice;
}

void* DX8Device::Get_D3D_Interface()
{
    return m_d3d;
}

const DX8Caps* DX8Device::Get_Caps() const
{
    // Temporary: Delegate to existing DX8Wrapper
    return DX8Wrapper::Get_Current_Caps();
}

unsigned DX8Device::Get_Render_Device_Count() const
{
    return DX8Wrapper::Get_Num_Render_Devices();
}

const RenderDeviceDescClass* DX8Device::Get_Render_Device_Desc(unsigned index) const
{
    return &DX8Wrapper::Get_Render_Device_Desc(index);
}

bool DX8Device::Set_Render_Device(unsigned index)
{
    return DX8Wrapper::Set_Device(index);
}

bool DX8Device::Set_Display_Mode(unsigned width, unsigned height, unsigned bits, bool windowed)
{
    m_displayWidth = width;
    m_displayHeight = height;
    m_displayBits = bits;
    m_windowed = windowed;
    
    // Temporary: Delegate to existing DX8Wrapper
    return DX8Wrapper::Set_Display_Mode(width, height, bits, windowed, 0, 0, false);
}

void DX8Device::Get_Display_Mode(unsigned& width, unsigned& height, unsigned& bits, bool& windowed) const
{
    width = m_displayWidth;
    height = m_displayHeight;
    bits = m_displayBits;
    windowed = m_windowed;
}

void DX8Device::Begin_Scene()
{
    if (m_d3dDevice) {
        m_d3dDevice->BeginScene();
    }
}

void DX8Device::End_Scene()
{
    if (m_d3dDevice) {
        m_d3dDevice->EndScene();
    }
}

void DX8Device::Present()
{
    if (m_d3dDevice) {
        m_d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
    }
}

void DX8Device::Clear(bool clear_color, bool clear_depth, const Vector3* color)
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

void DX8Device::Set_Texture(unsigned stage, void* texture)
{
    if (m_d3dDevice) {
        IDirect3DBaseTexture8* dx8Texture = static_cast<IDirect3DBaseTexture8*>(texture);
        m_d3dDevice->SetTexture(stage, dx8Texture);
    }
}

void DX8Device::Set_Transform(unsigned transform_type, const Matrix4& matrix)
{
    if (m_d3dDevice) {
        D3DMATRIX d3dMatrix;
        memcpy(&d3dMatrix, &matrix, sizeof(D3DMATRIX));
        m_d3dDevice->SetTransform((D3DTRANSFORMSTATETYPE)transform_type, &d3dMatrix);
    }
}

void DX8Device::Get_Transform(unsigned transform_type, Matrix4& matrix) const
{
    if (m_d3dDevice) {
        D3DMATRIX d3dMatrix;
        m_d3dDevice->GetTransform((D3DTRANSFORMSTATETYPE)transform_type, &d3dMatrix);
        memcpy(&matrix, &d3dMatrix, sizeof(Matrix4));
    }
}

void DX8Device::Set_Light(unsigned index, const void* light)
{
    if (m_d3dDevice && light) {
        const D3DLIGHT8* dx8Light = static_cast<const D3DLIGHT8*>(light);
        m_d3dDevice->SetLight(index, dx8Light);
    }
}

void DX8Device::Enable_Light(unsigned index, bool enable)
{
    if (m_d3dDevice) {
        m_d3dDevice->LightEnable(index, enable ? TRUE : FALSE);
    }
}

void DX8Device::Set_Material(const void* material)
{
    if (m_d3dDevice && material) {
        const D3DMATERIAL8* dx8Material = static_cast<const D3DMATERIAL8*>(material);
        m_d3dDevice->SetMaterial(dx8Material);
    }
}

void DX8Device::Set_Viewport(const void* viewport)
{
    if (m_d3dDevice && viewport) {
        const D3DVIEWPORT8* dx8Viewport = static_cast<const D3DVIEWPORT8*>(viewport);
        m_d3dDevice->SetViewport(dx8Viewport);
    }
}

void DX8Device::Get_Viewport(void* viewport) const
{
    if (m_d3dDevice && viewport) {
        D3DVIEWPORT8* dx8Viewport = static_cast<D3DVIEWPORT8*>(viewport);
        m_d3dDevice->GetViewport(dx8Viewport);
    }
}

void DX8Device::Set_Render_State(unsigned state, unsigned value)
{
    if (m_d3dDevice) {
        m_d3dDevice->SetRenderState((D3DRENDERSTATETYPE)state, value);
    }
}

unsigned DX8Device::Get_Render_State(unsigned state) const
{
    if (m_d3dDevice) {
        DWORD value = 0;
        m_d3dDevice->GetRenderState((D3DRENDERSTATETYPE)state, &value);
        return value;
    }
    return 0;
}

void DX8Device::Set_Texture_Stage_State(unsigned stage, unsigned state, unsigned value)
{
    if (m_d3dDevice) {
        m_d3dDevice->SetTextureStageState(stage, (D3DTEXTURESTAGESTATETYPE)state, value);
    }
}

void DX8Device::Set_Stream_Source(unsigned stream, void* buffer, unsigned stride)
{
    if (m_d3dDevice && buffer) {
        IDirect3DVertexBuffer8* vb = static_cast<IDirect3DVertexBuffer8*>(buffer);
        m_d3dDevice->SetStreamSource(stream, vb, stride);
    }
}

void DX8Device::Set_Indices(void* buffer, unsigned base_vertex_index)
{
    if (m_d3dDevice && buffer) {
        IDirect3DIndexBuffer8* ib = static_cast<IDirect3DIndexBuffer8*>(buffer);
        m_d3dDevice->SetIndices(ib, base_vertex_index);
    }
}

void DX8Device::Draw_Primitive(unsigned primitive_type, unsigned start_vertex, unsigned primitive_count)
{
    if (m_d3dDevice) {
        m_d3dDevice->DrawPrimitive((D3DPRIMITIVETYPE)primitive_type, start_vertex, primitive_count);
    }
}

void DX8Device::Draw_Indexed_Primitive(unsigned primitive_type, unsigned min_index, unsigned num_vertices,
                                      unsigned start_index, unsigned primitive_count)
{
    if (m_d3dDevice) {
        m_d3dDevice->DrawIndexedPrimitive(
            (D3DPRIMITIVETYPE)primitive_type,
            min_index,
            num_vertices,
            start_index,
            primitive_count
        );
    }
}

void DX8Device::Reset_Statistics()
{
    // Temporary: Delegate to existing system
    DX8Wrapper::Reset_Statistics();
}
