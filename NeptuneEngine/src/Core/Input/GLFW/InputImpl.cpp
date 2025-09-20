/**
* @file InputImpl.h.
* @brief The InputImpl Class Implementation.
* @author The Cherno.
*/

#include "Pchheader.h"
#include "InputImpl.h"
#include "Window/Window.h"

#include <GLFW/glfw3.h>

namespace Neptune::GLFW {

    bool InputImpl::IsKeyPressedImpl(const int& keycode)
    {
        NEPTUNE_PROFILE_ZONE

        // Get GLFW Window Pointer.
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        // Query GLFW Window Key State.
        const auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool InputImpl::IsMouseButtonPressedImpl(const int& button)
    {
        NEPTUNE_PROFILE_ZONE

        // Get GLFW Window Pointer.
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        // Query GLFW Window Mouse State.
        const auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> InputImpl::GetMousePositionImpl()
    {
        NEPTUNE_PROFILE_ZONE

        // Get GLFW Window Pointer.
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        // Query GLFW Window Cursor Position.
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    float InputImpl::GetMouseXImpl()
    {
        NEPTUNE_PROFILE_ZONE

        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float InputImpl::GetMouseYImpl()
    {
        NEPTUNE_PROFILE_ZONE

        auto [x, y] = GetMousePositionImpl();
        return y;
    }
}