/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackend.h"
#include "GPURuntime/Graphics/Backend/OpenGL/Infrastructure/InfrastructureHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

namespace Neptune::OpenGL {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::OpenGL)
        , m_GraphicsBackend(CreateUP<GraphicsBackend>())
    {}

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        const auto& window = Window::Instance();

        m_GraphicsBackend->OnInitialize(&window);

        RenderFrontend::OnInitialize();
    }

    void RenderBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        RenderFrontend::OnShutDown();

        m_GraphicsBackend->OnShutDown();
    }

    void RenderBackend::BeginFrame(Scene* scene) const
    {
        NEPTUNE_PROFILE_ZONE

        GetContext().Get<IWindowContext>()->MakeContextCurrent();

        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

        {
            GetContext().Get<IGraphicFence>()->Wait(clock.m_FrameIndex);
        }

        {
            DEBUGUTILS_BEGINLABEL(0, "MainGraphicQueue")
        }
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
        NEPTUNE_PROFILE_ZONE

        {
            DEBUGUTILS_ENDLABEL()
        }

        {
            DEBUGUTILS_BEGINLABEL(0, "PresentQueue")

            /*const auto& window = Window::Instance();

            window.SwapBuffers();*/

            DEBUGUTILS_ENDLABEL()
        }
    }

    void RenderBackend::Wait() const
    {
        NEPTUNE_PROFILE_ZONE

        m_GraphicsBackend->Wait();
    }

    GraphicsBackend::Context& RenderBackend::GetContext() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return m_GraphicsBackend->GetContext();
    }
    
    std::any RenderBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        return m_GraphicsBackend->CreateRHI(e, payload);
	}

    std::unordered_map<std::string, std::any> RenderBackend::AccessInfrastructure() const
	{
        NEPTUNE_PROFILE_ZONE

		return m_GraphicsBackend->AccessInfrastructure();
	}
    
}

#endif