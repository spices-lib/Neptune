/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"
#include "Converter.h"
#include "Window/Window.h"

namespace Neptune::Vulkan {
	
	GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(GraphicsBackendEnum::Vulkan)
    {
		NEPTUNE_PROFILE_ZONE

		HandleResultDelegate::SetHandler([&](VkResult result) {
			HandleResult(
				result, 
				GetContext().Has<IPhysicalDevice>() ? GetContext().Get<IPhysicalDevice>()->Handle() : nullptr,
				GetContext().Has<IDevice>() ? GetContext().Get<IDevice>()->Handle() : nullptr, 
				GetContext().Get<IFunctions>()->vkGetDeviceFaultInfoEXT
			); 
		});
	}

	void GraphicsBackend::OnInitialize(const Window* window)
	{
		NEPTUNE_PROFILE_ZONE
    	
		m_Context = CreateSP<Context>();

		m_Context->Registry<IInstance>(window ? window->Extension() : std::vector{ VK_KHR_SURFACE_EXTENSION_NAME });
		m_Context->Registry<IDebugUtilsObject>();
		if (window)
		{
			m_Context->Registry<ISurface>(window->Implement(), window->NativeWindow());
		}
		m_Context->Registry<IPhysicalDevice>();
		m_Context->Registry<IDevice>();

		m_Context->Registry<IMemoryAllocator>();
					  
		m_Context->Registry<IGraphicQueueSemaphore>(MaxFrameInFlight);
		m_Context->Registry<IGraphicFence>(MaxFrameInFlight);

		m_Context->Registry<IComputeQueueSemaphore>(MaxFrameInFlight);
		m_Context->Registry<IComputeFence>(MaxFrameInFlight);

		m_Context->Registry<IGraphicCommandPool>();
		m_Context->Registry<IGraphicCommandBuffer>(MaxFrameInFlight);

		m_Context->Registry<IComputeCommandPool>();
		m_Context->Registry<IComputeCommandBuffer>(MaxFrameInFlight);

		m_Context->Registry<IDescriptorPool>();

		m_Context->Registry<IGraphicThreadCommandPool>();
		m_Context->Registry<IComputeThreadCommandPool>();
		m_Context->Registry<ITransferThreadCommandPool>();
		m_Context->Registry<IVideoEncodeThreadCommandPool>();
		m_Context->Registry<IVideoDecodeThreadCommandPool>();
		m_Context->Registry<IOpticalFlowThreadCommandPool>();
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

		m_Context->Get<IDevice>()->Wait();
	}

	std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
		NEPTUNE_PROFILE_ZONE

		switch(e)
		{
			case RHI::ERHI::RenderPass:       return std::dynamic_pointer_cast<RHI::RHIRenderPass::Impl>    (CreateSP<RenderPass>           (*m_Context));
			case RHI::ERHI::DescriptorList:   return std::dynamic_pointer_cast<RHI::RHIDescriptorList::Impl>(CreateSP<DescriptorList>       (*m_Context));
			case RHI::ERHI::Pipeline:         return std::dynamic_pointer_cast<RHI::RHIPipeline::Impl>      (CreateSP<Pipeline>             (*m_Context));
			case RHI::ERHI::Shader:           return std::dynamic_pointer_cast<RHI::RHIShader::Impl>        (CreateSP<Shader>               (*m_Context));
			case RHI::ERHI::RenderTarget:     return std::dynamic_pointer_cast<RHI::RHIRenderTarget::Impl>  (CreateSP<RenderTarget>         (*m_Context));
			case RHI::ERHI::VertexBuffer:     return std::dynamic_pointer_cast<RHI::RHIVertexBuffer::Impl>  (CreateSP<VertexBuffer>         (*m_Context));
			case RHI::ERHI::IndexBuffer:      return std::dynamic_pointer_cast<RHI::RHIIndexBuffer::Impl>   (CreateSP<IndexBuffer>          (*m_Context));
			case RHI::ERHI::CmdList:          return std::dynamic_pointer_cast<RHI::RHICmdList::Impl>       (CreateSP<CmdList>              (*m_Context));
			case RHI::ERHI::CmdList2:         return std::dynamic_pointer_cast<RHI::RHICmdList2::Impl>      (CreateSP<CmdList2>             (*m_Context));
			case RHI::ERHI::Decoder:          return std::dynamic_pointer_cast<RHI::RHIDecoder::Impl>       (Decoder::Create                (*m_Context, payload));
			case RHI::ERHI::OpticalFlow:      return std::dynamic_pointer_cast<RHI::RHIOpticalFlow::Impl>   (CreateSP<OpticalFlowSession>   (*m_Context));
			default:                          NEPTUNE_CORE_ERROR("Vulkan do not support this RHI.")          return nullptr;
		}
	}

	std::unordered_map<std::string, std::any> GraphicsBackend::AccessInfrastructure() const
	{
		NEPTUNE_PROFILE_ZONE

		std::unordered_map<std::string, std::any> infrastructure;

		infrastructure["Instance"]              = m_Context->Get<IInstance>()->Handle();
		infrastructure["PhysicalDevice"]        = m_Context->Get<IPhysicalDevice>()->Handle();
		infrastructure["Device"]                = m_Context->Get<IDevice>()->Handle();
		infrastructure["GraphicQueueFamily"]    = m_Context->Get<IPhysicalDevice>()->GetQueueFamilies().graphic.value();
		infrastructure["GraphicQueue"]          = m_Context->Get<IGraphicQueue>()->Handle();
		infrastructure["DescriptorPool"]        = m_Context->Get<IDescriptorPool>()->Handle();
		infrastructure["MSAASamples"]           = VK_SAMPLE_COUNT_1_BIT;
		infrastructure["CheckVkResultFn"]       = +[](VkResult result) { std::invoke(HandleResultDelegate::GetHandler(), result); };

		return infrastructure;
	}

}

#endif