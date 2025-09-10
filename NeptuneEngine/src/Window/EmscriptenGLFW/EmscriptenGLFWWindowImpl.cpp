/**
* @file EmscriptenGLFWWindowImpl.cpp.
* @brief The EmscriptenGLFWWindowImpl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "EmscriptenGLFWWindowImpl.h"
#include "Core/Event/WindowEvent.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"

#include <GLFW/glfw3.h>
#include <GLFW/emscripten_glfw3.h>

namespace Neptune {

    EmscriptenGLFWWindowImpl::EmscriptenGLFWWindowImpl(const WindowInfo& initInfo, WindowImplement implement)
            : Window(initInfo, implement)
    {
        // initialize the library
        if(!glfwInit()) {
            NEPTUNE_CORE_CRITICAL("glfw init failed.")
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);        // @brief no OpenGL (use canvas2D)
        glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, GLFW_FALSE);  // @brief make it not Hi DPI Aware (simplify rendering code a bit)

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwWindowHint(GLFW_RED_BITS     , mode->redBits     );
        glfwWindowHint(GLFW_GREEN_BITS   , mode->greenBits   );
        glfwWindowHint(GLFW_BLUE_BITS    , mode->blueBits    );
        glfwWindowHint(GLFW_REFRESH_RATE , mode->refreshRate );

        // setting the association window <-> canvas
        emscripten_glfw_set_next_window_canvas_selector("#nepnep");

        // create the only window
        m_Windows = glfwCreateWindow(initInfo.width, initInfo.height, initInfo.name.c_str(), nullptr, nullptr);
        if(!m_Windows) {
            NEPTUNE_CORE_CRITICAL("Window create failed.")
        }

        // Set glfw call back object pointer.
        glfwSetWindowUserPointer(m_Windows, this);

        // makes the canvas resizable and match the full window size
        emscripten_glfw_make_canvas_resizable(m_Windows, "#nepnep-div", nullptr);

        // Set gltf event call back.
        SetInternalCallBack();
    }

    EmscriptenGLFWWindowImpl::~EmscriptenGLFWWindowImpl()
    {
        if (m_Windows) {
            glfwDestroyWindow(m_Windows);
        }
        glfwTerminate();
    }

    bool EmscriptenGLFWWindowImpl::IsWindowActive()
    {
        return !glfwWindowShouldClose(m_Windows);
    }

    void EmscriptenGLFWWindowImpl::PollEvents()
    {
        glfwPollEvents();
    }

    void* EmscriptenGLFWWindowImpl::NativeWindow()
    {
        return m_Windows;
    }

    void EmscriptenGLFWWindowImpl::SetInternalCallBack() const
    {
        // print the version on the console
        NEPTUNE_CORE_INFO(glfwGetVersionString())

        // Error event Callback.
        glfwSetErrorCallback([](int error, const char* description){

            std::stringstream ss;
            ss << "glfwError: " << error << " | " << description;

            NEPTUNE_CORE_ERROR(ss.str())
        });

        // Framebuffer resize event Callback, not in use.
        //glfwSetFramebufferSizeCallback(m_Windows, WindowsResizeCallback);

        // Window resize event Callback.
        glfwSetWindowSizeCallback(m_Windows, [](GLFWwindow* window, int width, int height)
        {
            // reinterpret the pointer to this class.
            const auto thisWindows = static_cast<EmscriptenGLFWWindowImpl*>(glfwGetWindowUserPointer(window));

            // Set this class's variable.
            thisWindows->m_WindowsResized    = true;
            thisWindows->m_WindowInfo.width  = width;
            thisWindows->m_WindowInfo.height = height;

            WindowResizeEvent event(width, height);
            Event::GetEventCallbackFn()(event);
        });

        // Key event Callback.
        glfwSetKeyCallback(m_Windows, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 0);
                    Event::GetEventCallbackFn()(event);

                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(static_cast<KeyCode>(key));
                    Event::GetEventCallbackFn()(event);

                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 1);
                    Event::GetEventCallbackFn()(event);

                    break;
                }
                default:
                    break;
            }
        });

        // Key Input event Callback.
        glfwSetCharCallback(m_Windows, [](GLFWwindow* window, unsigned int keycode)
        {
            KeyTypedEvent event(static_cast<KeyCode>(keycode));
            Event::GetEventCallbackFn()(event);
        });

        // Mouse Button event Callback.
        glfwSetMouseButtonCallback(m_Windows, [](GLFWwindow* window, int button, int action, int mods)
        {
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(static_cast<MouseCode>(button));
                    Event::GetEventCallbackFn()(event);

                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
                    Event::GetEventCallbackFn()(event);

                    break;
                }
                default:
                    break;
            }
        });

        // Mouse Scroll event Callback.
        glfwSetScrollCallback(m_Windows, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            Event::GetEventCallbackFn()(event);
        });

        // Mouse Move event Callback.
        glfwSetCursorPosCallback(m_Windows, [](GLFWwindow* window, double xPos, double yPos)
        {
            MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
            Event::GetEventCallbackFn()(event);
        });
    }

}

#endif