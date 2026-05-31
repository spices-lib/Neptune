/**
* @file CommandList.cpp.
* @brief The CommandList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "CommandList.h"
#include "GPURuntime/Graphics/Backend/Direct3D11/Infrastructure/DebugUtilsObject.h"
#include "GPURuntime/Graphics/Backend/Direct3D11/Infrastructure/Device.h"

namespace Neptune::Direct3D11::Resource {

    void CommandList::CreateDeviceContext()
    {
        NEPTUNE_PROFILE_ZONE

        ID3D11DeviceContext* baseContext;

        GetContext().Get<IDevice>()->Handle()->CreateDeferredContext(0, &baseContext);

        m_Context.SetHandle(static_cast<Unit::DeviceContext::Handle>(baseContext));
        
        DEBUGUTILS_SETOBJECTNAME(m_Context, "Deferred Device Context")
    }

    void CommandList::Finish()
    {
        NEPTUNE_PROFILE_ZONE

        Unit::CommandList::Handle handle;

        m_Context.GetHandle()->FinishCommandList(FALSE, &handle);

        m_CommandList = CreateUP<Unit::CommandList>();

        m_CommandList->SetHandle(handle);
        
        DEBUGUTILS_SETOBJECTNAME(*m_CommandList, "CommandList")
    }
}

#endif