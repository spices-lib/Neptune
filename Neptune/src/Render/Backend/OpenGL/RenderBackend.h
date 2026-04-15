/**
* @file RenderBackend.h.
* @brief The RenderBackend Class Definitions.
* @author Spices.
*/

#pragma once

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"

namespace Neptune {

    class Scene;
}

namespace Neptune::OpenGL {

    /**
    * @brief RenderBackend Class.
    * This class defines the RenderBackend behaves.
    */
    class RenderBackend : public RenderFrontend
    {
    public:

        /**
        * @brief Constructor Function.
        */
        RenderBackend();

        /**
        * @brief Destructor Function.
        */
        ~RenderBackend() override = default;

        /**
        * @brief Interface of Initialize.
        */
        void OnInitialize() override;

        /**
        * @brief Interface of ShutDown.
        */
        void OnShutDown() override;

        /**
        * @brief Interface of Begin a frame.
        *
        * @param[in] scene Scene.
        */
        void BeginFrame(Scene* scene) override;

        /**
        * @brief Interface of End a frame.
        *
        * @param[in] scene Scene.
        */
        void EndFrame(Scene* scene) override;

        /**
        * @brief Interface of Wait RenderBackend idle.
        */
        void Wait() override;

        /**
        * @brief Interface of CreateRHI.
        *
        * @param[in] e ERHI.
        * @param[in] payload RHI Payload.
        *
        * @return Returns RHI::Impl
        */
        std::any CreateRHI(RHI::ERHI e, void* payload) override;

    private:

    };
}

#endif