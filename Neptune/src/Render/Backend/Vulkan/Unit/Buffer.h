#pragma once
#include "Core/Core.h"
#include "Unit.h"
#include <vk_mem_alloc.h>
#include <variant>

namespace Neptune::Vulkan::Unit {

	class Buffer : public Unit<VkBuffer, VkObjectType::VK_OBJECT_TYPE_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Buffer() : Unit() {}

		~Buffer() override;

		const VkDeviceSize& Size() const { return m_Size; }

		void* HostMemory() const;

		void CreateBuffer(VkPhysicalDevice physicalDevice, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties);

		void CreateBuffer(VmaAllocator vma, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties);

		void WriteToBuffer(const void* data, VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

		void Flush(VkDeviceSize size = VK_WHOLE_SIZE, VkDeviceSize offset = 0);

	private:

		struct vkAlloc {
			VkDevice         device     = VK_NULL_HANDLE;
			VkDeviceMemory   memory     = VK_NULL_HANDLE;
			void*            hostMemory = nullptr;
		};

		struct vmaAlloc {
			VmaAllocator   vma        = VK_NULL_HANDLE;
			VmaAllocation  alloc      = VK_NULL_HANDLE;
			void*          hostMemory = nullptr;
		};

		std::variant<std::monostate, vkAlloc, vmaAlloc> m_Alloc{ std::monostate{} };
		VkDeviceAddress  m_Address;
		VkDeviceSize     m_Size;
	};
}