/**
* @file WebGPUSwapChain.h.
* @brief The WebGPUSwapChain Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

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
                WebGPUState&     webGPUState ,
                SP<WebGPUDevice> webGPUDevice
        );

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUSwapChain() override;

    private:

        /**
		* @brief The shared pointer of WebGPUDevice.
		*/
        SP<WebGPUDevice> m_WebGPUDevice;
    };
}

#endif