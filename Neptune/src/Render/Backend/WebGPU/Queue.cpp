/**
* @file Queue.cpp.
* @brief The Queue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Queue.h"
#include "Device.h"

namespace Neptune::WebGPU {

    Queue::Queue(Context& context)
        : Infrastructure(context)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = m_Context.Get<Device>()->GetQueue();

        if (m_Handle)
        {
            NEPTUNE_CORE_INFO("WGPUQueue created succeed.")
        }
        else
        {
            NEPTUNE_CORE_CRITICAL("WGPUQueue created failed.")
        }
    }

    void Queue::OnSubmittedWorkDone()
    {
        NEPTUNE_PROFILE_ZONE

        static auto callback = [](
            WGPUQueueWorkDoneStatus status   , 
            WGPUStringView          message  , 
            void*                   userdata1,
            void* 
        ) {

        };

        WGPUQueueWorkDoneCallbackInfo     info{};
        info.mode                       = WGPUCallbackMode_WaitAnyOnly;
        info.userdata1                  = nullptr;
        info.callback                   = callback;

        Wait(wgpuQueueOnSubmittedWorkDone(m_Handle, info));
    }

    void Queue::Submit()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUCommandBuffer commandBuffer[1];

        wgpuQueueSubmit(m_Handle, 1, commandBuffer);
    }

    void Queue::WriteBuffer()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUBuffer buffer{};
        void* data;

        wgpuQueueWriteBuffer(m_Handle, buffer, 0, data, 0);
    }

    void Queue::WriteTexture()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUTexelCopyTextureInfo info{};
        void* data;
        WGPUTexelCopyBufferLayout layout{};
        WGPUExtent3D extent{};

        wgpuQueueWriteTexture(m_Handle, &info, data, 0, &layout, &extent);
    }


}

#endif