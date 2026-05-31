/**
* @file CommandList.cpp.
* @brief The CommandList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "CommandList.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace Neptune::Direct3D11 {

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
            auto commandList = CreateSP<Resource::CommandList>(GetContext());

            m_CommandLists.push_back(commandList);
        }
    }

    void CommandList::Begin(uint32_t index) const
    {
        NEPTUNE_PROFILE_ZONE

        m_CommandLists[index]->DeviceContext()->ClearState();
    }

    void CommandList::End(uint32_t index) const
    {
        NEPTUNE_PROFILE_ZONE

        m_CommandLists[index]->Finish();
    }
}

#endif