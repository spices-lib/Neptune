/**
* @file GLFWWindowImpl.h.
* @brief The GLFWWindowImpl Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Window/Window.h"

class GLFWwindow;

namespace Neptune {

    /**
    * @brief GLFWWindowImpl Class.
    * This class defines the GLFWWindowImpl behaves.
    * This class is just a wrapper of glfwWindow.
    */
    class GLFWWindowImpl : public Window
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] initInfo WindowInfo.
        * @param[in] implement WindowImplement.
        */
        GLFWWindowImpl(const WindowInfo& initInfo, WindowImplement implement);

        /**
        * @brief Destructor Function.
        */
        ~GLFWWindowImpl() override;

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
        
        GLFWwindow* m_Windows;  // @brief native window.
    };
}

#endif