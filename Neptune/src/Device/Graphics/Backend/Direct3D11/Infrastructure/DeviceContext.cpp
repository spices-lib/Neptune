/**
* @file DeviceContext.cpp.
* @brief The DeviceContext Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D11

#include "DeviceContext.h"
#include "DebugUtilsObject.h"
#include "Device/Graphics/Backend/Direct3D11/Unit/Fence.h"

namespace Neptune::Direct3D11 {

    void DeviceContext::SetHandle(Unit::DeviceContext::Handle handle)
    {
        NEPTUNE_PROFILE_ZONE

        m_DeviceContext.SetHandle(handle);
        
        DEBUGUTILS_SETOBJECTNAME(m_DeviceContext, ToString())
    }

    void DeviceContext::Signal(const SP<Unit::Fence>& fence) const
    {
        NEPTUNE_PROFILE_ZONE

        m_DeviceContext.GetHandle()->Signal(fence->GetHandle(), fence->GetNextWaitValue());
    }

}

#endif