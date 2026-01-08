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

// TheSuperHackers @feature JohnsterID 08/01/2026 Graphics device factory implementation

#include "IGraphicsDevice.h"
#include "DX8/DX8Device.h"

// DX9 support compiled conditionally
#if RTS_USE_DIRECTX9
#include "DX9/DX9Device.h"
#endif

IGraphicsDevice* GraphicsDeviceFactory::Create_Device(bool use_dx9)
{
#if RTS_USE_DIRECTX9
    // DX9 support compiled in
    if (use_dx9) {
        return new DX9Device();
    }
    // Fall back to DX8
    return new DX8Device();
#else
    // Only DX8 support compiled in
    (void)use_dx9;  // Suppress unused parameter warning
    return new DX8Device();
#endif
}

void GraphicsDeviceFactory::Destroy_Device(IGraphicsDevice* device)
{
    delete device;
}

bool GraphicsDeviceFactory::Has_DX9_Support()
{
#if RTS_USE_DIRECTX9
    return true;
#else
    return false;
#endif
}

const char* GraphicsDeviceFactory::Get_API_Name(const IGraphicsDevice* device)
{
    if (device == nullptr) {
        return "Unknown";
    }
    
#if RTS_USE_DIRECTX9
    // Check if it's a DX9Device
    if (dynamic_cast<const DX9Device*>(device) != nullptr) {
        return "DirectX 9";
    }
#endif
    
    // Check if it's a DX8Device
    if (dynamic_cast<const DX8Device*>(device) != nullptr) {
        return "DirectX 8";
    }
    
    return "Unknown Device";
}
