/**
* @file GraphicsBackend.h.
* @brief The GraphicsBackend Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "GPURuntime/Graphic/Frontend/GraphicsFrontend.h"

namespace Neptune::Metal {

    /**
    * @brief GraphicsBackend Class.
    * This class defines the GraphicsBackend behaves.
    */
    class GraphicsBackend : public GraphicsFrontend
    {
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