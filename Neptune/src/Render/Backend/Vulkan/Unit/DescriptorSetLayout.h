/**
* @file DescriptorSetLayout.h.
* @brief The DescriptorSetLayout Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::DescriptorSetLayout Class.
	* This class defines the Vulkan::Unit::DescriptorSetLayout behaves.
	*/
	class DescriptorSetLayout : public Unit<VkDescriptorSetLayout, VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		DescriptorSetLayout() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~DescriptorSetLayout() override;

		/**
		* @brief Create DescriptorSetLayout.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkDescriptorSetLayoutCreateInfo.
		*/
		void CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;      // @brief VkDevice.
	};
}

#endif