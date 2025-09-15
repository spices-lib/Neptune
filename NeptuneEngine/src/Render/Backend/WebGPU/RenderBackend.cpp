/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackend.h"
#include "Instance.h"
#include "Adapter.h"
#include "Device.h"
#include "Surface.h"
#include "Queue.h"

#include <emscripten.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <GLFW/glfw3.h>
#include <GLFW/emscripten_glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_wgpu.h>

#include "Window/Window.h"

namespace Neptune::WebGPU {

    RenderBackend::RenderBackend(RenderBackendEnum backend)
        : RenderFrontend(backend)
    {
        m_Context = CreateSP<Context>();

        m_Context->Registry<Instance>();
        m_Context->Registry<Adapter>();
        m_Context->Registry<Device>();
        m_Context->Registry<Surface>();
        m_Context->Registry<Queue>();

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
    }

    RenderBackend::~RenderBackend()
    {
        // Cleanup
        /*ImGui_ImplWGPU_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();*/
    }

    static WGPUCommandEncoder graphicCommandEncoder = nullptr;

    void RenderBackend::BeginFrame()
    {
        // Create CommandEncoder.
        WGPUCommandEncoderDescriptor desc = {};
        graphicCommandEncoder = wgpuDeviceCreateCommandEncoder(m_Context->Get<Device>()->Handle(), &desc);
    }

    void RenderBackend::EndFrame()
    {
        // Get Command Buffer.
        WGPUCommandBufferDescriptor desc     = {};
        WGPUCommandBuffer commandBuffer      = wgpuCommandEncoderFinish(graphicCommandEncoder, &desc);

        // Submit CommandBuffer to Queue.
        wgpuQueueSubmit(m_Context->Get<Queue>()->Handle(), 1, &commandBuffer);

        // Release CommandEncoder and CommandBuffer.
        wgpuCommandEncoderRelease(graphicCommandEncoder);
        wgpuCommandBufferRelease(commandBuffer);
    }

    void RenderBackend::RenderFrame()
    {
        // Start the Dear ImGui frame
        /*ImGui_ImplWGPU_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);

        // Rendering
        ImGui::Render();*/

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
    }
}

#endif