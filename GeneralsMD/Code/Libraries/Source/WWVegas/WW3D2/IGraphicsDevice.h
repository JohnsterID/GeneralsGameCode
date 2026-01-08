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

// TheSuperHackers @feature JohnsterID 08/01/2026 Graphics device abstraction for DX8/DX9 support
// Based on architectural guidance from Mauller (PR #1, Sept 14, 2025)

#pragma once

#include "always.h"

class RenderDeviceDescClass;
class DX8Caps;
class Matrix4;
class Vector3;

/**
 * Abstract interface for graphics device implementations.
 * 
 * This interface allows runtime selection between DirectX 8, DirectX 9,
 * and future graphics APIs (DX11, Vulkan, OpenGL) without conditional
 * compilation in implementation files.
 * 
 * Each implementation (DX8Device, DX9Device) uses its native types
 * internally and handles the conversion through this interface.
 */
class IGraphicsDevice
{
public:
    virtual ~IGraphicsDevice() {}

    // Initialization & Lifecycle
    virtual bool Init(bool lite = false) = 0;
    virtual void Shutdown() = 0;
    virtual bool Is_Initialized() const = 0;

    // Device Access (for legacy code during transition)
    virtual void* Get_D3D_Device() = 0;      // Returns IDirect3DDevice8/9*
    virtual void* Get_D3D_Interface() = 0;   // Returns IDirect3D8/9*
    
    // Capabilities
    virtual const DX8Caps* Get_Caps() const = 0;
    
    // Device enumeration & selection
    virtual unsigned Get_Render_Device_Count() const = 0;
    virtual const RenderDeviceDescClass* Get_Render_Device_Desc(unsigned index) const = 0;
    virtual bool Set_Render_Device(unsigned index) = 0;
    
    // Display mode
    virtual bool Set_Display_Mode(unsigned width, unsigned height, unsigned bits, bool windowed) = 0;
    virtual void Get_Display_Mode(unsigned& width, unsigned& height, unsigned& bits, bool& windowed) const = 0;
    
    // Frame management
    virtual void Begin_Scene() = 0;
    virtual void End_Scene() = 0;
    virtual void Present() = 0;
    virtual void Clear(bool clear_color, bool clear_depth, const Vector3* color = nullptr) = 0;
    
    // Texture management
    virtual void Set_Texture(unsigned stage, void* texture) = 0;  // texture is IDirect3DBaseTexture8/9*
    
    // Transform & state
    virtual void Set_Transform(unsigned transform_type, const Matrix4& matrix) = 0;
    virtual void Get_Transform(unsigned transform_type, Matrix4& matrix) const = 0;
    
    // Lighting
    virtual void Set_Light(unsigned index, const void* light) = 0;  // light is D3DLIGHT8/9*
    virtual void Enable_Light(unsigned index, bool enable) = 0;
    
    // Material
    virtual void Set_Material(const void* material) = 0;  // material is D3DMATERIAL8/9*
    
    // Viewport
    virtual void Set_Viewport(const void* viewport) = 0;  // viewport is D3DVIEWPORT8/9*
    virtual void Get_Viewport(void* viewport) const = 0;
    
    // Render state
    virtual void Set_Render_State(unsigned state, unsigned value) = 0;
    virtual unsigned Get_Render_State(unsigned state) const = 0;
    
    // Texture stage state
    virtual void Set_Texture_Stage_State(unsigned stage, unsigned state, unsigned value) = 0;
    
    // Vertex/Index buffers (for legacy code - will be refactored later)
    virtual void Set_Stream_Source(unsigned stream, void* buffer, unsigned stride) = 0;
    virtual void Set_Indices(void* buffer, unsigned base_vertex_index) = 0;
    
    // Draw commands
    virtual void Draw_Primitive(unsigned primitive_type, unsigned start_vertex, unsigned primitive_count) = 0;
    virtual void Draw_Indexed_Primitive(unsigned primitive_type, unsigned min_index, unsigned num_vertices, 
                                       unsigned start_index, unsigned primitive_count) = 0;
    
    // Statistics
    virtual void Reset_Statistics() = 0;
};

/**
 * Factory for creating graphics device instances.
 * 
 * The factory creates the appropriate device based on compile-time
 * configuration (RTS_USE_DIRECTX9) and potentially runtime selection.
 */
class GraphicsDeviceFactory
{
public:
    /**
     * Create a graphics device instance.
     * 
     * @param use_dx9 Request DirectX 9 if available (only works if compiled with RTS_USE_DIRECTX9)
     * @return Pointer to graphics device (caller must delete)
     */
    static IGraphicsDevice* Create_Device(bool use_dx9 = false);
    
    /**
     * Destroy a graphics device instance.
     * 
     * @param device Device to destroy (can be nullptr)
     */
    static void Destroy_Device(IGraphicsDevice* device);
    
    /**
     * Check if DirectX 9 support was compiled in.
     * 
     * @return true if RTS_USE_DIRECTX9 was defined during compilation
     */
    static bool Has_DX9_Support();
    
    /**
     * Get human-readable name of the graphics API.
     * 
     * @param device Device instance
     * @return "DirectX 8", "DirectX 9", etc.
     */
    static const char* Get_API_Name(const IGraphicsDevice* device);
};
