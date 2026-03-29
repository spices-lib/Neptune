/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Surface.h"
#include "Window/Window.h"

namespace Neptune::Vulkan {

    Surface::Surface(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Surface::Create()
    {
        NEPTUNE_PROFILE_ZONE

        const auto instance = GetContext().Get<IInstance>()->Handle();
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        m_Surface.CreateSurface(instance, window);
    }

}