/**
* @file WebGPUDevice.h.
* @brief The WebGPUDevice Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "WebGPUUtils.h"

namespace Neptune {

    /**
	* @brief SwapChain Utils.
	* Queried from device.
	*/
    struct SwapChainSupportDetails
    {
        WGPUTextureFormat format;     // @brief The selected VkSurfaceFormatKHR.
        WGPUPresentMode presentMode;  // @brief The selected VkPresentModeKHR.
    };

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
        */
        WebGPUDevice(WebGPUState& webGPUState);

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGPUDevice() override = default;

        /**
		* @brief Get SwapChain Utils.
		* @return Returns SwapChain Utils.
		*/
        inline const SwapChainSupportDetails& GetSwapChainSupport() { return m_SwapChainSupportDetails; }

    private:

        /**
        * @brief Create logical device.
        */
        void CreateDevice();

        /**
        * @brief Create surface.
        */
        void CreateSurface();

        /**
        * @brief Create queue.
        */
        void CreateQueue();

        /**
        * @brief Fetch SwapChain device support.
        */
        void QuerySwapChainSupport();

    private:

        /**
        * @brief SwapChainSupportDetails.
        */
        SwapChainSupportDetails m_SwapChainSupportDetails;

    };
}

#endif