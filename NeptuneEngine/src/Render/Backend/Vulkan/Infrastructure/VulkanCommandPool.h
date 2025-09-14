/**
* @file VulkanCommandPool.h.
* @brief The VulkanCommandPool Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "VulkanInfrastructure.h"

namespace Neptune {

	/**
	* @brief VulkanCommandPool Class.
	*/
	class VulkanCommandPool : public VulkanInfrastructure
	{
	public:

		/**
		* @brief Mark as VulkanCommandPool Type.
		*/
		static constexpr EVulkanInfrastructure Type = EVulkanInfrastructure::VulkanCommandPool;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global VulkanContext.
		*/
		VulkanCommandPool(VulkanContext& context);

		/**
		* @brief Destructor Function.
		*/
		~VulkanCommandPool() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkCommandPool& Row() { return m_CommandPool; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkCommandPool.
		*/
		VkCommandPool m_CommandPool = nullptr;

	};

	template<>
	inline void VulkanInfrastructure::Destroy(VulkanCommandPool* infrastructure)
	{

	}

}

#endif