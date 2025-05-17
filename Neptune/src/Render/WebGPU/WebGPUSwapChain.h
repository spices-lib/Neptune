/**
* @file WebGPUSwapChain.h.
* @brief The WebGPUSwapChain Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "WebGPUUtils.h"

namespace Neptune {

    class WebGPUDevice;

    /**
    * @brief WebGPUSwapChain Class.
    * This class defines the WebGPUSwapChain behaves.
    * This class is just a wrapper of WebGPUSwapChain.
    */
    class WebGPUSwapChain : public WebGPUObject
    {
    public:

        /**
        * @brief Constructor Function.
        * Create WebGPUDevice.
        * @param[in] webGPUState The global VulkanState.
        * @param[in] WebGPUDevice The shared pointer of WebGPUDevice.
        */
        WebGPUSwapChain(
                WebGPUState&                  webGPUState ,
                std::shared_ptr<WebGPUDevice> webGPUDevice
        );

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUSwapChain() override;

    private:

        /**
		* @brief The shared pointer of WebGPUDevice.
		*/
        std::shared_ptr<WebGPUDevice> m_WebGPUDevice;
    };
}