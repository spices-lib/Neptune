/**
* @file VulkanRenderBackend.h.
* @brief The VulkanRenderBackend Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"

namespace Neptune {

    /**
    * @brief VulkanRenderBackend Class.
    * This class defines the VulkanRenderBackend behaves.
    */
    class VulkanRenderBackend : public RenderFrontend
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] backend RenderBackendEnum.
        */
        VulkanRenderBackend(RenderBackendEnum backend);

        /**
        * @brief Destructor Function.
        */
        ~VulkanRenderBackend() override;

        /**
        * @brief Interface of Begin a frame.
        */
        void BeginFrame() override;

        /**
        * @brief Interface of End a frame.
        */
        void EndFrame() override;

        /**
        * @brief Interface of Render a frame.
        */
        void RenderFrame() override;

    private:

    };
}

#endif