/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "RenderBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"

namespace Neptune::Direct3D12 {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::Direct3D12)
    {
        NEPTUNE_PROFILE_ZONE

    	HandleResultDelegate::SetHandler([&](HRESULT result) { HandleResult(result); });
    }

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        const auto& window = Window::Instance();

        m_Context = CreateSP<Context>();

        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<IFactory>();
        m_Context->Registry<IDevice>();

        m_Context->Registry<IGraphicQueue>();
        m_Context->Registry<IComputeQueue>();

    	m_Context->Registry<ISwapChain>(MaxFrameInFlight, window.Implement(), window.NativeWindow());
    	
        m_Context->Registry<IGraphicFence>(MaxFrameInFlight);
        m_Context->Registry<IComputeFence>(MaxFrameInFlight);

        m_Context->Registry<IGraphicCommandList>(MaxFrameInFlight);
        m_Context->Registry<IComputeCommandList>(MaxFrameInFlight);

        RenderFrontend::OnInitialize();
    }

    void RenderBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        RenderFrontend::OnShutDown();

        m_Context->UnRegistry();
    }

    Context& RenderBackend::GetContext() const
    {
        return *m_Context;
    }

    void RenderBackend::BeginFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE

        auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

		{
			m_Context->Get<IComputeFence>()->Wait(clock.m_FrameIndex);

			m_Context->Get<IGraphicFence>()->Wait(clock.m_FrameIndex);
		}

		{
            m_Context->Get<IComputeCommandList>()->Begin(clock.m_FrameIndex);

            m_Context->Get<IGraphicCommandList>()->Begin(clock.m_FrameIndex);
		}
    }

    void RenderBackend::EndFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE

        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

		{
			m_Context->Get<IComputeCommandList>()->End(clock.m_FrameIndex);

			m_Context->Get<IGraphicCommandList>()->End(clock.m_FrameIndex);
		}

		{
            DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IComputeQueue>()->Handle(), "MainComputeQueue")

			m_Context->Get<IComputeQueue>()->Submit(m_Context->Get<IComputeCommandList>()->Handle(clock.m_FrameIndex), m_Context->Get<IComputeFence>()->IHandle(clock.m_FrameIndex));
        	
			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IComputeQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			m_Context->Get<IGraphicQueue>()->Submit(m_Context->Get<IGraphicCommandList>()->Handle(clock.m_FrameIndex), m_Context->Get<IGraphicFence>()->IHandle(clock.m_FrameIndex));
        	
			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IGraphicQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			auto result = m_Context->Get<ISwapChain>()->Present();

			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IGraphicQueue>()->Handle())
		}
    }

    void RenderBackend::Wait()
    {
        NEPTUNE_PROFILE_ZONE
    }

    std::any RenderBackend::CreateRHI(RHI::ERHI e, void* payload)
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
            case RHI::ERHI::RenderPass:       return std::dynamic_pointer_cast<RHI::RHIRenderPass::Impl>        (CreateSP<RenderPass>           (*m_Context));
			case RHI::ERHI::DescriptorList:   return std::dynamic_pointer_cast<RHI::RHIDescriptorList::Impl>    (CreateSP<DescriptorList>       (*m_Context));
			case RHI::ERHI::Pipeline:         return std::dynamic_pointer_cast<RHI::RHIPipeline::Impl>          (CreateSP<Pipeline>             (*m_Context));
			case RHI::ERHI::Shader:           return std::dynamic_pointer_cast<RHI::RHIShader::Impl>            (CreateSP<Shader>               (*m_Context));
			case RHI::ERHI::RenderTarget:     return std::dynamic_pointer_cast<RHI::RHIRenderTarget::Impl>      (CreateSP<RenderTarget>         (*m_Context));
			case RHI::ERHI::VertexBuffer:     return std::dynamic_pointer_cast<RHI::RHIVertexBuffer::Impl>      (CreateSP<VertexBuffer>         (*m_Context));
			case RHI::ERHI::IndexBuffer:      return std::dynamic_pointer_cast<RHI::RHIIndexBuffer::Impl>       (CreateSP<IndexBuffer>          (*m_Context));
            case RHI::ERHI::CmdList:          return std::dynamic_pointer_cast<RHI::RHICmdList::Impl>           (CreateSP<CmdList>              (*m_Context));
			case RHI::ERHI::CmdList2:         return std::dynamic_pointer_cast<RHI::RHICmdList2::Impl>          (CreateSP<CmdList2>             (*m_Context));
            case RHI::ERHI::Decoder:          NEPTUNE_CORE_ERROR("Direct3D12 do not support Decoder RHI.")       return nullptr;
            case RHI::ERHI::OpticalFlow:      NEPTUNE_CORE_ERROR("Direct3D12 do not support OpticalFlow RHI.")   return nullptr;
            default:                          NEPTUNE_CORE_ERROR("Direct3D12 do not support this RHI.")          return nullptr;
		}
	}

    std::unordered_map<std::string, std::any> RenderBackend::AccessInfrastructure()
    {
        NEPTUNE_PROFILE_ZONE

        std::unordered_map<std::string, std::any> infrastructure;

        return infrastructure;
    }
}

#endif