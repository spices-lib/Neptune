/**
* @file VulkanDevice.h.
* @brief The VulkanDevice Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "VulkanInfrastructure.h"

namespace Neptune {

	/**
	* @brief VulkanDevice Class.
	*/
	class VulkanDevice : public VulkanInfrastructure
	{
	public:

		/**
		* @brief Mark as VulkanDevice Type.
		*/
		static constexpr EVulkanInfrastructure Type = EVulkanInfrastructure::VulkanDevice;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global VulkanContext.
		*/
		VulkanDevice(VulkanContext& context);

		/**
		* @brief Destructor Function.
		*/
		~VulkanDevice() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkDevice& Row() { return m_Device; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkDevice.
		*/
		VkDevice m_Device = nullptr;

	};

	template<>
	inline void VulkanInfrastructure::Destroy(VulkanDevice* infrastructure)
	{
		vkDestroyDevice(infrastructure->Row(), nullptr);
		infrastructure->Row() = nullptr;
	}

}

#endif