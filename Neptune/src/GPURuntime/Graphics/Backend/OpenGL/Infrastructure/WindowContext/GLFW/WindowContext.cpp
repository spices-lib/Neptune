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

    WindowContext::WindowContext(Context& context, EInfrastructure e)
        : OpenGL::WindowContext(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void WindowContext::Create()
    {
        NEPTUNE_PROFILE_ZONE
        
        // Hidden Window.
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        // Set OpenGL Version 4.6.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef NEPTUNE_DEBUG

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

#endif

        m_Window = glfwCreateWindow(1, 1, "OpenGLContext", nullptr, nullptr);

        MakeContextCurrent();

        // Turn off v-sync.
        glfwSwapInterval(0);

        // Use glad to load OpenGL APIs.
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            NEPTUNE_CORE_CRITICAL("Failed to initialize GLAD")
        }
    }

    WindowContext::~WindowContext()
    {
        NEPTUNE_PROFILE_ZONE
        
        if (m_Window)
        {
            glfwDestroyWindow(static_cast<GLFWwindow*>(m_Window));
        }
    }
    
    void WindowContext::MakeContextCurrent()
    {
        NEPTUNE_PROFILE_ZONE

        glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_Window));
    }
    
}

#endif