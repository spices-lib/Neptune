/**
* @file MemoryAllocator.h.
* @brief The MemoryAllocator Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"

#include <vma/vk_mem_alloc.h>

namespace Neptune::Vulkan {

	/**
	* @brief Extend of VkMemoryPropertyFlagBits.
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

	using IMemoryAllocator = InfrastructureClass<class MemoryAllocator, EInfrastructure::MemoryAllocator>;

	/**
	* @brief Vulkan::MemoryAllocator Class.
	* This class defines the Vulkan::MemoryAllocator behaves.
	*/
	class MemoryAllocator : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		MemoryAllocator(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~MemoryAllocator() override;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const VmaAllocator& Handle() const { return m_Handle; }

	private:

		/**
		* @brief Create Instance.
		*/
		void Create();

	private:

		VmaAllocator m_Handle = nullptr;  // @brief This VmaAllocator.

	};

}