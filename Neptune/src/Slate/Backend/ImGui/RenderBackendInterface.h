/**
* @file RenderBackendInterface.h.
* @brief The RenderBackendInterface Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Render/Frontend/Enum.h"

namespace Neptune::imgui {

    /**
    * @brief RenderAPIInterface Class.
    */
    class RenderAPIInterface
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
    * @param[in] backend RenderBackendEnum.
    * 
    * @return Returns RenderAPIInterface.
    */
    SP<RenderAPIInterface> CreateRenderInterface(RenderBackendEnum backend);

    /**
    * @brief Vulkan APIInterface.
    */
    class VulkanInterface : public RenderAPIInterface
    {
    public:

        /**
        * @brief Destructor Function.
        */
        ~VulkanInterface() = default;
        
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