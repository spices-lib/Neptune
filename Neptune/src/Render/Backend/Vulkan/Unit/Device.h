/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Device Class.
	* This class defines the Vulkan::Unit::Device behaves.
	*/
	class Device : public Unit<VkDevice, VkObjectType::VK_OBJECT_TYPE_DEVICE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Device() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Device() override;

		/**
		* @brief Create Device.
		*
		* @param[in] physicalDevice VkPhysicalDevice.
		* @param[in] createInfo VkDeviceCreateInfo.
		*/
		void CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* createInfo);

		/**
		* @brief Create Device Queue.
		*
		* @param[in] queueFamilyIndex .
		* @param[in] queueIndex .
		* 
		* @return Returns VkQueue.
		*/
		VkQueue GetDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex) const;

		/**
		* @brief Device wait idle.
		*/
		void Wait() const;
	};
}