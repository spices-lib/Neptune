/**
* @file WindowImpl.h.
* @brief The WindowImpl Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Window/Window.h"

struct GLFWwindow;

namespace Neptune::GLFW {

    /**
    * @brief WindowImpl Class.
    * This class defines the WindowImpl behaves.
    * This class is just a wrapper of glfwWindow.
    */
    class WindowImpl : public Window
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] initInfo WindowInfo.
        * @param[in] implement WindowImplement.
        */
        WindowImpl(const WindowInfo& initInfo, WindowImplement implement);

        /**
        * @brief Destructor Function.
        */
        ~WindowImpl() override;

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