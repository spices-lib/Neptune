/**
* @file QueryPool.h.
* @brief The QueryPool Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/QueryPool.h"

namespace Neptune::Vulkan::Resource {

	/**
	* @brief Vulkan::QueryPool Class.
	* This class defines the Vulkan::QueryPool behaves.
	*/
	class QueryPool : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit QueryPool(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~QueryPool() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::QueryPool::Handle& Handle() const { return m_Pool.GetHandle(); }

		/**
		* @brief Get VkQueryControlFlags.
		*
		* @return Returns VkQueryControlFlags.
		*/
		VkQueryControlFlags Flag() const { return m_Flag; }

		/**
		* @brief Get query count.
		*
		* @return Returns query count.
		*/
		uint32_t Count() const { return m_Count; }

		/**
		* @brief Create Query Pool.
		*
		* @param[in] info VkQueryPoolCreateInfo.
		* @param[in] stride Query stride.
		*/
		void CreateQueryPool(const VkQueryPoolCreateInfo& info, uint32_t stride);

		/**
		* @brief Get Query Pool Result.
		*
		* @return Returns Query Pool Result.
		*/
		std::vector<uint64_t> GetQueryPoolResult() const;

		/**
		* @brief Get Query Pool Result.
		*
		* @param[in] index Query index.
		* 
		* @return Returns Query Pool Result.
		*/
		uint64_t GetQueryPoolResult(uint32_t index) const;

	private:

		Unit::QueryPool       m_Pool;            // @brief This QueryPool.
		VkQueryControlFlags   m_Flag{};          // @brief VkQueryControlFlags.
		uint32_t              m_Count{};         // @brief Count.
		uint32_t              m_Stride{};        // @brief Stride.
	};
}

#endif