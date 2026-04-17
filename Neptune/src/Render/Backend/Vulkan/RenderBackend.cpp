/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"
#include "Render/Backend/Vulkan/Converter.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Frontend/Pass/SlatePass.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/ClockComponent.h"

namespace Neptune::Vulkan {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::Vulkan)
    {
		NEPTUNE_PROFILE_ZONE

		HandleVulkanResultDelegate::SetHandler([&](VkResult result) { 
			HandleVulkanResult(
				result, 
				GetContext().Has<IPhysicalDevice>() ? GetContext().Get<IPhysicalDevice>()->Handle() : nullptr,
				GetContext().Has<IDevice>() ? GetContext().Get<IDevice>()->Handle() : nullptr, 
				GetContext().Get<IFunctions>()->vkGetDeviceFaultInfoEXT
			); 
		});
	}

	void RenderBackend::OnInitialize()
	{
		NEPTUNE_PROFILE_ZONE

    	const auto& window = Window::Instance();
    	
		m_Context = CreateSP<Context>();

		m_Context->Registry<IInstance>(window.Extension());
		m_Context->Registry<IDebugUtilsObject>();
		m_Context->Registry<ISurface>(window.Implement(), window.NativeWindow());
		m_Context->Registry<IPhysicalDevice>();
		m_Context->Registry<IDevice>();

		m_Context->Registry<IMemoryAllocator>();
		m_Context->Registry<ISwapChain>(MaxFrameInFlight);
					  
		m_Context->Registry<IGraphicImageSemaphore>(MaxFrameInFlight);
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

		auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		{
			m_Context->Get<IComputeFence>()->Wait(clock.m_FrameIndex);

			m_Context->Get<IGraphicFence>()->Wait(clock.m_FrameIndex);
		}

		{
			if (!m_Context->Get<ISwapChain>()->GetNextImage(m_Context->Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameIndex), clock.m_ImageIndex))
			{
				RecreateSwapChain();
			}
		}

		{
			VkCommandBufferBeginInfo               beginInfo{};
			beginInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags                      = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			beginInfo.pInheritanceInfo           = nullptr;

            m_Context->Get<IComputeCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);

            beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
            m_Context->Get<IGraphicCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);
		}
    }

    void RenderBackend::EndFrame(Scene* scene)
    {
		NEPTUNE_PROFILE_ZONE

		auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		{
			m_Context->Get<IComputeCommandBuffer>()->End(clock.m_FrameIndex);

			m_Context->Get<IGraphicCommandBuffer>()->End(clock.m_FrameIndex);
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IComputeQueue>()->Handle(), "MainComputeQueue")

			VkSemaphore waitSemaphores[]         = { m_Context->Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameIndex) };
			VkSemaphore signalSemaphores[]       = { m_Context->Get<IComputeQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkPipelineStageFlags waitStages[]    = { VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT };

			VkSubmitInfo                           submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount        = 1;
			submitInfo.pWaitSemaphores           = waitSemaphores;
			submitInfo.pWaitDstStageMask         = waitStages;
			submitInfo.commandBufferCount        = 1;
			submitInfo.pCommandBuffers           = &m_Context->Get<IComputeCommandBuffer>()->Handle(clock.m_FrameIndex);
			submitInfo.signalSemaphoreCount      = 1;
			submitInfo.pSignalSemaphores         = signalSemaphores;

			m_Context->Get<IComputeQueue>()->Submit(submitInfo, m_Context->Get<IComputeFence>()->Handle(clock.m_FrameIndex));

			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IComputeQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			VkSemaphore waitSemaphores[]         = { m_Context->Get<IComputeQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkSemaphore signalSemaphores[]       = { m_Context->Get<IGraphicQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkPipelineStageFlags waitStages[]    = { VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

			VkSubmitInfo                           submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount        = 1;
			submitInfo.pWaitSemaphores           = waitSemaphores;
			submitInfo.pWaitDstStageMask         = waitStages;
			submitInfo.commandBufferCount        = 1;
			submitInfo.pCommandBuffers           = &m_Context->Get<IGraphicCommandBuffer>()->Handle(clock.m_FrameIndex);
			submitInfo.signalSemaphoreCount      = 1;
			submitInfo.pSignalSemaphores         = signalSemaphores;

			m_Context->Get<IGraphicQueue>()->Submit(submitInfo, m_Context->Get<IGraphicFence>()->Handle(clock.m_FrameIndex));

			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IGraphicQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IPresentQueue>()->Handle(), "PresentQueue")

			VkPresentInfoKHR                       presentInfo{};
			presentInfo.sType                    = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount       = 1;
			presentInfo.pWaitSemaphores          = &m_Context->Get<IGraphicQueueSemaphore>()->Handle(clock.m_FrameIndex);
			presentInfo.swapchainCount           = 1;
			presentInfo.pImageIndices            = &clock.m_ImageIndex;
			presentInfo.pResults                 = nullptr;

			if (!m_Context->Get<ISwapChain>()->Present(presentInfo))
			{
				RecreateSwapChain();
			}

			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IPresentQueue>()->Handle())
		}
    }

	void RenderBackend::Wait()
	{
		NEPTUNE_PROFILE_ZONE

		m_Context->Get<IDevice>()->Wait();
	}

	std::any RenderBackend::CreateRHI(RHI::ERHI e, void* payload)
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
			default: return nullptr;
		}
	}

	std::unordered_map<std::string, std::any> RenderBackend::AccessInfrastructure()
	{
		NEPTUNE_PROFILE_ZONE

		std::unordered_map<std::string, std::any> infrastructure;

		auto pass = std::dynamic_pointer_cast<Render::SlatePass>(m_RenderPasses.back());

		infrastructure["Instance"]              = m_Context->Get<IInstance>()->Handle();
		infrastructure["PhysicalDevice"]        = m_Context->Get<IPhysicalDevice>()->Handle();
		infrastructure["Device"]                = m_Context->Get<IDevice>()->Handle();
		infrastructure["GraphicQueueFamily"]    = m_Context->Get<IPhysicalDevice>()->GetQueueFamilies().graphic.value();
		infrastructure["GraphicQueue"]          = m_Context->Get<IGraphicQueue>()->Handle();
		infrastructure["DescriptorPool"]        = m_Context->Get<IDescriptorPool>()->Handle();
		infrastructure["RenderPass"]            = pass->GetRenderPass()->GetRHIImpl<RenderPass>()->Handle();
		infrastructure["MSAASamples"]           = VK_SAMPLE_COUNT_1_BIT;
		infrastructure["Allocator"]             = VK_NULL_HANDLE;
		infrastructure["CheckVkResultFn"]       = [](VkResult result) { std::invoke(HandleVulkanResultDelegate::GetHandler(), result); };

		return infrastructure;
	}

	void RenderBackend::RecreateSwapChain()
	{
		NEPTUNE_PROFILE_ZONE

		GetContext().Get<IGraphicQueue>()->Wait();

		GetContext().UnRegistry<ISwapChain>();

		GetContext().Registry<ISwapChain>(MaxFrameInFlight);

		RenderFrontend::RecreateSwapChain();
	}
}

#endif