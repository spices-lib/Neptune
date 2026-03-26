/**
* @file RenderBackend.h.
* @brief The RenderBackend Class Definitions.
* @author Spices.
*/

#pragma once
#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"

namespace Neptune::WebGPU {

    class Context;

    /**
    * @brief RenderBackend Class.
    * This class defines the RenderBackend behaves.
    */
    class RenderBackend : public RenderFrontend
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] backend RenderBackendEnum.
        */
        RenderBackend(RenderBackendEnum backend);

        /**
        * @brief Destructor Function.
        */
        ~RenderBackend() override;

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
        SP<Context> m_Context;
    };
}

#endif