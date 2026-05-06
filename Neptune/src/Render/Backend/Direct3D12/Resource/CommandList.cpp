/**
* @file CommandList.cpp.
* @brief The CommandList Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "CommandList.h"
#include "Render/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Direct3D12 {

    void CommandList::CreateCommandList(D3D12Device device, D3D12_COMMAND_LIST_TYPE type)
    {
        NEPTUNE_PROFILE_ZONE
            
        {
            m_CommandAllocator.CreateCommandAllocator(device, type);

            DEBUGUTILS_SETOBJECTNAME(m_CommandAllocator, "CommmandAllocator")
        }

        {
            m_CommandList.CreateGraphicsCommandList(device, m_CommandAllocator.GetHandle(), type);

            DEBUGUTILS_SETOBJECTNAME(m_CommandList, "CommandList")
        }

        m_Open = true;
    }

    void CommandList::Begin()
    {
        NEPTUNE_PROFILE_ZONE

        if (m_Open) return;

        m_Open = true;

        m_CommandList.GetHandle()->Reset(m_CommandAllocator.GetHandle(), nullptr);
    }

    void CommandList::End()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Open) return;

        m_Open = false;

        m_CommandList.GetHandle()->Close();
    }
}

#endif