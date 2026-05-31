/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "RenderBackend.h"
#include "GPURuntime/Graphics/Backend/Direct3D12/Infrastructure/InfrastructureHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

namespace Neptune::Direct3D12 {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::Direct3D12)
		, m_GraphicsBackend(CreateUP<GraphicsBackend>())
    {}

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

    	m_GraphicsBackend->OnInitialize();
    	
        const auto& window = Window::Instance();

    	GetContext().Registry<ISwapChain>(MaxFrameInFlight, window.Implement(), window.NativeWindow());
    	
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

        auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

    	auto& context = m_GraphicsBackend->GetContext();
    	
		{
			context.Get<IComputeFence>()->Wait(clock.m_FrameIndex);

			context.Get<IGraphicFence>()->Wait(clock.m_FrameIndex);
		}

		{
            context.Get<IComputeCommandList>()->Begin(clock.m_FrameIndex);

            context.Get<IGraphicCommandList>()->Begin(clock.m_FrameIndex);
		}
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
        NEPTUNE_PROFILE_ZONE

        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

    	auto& context = m_GraphicsBackend->GetContext();
    	
		{
			context.Get<IComputeCommandList>()->End(clock.m_FrameIndex);

			context.Get<IGraphicCommandList>()->End(clock.m_FrameIndex);
		}

		{
            DEBUGUTILS_BEGINQUEUELABEL(context.Get<IComputeQueue>()->Handle(), "MainComputeQueue")

			context.Get<IComputeQueue>()->Submit(context.Get<IComputeCommandList>()->Handle(clock.m_FrameIndex), context.Get<IComputeFence>()->IHandle(clock.m_FrameIndex));
        	
			DEBUGUTILS_ENDQUEUELABEL(context.Get<IComputeQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			context.Get<IGraphicQueue>()->Submit(context.Get<IGraphicCommandList>()->Handle(clock.m_FrameIndex), context.Get<IGraphicFence>()->IHandle(clock.m_FrameIndex));
        	
			DEBUGUTILS_ENDQUEUELABEL(context.Get<IGraphicQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			auto result = context.Get<ISwapChain>()->Present();

			DEBUGUTILS_ENDQUEUELABEL(context.Get<IGraphicQueue>()->Handle())
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