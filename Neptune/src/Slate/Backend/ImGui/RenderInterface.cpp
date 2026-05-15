/**
* @file RenderInterface.cpp.
* @brief The RenderInterface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderInterface.h"
#include "Render/Frontend/Utils.h"

#ifndef NP_PLATFORM_EMSCRIPTEN
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_opengl3.h>
#endif

#ifdef NP_PLATFORM_WINDOWS
#include <backends/imgui_impl_dx12.h>
#endif

namespace Neptune::imgui {

	SP<RenderInterface> CreateRenderInterface(RenderBackendEnum backend)
	{
		NEPTUNE_PROFILE_ZONE

		switch (backend)
		{
#ifdef NP_PLATFORM_WINDOWS
			case RenderBackendEnum::Direct3D12: return CreateSP<Direct3D12Interface>();
#endif

#ifndef NP_PLATFORM_EMSCRIPTEN
			case RenderBackendEnum::OpenGL: return CreateSP<OpenGLInterface>();
			case RenderBackendEnum::Vulkan: return CreateSP<VulkanInterface>();
#endif

			default:
			{
				NEPTUNE_CORE_CRITICAL("Not supported RenderBackend in ImGui Slate Configuration.")
				return nullptr;
			}
		}
	}

#ifndef NP_PLATFORM_EMSCRIPTEN
	
	void OpenGLInterface::OnInitialize(const std::unordered_map<std::string, std::any>& infrastructure) const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void OpenGLInterface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplOpenGL3_Shutdown();
	}

	void OpenGLInterface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplOpenGL3_NewFrame();
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
		init_info.Allocator                 = VK_NULL_HANDLE;
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

#endif

#ifdef NP_PLATFORM_WINDOWS
	
	void Direct3D12Interface::OnInitialize(const std::unordered_map<std::string, std::any>& infrastructure) const
	{
		NEPTUNE_PROFILE_ZONE

		const auto CPUHandle = std::any_cast<D3D12_CPU_DESCRIPTOR_HANDLE>(infrastructure.at("SRVCPUHandle"));
		const auto GPUHandle = std::any_cast<D3D12_GPU_DESCRIPTOR_HANDLE>(infrastructure.at("SRVGPUHandle"));

		ImGui_ImplDX12_InitInfo                       init_info{};
		init_info.Device                            = std::any_cast<ID3D12Device*>                (infrastructure.at("Device"));
		init_info.CommandQueue                      = std::any_cast<ID3D12CommandQueue*>          (infrastructure.at("CommandQueue"));					                                                               
		init_info.RTVFormat                         = std::any_cast<DXGI_FORMAT>                  (infrastructure.at("RTVFormat"));
		init_info.DSVFormat                         = std::any_cast<DXGI_FORMAT>                  (infrastructure.at("DSVFormat"));	       
		init_info.SrvDescriptorHeap                 = std::any_cast<ID3D12DescriptorHeap*>        (infrastructure.at("SRVDescriptorHeap"));
		init_info.SrvDescriptorAllocFn              = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE* OCPUHandle, D3D12_GPU_DESCRIPTOR_HANDLE* OGPUHandle){};
		init_info.SrvDescriptorFreeFn               = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_GPU_DESCRIPTOR_HANDLE){};
		init_info.LegacySingleSrvCpuDescriptor      = CPUHandle;
		init_info.LegacySingleSrvGpuDescriptor      = GPUHandle;
		init_info.NumFramesInFlight                 = MaxFrameInFlight;	
		init_info.UserData                          = nullptr;	

		ImGui_ImplDX12_Init(&init_info);
	}
	
	void Direct3D12Interface::OnShutDown() const
	{
		NEPTUNE_PROFILE_ZONE
		
		ImGui_ImplDX12_Shutdown();
	}

	void Direct3D12Interface::BeginFrame() const
	{
		NEPTUNE_PROFILE_ZONE

		ImGui_ImplDX12_NewFrame();
	}

#endif
}