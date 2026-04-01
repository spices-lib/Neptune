/**
* @file RenderBackendInterface.h.
* @brief The Interface Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Frontend/Enum.h"

struct GLFWwindow;

namespace Neptune::GLFW {

    /**
    * @brief APIInterface Class.
    */
    class APIInterface
    {
    public:

        /**
        * @brief Interface of GLFW Hint Configuration with RenderBackend.
        */
        virtual void Hint() const = 0;

        /**
        * @brief Interface of GLFW API Load Configuration with RenderBackend.
        * 
        * @param[in] handle GLFWwindow.
        */
        virtual void APILoad(GLFWwindow* handle) const = 0;

        /**
        * @brief Interface of GLFW SwapBuffers with RenderBackend.
        * 
        * @param[in] handle GLFWwindow.
        */
        virtual void SwapBuffers(GLFWwindow* handle) const = 0;
        
        /**
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        virtual std::vector<const char*> Extension() const = 0;
    };

    /**
    * @brief Create APIInterface With RenderBackend.
    * 
    * @param[in] backend RenderBackendEnum.
    * 
    * @return Returns APIInterface.
    */
    SP<APIInterface> CreateInterface(RenderBackendEnum backend);

    /**
    * @brief OpenGL APIInterface.
    */
    class OpenGLInterface : public APIInterface
    {
    public:

        /**
        * @brief Interface of GLFW Hint Configuration with RenderBackend.
        */
        void Hint() const override;

        /**
        * @brief Interface of GLFW API Load Configuration with RenderBackend.
        * 
        * @param[in] handle GLFWwindow.
        */
        void APILoad(GLFWwindow* handle) const override;

        /**
        * @brief Interface of GLFW SwapBuffers with RenderBackend.
        * 
        * @param[in] handle GLFWwindow.
        */
        void SwapBuffers(GLFWwindow* handle) const override;
        
        /**
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override { return {}; }
    };

    /**
    * @brief Vulkan APIInterface.
    */
    class VulkanInterface : public APIInterface
    {
    public:

        /**
        * @brief Interface of GLFW Hint Configuration with RenderBackend.
        */
        void Hint() const override;

        /**
        * @brief Interface of GLFW API Load Configuration with RenderBackend.
        * 
        * @param[in] handle GLFWwindow.
        */
        void APILoad(GLFWwindow* handle) const override {}

        /**
        * @brief Interface of GLFW SwapBuffers with RenderBackend.
        * 
        * @param[in] handle GLFWwindow.
        */
        void SwapBuffers(GLFWwindow* handle) const override {}
        
        /**
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override;
    };

}

#endif