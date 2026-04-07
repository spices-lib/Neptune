/**
* @file WindowBackendInterface.h.
* @brief The WindowBackendInterface Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Window/Enum.h"

namespace Neptune::imgui {

    /**
    * @brief WindowAPIInterface Class.
    */
    class WindowAPIInterface
    {
    public:

        /**
        * @brief Interface of Initialize.
        */
        virtual void OnInitialize() const = 0;

        /**
        * @brief Interface of ShutDown.
        */
        virtual void OnShutDown() const = 0;

        /**
        * @brief Interface of Begin a frame.
        */
        virtual void BeginFrame() const = 0;
    };

    /**
    * @brief Create APIInterface With RenderBackend.
    *
    * @param[in] implement WindowImplement.
    *
    * @return Returns WindowAPIInterface.
    */
    SP<WindowAPIInterface> CreateWindowInterface(WindowImplement implement);

    /**
    * @brief GLFW APIInterface.
    */
    class GLFWInterface : public WindowAPIInterface
    {
    public:

        /**
        * @brief Interface of Initialize.
        */
        void OnInitialize() const override;

        /**
        * @brief Interface of ShutDown.
        */
        void OnShutDown() const override;

        /**
        * @brief Interface of Begin a frame.
        */
        void BeginFrame() const override;
    };

}