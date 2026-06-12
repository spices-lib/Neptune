/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "RenderBackend.h"
#include "Device/Graphics/Frontend/RHI/RenderPass.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/InfrastructureHeader.h"
#include "Device/Graphics/Backend/Vulkan/RHI/RenderPass.h"
#include "Render/Frontend/Pass/SlatePass.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

namespace Neptune::Vulkan {
	
    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::Vulkan)
		, m_GraphicsBackend(CreateUP<GraphicsBackend>())
    {}

	void RenderBackend::OnInitialize()
	{
		NEPTUNE_PROFILE_ZONE
    	
		const auto& window = Window::Instance();

    	m_GraphicsBackend->OnInitialize(&window);
		
		GetContext().Registry<ISwapChain>(MaxFrameInFlight);

		GetContext().Registry<IGraphicImageSemaphore>(MaxFrameInFlight);

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
			if (!context.Get<ISwapChain>()->GetNextImage(context.Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameIndex), clock.m_ImageIndex))
			{
				RecreateSwapChain();
			}
		}

		{
			VkCommandBufferBeginInfo               beginInfo{};
			beginInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags                      = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			beginInfo.pInheritanceInfo           = nullptr;

            context.Get<IComputeCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);

            beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
            context.Get<IGraphicCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);
		}
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
		NEPTUNE_PROFILE_ZONE

		const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

    	auto& context = m_GraphicsBackend->GetContext();
    	
		{
			context.Get<IComputeCommandBuffer>()->End(clock.m_FrameIndex);

			context.Get<IGraphicCommandBuffer>()->End(clock.m_FrameIndex);
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IComputeQueue>()->Handle(), "MainComputeQueue")

			VkSemaphore waitSemaphores[]         = { context.Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameIndex) };
			VkSemaphore signalSemaphores[]       = { context.Get<IComputeQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkPipelineStageFlags waitStages[]    = { VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT };

			VkSubmitInfo                           submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount        = 1;
			submitInfo.pWaitSemaphores           = waitSemaphores;
			submitInfo.pWaitDstStageMask         = waitStages;
			submitInfo.commandBufferCount        = 1;
			submitInfo.pCommandBuffers           = &context.Get<IComputeCommandBuffer>()->Handle(clock.m_FrameIndex);
			submitInfo.signalSemaphoreCount      = 1;
			submitInfo.pSignalSemaphores         = signalSemaphores;

			context.Get<IComputeQueue>()->Submit(submitInfo, context.Get<IComputeFence>()->Handle(clock.m_FrameIndex));

			DEBUGUTILS_ENDQUEUELABEL(context.Get<IComputeQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			VkSemaphore waitSemaphores[]         = { context.Get<IComputeQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkSemaphore signalSemaphores[]       = { context.Get<IGraphicQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkPipelineStageFlags waitStages[]    = { VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

			VkSubmitInfo                           submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount        = 1;
			submitInfo.pWaitSemaphores           = waitSemaphores;
			submitInfo.pWaitDstStageMask         = waitStages;
			submitInfo.commandBufferCount        = 1;
			submitInfo.pCommandBuffers           = &context.Get<IGraphicCommandBuffer>()->Handle(clock.m_FrameIndex);
			submitInfo.signalSemaphoreCount      = 1;
			submitInfo.pSignalSemaphores         = signalSemaphores;

			context.Get<IGraphicQueue>()->Submit(submitInfo, context.Get<IGraphicFence>()->Handle(clock.m_FrameIndex));

			DEBUGUTILS_ENDQUEUELABEL(context.Get<IGraphicQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(context.Get<IPresentQueue>()->Handle(), "PresentQueue")

			VkPresentInfoKHR                       presentInfo{};
			presentInfo.sType                    = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount       = 1;
			presentInfo.pWaitSemaphores          = &context.Get<IGraphicQueueSemaphore>()->Handle(clock.m_FrameIndex);
			presentInfo.swapchainCount           = 1;
			presentInfo.pImageIndices            = &clock.m_ImageIndex;
			presentInfo.pResults                 = nullptr;

			if (!context.Get<ISwapChain>()->Present(presentInfo))
			{
				RecreateSwapChain();
			}

			DEBUGUTILS_ENDQUEUELABEL(context.Get<IPresentQueue>()->Handle())
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

		auto infrastructure = m_GraphicsBackend->AccessInfrastructure();

		auto pass = std::dynamic_pointer_cast<Render::SlatePass>(m_RenderPasses.back());
    	
		infrastructure["RenderPass"] = pass->GetRenderPass()->GetRHIImpl<RenderPass>()->Handle();

		return infrastructure;
	}

	void RenderBackend::RecreateSwapChain() const
	{
		NEPTUNE_PROFILE_ZONE

		GetContext().Get<IGraphicQueue>()->Wait();

		GetContext().UnRegistry<ISwapChain>();

		GetContext().Registry<ISwapChain>(MaxFrameInFlight);

		RenderFrontend::RecreateSwapChain();
	}
	
}

#endif