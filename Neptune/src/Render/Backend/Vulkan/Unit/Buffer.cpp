#include "Pchheader.h"
#include "Buffer.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"

namespace Neptune::Vulkan::Unit {

	Buffer::~Buffer()
	{
		if (!m_Handle) return;

		if (auto* p = std::get_if<vkAlloc>(&m_Alloc))
		{
			if (p->hostMemory)
			{
				vkUnmapMemory(p->device, p->memory);

				p->hostMemory = nullptr;
			}

			vkDestroyBuffer(p->device, m_Handle, nullptr);

			if (p->memory)
			{
				vkFreeMemory(p->device, p->memory, nullptr);
			}
		}
		else if (auto* p = std::get_if<vmaAlloc>(&m_Alloc))
		{
			if (p->hostMemory)
			{
				vmaUnmapMemory(p->vma, p->alloc);

				p->hostMemory = nullptr;
			}

			vmaDestroyBuffer(p->vma, m_Handle, p->alloc);
		}
		else
		{
			return;
		}
	}

	void* Buffer::HostMemory() const
	{
		if (auto* p = std::get_if<vkAlloc>(&m_Alloc))
		{
			return p->hostMemory;
		}
		else if (auto* p = std::get_if<vmaAlloc>(&m_Alloc))
		{
			return p->hostMemory;
		}
		else
		{
			return nullptr;
		}
	}
	
	void Buffer::CreateBuffer(VkPhysicalDevice physicalDevice, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		assert(device);

		vkAlloc alloc{};
		alloc.device = device;

		VK_CHECK(vkCreateBuffer(device, &info, nullptr, &m_Handle))

		VkMemoryDedicatedRequirements                       dedicatedRegs{};
		dedicatedRegs.sType                               = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS;

		VkMemoryRequirements2                               memReqs{};
		memReqs.sType                                     = VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2;
		memReqs.pNext                                     = &dedicatedRegs;

		VkBufferMemoryRequirementsInfo2                     bufferReqs{};
		bufferReqs.sType                                  = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
		bufferReqs.buffer                                 = m_Handle;

		vkGetBufferMemoryRequirements2(device, &bufferReqs, &memReqs);

		VkMemoryAllocateInfo                                allocInfo{};
		allocInfo.sType                                   = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize                          = memReqs.memoryRequirements.size;

		VkMemoryAllocateFlagsInfoKHR                        flagsInfo{};
		flagsInfo.sType                                   = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR;
		flagsInfo.flags                                   = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT;

		if (info.usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)
		{
			allocInfo.pNext = &flagsInfo;
		}

		VkPhysicalDeviceMemoryProperties memProperties{};
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if (memReqs.memoryRequirements.memoryTypeBits & (1 << i) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				allocInfo.memoryTypeIndex = i;
				break;
			}
		}

		VK_CHECK(vkAllocateMemory(device, &allocInfo, nullptr, &alloc.memory));
		VK_CHECK(vkBindBufferMemory(device, m_Handle, alloc.memory, 0));

		if (info.usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)
		{
			VkBufferDeviceAddressInfo           info{};
			info.sType                        = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
			info.buffer                       = m_Handle;

			m_Address = vkGetBufferDeviceAddress(alloc.device, &info);
		}

		if (properties & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			VK_CHECK(vkMapMemory(alloc.device, alloc.memory, 0, info.size, 0, &alloc.hostMemory))
		}

		m_Alloc = alloc;
		m_Size  = info.size;
	}

	void Buffer::CreateBuffer(VmaAllocator vma, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		assert(vma);

		vmaAlloc alloc{};
		alloc.vma = vma;

		VmaAllocationCreateInfo                             allocInfo{};
		allocInfo.usage                                   = VMA_MEMORY_USAGE_AUTO;

		if (properties & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			allocInfo.flags |= VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
		}

		if (properties & VMA_MEMORY_PROPERTY_DEDICATED_MEMORY_BIT)
		{
			allocInfo.flags |= VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;
		}

		VK_CHECK(vmaCreateBuffer(vma, &info, &allocInfo, &m_Handle, &alloc.alloc, nullptr))

		if (info.usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)
		{
			VkBufferDeviceAddressInfo           info{};
			info.sType                        = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
			info.buffer                       = m_Handle;

			m_Address = vkGetBufferDeviceAddress(device, &info);
		}

		if (properties & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		{
			VK_CHECK(vmaMapMemory(vma, alloc.alloc, &alloc.hostMemory))
		}

		m_Alloc = alloc;
		m_Size  = info.size;
	}

	void Buffer::WriteToBuffer(const void* data, VkDeviceSize size, VkDeviceSize offset)
	{
		if (auto* p = std::get_if<vkAlloc>(&m_Alloc))
		{
			if (!p->hostMemory)
			{
				CORE_WARN("Vulkan::Unit::Buffer Property without VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT.");
				return;
			}

			if (size == VK_WHOLE_SIZE) 
			{
				memcpy(p->hostMemory, data, m_Size);
			}
			else 
			{
				char* memOffset = static_cast<char*>(p->hostMemory);
				memOffset += offset;
				memcpy(memOffset, data, size);
			}
		}
		else if (auto* p = std::get_if<vmaAlloc>(&m_Alloc))
		{
			if (!p->hostMemory)
			{
				CORE_WARN("Vulkan::Unit::Buffer Property without VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT.");
				return;
			}

			if (size == VK_WHOLE_SIZE)
			{
				VK_CHECK(vmaCopyMemoryToAllocation(p->vma, data, p->alloc, offset, m_Size))
			}
			else
			{
				VK_CHECK(vmaCopyMemoryToAllocation(p->vma, data, p->alloc, offset, size))
			}
		}
		else
		{
			return;
		}
	}

	void Buffer::Flush(VkDeviceSize size, VkDeviceSize offset)
	{
		size = size == VK_WHOLE_SIZE ? m_Size : size;

		if (auto* p = std::get_if<vkAlloc>(&m_Alloc))
		{
			VkMappedMemoryRange                  range{};
			range.sType                        = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
			range.memory                       = p->memory;
			range.offset                       = offset;
			range.size                         = size;

			VK_CHECK(vkFlushMappedMemoryRanges(p->device, 1, &range))
		}
		else if (auto* p = std::get_if<vmaAlloc>(&m_Alloc))
		{
			VK_CHECK(vmaFlushAllocation(p->vma, p->alloc, offset, size))
		}
		else
		{
			return;
		}
	}
}