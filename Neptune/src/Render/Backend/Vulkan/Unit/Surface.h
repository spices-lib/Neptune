/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Vulkan::Unit {

	/**
	* @brief Vulkan::Unit::Surface Class.
	* This class defines the Vulkan::Unit::Surface behaves.
	*/
	class Surface : public Unit<VkSurfaceKHR, VkObjectType::VK_OBJECT_TYPE_SURFACE_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Surface() : Unit() {}

		/**
		* @brief Destructor Function.
		*/
		~Surface() override;

		/**
		* @brief Create Surface.
		*
		* @param[in] instance VkInstance.
		*/
		void SetInstance(VkInstance instance);

	private:

		VkInstance m_Instance;     // @brief VkInstance.
	};
}