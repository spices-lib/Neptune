/**
* @file Future.h.
* @brief The Future Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/WebGPU/Unit/Future.h"

namespace Neptune::WebGPU {

    using IFuture = IInfrastructure<class Future, EInfrastructure::Future>;

    /**
    * @brief WebGPU::Future Class.
    * This class defines the WebGPU::Future behaves.
    */
    class Future : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        * @param[in] count CommandBuffer Counts.
        */
        Future(Context& context, EInfrastructure e, uint32_t count = 1);

        /**
        * @brief Destructor Function.
        */
        ~Future() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @param[in] index Handle index.
        * 
        * @return Returns Unit Handle.
        */
        const Unit::Future::Handle& Handle(uint32_t index = 0) const { return m_Futures[index]->GetHandle(); }

        /**
        * @brief Set Unit Handle.
        *
        * @param[in] index Handle index.
        * @param[in] handle WGPUFuture.
        */
        void SetHandle(uint32_t index = 0, WGPUFuture handle);
        
        /**
        * @brief Wait Future idle.
        *
        * @param[in] index Handle index.
        */
        void Wait(uint32_t index = 0) const;
        
    private:

        /**
        * @brief Create Future.
        * 
        * @param[in] count Future Counts.
        */
        void Create(uint32_t count);

    private:

        std::vector<SP<Unit::Future>> m_Futures;  // @brief Container of Futures.
    };
    
}

#endif