/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Frontend/Core.h"

#include <vulkan/vulkan.h>
#include <functional>

namespace Neptune::Vulkan {

	constexpr uint32_t MaxFrameInFlight = Neptune::MaxFrameInFlight;       // @brief Frames In Flight.

	constexpr uint32_t NThreadQueue = 4;                                   // @brief Thread Queue Counts.

	constexpr uint32_t MaxDPBSlots = 16;                                   // @brief DPB Slot Counts.

	#define VK_VERSION VK_API_VERSION_1_4                                  // @brief Use Vulkan 1.4.

	#define VKImageHostOperation 0                                         // @brief Not use host operation.

	/**
	* @brief Result Delegate Class.
	*/
    struct HandleResultDelegate
    {
        using Handler = std::function<void(VkResult)>;

		/**
		* @brief Set Handler.
		* 
		* @param[in] fn Handler.
		*/
        static void SetHandler(const Handler& fn);

		/**
		* @brief Get Handler.
		*
		* @return Returns Handler.
		*/
        static const Handler& GetHandler();
    };

	/**
	* @brief Debug Callback Functor.
	* 
	* @param[in] messageSeverity VkDebugUtilsMessageSeverityFlagBitsEXT.
	* @param[in] messageType VkDebugUtilsMessageTypeFlagsEXT.
	* @param[in] pCallbackData VkDebugUtilsMessengerCallbackDataEXT.
	* @param[in] pUserData Payload.
	* 
	* @return Returns resumed.
	*/
	VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT         messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT                messageType, 
		const VkDebugUtilsMessengerCallbackDataEXT*    pCallbackData, 
		void*                                          pUserData
	);
	
	/**
	* @brief Handle Error Result.
	*
	* @param[in] result VkResult.
	* @param[in] physicalDevice VkPhysicalDevice.
	* @param[in] device VkDevice.
	* @param[in] vkGetDeviceFaultInfoEXT PFN_vkGetDeviceFaultInfoEXT.
	*/
	void HandleResult(VkResult result, VkPhysicalDevice physicalDevice, VkDevice device, PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT);

	#define VK_CHECK(expr)  { auto expr_value = expr; if (expr_value != VK_SUCCESS) { std::invoke(HandleResultDelegate::GetHandler(), expr_value); } }
}

#endif