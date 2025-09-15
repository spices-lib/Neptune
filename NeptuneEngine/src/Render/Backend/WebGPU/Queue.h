/**
* @file Queue.h.
* @brief The Queue Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::WebGPU {

    /**
    * @brief Queue Class.
    */
    class Queue : public Infrastructure<WGPUQueue, EInfrastructure::Queue>
    {
    public:

        /**
        * @brief Mark as Queue Infrastructure Type.
        */
        static constexpr EInfrastructure Type = Infrastructure<WGPUQueue, EInfrastructure::Queue>::Type;

    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context The global WebGPU Context.
        */
        explicit Queue(Context& context);

        /**
        * @brief Destructor Function.
        */
        ~Queue() override = default;

    private:

        void OnSubmittedWorkDone();
        void Submit();
        void WriteBuffer();
        void WriteTexture();

    };

    template<>
    inline void InfrastructureBase::AddRef(Queue* object)
    {
        wgpuQueueAddRef(object->Handle());
    }

    template<>
    inline void InfrastructureBase::Release(Queue* object)
    {
        if (!object->Handle())
        {
            return;
        }

        wgpuQueueRelease(object->Handle());
        object->SetHandleNullptr();
    }

    template<>
    inline void InfrastructureBase::SetLabel(Queue* object, const std::string& label)
    {
        WGPUStringView view{ label.c_str() };

        wgpuQueueSetLabel(object->Handle(), view);
    }

}

#endif