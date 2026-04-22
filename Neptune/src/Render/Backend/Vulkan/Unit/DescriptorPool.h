/**
* @file DescriptorPool.h.
* @brief The DescriptorPool Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::DescriptorPool Class.
	* This class defines the Vulkan::Unit::DescriptorPool behaves.
	*/
	class DescriptorPool : public Common::Unit<VkDescriptorPool, VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_POOL>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		DescriptorPool() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~DescriptorPool() override;

		/**
		* @brief Create DescriptorPool.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkDescriptorPoolCreateInfo.
		*/
		void CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;         // @brief VkDevice.
	};
}

#endif