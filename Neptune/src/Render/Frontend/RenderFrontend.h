/**
* @file RenderFrontend.h.
* @brief The RenderFrontend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Core/Event/Event.h"
#include "RHI/RHI.h"
#include "Enum.h"

#include <vector>
#include <any>
#include <glm/glm.hpp>

namespace Neptune {

    namespace Render {

        class Pass;
    }

    /**
    * @brief RenderFrontend Class.
    * This class defines the RenderFrontEnd behaves.
    */
    class RenderFrontend : public NonCopyable
    {
    public:

        /**
        * @brief Create Render Frontend.
        *
        * @param[in] backend RenderBackendEnum.
        *
        * @return Returns Render Frontend pointer.
        */
        static SP<RenderFrontend> Create(RenderBackendEnum backend);

    public:

        /**
        * @brief Destructor Function.
        */
        ~RenderFrontend() override = default;

        virtual void OnInitialize();
        virtual void OnShutDown();

        /**
        * @brief Interface of Begin a frame.
        */
        virtual void BeginFrame() = 0;

        /**
        * @brief Interface of End a frame.
        */
        virtual void EndFrame() = 0;

        /**
        * @brief Render a frame.
        */
        void RenderFrame();

        virtual void Wait() = 0;
        virtual void InitSlateModule() = 0;
        virtual void ShutdownSlateModule() = 0;
        virtual std::any CreateRHI(RHI::ERHI e, void* payload) = 0;

        void ConstructDefaultPasses(const glm::vec2& rtSize = { 100.0f, 100.0f });

        void ConstructSlatePass();

    protected:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] backend RenderBackendEnum.
        */
        RenderFrontend(RenderBackendEnum backend) : m_RenderBackendEnum(backend) {}

        virtual void RecreateSwapChain();

    private:

        void AddPass(SP<Render::Pass> pass);

    protected:

        /**
        * @brief RenderBackendEnum.
        */
        RenderBackendEnum m_RenderBackendEnum;

        std::vector<SP<Render::Pass>> m_RenderPasses;
    };
}