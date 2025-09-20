/**
* @file Window.cpp.
* @brief The Window Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Window.h"

#ifdef NP_PLATFORM_EMSCRIPTEN
#include "Window/EmscriptenGLFW/WindowImpl.h"
#endif

#ifdef NP_PLATFORM_WINDOWS
#include "Window/GLFW/WindowImpl.h"
#endif

namespace Neptune {

    static SP<Window> S_Instance = nullptr;

    SP<Window> Window::Create(const WindowInfo& initInfo, WindowImplement implement, RenderBackendEnum backend)
    {
        switch (implement)
        {
#ifdef NP_PLATFORM_EMSCRIPTEN
            case WindowImplement::emscripten_glfw:
            {
                S_Instance = CreateSP<EmscriptenGLFW::WindowImpl>(initInfo, implement);
                break;
            }
#endif

#ifdef NP_PLATFORM_WINDOWS
            case WindowImplement::GLFW:
            {
                S_Instance = CreateSP<GLFW::WindowImpl>(initInfo, implement, backend);
                break;
            }
#endif
            default:
            {
                NEPTUNE_CORE_CRITICAL("Not supported Windows Implement.")
                return nullptr;
            }
        }

        NEPTUNE_CORE_INFO("GLFW Window created.")
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