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
        
        m_Context->Registry<IQueue>();
        
        m_Context->Registry<IFuture>(MaxFrameInFlight);
        
        m_Context->Registry<ICommandEncoder>(MaxFrameInFlight);

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

        auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

        {
            m_Context->Get<IFuture>()->Wait(clock.m_FrameIndex);
        }

        {
            m_Context->Get<ICommandEncoder>()->Begin(clock.m_FrameIndex);
        }
    }

    void RenderBackend::EndFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE

        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

		{
			DEBUGUTILS_BEGINLABEL(m_Context->Get<IQueue>()->Handle(), "MainQueue")

			m_Context->Get<IQueue>()->Submit(m_Context->Get<ICommandEncoder>()->End(clock.m_FrameIndex));

			DEBUGUTILS_ENDLABEL(m_Context->Get<IQueue>()->Handle())
		}
        
        // Present ?
    }

    void RenderBackend::Wait()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Context->Get<IQueue>()->OnSubmittedWorkDone();
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

        infrastructure["Device"]                     = m_Context->Get<IDevice>()->Handle();
        infrastructure["RTVFormat"]                  = WGPUTextureFormat_RGBA8Unorm;
        infrastructure["DSVFormat"]                  = WGPUTextureFormat_Undefined;
        
		return infrastructure;
	}

/*    void RenderBackend::RenderFrame()
    {
        NEPTUNE_PROFILE_ZONE

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