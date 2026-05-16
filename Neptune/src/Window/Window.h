/**
* @file Window.h.
* @brief The Window Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core.h"
#include "Core/NonCopyable.h"
#include "Enum.h"
#include "Render/Frontend/Enum.h"

#include <glm/glm.hpp>

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
        */
        static void Create(const WindowInfo& initInfo, WindowImplement implement, RenderBackendEnum backend);

        /**
        * @brief Get Window Instance.
        *
        * @return Returns Window reference.
        */
        static const Window& Instance();

        /**
        * @brief Destroy Window Instance.
        */
        static void Destroy();

    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] implement WindowImplement.
        */
        Window(WindowImplement implement);

        /**
        * @brief Destructor Function.
        */
        ~Window() override = default;

        /**
        * @brief Interface of determine if window is still active.
        *
        * @return Returns true if window is active.
        */
        virtual bool IsWindowActive() const = 0;

        /**
        * @brief Interface of window poll events.
        */
        virtual void PollEvents() const = 0;

        /**
        * @brief Interface of window swap buffers.
        */
        virtual void SwapBuffers() const = 0;

        /**
        * @brief Interface of window get extent.
        */
        virtual glm::ivec2 Extent() const = 0;

        /**
        * @brief Get Window Extension.
        *
        * @return Returns Window Extension.
        */
        virtual std::vector<const char*> Extension() const = 0;
        
        /**
        * @brief Interface of get native window pointer.
        *
        * @return Returns native window pointer.
        */
        virtual void* NativeWindow() const = 0;

    public:

        /**
        * @brief Get WindowImplement.
        *
        * @return Returns WindowImplement.
        */
        WindowImplement Implement() const { return m_WindowImplement; }
        
    protected:

        WindowImplement m_WindowImplement;    // @brief Window implement.
    };
}