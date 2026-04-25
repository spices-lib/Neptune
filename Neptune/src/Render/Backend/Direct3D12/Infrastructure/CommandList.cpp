/**
* @file CommandList.cpp.
* @brief The CommandList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "CommandList.h"
#include "CommandAllocator.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Direct3D12 {

    CommandList::CommandList(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void CommandList::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        for (uint32_t i = 0; i < count; ++i)
        {
            auto commandList = CreateSP<Unit::GraphicsCommandList>();

            commandList->CreateGraphicsCommandList(GetContext().Get<IDevice>()->Handle(), GetCommandAllocator(), GetCommandListType());

            m_CommandLists.emplace_back(commandList);

            DEBUGUTILS_SETOBJECTNAME(*commandList, ToString())
        }
    }

    const D3D12CommandAllocator& CommandList::GetCommandAllocator() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (GetEInfrastructure())
		{
			case EInfrastructure::GraphicCommandList:		return GetContext().Get<IGraphicCommandAllocator>()->Handle();
			case EInfrastructure::ComputeCommandList:       return GetContext().Get<IComputeCommandAllocator>()->Handle();
			default: return nullptr;
		}
    }

    D3D12_COMMAND_LIST_TYPE CommandList::GetCommandListType() const
    {
        NEPTUNE_PROFILE_ZONE

        switch (GetEInfrastructure())
		{
			case EInfrastructure::GraphicCommandList:		return D3D12_COMMAND_LIST_TYPE_DIRECT;
			case EInfrastructure::ComputeCommandList:       return D3D12_COMMAND_LIST_TYPE_COMPUTE;
			default: return D3D12_COMMAND_LIST_TYPE_DIRECT;
		}
    }

    void CommandList::Begin(uint32_t index) const
    {
        NEPTUNE_PROFILE_ZONE

        m_CommandLists[index]->GetHandle()->Reset(GetCommandAllocator(), nullptr);
    }

    void CommandList::End(uint32_t index) const
    {
        NEPTUNE_PROFILE_ZONE

        m_CommandLists[index]->GetHandle()->Close();
    }
}

#endif