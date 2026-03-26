/**
* @file CommandPool.h.
* @brief The CommandPool Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Infrastructure.h"

namespace Neptune::Vulkan {

	/**
	* @brief CommandPool Class.
	*/
	class CommandPool : public Infrastructure
	{
	public:

		/**
		* @brief Mark as CommandPool Infrastructure Type.
		*/
		static constexpr EInfrastructure Type = EInfrastructure::CommandPool;

	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context The global VulkanContext.
		*/
		CommandPool(Context& context);

		/**
		* @brief Destructor Function.
		*/
		~CommandPool() override = default;

		/**
		* @brief Get Row Vulkan Infrastructure.
		*
		* @return Returns Row Vulkan Infrastructure.
		*/
		VkCommandPool& Handle() { return m_Handle; }

	private:

		/**
		* @brief Create VkInstance.
		*/
		void Create();

	private:

		/**
		* @brief VkCommandPool.
		*/
		VkCommandPool m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(CommandPool* infrastructure)
	{

	}

}

#endif