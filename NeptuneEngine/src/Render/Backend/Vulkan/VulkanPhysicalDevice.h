/**
* @file VulkanPhysicalDevice.h.
* @brief The VulkanPhysicalDevice Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "VulkanInfrastructure.h"

namespace Neptune {
	
	/**
	* @brief VulkanPhysicalDevice Class.
	*/
	class VulkanPhysicalDevice : public VulkanInfrastructure
	{
	public:

		/**
		* @brief Mark as VulkanPhysicalSurface Type.
		*/
		static constexpr EVulkanInfrastructure Type = EVulkanInfrastructure::VulkanPhysicalSurface;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global VulkanContext.
		*/
		VulkanPhysicalDevice(VulkanContext& context);

		/**
		* @brief Destructor Function.
		*/
		~VulkanPhysicalDevice() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkPhysicalDevice& Row() { return m_PhysicalDevice; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief Check all Extension we need meet.
		* 
		* @param[in] device VkPhysicalDevice.
		* 
		* @return Returns true if all Extension we need meet.
		*/
		bool IsExtensionMeetDemand(const VkPhysicalDevice& device);

		/**
		* @brief Check all Property we need meet.
		* 
		* @param[in] device VkPhysicalDevice.
		* 
		* @return Returns true if all Property we need meet.
		*/
		bool IsPropertyMeetDemand(const VkPhysicalDevice& device);

		/**
		* @brief Check all  Feature we need meet.
		* 
		* @param[in] device VkPhysicalDevice.
		* 
		* @return Returns true if all Feature we need meet.
		*/
		bool IsFeatureMeetDemand(const VkPhysicalDevice& device);

		/**
		* @brief Check all Queue we need meet.
		* 
		* @param[in] device VkPhysicalDevice.
		* @param[in] surface VkSurfaceKHR.
		* 
		* @return Returns true if all Extension we need meet.
		*/
		bool IsQueueMeetDemand(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

	private:

		/**
		* @brief VkPhysicalDevice.
		*/
		VkPhysicalDevice m_PhysicalDevice = nullptr;

	};

	template<>
	void VulkanInfrastructure::Destroy(VulkanPhysicalDevice* infrastructure)
	{
		infrastructure->Row() = nullptr;
	}

}

#endif