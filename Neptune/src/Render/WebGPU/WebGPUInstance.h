/**
* @file WebGPUInstance.h.
* @brief The WebGPUInstance Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "WebGPUUtils.h"

namespace Neptune {

    /**
    * @brief WebGPUInstance Class.
    * This class defines the WebGPUInstance behaves.
    * This class is just a wrapper of WGPUInstance and WGPUSurface.
    */
    class WebGPUInstance : public WebGPUObject
    {
    public:

        /**
        * @brief Constructor Function.
        * Create WGPUInstance and WGPUSurface.
        * @param[in] webGPUState The global VulkanState.
        * @param[in] name Application name.
        * @param[in] engineName Engine name.
        */
        WebGPUInstance(
                WebGPUState&       webGPUState ,
                const std::string& name        ,
                const std::string& engineName
        );

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUInstance() override = default;
    };
}