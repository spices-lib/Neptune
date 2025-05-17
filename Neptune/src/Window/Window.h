/**
* @file Window.h.
* @brief The Window Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace Neptune {

    /**
    * @brief Enum of Window Implement.
    */
    enum class WindowImplement
    {
        None            = 0,
        GLFW            = 1,
        emscripten_glfw = 2,
        SDL             = 3,
        WindowsOriginal = 4,
        MacOSOriginal   = 5,
        LinuxOriginal   = 6
    };

    /**
	* @brief This struct defines the basic information of window.
	*/
    struct WindowInfo
    {
        int width;         // @brief Window's width.
        int height;        // @brief Window's height.
        std::string name;  // @brief Window's name.
    };

    /**
    * @brief Windows Class.
    * This class defines the Windows behaves.
    */
    class Window : public NonCopyable
    {
    public:

        static SP<Window> Create(const WindowInfo& initInfo, WindowImplement implement);

    public:

        /**
        * @brief Constructor Function.
        * @param[in] initInfo WindowInfo.
        * @param[in] implement WindowImplement.
        */
        Window(const WindowInfo& initInfo, WindowImplement implement);

        /**
        * @brief Destructor Function.
        */
        virtual ~Window() = default;

        virtual bool IsWindowActive() = 0;
        virtual void PollEvents() = 0;

    protected:

        WindowInfo m_WindowInfo;
        WindowImplement m_WindowImplement;
        bool m_WindowsResized;
    };
}