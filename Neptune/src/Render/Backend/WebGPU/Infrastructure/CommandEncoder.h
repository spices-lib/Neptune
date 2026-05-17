/**
* @file CommandEncoder.h.
* @brief The CommandEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/WebGPU/Unit/CommandEncoder.h"

namespace Neptune::WebGPU {

    namespace Unit {
        
        class CommandBuffer;
    }
    
    using ICommandEncoder = IInfrastructure<class CommandEncoder, EInfrastructure::CommandEncoder>;

    /**
    * @brief WebGPU::CommandEncoder Class.
    * This class defines the WebGPU::CommandEncoder behaves.
    */
    class CommandEncoder : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        * @param[in] count CommandBuffer Counts.
        */
        CommandEncoder(Context& context, EInfrastructure e, uint32_t count = 1);

        /**
        * @brief Destructor Function.
        */
        ~CommandEncoder() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @param[in] index Handle index.
        *
        * @return Returns Unit Handle.
        */
        const Unit::CommandEncoder::Handle& Handle(uint32_t index = 0) const { return m_CommandEncoders[index]->GetHandle(); }

        /**
        * @brief Begin CommandEncoder.
        * 
        * @param[in] index Handle index.
        */
        void Begin(uint32_t index = 0);
		
        /**
        * @brief End CommandEncoder.
        * 
        * @param[in] index Handle index.
        * 
        * return Returns Unit::CommandBuffer.
        */
        SP<Unit::CommandBuffer> End(uint32_t index = 0);
        
    private:

        /**
        * @brief Create CommandEncoder.
        *
        * @param[in] count Future Counts.
        */
        void Create(uint32_t count);

    private:

        std::vector<SP<Unit::CommandEncoder>> m_CommandEncoders;  // @brief Container of CommandEncoders.
    };

}

#endif