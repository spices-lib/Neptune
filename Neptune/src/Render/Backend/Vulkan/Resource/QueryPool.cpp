/**
* @file QueryPool.cpp.
* @brief The QueryPool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "QueryPool.h"
#include "Render/Backend/Vulkan/Infrastructure/Context.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace Neptune::Vulkan {

	void QueryPool::CreateQueryPool(const VkQueryPoolCreateInfo& info, uint32_t stride)
	{
		NEPTUNE_PROFILE_ZONE

		m_Count           = info.queryCount;
		m_Stride          = stride;
		m_Flag            = 0;

		if (info.queryType & VK_QUERY_TYPE_OCCLUSION)
		{
			m_Flag |= VK_QUERY_CONTROL_PRECISE_BIT;
		}

		m_Pool.CreateQueryPool(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_Pool, "QueryPool")
	}

	std::vector<uint64_t> QueryPool::GetQueryPoolResult() const
	{
		NEPTUNE_PROFILE_ZONE

		return m_Pool.GetQueryPoolResult(0, m_Count, m_Stride);
	}

	uint64_t QueryPool::GetQueryPoolResult(uint32_t index) const
	{
		NEPTUNE_PROFILE_ZONE

		return m_Pool.GetQueryPoolResult(index, 1, m_Stride)[0];
	}
}

#endif