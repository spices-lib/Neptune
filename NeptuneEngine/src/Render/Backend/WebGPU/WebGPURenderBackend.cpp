/**
* @file WebGPURenderBackend.cpp.
* @brief The WebGPURenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "WebGPURenderBackend.h"
#include "WebGPUInstance.h"
#include "WebGPUAdapter.h"
#include "WebGPUDevice.h"

#include <emscripten.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include <GLFW/glfw3.h>
#include <GLFW/emscripten_glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_wgpu.h>

#include "Window/Window.h"

namespace Neptune {

    WebGPURenderBackend::WebGPURenderBackend(RenderBackendEnum backend)
        : RenderFrontend(backend)
    {
        /*m_State     = CreateSP<WebGPUState>();
        m_Instance  = CreateSP<WebGPUInstance>(*m_State);
        m_Device    = CreateSP<WebGPUDevice>(*m_State);

        GLFWwindow* window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());*/

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

    WebGPURenderBackend::~WebGPURenderBackend()
    {
        // Cleanup
        /*ImGui_ImplWGPU_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();*/
    }

    void WebGPURenderBackend::BeginFrame()
    {
        // Create CommandEncoder.
        /*WGPUCommandEncoderDescriptor desc = {};
        m_State->m_GraphicCommandEncoder = wgpuDeviceCreateCommandEncoder(m_State->m_Device, &desc);*/
    }

    void WebGPURenderBackend::EndFrame()
    {
        //// Get Command Buffer.
        //WGPUCommandBufferDescriptor desc     = {};
        //WGPUCommandBuffer commandBuffer      = wgpuCommandEncoderFinish(m_State->m_GraphicCommandEncoder, &desc);

        //// Submit CommandBuffer to Queue.
        //wgpuQueueSubmit(m_State->m_GraphicQueue, 1, &commandBuffer);

        //// Release CommandEncoder and CommandBuffer.
        //wgpuCommandEncoderRelease(m_State->m_GraphicCommandEncoder);
        //wgpuCommandBufferRelease(commandBuffer);
    }

    void WebGPURenderBackend::RenderFrame()
    {
        // Start the Dear ImGui frame
        /*ImGui_ImplWGPU_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);

        // Rendering
        ImGui::Render();*/

        //WGPUSurfaceTexture swapChainTexture;
        //wgpuSurfaceGetCurrentTexture(m_State->m_Surface, &swapChainTexture);

        //WGPURenderPassColorAttachment color_attachments = {};
        //color_attachments.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
        //color_attachments.loadOp = WGPULoadOp_Clear;
        //color_attachments.storeOp = WGPUStoreOp_Store;
        //color_attachments.clearValue = { 1.0, 0.0, 0.0, 1.0 };
        //color_attachments.view = wgpuTextureCreateView(swapChainTexture.texture, nullptr);

        //WGPURenderPassDescriptor render_pass_desc = {};
        //render_pass_desc.colorAttachmentCount = 1;
        //render_pass_desc.colorAttachments = &color_attachments;
        //render_pass_desc.depthStencilAttachment = nullptr;

        //WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(m_State->m_GraphicCommandEncoder, &render_pass_desc);
        ////ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), pass);
        //wgpuRenderPassEncoderEnd(pass);

        //wgpuTextureViewRelease(color_attachments.view);
        //wgpuRenderPassEncoderRelease(pass);
    }
}

#endif