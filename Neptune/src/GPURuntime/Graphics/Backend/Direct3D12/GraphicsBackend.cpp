/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"

namespace Neptune::Direct3D12 {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(GraphicsBackendEnum::Direct3D12)
    {
        NEPTUNE_PROFILE_ZONE

    	HandleResultDelegate::SetHandler([&](HRESULT result) { HandleResult(result); });
    }

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE
    	
        m_Context = CreateSP<Context>();

        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<IFactory>();
        m_Context->Registry<IDevice>();

        m_Context->Registry<IGraphicQueue>();
        m_Context->Registry<IComputeQueue>();
    	
        m_Context->Registry<IGraphicFence>(MaxFrameInFlight);
        m_Context->Registry<IComputeFence>(MaxFrameInFlight);

        m_Context->Registry<IGraphicCommandList>(MaxFrameInFlight);
        m_Context->Registry<IComputeCommandList>(MaxFrameInFlight);

        m_Context->Registry<IRTVDescriptorHeap>();
        m_Context->Registry<IDSVDescriptorHeap>();
        m_Context->Registry<ISRVDescriptorHeap>();
        m_Context->Registry<IUAVDescriptorHeap>();
    }

    void GraphicsBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        m_Context->UnRegistry();
    }

    Context& GraphicsBackend::GetContext() const
    {
        return *m_Context;
    }

    void GraphicsBackend::Wait() const
    {
        NEPTUNE_PROFILE_ZONE
    }

    std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
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

    std::unordered_map<std::string, std::any> GraphicsBackend::AccessInfrastructure() const
    {
        NEPTUNE_PROFILE_ZONE

        std::unordered_map<std::string, std::any> infrastructure;

        infrastructure["Device"]                     = static_cast<ID3D12Device*>(m_Context->Get<IDevice>()->Handle());
		infrastructure["CommandQueue"]               = static_cast<ID3D12CommandQueue*>(m_Context->Get<IGraphicQueue>()->Handle());
		infrastructure["RTVFormat"]                  = DXGI_FORMAT_B8G8R8A8_UNORM;
		infrastructure["DSVFormat"]                  = DXGI_FORMAT_B8G8R8A8_UNORM;
		infrastructure["SRVDescriptorHeap"]          = static_cast<ID3D12DescriptorHeap*>(m_Context->Get<ISRVDescriptorHeap>()->Handle());
        infrastructure["SRVCPUHandle"]               = m_Context->Get<ISRVDescriptorHeap>()->Handle()->GetCPUDescriptorHandleForHeapStart();
        infrastructure["SRVGPUHandle"]               = m_Context->Get<ISRVDescriptorHeap>()->Handle()->GetGPUDescriptorHandleForHeapStart();

        return infrastructure;
    }
}

#endif