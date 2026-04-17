/**
* @file RenderFrontendInterface.cpp.
* @brief The Interface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderInterface.h"
#include "Render/Frontend/Utils.h"

#include <backends/imgui_impl_vulkan.h>

namespace Neptune::imgui {

	SP<RenderInterface> CreateRenderInterface(RenderBackendEnum backend)
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

	void VulkanInterface::OnInitialize(const std::unordered_map<std::string, std::any>& infrastructure) const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplVulkan_InitInfo             init_info{};
		init_info.Instance                  = std::any_cast<VkInstance>                    (infrastructure.at("Instance"));
		init_info.PhysicalDevice            = std::any_cast<VkPhysicalDevice>              (infrastructure.at("PhysicalDevice"));
		init_info.Device                    = std::any_cast<VkDevice>                      (infrastructure.at("Device"));
		init_info.QueueFamily               = std::any_cast<uint32_t>                      (infrastructure.at("GraphicQueueFamily"));
		init_info.Queue                     = std::any_cast<VkQueue>                       (infrastructure.at("GraphicQueue"));
		init_info.PipelineCache             = VK_NULL_HANDLE;						       
		init_info.DescriptorPool            = std::any_cast<VkDescriptorPool>              (infrastructure.at("DescriptorPool"));
		init_info.RenderPass                = std::any_cast<VkRenderPass>                  (infrastructure.at("RenderPass"));
		init_info.Subpass                   = 0;
		init_info.MinImageCount             = MaxFrameInFlight;
		init_info.ImageCount                = MaxFrameInFlight;
		init_info.MSAASamples               = std::any_cast<VkSampleCountFlagBits>         (infrastructure.at("MSAASamples"));
		init_info.Allocator                 = std::any_cast<const VkAllocationCallbacks*>  (infrastructure.at("Allocator"));
		init_info.CheckVkResultFn           = std::any_cast<void(*)(VkResult)>             (infrastructure.at("CheckVkResultFn"));

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