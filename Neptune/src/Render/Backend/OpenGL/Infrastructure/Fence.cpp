/**
* @file Fence.cpp.
* @brief The Fence Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Fence.h"
#include "DebugUtilsObject.h"

namespace Neptune::OpenGL {

    Fence::Fence(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(count);
    }

    void Fence::Create(uint32_t count)
    {
        NEPTUNE_PROFILE_ZONE

        for (uint32_t i = 0; i < count; ++i)
        {
            auto fence = CreateSP<Unit::Sync>();

            fence->CreateSync();
 
            m_Fences.emplace_back(fence);

            DEBUGUTILS_SETOBJECTNAME(*fence, ToString())
        }
    }

    void Fence::Wait(uint32_t index)
    {
        NEPTUNE_PROFILE_ZONE

        m_Fences[index]->ClientWait();

        m_Fences[index] = CreateSP<Unit::Sync>();

        DEBUGUTILS_SETOBJECTNAME(*m_Fences[index], ToString())
    }

    void Fence::Barrier(uint32_t index)
    {
        NEPTUNE_PROFILE_ZONE

        m_Fences[index]->Wait();

        m_Fences[index] = CreateSP<Unit::Sync>();

        DEBUGUTILS_SETOBJECTNAME(*m_Fences[index], ToString())
    }

    void Fence::WaitAll()
    {
        NEPTUNE_PROFILE_ZONE

        for (int i = 0; i < m_Fences.size(); ++i)
        {
            m_Fences[i]->ClientWait();

            m_Fences[i] = CreateSP<Unit::Sync>();

            DEBUGUTILS_SETOBJECTNAME(*m_Fences[i], ToString())
        }
    }

}

#endif