/**
* @file CommandAllocator.cpp.
* @brief The CommandAllocator Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "CommandAllocator.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Direct3D12 {

    CommandAllocator::CommandAllocator(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void CommandAllocator::Create()
    {
        NEPTUNE_PROFILE_ZONE

        m_CommandAllocator.CreateCommandAllocator(GetContext().Get<IDevice>()->Handle(), GetCommandListType());

        DEBUGUTILS_SETOBJECTNAME(m_CommandAllocator, ToString())
    }

    D3D12_COMMAND_LIST_TYPE CommandAllocator::GetCommandListType() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (GetEInfrastructure())
		{
			case EInfrastructure::GraphicQueue:		return D3D12_COMMAND_LIST_TYPE_DIRECT;
			case EInfrastructure::ComputeQueue:     return D3D12_COMMAND_LIST_TYPE_COMPUTE;
			default: return D3D12_COMMAND_LIST_TYPE_DIRECT;
		}
    }
}

#endif