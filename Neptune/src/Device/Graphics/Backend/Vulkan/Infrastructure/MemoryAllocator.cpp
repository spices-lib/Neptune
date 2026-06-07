/**
* @file MemoryAllocator.cpp.
* @brief The MemoryAllocator Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#define VMA_IMPLEMENTATION

#include "MemoryAllocator.h"
#include "Instance.h"
#include "PhysicalDevice.h"
#include "Device.h"

namespace Neptune::Vulkan {

	MemoryAllocator::MemoryAllocator(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create();
	}

	MemoryAllocator::~MemoryAllocator()
	{
		NEPTUNE_PROFILE_ZONE

		vmaDestroyAllocator(Handle());

		m_Handle = nullptr;
	}

	void MemoryAllocator::Create()
	{
		NEPTUNE_PROFILE_ZONE

		// see https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/quick_start.html
		VmaAllocatorCreateInfo                  createInfo {};
		createInfo.instance                   = GetContext().Get<IInstance>()->Handle();
		createInfo.physicalDevice             = GetContext().Get<IPhysicalDevice>()->Handle();
		createInfo.device                     = GetContext().Get<IDevice>()->Handle();
		createInfo.vulkanApiVersion           = VK_VERSION;
		createInfo.flags                      = VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT      | 
												VMA_ALLOCATOR_CREATE_KHR_BIND_MEMORY2_BIT              |
												VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE4_BIT              |
												VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE5_BIT              |
												VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT             |
												VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT           |
												VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT |
												VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT           ;

		VK_CHECK(vmaCreateAllocator(&createInfo, &m_Handle))
	}
}

#endif