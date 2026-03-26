#include "Pchheader.h"
#include "QueryPool.h"

namespace Neptune::Vulkan::Unit {

	QueryPool::~QueryPool()
	{
		if (!m_Handle) return;

		vkDestroyQueryPool(m_Device, m_Handle, nullptr);
	}

	void QueryPool::CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateQueryPool(device, &info, nullptr, &m_Handle))
	}

	std::vector<uint64_t> QueryPool::GetQueryPoolResult(uint32_t first, uint32_t count, uint32_t stride)
	{
		std::vector<uint64_t> result(count);

		VK_CHECK(vkGetQueryPoolResults(m_Device, m_Handle, first, count, count * stride + sizeof(uint64_t), result.data(), stride, VK_QUERY_RESULT_64_BIT | VK_QUERY_RESULT_WITH_STATUS_BIT_KHR | VK_QUERY_RESULT_WAIT_BIT))

		return result;
	}
}