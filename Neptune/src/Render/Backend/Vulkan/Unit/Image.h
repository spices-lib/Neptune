/**
* @file Image.h.
* @brief The Image Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

#include <vma/vk_mem_alloc.h>
#include <variant>

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Image Class.
	* This class defines the Vulkan::Unit::Image behaves.
	*/
	class Image : public Unit<VkImage, VkObjectType::VK_OBJECT_TYPE_IMAGE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Image() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Image() override;

		/**
		* @brief Create Image.
		*
		* @param[in] physicalDevice VkPhysicalDevice.
		* @param[in] device VkDevice.
		* @param[in] info VkImageCreateInfo.
		* @param[in] properties VkMemoryPropertyFlags.
		*/
		void CreateImage(VkPhysicalDevice physicalDevice, VkDevice device, const VkImageCreateInfo& info, VkMemoryPropertyFlags properties);

		/**
		* @brief Create Image.
		*
		* @param[in] vma VmaAllocator.
		* @param[in] info VkImageCreateInfo.
		* @param[in] properties VkMemoryPropertyFlags.
		*/
		void CreateImage(VmaAllocator vma, const VkImageCreateInfo& info, VkMemoryPropertyFlags properties);

	private:

		/**
		* @brief vkAlloc
		*/
		struct vkAlloc {
			VkDevice       device = VK_NULL_HANDLE;
			VkDeviceMemory memory = VK_NULL_HANDLE;
		};

		/**
		* @brief vmaAlloc
		*/
		struct vmaAlloc {
			VmaAllocator   vma    = VK_NULL_HANDLE;
			VmaAllocation  alloc  = VK_NULL_HANDLE;
		};

		std::variant<std::monostate, vkAlloc, vmaAlloc> m_Alloc{ std::monostate{} };     // @brief Alloc data.
	};
}