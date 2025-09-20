/**
* @file Window.h.
* @brief The Window Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Enum.h"
#include "Render/Frontend/Enum.h"

namespace Neptune {

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
        * @param[in] backend RenderBackendEnum.
        *
        * @return Returns Window pointer.
        */
        static SP<Window> Create(const WindowInfo& initInfo, WindowImplement implement, RenderBackendEnum backend);

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
        * 
        * @param[in] initInfo WindowInfo.
        * @param[in] implement WindowImplement.
        */
        Window(const WindowInfo& initInfo, WindowImplement implement);

        /**
        * @brief Destructor Function.
        */
        ~Window() override = default;

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
        * @brief Interface of window swap buffers.
        */
        virtual void SwapBuffers() = 0;

        /**
        * @brief Interface of get native window pointer.
        *
        * @return Returns native window pointer.
        */
        virtual void* NativeWindow() = 0;

    protected:

        WindowInfo m_WindowInfo;              // @brief Window init config.
        WindowImplement m_WindowImplement;    // @brief Window implement.
        bool m_WindowsResized;                // @brief Window resized.
    };
}