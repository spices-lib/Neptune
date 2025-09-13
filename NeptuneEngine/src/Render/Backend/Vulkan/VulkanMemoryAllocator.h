/**
* @file VulkanMemoryAllocator.h.
* @brief The VulkanMemoryAllocator Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "VulkanInfrastructure.h"

#include <vk_mem_alloc.h>

namespace Neptune {

	/**
	* @brief Map to VmaAllocationCreateFlagBits while use VMA for memory create.
	*/
	typedef enum VMAMemoryPropertyFlagExtendBits {

		/**
		* @brief VkMemoryPropertyFlagBits
		*/
		//VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT        = 0x00000001,
		//VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT        = 0x00000002,
		//VK_MEMORY_PROPERTY_HOST_COHERENT_BIT       = 0x00000004,
		//VK_MEMORY_PROPERTY_HOST_CACHED_BIT         = 0x00000008,
		//VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT    = 0x00000010,
		//VK_MEMORY_PROPERTY_PROTECTED_BIT           = 0x00000020,
		//VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD = 0x00000040,
		//VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD = 0x00000080,
		//VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV     = 0x00000100,
		//VK_MEMORY_PROPERTY_FLAG_BITS_MAX_ENUM      = 0x7FFFFFFF

		/**
		* @brief VmaAllocationCreateFlagBits map.
		*/
		VMA_MEMORY_PROPERTY_DEDICATED_MEMORY_BIT     = 0x10000000,

	} VMAMemoryPropertyFlagExtendBits;

	class VulkanMemoryAllocator : public VulkanInfrastructure
	{
	public:

		/**
		* @brief Mark as VulkanInfrastructure Type.
		*/
		static constexpr EVulkanInfrastructure Type = EVulkanInfrastructure::VulkanMemoryAllocator;

	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] context The global VulkanContext.
		*/
		VulkanMemoryAllocator(VulkanContext& context);

		/**
		* @brief Destructor Function.
		*/
		~VulkanMemoryAllocator() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VmaAllocator& Row() { return m_VmaAllocator; }

	private:

		/**
		* @brief Create VmaAllocator.
		*/
		void Create();

	private:

		/**
		* @brief From VulkanMemoryAllocator.
		*/
		VmaAllocator m_VmaAllocator = nullptr;
	};

	template<>
	inline void VulkanInfrastructure::Destroy(VulkanMemoryAllocator* infrastructure)
	{
		vmaDestroyAllocator(infrastructure->Row());
		infrastructure->Row() = nullptr;
	}

}

#endif