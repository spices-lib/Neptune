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

        //Wait(wgpuQueueOnSubmittedWorkDone(m_Handle, info));
    }

    void Queue::Submit() const
    {
        NEPTUNE_PROFILE_ZONE

        WGPUCommandBuffer commandBuffer[1];

        wgpuQueueSubmit(m_Queue.GetHandle(), 1, commandBuffer);
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