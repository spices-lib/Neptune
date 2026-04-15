/**
* @file DescriptorSet.h.
* @brief The DescriptorSet Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::DescriptorSet Class.
	* This class defines the Vulkan::Unit::DescriptorSet behaves.
	*/
	class DescriptorSet : public Unit<VkDescriptorSet, VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_SET>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		DescriptorSet() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~DescriptorSet() override;

		/**
		* @brief Allocate DescriptorSet.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkDescriptorSetAllocateInfo.
		*/
		void AllocateDescriptorSet(VkDevice device, const VkDescriptorSetAllocateInfo& info);

		/**
		* @brief Update DescriptorSet.
		*
		* @param[in] write VkWriteDescriptorSet.
		*/
		void UpdateDescriptorSet(const VkWriteDescriptorSet& write) const;

	private:

		VkDevice             m_Device         = VK_NULL_HANDLE;      // @brief VkDevice.
		VkDescriptorPool     m_DescriptorPool = VK_NULL_HANDLE;      // @brief VkDescriptorPool.
	};
}

#endif