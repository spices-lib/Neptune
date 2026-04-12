/**
* @file RenderBackendInterface.cpp.
* @brief The Interface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderBackendInterface.h"

#include <backends/imgui_impl_vulkan.h>

namespace Neptune::imgui {

	SP<RenderAPIInterface> CreateRenderInterface(RenderBackendEnum backend)
	{
		NEPTUNE_PROFILE_ZONE

		switch (backend)
		{
			case RenderBackendEnum::Vulkan: return CreateSP<VulkanInterface>();
			default:
			{
				NEPTUNE_CORE_CRITICAL("Not supported RenderBackend in ImGui Slate Configuration.")
				return nullptr;
			}
		}
	}

	void VulkanInterface::OnInitialize() const
	{
		NEPTUNE_PROFILE_ZONE

		//auto pass = std::dynamic_pointer_cast<Render::SlatePass>(m_RenderPasses.back());

		ImGui_ImplVulkan_InitInfo             init_info{};
		/*init_info.Instance                  = m_Context->Get<IInstance>()->Handle();
		init_info.PhysicalDevice            = m_Context->Get<IPhysicalDevice>()->Handle();
		init_info.Device                    = m_Context->Get<IDevice>()->Handle();
		init_info.QueueFamily               = m_Context->Get<IPhysicalDevice>()->GetQueueFamilies().graphic.value();
		init_info.Queue                     = m_Context->Get<IGraphicQueue>()->Handle();
		init_info.PipelineCache             = VK_NULL_HANDLE;
		init_info.DescriptorPool            = m_Context->Get<IDescriptorPool>()->Handle();
		init_info.RenderPass                = pass->GetRenderPass()->GetRHIImpl<RenderPass>()->Handle();
		init_info.Subpass                   = 0;
		init_info.MinImageCount             = MaxFrameInFlight;
		init_info.ImageCount                = MaxFrameInFlight;
		init_info.MSAASamples               = VK_SAMPLE_COUNT_1_BIT;
		init_info.Allocator                 = VK_NULL_HANDLE;
		init_info.CheckVkResultFn           = [](VkResult result) { std::invoke(HandleVulkanResultDelegate::GetHandler(), result); };*/

		ImGui_ImplVulkan_Init(&init_info);
	}
	
	void VulkanInterface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui_ImplVulkan_Shutdown();
	}

	void VulkanInterface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplVulkan_NewFrame();
	}

}