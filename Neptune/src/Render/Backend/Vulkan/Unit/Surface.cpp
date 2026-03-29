/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Surface.h"
#include <GLFW/glfw3.h>

namespace Neptune::Vulkan::Unit {

	Surface::~Surface()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle || !m_Instance) return;

		vkDestroySurfaceKHR(m_Instance, m_Handle, nullptr);
	}

	void Surface::CreateSurface(VkInstance instance, GLFWwindow* window)
	{
		NEPTUNE_PROFILE_ZONE

		assert(instance && window && !m_Handle);

		m_Instance = instance;

		VK_CHECK(glfwCreateWindowSurface(instance, window, nullptr, &m_Handle))
	}
}