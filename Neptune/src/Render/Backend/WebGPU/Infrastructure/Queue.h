/**
* @file Queue.h.
* @brief The Queue Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/WebGPU/Unit/Queue.h"

namespace Neptune::WebGPU {

    namespace Unit {
        
        class CommandBuffer;
    }
    
    using IQueue = IInfrastructure<class Queue, EInfrastructure::Queue>;
    
    /**
    * @brief WebGPU::Queue Class.
    * This class defines the WebGPU::Queue behaves.
    */
    class Queue : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Queue(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Queue() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Queue::Handle& Handle() const { return m_Queue.GetHandle(); }
        
        /**
        * @brief Wait Queue Idle.
        */
        void OnSubmittedWorkDone() const;
        
        /**
        * @brief Submit CommandEncoder to Queue.
        * 
        * @param[in] commandBuffer Unit::CommandBuffer.
        */
        void Submit(const SP<Unit::CommandBuffer>& commandBuffer) const;
        
    private:

        /**
        * @brief Create Surface.
        */
        void Create();
        
        void WriteBuffer() const;
        void WriteTexture() const;

    private:

        Unit::Queue m_Queue; // @brief This Queue.
    };

}

#endif