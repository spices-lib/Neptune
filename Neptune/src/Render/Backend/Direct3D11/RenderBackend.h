/**
* @file RenderBackend.h.
* @brief The RenderBackend Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"
#include "Device/Graphics/Backend/Direct3D11/GraphicsBackend.h"

namespace Neptune {

    class Scene;
}

namespace Neptune::Direct3D11 {

    /**
    * @brief Direct3D11::RenderBackend Class.
    * This class defines the Direct3D11::RenderBackend behaves.
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