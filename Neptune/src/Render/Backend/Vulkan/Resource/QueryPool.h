#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/QueryPool.h"

namespace Neptune::Vulkan {

	class QueryPool : public ContextAccessor
	{
	public:

		QueryPool(Context& context) : ContextAccessor(context) {}
		~QueryPool() override = default;

		const Unit::QueryPool::Handle& Handle() const { return m_Pool.GetHandle(); }

		VkQueryControlFlags Flag() const { return m_Flag; }

		uint32_t Count() const { return m_Count; }

		void CreateQueryPool(const VkQueryPoolCreateInfo& info, uint32_t stride);

		std::vector<uint64_t> GetQueryPoolResult();

		uint64_t GetQueryPoolResult(uint32_t index);

	private:

		Unit::QueryPool       m_Pool;
		VkQueryControlFlags   m_Flag;
		uint32_t              m_Count;
		uint32_t              m_Stride;
	};
}