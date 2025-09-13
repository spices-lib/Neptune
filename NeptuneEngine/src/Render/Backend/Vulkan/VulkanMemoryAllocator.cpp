/**
* @file VulkanMemoryAllocator.cpp.
* @brief The VulkanMemoryAllocator Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#define VMA_IMPLEMENTATION

#include "VulkanMemoryAllocator.h"
#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanDevice.h"

namespace Neptune {

	VulkanMemoryAllocator::VulkanMemoryAllocator(VulkanContext& context)
		: VulkanInfrastructure(context)
	{
		Create();
	}

	void VulkanMemoryAllocator::Create()
	{
		// see https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/quick_start.html
		VmaAllocatorCreateInfo                  createInfo {};
		createInfo.instance                   = m_Context.Get<VulkanInstance>()->Row();
		createInfo.physicalDevice             = m_Context.Get<VulkanPhysicalDevice>()->Row();
		createInfo.device                     = m_Context.Get<VulkanDevice>()->Row();
		createInfo.vulkanApiVersion           = VK_API_VERSION_1_3;
		createInfo.flags                      = VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT      | 
												VMA_ALLOCATOR_CREATE_KHR_BIND_MEMORY2_BIT              |
												VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE4_BIT              |
												VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE5_BIT              |
												VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT             |
												VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT         |
												VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT           |
												VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT |
												VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT           ;

		VK_CHECK(vmaCreateAllocator(&createInfo, &m_VmaAllocator))
	}
}

#endif