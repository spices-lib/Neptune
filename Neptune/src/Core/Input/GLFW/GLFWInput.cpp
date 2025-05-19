/**
* @file GLFWInput.h.
* @brief The GLFWInput Class Implementation.
* @author The Cherno.
*/

#include "Pchheader.h"
#include "GLFWInput.h"
#include "Window/Window.h"

#include <GLFW/glfw3.h>

namespace Neptune {

    /**
    * @brief Instance a WindowsInput single instance.
    */
    std::unique_ptr<Input> Input::s_Instance = std::make_unique<GLFWInput>();

    bool GLFWInput::IsKeyPressedImpl(const int& keycode)
    {
        // Get GLFW Window Pointer.
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        // Query GLFW Window Key State.
        const auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool GLFWInput::IsMouseButtonPressedImpl(const int& button)
    {
        // Get GLFW Window Pointer.
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        // Query GLFW Window Mouse State.
        const auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> GLFWInput::GetMousePositionImpl()
    {
        // Get GLFW Window Pointer.
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        // Query GLFW Window Cursor Position.
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    float GLFWInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float GLFWInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }
}