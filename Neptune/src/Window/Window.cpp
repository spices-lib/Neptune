/**
* @file Window.cpp.
* @brief The Window Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Window.h"
#include "Window/GLFW/GLFWWindowImpl.h"

namespace Neptune {

    static SP<Window> S_Instance = nullptr;

    SP<Window> Window::Create(const WindowInfo& initInfo, WindowImplement implement)
    {
        switch(implement)
        {
            case WindowImplement::emscripten_glfw:
            case WindowImplement::GLFW:
                S_Instance = CreateSP<GLFWWindowImpl>(initInfo, implement);
                NEPTUNE_CORE_INFO("GLFW Window created.")
                break;
            default:
            {
                NEPTUNE_CORE_CRITICAL("Not supported Windows Implement.")
            }
        }

        return S_Instance;
    }

    Window& Window::Instance()
    {
        assert(S_Instance);
        return *S_Instance;
    }

    void Window::Destroy()
    {
        S_Instance.reset();
        S_Instance = nullptr;

        NEPTUNE_CORE_INFO("GLFW Window destroyed.")
    }

    Window::Window(const WindowInfo& initInfo, WindowImplement implement)
        : m_WindowInfo(initInfo)
        , m_WindowImplement(implement)
        , m_WindowsResized(false)
    {}

}