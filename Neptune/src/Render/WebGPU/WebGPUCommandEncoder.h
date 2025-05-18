/**
* @file WebGPUCommandEncoder.h.
* @brief The WebGPUCommandEncoder Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "WebGPUUtils.h"

namespace Neptune {

    /**
    * @brief WebGPUCommandEncoder Class.
    * This class defines the WebGPUCommandEncoder behaves.
    */
    class WebGPUCommandEncoder : public WebGPUObject
    {
    public:

        /**
        * @brief Constructor Function.
        * Create WGPUInstance and WGPUSurface.
        * @param[in] webGPUState The global VulkanState.
        */
        WebGPUCommandEncoder(WebGPUState& webGPUState);

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUCommandEncoder() override;
    };
}