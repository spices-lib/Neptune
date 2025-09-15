/**
* @file Instance.cpp.
* @brief The Instance Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Surface.h"
#include "Window/Window.h"

#include <GLFW/glfw3.h>

namespace Neptune::Vulkan {

    Surface::Surface(Context& context)
        : Infrastructure(context)
    {
        Create();
    }

    void Surface::Create()
    {
        const auto instance = m_Context.Get<Instance>()->Handle();
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        /**
        * @attention Init with Window's size, but we need resize it to viewport's size after.
        */
        VK_CHECK(glfwCreateWindowSurface(instance, window, nullptr, &m_Handle))
    }

}

#endif