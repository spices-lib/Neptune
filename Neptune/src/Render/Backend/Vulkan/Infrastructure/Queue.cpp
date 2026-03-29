/**
* @file Queue.cpp.
* @brief The Queue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Queue.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

    Queue::Queue(Context& context, EInfrastructure e, VkQueue queue)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Init(queue);
    }

    void Queue::Init(VkQueue queue)
    {
        NEPTUNE_PROFILE_ZONE

        m_Queue.SetHandle(queue);
        
        DEBUGUTILS_SETOBJECTNAME(m_Queue, ToString())
    }

    void Queue::Submit(const VkSubmitInfo& info, VkFence fence) const
    {
        NEPTUNE_PROFILE_ZONE

        m_Queue.Submit(info, fence);
    }

    void Queue::Wait() const
    {
        NEPTUNE_PROFILE_ZONE

        m_Queue.Wait();
    }
}