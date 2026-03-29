/**
* @file CommandPool.h.
* @brief The CommandPool Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::CommandPool Class.
	* This class defines the Vulkan::Unit::CommandPool behaves.
	*/
	class CommandPool : public Unit<VkCommandPool, VkObjectType::VK_OBJECT_TYPE_COMMAND_POOL>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		CommandPool() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~CommandPool() override;

		/**
		* @brief Create CommandPool.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkCommandPoolCreateInfo.
		*/
		void CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;       // @brief VkDevice.
	};
}