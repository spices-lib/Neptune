/**
* @file Window.cpp.
* @brief The Window Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Window.h"
#include "Window/GLFW/GLFWWindowImpl.h"

namespace Neptune {

    SP<Window> Window::Create(const WindowInfo& initInfo, WindowImplement implement)
    {
        switch(implement)
        {
            case WindowImplement::emscripten_glfw : return CreateSP<GLFWWindowImpl>(initInfo, implement);
            default:
            {
                printf("Not supported Windows Implement.\n");
            }
        }

        return nullptr;
    }

    Window::Window(const WindowInfo& initInfo, WindowImplement implement)
        : m_WindowInfo(initInfo)
        , m_WindowImplement(implement)
        , m_WindowsResized(false)
    {}

}