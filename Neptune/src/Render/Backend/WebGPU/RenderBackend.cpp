/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"

namespace Neptune::WebGPU {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::WebGPU)
    {
        NEPTUNE_PROFILE_ZONE

        /*GLFWwindow* window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());*/

        // Setup Dear ImGui context
        /*IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOther(window, true);

        ImGui_ImplWGPU_InitInfo init_info;
        init_info.Device = m_State->m_Device;
        init_info.NumFramesInFlight = 3;
        init_info.RenderTargetFormat = m_Device->GetSwapChainSupport().format;
        init_info.DepthStencilFormat = WGPUTextureFormat_Undefined;
        ImGui_ImplWGPU_Init(&init_info);*/

        // Cleanup
        /*ImGui_ImplWGPU_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();*/
    }

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateSP<Context>();
        
        m_Context->Registry<IInstance>();
        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<ISurface>();
        m_Context->Registry<IAdapter>();
        m_Context->Registry<IDevice>();
        
        m_Context->Registry<IGraphicQueue>();

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

        // Create CommandEncoder.
        //WGPUCommandEncoderDescriptor desc{};
        //graphicCommandEncoder = wgpuDeviceCreateCommandEncoder(m_Context->Get<Device>()->Handle(), &desc);
    }

    void RenderBackend::EndFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE

        // Get Command Buffer.
/*        WGPUCommandBufferDescriptor desc     = {};
        WGPUCommandBuffer commandBuffer      = wgpuCommandEncoderFinish(graphicCommandEncoder, &desc);

        // Submit CommandBuffer to Queue.
        wgpuQueueSubmit(m_Context->Get<Queue>()->Handle(), 1, &commandBuffer);

        // Release CommandEncoder and CommandBuffer.
        wgpuCommandEncoderRelease(graphicCommandEncoder);
        wgpuCommandBufferRelease(commandBuffer);*/
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
			default:                          NEPTUNE_CORE_ERROR("WebGPU do not support this RHI.")          return nullptr;
		}
	}

    std::unordered_map<std::string, std::any> RenderBackend::AccessInfrastructure()
	{
        NEPTUNE_PROFILE_ZONE

		std::unordered_map<std::string, std::any> infrastructure;

		return infrastructure;
	}

/*    void RenderBackend::RenderFrame()
    {
        NEPTUNE_PROFILE_ZONE

        // Start the Dear ImGui frame
        ImGui_ImplWGPU_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);

        // Rendering
        ImGui::Render();

        WGPUSurfaceTexture swapChainTexture;
        wgpuSurfaceGetCurrentTexture(m_Context->Get<Surface>()->Handle(), &swapChainTexture);

        WGPURenderPassColorAttachment                 color_attachments = {};
        color_attachments.depthSlice                = WGPU_DEPTH_SLICE_UNDEFINED;
        color_attachments.loadOp                    = WGPULoadOp_Clear;
        color_attachments.storeOp                   = WGPUStoreOp_Store;
        color_attachments.clearValue                = { 1.0, 0.0, 0.0, 1.0 };
        color_attachments.view                      = wgpuTextureCreateView(swapChainTexture.texture, nullptr);

        WGPURenderPassDescriptor                      render_pass_desc = {};
        render_pass_desc.colorAttachmentCount       = 1;
        render_pass_desc.colorAttachments           = &color_attachments;
        render_pass_desc.depthStencilAttachment     = nullptr;

        WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(graphicCommandEncoder, &render_pass_desc);
        //ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), pass);
        wgpuRenderPassEncoderEnd(pass);

        wgpuTextureViewRelease(color_attachments.view);
        wgpuRenderPassEncoderRelease(pass);
    }*/
}

#endif