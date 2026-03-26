#pragma once
#include "Core/Core.h"
#include "Unit.h"
#include <vector>

namespace Neptune::Vulkan::Unit {

	class QueryPool : public Unit<VkQueryPool, VkObjectType::VK_OBJECT_TYPE_QUERY_POOL>
	{
	public:

		using Handle = Unit::Handle;

	public:

		QueryPool() : Unit() {}

		~QueryPool() override;

		void CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo& info);

		std::vector<uint64_t> GetQueryPoolResult(uint32_t first, uint32_t count, uint32_t stride);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}