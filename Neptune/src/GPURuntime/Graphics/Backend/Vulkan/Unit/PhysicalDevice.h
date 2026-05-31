/**
* @file PhysicalDevice.h.
* @brief The PhysicalDevice Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::PhysicalDevice Class.
	* This class defines the Vulkan::Unit::PhysicalDevice behaves.
	*/
	class PhysicalDevice : public Unit<VkPhysicalDevice, VkObjectType::VK_OBJECT_TYPE_PHYSICAL_DEVICE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		PhysicalDevice() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~PhysicalDevice() override = default;
	};
}

#endif