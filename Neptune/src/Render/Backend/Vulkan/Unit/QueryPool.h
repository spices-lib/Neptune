/**
* @file QueryPool.h.
* @brief The QueryPool Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"
#include <vector>

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::QueryPool Class.
	* This class defines the Vulkan::Unit::QueryPool behaves.
	*/
	class QueryPool : public Unit<VkQueryPool, VkObjectType::VK_OBJECT_TYPE_QUERY_POOL>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		QueryPool() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~QueryPool() override;

		/**
		* @brief Create QueryPool.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkQueryPoolCreateInfo.
		*/
		void CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo& info);

		/**
		* @brief Get QueryPool Result.
		*
		* @param[in] first .
		* @param[in] count .
		* @param[in] stride .
		* 
		* @return Returns QueryPoolResult.
		*/
		std::vector<uint64_t> GetQueryPoolResult(uint32_t first, uint32_t count, uint32_t stride) const;

	private:

		VkDevice m_Device = VK_NULL_HANDLE;     // @brief VkDevice.
	};
}

#endif