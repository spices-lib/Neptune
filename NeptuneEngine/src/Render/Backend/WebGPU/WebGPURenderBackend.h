/**
* @file WebGPURenderBackend.h.
* @brief The WebGPURenderBackend Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"

namespace Neptune {

    class WebGPUContext;

    /**
    * @brief WebGPURenderBackend Class.
    * This class defines the WebGPURenderBackend behaves.
    */
    class WebGPURenderBackend : public RenderFrontend
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] backend RenderBackendEnum.
        */
        WebGPURenderBackend(RenderBackendEnum backend);

        /**
        * @brief Destructor Function.
        */
        ~WebGPURenderBackend() override;

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

        /**
        * @brief WebGPU Context.
        */
        SP<WebGPUContext> m_Context;
    };
}

#endif