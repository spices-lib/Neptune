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

        /**
        * @brief Create Window with specific implement.
        *
        * @param[in] initInfo WindowInfo.
        * @param[in] implement WindowImplement.
        *
        * @return Returns Window pointer.
        */
        static SP<Window> Create(const WindowInfo& initInfo, WindowImplement implement);

        /**
        * @brief Get Window Instance.
        *
        * @return Returns Window reference.
        */
        static Window& Instance();

        /**
        * @brief Destroy Window Instance.
        */
        static void Destroy();

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

        /**
        * @brief Interface of determine if window is still active.
        *
        * @return Returns true if window is active.
        */
        virtual bool IsWindowActive() = 0;

        /**
        * @brief Interface of window poll events.
        */
        virtual void PollEvents() = 0;

        /**
        * @brief Interface of get native window pointer.
        *
        * @return Returns native window pointer.
        */
        virtual void* NativeWindow() = 0;

    protected:

        WindowInfo m_WindowInfo;
        WindowImplement m_WindowImplement;
        bool m_WindowsResized;
    };
}