/**
* @file Queue.h.
* @brief The Queue Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"
#include <vector>

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Queue Class.
	* This class defines the Vulkan::Unit::Queue behaves.
	*/
	class Queue : public Common::Unit<VkQueue, VkObjectType::VK_OBJECT_TYPE_QUEUE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Queue() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Queue() override = default;

		/**
		* @brief Submit Queue.
		*
		* @param[in] info VkSubmitInfo.
		* @param[in] fence VkFence.
		*/
		void Submit(const VkSubmitInfo& info, VkFence fence = VK_NULL_HANDLE) const;

		/**
		* @brief Queue wait idle.
		*/
		void Wait() const;
	};
}

#endif