/**
* @file WindowInterface.h.
* @brief The WindowInterface Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Window/Enum.h"

namespace Neptune::imgui {

    /**
    * @brief WindowInterface Class.
    */
    class WindowInterface
    {
    public:

        /**
        * @brief Destructor Function.
        */
        virtual ~WindowInterface() = default;
        
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
    * @brief Create Interface With RenderBackend.
    *
    * @param[in] implement WindowImplement.
    *
    * @return Returns WindowInterface.
    */
    SP<WindowInterface> CreateWindowInterface(WindowImplement implement);

    /**
    * @brief GLFW APIInterface.
    */
    class GLFWInterface : public WindowInterface
    {
    public:

        /**
        * @brief Destructor Function.
        */
        ~GLFWInterface() override = default;
        
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