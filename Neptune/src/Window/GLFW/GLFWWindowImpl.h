/**
* @file GLFWWindowImpl.h.
* @brief The GLFWWindowImpl Class Definitions.
* @author Spices.
*/

#pragma once
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
        virtual ~GLFWWindowImpl() override;

        /**
        * @brief Interface of determine if window is still active.
        *
        * @return Returns true if window is active.
        */
        virtual bool IsWindowActive() override;

        /**
        * @brief Interface of window poll events.
        */
        virtual void PollEvents() override;

        /**
        * @brief Interface of get native window pointer.
        *
        * @return Returns native window pointer.
        */
        virtual void* NativeWindow() override;

    private:

        /**
        * @brief Set event/error/input callback.
        */
        void SetInternalCallBack();

    private:

        /**
        * @brief native window.
        */
        GLFWwindow* m_Windows;
    };
}