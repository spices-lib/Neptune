/**
* @file WebGLRenderBackend.h.
* @brief The WebDLRenderBackend Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"

namespace Neptune {

    /**
    * @brief WebGLRenderBackend Class.
    * This class defines the WebGLRenderBackend behaves.
    */
    class WebGLRenderBackend : public RenderFrontend
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] backend RenderBackendEnum.
        */
        WebGLRenderBackend(RenderBackendEnum backend);

        /**
        * @brief Destructor Function.
        */
        virtual ~WebGLRenderBackend();

        /**
        * @brief Interface of Begin a frame.
        */
        virtual void BeginFrame() override;

        /**
        * @brief Interface of End a frame.
        */
        virtual void EndFrame() override;

        /**
        * @brief Interface of Render a frame.
        */
        virtual void RenderFrame() override;

    private:

    };
}

#endif