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

    namespace {
    
        UP<Window> S_Instance = nullptr;     // @brief World Instance.
    }

    void Window::Create(const WindowInfo& initInfo, WindowImplement implement, RenderBackendEnum backend)
    {
        NEPTUNE_PROFILE_ZONE

        switch (implement)
        {
#ifdef NP_PLATFORM_EMSCRIPTEN
            case WindowImplement::emscripten_glfw:
            {
                S_Instance = CreateUP<EmscriptenGLFW::WindowImpl>(initInfo, implement, backend);
                break;
            }
#endif

#ifdef NP_PLATFORM_WINDOWS
            case WindowImplement::GLFW:
            {
                S_Instance = CreateUP<GLFW::WindowImpl>(initInfo, implement, backend);
                break;
            }
#endif
            default:
            {
                NEPTUNE_CORE_CRITICAL("Not supported Windows Implement.")
                return;
            }
        }

        NEPTUNE_CORE_INFO("Window Created.")
    }

    const Window& Window::Instance()
    {
        NEPTUNE_PROFILE_ZONE

        assert(S_Instance);

        return *S_Instance;
    }

    void Window::Destroy()
    {
        NEPTUNE_PROFILE_ZONE

        S_Instance.reset();

        NEPTUNE_CORE_INFO("Window destroyed.")
    }

    Window::Window(WindowImplement implement)
        : m_WindowImplement(implement)
    {}

}