/**
* @file OpenGLRenderBackend.h.
* @brief The OpenGLRenderBackend Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"

namespace Neptune {

    /**
    * @brief OpenGLRenderBackend Class.
    * This class defines the OpenGLRenderBackend behaves.
    */
    class OpenGLRenderBackend : public RenderFrontend
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] backend RenderBackendEnum.
        */
        OpenGLRenderBackend(RenderBackendEnum backend);

        /**
        * @brief Destructor Function.
        */
        ~OpenGLRenderBackend() override;

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