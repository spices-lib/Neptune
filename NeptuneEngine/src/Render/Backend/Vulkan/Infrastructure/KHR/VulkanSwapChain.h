/**
* @file VulkanSwapChain.h.
* @brief The VulkanSwapChain Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/VulkanInfrastructure.h"
#include "Render/Backend/Vulkan/Infrastructure/VulkanDevice.h"

namespace Neptune {

	/**
	* @brief VulkanSwapChain Class.
	*/
	class VulkanSwapChain : public VulkanInfrastructure
	{
	public:

		/**
		* @brief Mark as VulkanSwapChain Type.
		*/
		static constexpr EVulkanInfrastructure Type = EVulkanInfrastructure::VulkanSwapChain;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global VulkanContext.
		*/
		VulkanSwapChain(VulkanContext& context);

		/**
		* @brief Destructor Function.
		*/
		~VulkanSwapChain() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkSwapchainKHR& Row() { return m_Swapchain; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkSwapchainKHR.
		*/
		VkSwapchainKHR m_Swapchain = nullptr;

	};

	template<>
	inline void VulkanInfrastructure::Destroy(VulkanSwapChain* infrastructure)
	{
		const auto device = infrastructure->m_Context.Get<VulkanDevice>()->Row();

		vkDestroySwapchainKHR(device, infrastructure->Row(), nullptr);
		infrastructure->Row() = nullptr;
	}

}

#endif