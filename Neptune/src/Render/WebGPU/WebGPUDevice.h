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

        void CreateDevice();
        void CreateSurface();
        void QuerySwapChainSupport();

    private:

        SwapChainSupportDetails m_SwapChainSupportDetails;

    };
}