/**
* @file Queue.cpp.
* @brief The Queue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Queue.h"
#include "DebugUtilsObject.h"
#include "Device.h"
#include "Render/Backend/Direct3D12/Unit/Fence.h"

namespace Neptune::Direct3D12 {

    Queue::Queue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Queue::Create()
    {
        NEPTUNE_PROFILE_ZONE

        D3D12_COMMAND_QUEUE_DESC          desc{};
		desc.Flags                      = D3D12_COMMAND_QUEUE_FLAG_NONE;
		desc.NodeMask                   = 0;
		desc.Priority                   = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		desc.Type                       = GetCommandListType();

        m_Queue.CreateCommandQueue(GetContext().Get<IDevice>()->Handle(), desc);
        
        DEBUGUTILS_SETOBJECTNAME(m_Queue, ToString())
    }

    void Queue::Submit(D3D12GraphicsCommandList commandList, const SP<Unit::Fence>& fence) const
    {
        NEPTUNE_PROFILE_ZONE

        ID3D12CommandList* const handle =  commandList;
        
        m_Queue.GetHandle()->ExecuteCommandLists(1, &handle);
        
        m_Queue.GetHandle()->Signal(fence->GetHandle(), fence->IncreaseValue());
    }

    D3D12_COMMAND_LIST_TYPE Queue::GetCommandListType() const
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