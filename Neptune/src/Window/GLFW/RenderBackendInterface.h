/**
* @file RenderBackendInterface.h.
* @brief The Interface Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

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
        * @brief Destructor Function.
        */
        virtual ~APIInterface() = default;
        
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

#ifdef NP_GRAPHICS_OPENGL
    
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
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override { return {}; }
    };

#endif
    
#ifdef NP_GRAPHICS_VULKAN
    
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
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override;
    };

#endif
    
#ifdef NP_GRAPHICS_DIRECT3D11
    
    /**
    * @brief Direct3D11 APIInterface.
    */
    class Direct3D11Interface : public APIInterface
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
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override { return {}; }
    };
    
#endif
    
#ifdef NP_GRAPHICS_DIRECT3D12
    
    /**
    * @brief Direct3D12 APIInterface.
    */
    class Direct3D12Interface : public APIInterface
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
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override { return {}; }
    };
    
#endif

}

#endif