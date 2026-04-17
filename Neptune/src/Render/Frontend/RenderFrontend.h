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

        /**
        * @brief Interface of Initialize.
        */
        virtual void OnInitialize();

        /**
        * @brief Interface of ShutDown.
        */
        virtual void OnShutDown();

        /**
        * @brief Interface of Begin a frame.
        * 
        * @param[in] scene Scene.
        */
        virtual void BeginFrame(class Scene* scene) = 0;

        /**
        * @brief Interface of End a frame.
        * 
        * @param[in] scene Scene.
        */
        virtual void EndFrame(class Scene* scene) = 0;

        /**
        * @brief Interface of Wait RenderBackend idle.
        */
        virtual void Wait() = 0;

        /**
        * @brief Interface of CreateRHI.
        * 
        * @param[in] e ERHI.
        * @param[in] payload RHI Payload.
        * 
        * @return Returns RHI::Impl
        */
        virtual std::any CreateRHI(RHI::ERHI e, void* payload) = 0;

        /**
        * @brief Interface of Access Infrastructure.
        *
        * @return Returns Infrastructure.
        */
        virtual std::unordered_map<std::string, std::any> AccessInfrastructure() = 0;

        /**
        * @brief Render a frame.
        *
        * @param[in] scene Scene.
        */
        void RenderFrame(class Scene* scene);

        /**
        * @brief Construct Default Passes.
        *
        * @param[in] rtSize Passes RT Size.
        */
        void ConstructDefaultPasses(const glm::vec2& rtSize = { 100.0f, 100.0f });

        /**
        * @brief Construct Slate Pass.
        */
        void ConstructSlatePass();

    protected:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] backend RenderBackendEnum.
        */
        RenderFrontend(RenderBackendEnum backend) : m_RenderBackendEnum(backend) {}

        /**
        * @brief Recreate SwapChain.
        */
        virtual void RecreateSwapChain();

    private:

        /**
        * @brief Add Pass.
        * 
        * @param[in] pass Pass.
        */
        void AddPass(SP<Render::Pass> pass);

    protected:

        RenderBackendEnum m_RenderBackendEnum;                 // @brief RenderBackendEnum.
        std::vector<SP<Render::Pass>> m_RenderPasses;          // @brief Container of Passes.
    };
}