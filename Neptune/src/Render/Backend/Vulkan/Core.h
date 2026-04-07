/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/ContextAccessor.h"
#include "Render/Frontend/Utils.h"

#include <vulkan/vulkan.h>
#include <sstream>
#include <vector>
#include <functional>

namespace Neptune::Vulkan {

	constexpr uint32_t MaxFrameInFlight = Neptune::MaxFrameInFlight;       // @brief Frames In Flight.

	constexpr uint32_t NThreadQueue = 4;                                   // @brief Thread Queue Counts.

	constexpr uint32_t MaxDPBSlots = 16;                                   // @brief DPB Slot Counts.

	#define VK_VERSION VK_API_VERSION_1_4                                  // @brief Use Vulkan 1.4.

	#define VKImageHostOperation 0                                         // @brief Not use host operation.

	/**
	* @brief VulkanResult Delegate Class.
	*/
    struct HandleVulkanResultDelegate
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
	* @brief Handle Vulkan Error Result.
	*
	* @param[in] result VkResult.
	* @param[in] physicalDevice VkPhysicalDevice.
	* @param[in] device VkDevice.
	* @param[in] vkGetDeviceFaultInfoEXT PFN_vkGetDeviceFaultInfoEXT.
	*/
	void HandleVulkanResult(VkResult result, VkPhysicalDevice physicalDevice, VkDevice device, PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT);

	#define VK_CHECK(expr)  { auto expr_value = expr; if (expr_value != VK_SUCCESS) { std::invoke(HandleVulkanResultDelegate::GetHandler(), expr_value); } }
}