/**
* @file VulkanInstance.cpp.
* @brief The VulkanInstance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "VulkanSurface.h"
#include "Window/Window.h"

#include <GLFW/glfw3.h>

namespace Neptune {

    VulkanSurface::VulkanSurface(VulkanContext& context)
        : VulkanInfrastructure(context)
    {
        Create();
    }

    void VulkanSurface::Create()
    {
        const auto instance = m_Context.Get<VulkanInstance>()->Row();
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        /**
        * @attention Init with Window's size, but we need resize it to viewport's size after.
        */
        VK_CHECK(glfwCreateWindowSurface(instance, window, nullptr, &m_Surface))
    }

}

#endif