#include "Pchheader.h"
#include "ThreadQueue.h"
#include "DebugUtilsObject.h"

namespace Neptune::Vulkan {

    ThreadQueue::ThreadQueue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

    void ThreadQueue::Add(VkQueue handle)
    {
        auto queue = CreateSP<Unit::Queue>();
        queue->SetHandle(handle);

        m_Queues.Push(queue);

        DEBUGUTILS_SETOBJECTNAME(*queue, ToString())
    }
}