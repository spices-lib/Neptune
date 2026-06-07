/**
* @file WindowContext.cpp.
* @brief The WindowContext Class Implementation.
* @author Spices.
*/
#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "WindowContext.h"
#include "GPURuntime/Graphics/Backend/OpenGL/Core.h"

#include <GLFW/glfw3.h>

namespace Neptune::OpenGL::GLFW {

    WindowContext::WindowContext(Context& context, EInfrastructure e, void* window)
        : OpenGL::WindowContext(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create(window);
    }

    WindowContext::~WindowContext()
    {
        NEPTUNE_PROFILE_ZONE
        
        switch (GetEInfrastructure())
        {
            case EInfrastructure::WindowContext:
            {
                if (m_Window)
                {
                    glfwDestroyWindow(static_cast<GLFWwindow*>(m_Window));
                    break;
                }
            }
            case EInfrastructure::PresentWindowContext:
            {
                break;
            }
        }
    }

    void WindowContext::Create(void* window)
    {
        m_Window = window ? window : CreateWindow();

        MakeContextCurrent();

        // Turn off v-sync.
        glfwSwapInterval(0);

        // Use glad to load OpenGL APIs.
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            NEPTUNE_CORE_CRITICAL("Failed to initialize GLAD")
        }
    }

    void* WindowContext::CreateWindow() const
    {
        NEPTUNE_PROFILE_ZONE
        
        // Initialize the library
        if (!glfwInit())
        {
            NEPTUNE_CORE_CRITICAL("glfw init failed.")
        }

        // Hidden Window.
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        // Set OpenGL Version 4.6.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef NEPTUNE_DEBUG

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

#endif

        auto shared = GetContext().Has<IWindowContext>() ? static_cast<GLFWwindow*>(GetContext().Get<IWindowContext>()->Handle()) : nullptr;
        auto window = glfwCreateWindow(1, 1, "OpenGLContext", nullptr, shared);
        if (!window)
        {
            NEPTUNE_CORE_CRITICAL("Failed to Create glfwWindow")
        }

        return window;
    }
    
    void WindowContext::MakeContextCurrent()
    {
        NEPTUNE_PROFILE_ZONE

        glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_Window));
    }
    
    void WindowContext::SwapBuffers()
    {
        NEPTUNE_PROFILE_ZONE
        
        glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window));
    }
    
}

#endif