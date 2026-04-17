/**
* @file RenderInterface.h.
* @brief The RenderInterface Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Frontend/Enum.h"
#include "Slate/Frontend/SlateFrontend.h"

namespace Neptune::imgui {

    /**
    * @brief RenderInterface Class.
    */
    class RenderInterface
    {
    public:

        /**
        * @brief Interface of Initialize.
        * 
        * @param[in] infrastructure RenderFrontend Infrastructure.
        */
        virtual void OnInitialize(const std::unordered_map<std::string, std::any>& infrastructure) const = 0;

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
    * @brief Create Interface With RenderFrontend.
    * 
    * @param[in] backend RenderBackendEnum.
    * 
    * @return Returns RenderInterface.
    */
    SP<RenderInterface> CreateRenderInterface(RenderBackendEnum backend);

    /**
    * @brief OpenGL Interface.
    */
    class OpenGLInterface : public RenderInterface
    {
    public:

        /**
        * @brief Destructor Function.
        */
        ~OpenGLInterface() = default;

        /**
        * @brief Interface of Initialize.
        *
        * @param[in] infrastructure RenderFrontend Infrastructure.
        */
        void OnInitialize(const std::unordered_map<std::string, std::any>& infrastructure) const override;

        /**
        * @brief Interface of ShutDown.
        */
        void OnShutDown() const override;

        /**
        * @brief Interface of Begin a frame.
        */
        void BeginFrame() const override;

    };

    /**
    * @brief Vulkan Interface.
    */
    class VulkanInterface : public RenderInterface
    {
    public:

        /**
        * @brief Destructor Function.
        */
        ~VulkanInterface() = default;
        
        /**
        * @brief Interface of Initialize.
        * 
        * @param[in] infrastructure RenderFrontend Infrastructure.
        */
        void OnInitialize(const std::unordered_map<std::string, std::any>& infrastructure) const override;

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