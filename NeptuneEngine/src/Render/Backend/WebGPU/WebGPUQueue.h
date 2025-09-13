/**
* @file WebGPUQueue.h.
* @brief The WebGPUQueue Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "WebGPUObject.h"

namespace Neptune {

    /**
    * @brief WebGPUQueue Class.
    */
    class WebGPUQueue : public WebGPUObject
    {
    public:

        /**
        * @brief Mark as WebGPUQueue Type.
        */
        static constexpr EWebGPUObject Type = EWebGPUObject::WebGPUQueue;

    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPUContext.
        */
        explicit WebGPUQueue(WebGPUContext& context);

        /**
        * @brief Destructor Function.
        */
        ~WebGPUQueue() override = default;

        /**
        * @brief Get Row WebGPU Object.
        *
        * @return Returns Row WebGPU Object.
        */
        WGPUQueue& Row() { return m_Queue; }

    public:

        /**
        * @brief Get EWebGPUObject.
        *
        * @return Returns EWebGPUObject.
        */
        const EWebGPUObject& GetType() const override { return WebGPUQueue::Type; };

    private:

        void OnSubmittedWorkDone();
        void Submit();
        void WriteBuffer();
        void WriteTexture();

    private:

        /**
        * @brief WGPUQueue.
        */
        WGPUQueue m_Queue = nullptr;
    };

    template<>
    inline void WebGPUObject::AddRef(WebGPUQueue* object)
    {
        wgpuQueueAddRef(object->Row());
    }

    template<>
    inline void WebGPUObject::Release(WebGPUQueue* object)
    {
        if (!object->Row())
        {
            return;
        }

        wgpuQueueRelease(object->Row());
        object->Row() = nullptr;
    }

    template<>
    inline void WebGPUObject::SetLabel(WebGPUQueue* object, const std::string& label)
    {
        WGPUStringView view{ label.c_str() };

        wgpuQueueSetLabel(object->Row(), view);
    }

}

#endif