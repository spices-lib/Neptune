/**
* @file ThreadQueue.h.
* @brief The ThreadQueue Class Definitions.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "ThreadQueue.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

    ThreadQueue::ThreadQueue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

    void ThreadQueue::Add(Unit::Queue::Handle handle)
    {
        NEPTUNE_PROFILE_ZONE

        auto queue = CreateSP<Unit::Queue>();

        queue->SetHandle(handle);

        m_Queues.Push(queue);

        DEBUGUTILS_SETOBJECTNAME(*queue, ToString())
    }
}

#endif