/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

#include <vma/vk_mem_alloc.h>
#include <variant>

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Buffer Class.
	* This class defines the Vulkan::Unit::Buffer behaves.
	*/
	class Buffer : public Unit<VkBuffer, VkObjectType::VK_OBJECT_TYPE_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Buffer() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Buffer() override;

		/**
		* @brief Get Buffer size.
		* 
		* @return Returns Buffer size.
		*/
		const VkDeviceSize& Size() const { return m_Size; }

		/**
		* @brief Get Buffer Host data.
		*
		* @return Returns Buffer Host data.
		*/
		void* HostMemory() const;

		/**
		* @brief Create Buffer.
		*
		* @param[in] physicalDevice VkPhysicalDevice.
		* @param[in] device VkDevice.
		* @param[in] info VkBufferCreateInfo.
		* @param[in] properties VkMemoryPropertyFlags.
		*/
		void CreateBuffer(VkPhysicalDevice physicalDevice, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties);

		/**
		* @brief Create Buffer.
		*
		* @param[in] vma VmaAllocator.
		* @param[in] device VkDevice.
		* @param[in] info VkBufferCreateInfo.
		* @param[in] properties VkMemoryPropertyFlags.
		*/
		void CreateBuffer(VmaAllocator vma, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties);

		/**
		* @brief Write data to Buffer.
		*
		* @param[in] data .
		* @param[in] size VkDeviceSize.
		* @param[in] offset VkDeviceSize.
		*/
		void WriteToBuffer(const void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		/**
		* @brief Flush Buffer data.
		*
		* @param[in] size VkDeviceSize.
		* @param[in] offset VkDeviceSize.
		*/
		void Flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

	private:

		/**
		* @brief vkAlloc
		*/
		struct vkAlloc {
			VkDevice         device     = VK_NULL_HANDLE;
			VkDeviceMemory   memory     = VK_NULL_HANDLE;
			void*            hostMemory = nullptr;
		};

		/**
		* @brief vmaAlloc
		*/
		struct vmaAlloc {
			VmaAllocator   vma        = VK_NULL_HANDLE;
			VmaAllocation  alloc      = VK_NULL_HANDLE;
			void*          hostMemory = nullptr;
		};

		std::variant<std::monostate, vkAlloc, vmaAlloc> m_Alloc{ std::monostate{} };   // @brief Alloc data.
		VkDeviceAddress  m_Address;                                                    // @brief Buffer Device Address.
		VkDeviceSize     m_Size;                                                       // @brief Buffer Size.
	};
}

#endif