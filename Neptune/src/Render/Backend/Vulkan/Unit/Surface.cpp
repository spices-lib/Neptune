/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Surface.h"

namespace Neptune::Vulkan::Unit {

	Surface::~Surface()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle || !m_Instance) return;

		vkDestroySurfaceKHR(m_Instance, m_Handle, nullptr);
	}

	void Surface::SetInstance(VkInstance instance)
	{
		NEPTUNE_PROFILE_ZONE

		m_Instance = instance;
	}
}