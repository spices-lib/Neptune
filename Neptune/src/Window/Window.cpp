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
            case WindowImplement::emscripten_glfw :
                S_Instance = CreateSP<GLFWWindowImpl>(initInfo, implement);
                break;
            default:
            {
                printf("Not supported Windows Implement.\n");
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
    }

    Window::Window(const WindowInfo& initInfo, WindowImplement implement)
        : m_WindowInfo(initInfo)
        , m_WindowImplement(implement)
        , m_WindowsResized(false)
    {}

}