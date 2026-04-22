/**
* @file Fence.h.
* @brief The Fence Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Fence Class.
	* This class defines the Vulkan::Unit::Fence behaves.
	*/
	class Fence : public Unit<VkFence, VkObjectType::VK_OBJECT_TYPE_FENCE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Fence() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Fence() override;

		/**
		* @brief Create Fence.
		*
		* @param[in] device VkDevice.
		* @param[in] info VkFenceCreateInfo.
		*/
		void CreateFence(VkDevice device, const VkFenceCreateInfo& info);

		/**
		* @brief Fence wait idle.
		*/
		void Wait() const;

		/**
		* @brief Reset Fence.
		*/
		void ResetFence() const;

	private:

		VkDevice m_Device = VK_NULL_HANDLE;        // @brief VkDevice
	};
}

#endif