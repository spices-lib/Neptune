/**
* @file GraphicsBackend.h.
* @brief The GraphicsBackend Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D11

#include "Core/Core.h"
#include "Device/Graphics/Frontend/GraphicsFrontend.h"
#include "Infrastructure/Enum.h"
#include "Device/Graphics/Backend/Common/Concept.h"

namespace Neptune::Render::Common {

    template<typename T>
    requires IsEnum<T>
    class Context;
}

namespace Neptune::Direct3D11 {

    /**
    * @brief GraphicsBackend Class.
    * This class defines the GraphicsBackend behaves.
    */
    class GraphicsBackend : public GraphicsFrontend
    {
    public:

        using Context = Render::Common::Context<EInfrastructure>;

    public:

        /**
        * @brief Constructor Function.
        */
        GraphicsBackend();

        /**
        * @brief Destructor Function.
        */
        ~GraphicsBackend() override = default;

        /**
        * @brief Interface of Initialize.
        * 
        * @param[in] window Window.
        */
        void OnInitialize(const Window* window = nullptr) override;

        /**
        * @brief Interface of ShutDown.
        */
        void OnShutDown() override;

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

        /**
        * @brief Get Context.
        *
        * @return Returns Context.
        */
        Context& GetContext() const;

    private:

        SP<Context> m_Context; // @brief This Context.

    };
}

#endif