/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Surface.h"
#include "Render/Backend/Vulkan/Infrastructure/Instance.h"

#include <GLFW/glfw3.h>

namespace Neptune::Vulkan::GLFW {

    Surface::Surface(Context& context, EInfrastructure e, void* window)
        : Vulkan::Surface(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(window);
    }

    void Surface::Create(void* window)
    {
        NEPTUNE_PROFILE_ZONE

        const auto instance = GetContext().Get<IInstance>()->Handle();

        Unit::Surface::Handle handle;

        VK_CHECK(glfwCreateWindowSurface(instance, static_cast<GLFWwindow*>(window), nullptr, &handle))

        m_Surface.SetHandle(handle);

        m_Surface.SetInstance(instance);
    }

}