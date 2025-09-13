/**
* @file WebGPUQueue.cpp.
* @brief The WebGPUQueue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPUQueue.h"
#include "WebGPUDevice.h"

namespace Neptune {

    WebGPUQueue::WebGPUQueue(WebGPUContext& context)
        : WebGPUObject(context)
    {
        m_Queue = m_Context.Get<WebGPUDevice>()->GetQueue();

        if (m_Queue)
        {
            NEPTUNE_CORE_INFO("WGPUQueue created succeed.")
        }
        else
        {
            NEPTUNE_CORE_CRITICAL("WGPUQueue created failed.")
        }
    }

    void WebGPUQueue::OnSubmittedWorkDone()
    {
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

        Wait(wgpuQueueOnSubmittedWorkDone(m_Queue, info));
    }

    void WebGPUQueue::Submit()
    {
        WGPUCommandBuffer commandBuffer[1];

        wgpuQueueSubmit(m_Queue, 1, commandBuffer);
    }

    void WebGPUQueue::WriteBuffer()
    {
        WGPUBuffer buffer{};
        void* data;

        wgpuQueueWriteBuffer(m_Queue, buffer, 0, data, 0);
    }

    void WebGPUQueue::WriteTexture()
    {
        WGPUTexelCopyTextureInfo info{};
        void* data;
        WGPUTexelCopyBufferLayout layout{};
        WGPUExtent3D extent{};

        wgpuQueueWriteTexture(m_Queue, &info, data, 0, &layout, &extent);
    }


}

#endif