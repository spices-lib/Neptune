/**
* @file WWindowImpl.h.
* @brief The WindowImpl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Window/Window.h"

struct GLFWwindow;

namespace Neptune::EmscriptenGLFW {

    class APIInterface;

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
        * @param[in] backend RenderBackendEnum.
        */
        WindowImpl(const WindowInfo& initInfo, WindowImplement implement, RenderBackendEnum backend);

        /**
        * @brief Destructor Function.
        */
        ~WindowImpl() override;

        /**
        * @brief Interface of determine if window is still active.
        *
        * @return Returns true if window is active.
        */
        bool IsWindowActive() const override;

        /**
        * @brief Interface of window poll events.
        */
        void PollEvents() const override;

        /**
        * @brief Interface of window swap buffers.
        */
        void SwapBuffers() const override;

        /**
        * @brief Interface of window get extent.
        */
        glm::ivec2 Extent() const override;

        /**
        * @brief Get Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override;

        /**
        * @brief Interface of get native window pointer.
        *
        * @return Returns native window pointer.
        */
        void* NativeWindow() const override;

    private:

        /**
        * @brief Set event/error/input callback.
        */
        void SetInternalCallBack() const;

    private:

        GLFWwindow* m_Windows;             // @brief native window.
        SP<APIInterface> m_APIInterface;   // @brief render backend interface.
    };
}

#endif