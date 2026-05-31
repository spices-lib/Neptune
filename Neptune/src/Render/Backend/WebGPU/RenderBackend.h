/**
* @file RenderBackend.h.
* @brief The RenderBackend Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "Core/Core.h"
#include "GPURuntime/Graphics/Backend/WebGPU/GraphicsBackend.h"

namespace Neptune {

    class Scene;
}

namespace Neptune::WebGPU {

    /**
    * @brief WebGPU::RenderBackend Class.
    * This class defines the WebGPU::RenderBackend behaves.
    */
    class RenderBackend : public RenderFrontend
    {
    public:

        using Context = Render::Common::Context<EInfrastructure>;

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
        void BeginFrame(Scene* scene) const override;

        /**
        * @brief Interface of End a frame.
        *
        * @param[in] scene Scene.
        */
        void EndFrame(Scene* scene) const override;

        /**
        * @brief Interface of Wait RenderBackend idle.
        */
        void Wait() const override;

        /**
        * @brief Interface of CreateRHI.
        *
        * @param[in] e ERHI.
        * @param[in] payload RHI Payload.
        *
        * @return Returns RHI::Impl
        */
        std::any CreateRHI(RHI::ERHI e, void* payload) const override;

        /**
        * @brief Interface of Access Infrastructure.
        *
        * @return Returns Infrastructure.
        */
        std::unordered_map<std::string, std::any> AccessInfrastructure() const override;

    private:

        /**
        * @brief Get Context.
        *
        * @return Returns Context.
        */
        GraphicsBackend::Context& GetContext() const;

    private:

        UP<GraphicsBackend> m_GraphicsBackend; // @brief This GraphicsBackend.
    };
}

#endif