/**
* @file EmscriptenGLFWWindowImpl.h.
* @brief The EmscriptenGLFWWindowImpl Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Window/Window.h"

class GLFWwindow;

namespace Neptune {

    /**
    * @brief EmscriptenGLFWWindowImpl Class.
    * This class defines the EmscriptenGLFWWindowImpl behaves.
    * This class is just a wrapper of glfwWindow.
    */
    class EmscriptenGLFWWindowImpl : public Window
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] initInfo WindowInfo.
        * @param[in] implement WindowImplement.
        */
        EmscriptenGLFWWindowImpl(const WindowInfo& initInfo, WindowImplement implement);

        /**
        * @brief Destructor Function.
        */
        ~EmscriptenGLFWWindowImpl() override;

        /**
        * @brief Interface of determine if window is still active.
        *
        * @return Returns true if window is active.
        */
        bool IsWindowActive() override;

        /**
        * @brief Interface of window poll events.
        */
        void PollEvents() override;

        /**
        * @brief Interface of get native window pointer.
        *
        * @return Returns native window pointer.
        */
        void* NativeWindow() override;

    private:

        /**
        * @brief Set event/error/input callback.
        */
        void SetInternalCallBack() const;

    private:

        /**
        * @brief native window.
        */
        GLFWwindow* m_Windows;
    };
}

#endif