/**
* @file DeviceContext.cpp.
* @brief The DeviceContext Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "DeviceContext.h"
#include "DebugUtilsObject.h"

namespace Neptune::Direct3D11 {

    void DeviceContext::SetHandle(Unit::DeviceContext::Handle handle)
    {
        NEPTUNE_PROFILE_ZONE

        m_DeviceContext.SetHandle(handle);
        
        DEBUGUTILS_SETOBJECTNAME(m_DeviceContext, ToString())
    }

}

#endif