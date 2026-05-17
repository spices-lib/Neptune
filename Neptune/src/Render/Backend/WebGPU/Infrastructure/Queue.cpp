/**
* @file Queue.cpp.
* @brief The Queue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Queue.h"
#include "Device.h"
#include "Instance.h"
#include "DebugUtilsObject.h"
#include "Render/Backend/WebGPU/Unit/CommandBuffer.h"
#include "Render/Backend/WebGPU/Unit/Future.h"

namespace Neptune::WebGPU {

    Queue::Queue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Queue::Create()
    {
        NEPTUNE_PROFILE_ZONE

        m_Queue.CreateQueue(GetContext().Get<IDevice>()->Handle());
        
        DEBUGUTILS_SETOBJECTNAME(m_Queue, ToString())
    }
    
    void Queue::OnSubmittedWorkDone() const
    {
        NEPTUNE_PROFILE_ZONE

        static auto callback = [](
            WGPUQueueWorkDoneStatus status   , 
            WGPUStringView          message  , 
            void*                   userdata1,
            void* 
        ) {
            if (status == WGPUQueueWorkDoneStatus_CallbackCancelled)
            {
                NEPTUNE_CORE_INFO("Queue::OnSubmittedWorkDone::CallbackCancelled")
            }
            else if (status == WGPUQueueWorkDoneStatus_Error)
            {
                NEPTUNE_CORE_ERROR("Queue::OnSubmittedWorkDone::Error")
            }
        };

        WGPUQueueWorkDoneCallbackInfo        info{};
        info.mode                          = WGPUCallbackMode_WaitAnyOnly;
        info.userdata1                     = nullptr;
        info.callback                      = callback;

        Unit::Future future;
        
        future.SetHandle(wgpuQueueOnSubmittedWorkDone(m_Queue.GetHandle(), info));

        future.Wait(GetContext().Get<IInstance>()->Handle());
    }

    void Queue::Submit(const SP<Unit::CommandBuffer>& commandBuffer) const
    {
        NEPTUNE_PROFILE_ZONE

        wgpuQueueSubmit(m_Queue.GetHandle(), 1, &commandBuffer->GetHandle());
    }

    void Queue::WriteBuffer() const
    {
        NEPTUNE_PROFILE_ZONE

        WGPUBuffer buffer{};
        void* data;

        wgpuQueueWriteBuffer(m_Queue.GetHandle(), buffer, 0, data, 0);
    }

    void Queue::WriteTexture() const
    {
        NEPTUNE_PROFILE_ZONE

        WGPUTexelCopyTextureInfo info{};
        void* data;
        WGPUTexelCopyBufferLayout layout{};
        WGPUExtent3D extent{};

        wgpuQueueWriteTexture(m_Queue.GetHandle(), &info, data, 0, &layout, &extent);
    }


}

#endif