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

        virtual bool IsWindowActive() override;
        virtual void PollEvents() override;

    private:

        void SetInternalCallBack();

    private:

        GLFWwindow* m_Windows;
    };
}