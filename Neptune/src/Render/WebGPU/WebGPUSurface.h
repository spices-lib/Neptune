/**
* @file WebGPUDevice.h.
* @brief The WebGPUDevice Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "WebGPUUtils.h"

namespace Neptune {

    /**
    * @brief WebGPUSurface Class.
    * This class defines the WebGPUSurface behaves.
    * This class is just a wrapper of WebGPUSurface.
    */
    class WebGPUSurface : public WebGPUObject
    {
    public:

        /**
        * @brief Constructor Function.
        * Create WebGPUSurface.
        * @param[in] webGPUState The global VulkanState.
        * @param[in] name Application name.
        * @param[in] engineName Engine name.
        */
        WebGPUSurface(
                WebGPUState&       webGPUState ,
                const std::string& name        ,
                const std::string& engineName
        );

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUSurface() override = default;
    };
}