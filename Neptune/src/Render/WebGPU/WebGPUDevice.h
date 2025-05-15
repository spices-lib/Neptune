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
    * @brief WebGPUDevice Class.
    * This class defines the WebGPUDevice behaves.
    * This class is just a wrapper of WebGPUDevice.
    */
    class WebGPUDevice : public WebGPUObject
    {
    public:

        /**
        * @brief Constructor Function.
        * Create WebGPUDevice.
        * @param[in] webGPUState The global VulkanState.
        * @param[in] name Application name.
        * @param[in] engineName Engine name.
        */
        WebGPUDevice(
                WebGPUState&       webGPUState ,
                const std::string& name        ,
                const std::string& engineName
        );

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUDevice() override = default;
    };
}