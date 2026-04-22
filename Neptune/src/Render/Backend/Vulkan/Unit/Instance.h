/**
* @file Instance.h.
* @brief The Instance Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Instance Class.
	* This class defines the Vulkan::Unit::Instance behaves.
	*/
	class Instance : public Common::Unit<VkInstance, VkObjectType::VK_OBJECT_TYPE_INSTANCE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Instance() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Instance() override;

		/**
		* @brief Create Instance.
		*
		* @param[in] createInfo VkInstanceCreateInfo.
		*/
		void CreateInstance(const VkInstanceCreateInfo& createInfo);
	};
}

#endif