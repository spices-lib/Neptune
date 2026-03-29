/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

#include <vector>

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::SwapChain Class.
	* This class defines the Vulkan::Unit::SwapChain behaves.
	*/
	class SwapChain : public Unit<VkSwapchainKHR, VkObjectType::VK_OBJECT_TYPE_SWAPCHAIN_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		SwapChain() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~SwapChain() override;

		/**
		* @brief Create Swapchain.
		*
		* @param[in] device VkDevice.
		* @param[in] createInfo VkSwapchainCreateInfoKHR.
		*/
		void CreateSwapchain(VkDevice device, const VkSwapchainCreateInfoKHR& createInfo);

		/**
		* @brief Get SwapchainImages.
		*
		* @param[in] imageCount .
		* 
		* @return Returns SwapchainImages.
		*/
		std::vector<VkImage> GetSwapchainImages(uint32_t imageCount) const;

		/**
		* @brief Get next SwapchainImage.
		*
		* @param[in] semaphore VkSemaphore.
		* @param[out] imageIndex .
		*
		* @return Returns VkResult.
		*/
		VkResult GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex) const;

	private:

		VkDevice m_Device = nullptr;    // @brief VkDevice.
	};
}