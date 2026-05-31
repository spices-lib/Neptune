/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackend.h"
#include "GPURuntime/Graphics/Backend/WebGPU/Infrastructure/InfrastructureHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/Component.h"
#include "Data/Clock.h"

namespace Neptune::WebGPU {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::WebGPU)
        , m_GraphicsBackend(CreateUP<GraphicsBackend>())
    {}

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_GraphicsBackend->OnInitialize();
        
        GetContext().Registry<ISurface>();

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
            context.Get<IFuture>()->Wait(clock.m_FrameIndex);
        }

        {
            context.Get<ICommandEncoder>()->Begin(clock.m_FrameIndex);
        }
    }

    void RenderBackend::EndFrame(Scene* scene) const
    {
        NEPTUNE_PROFILE_ZONE

        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

        auto& context = m_GraphicsBackend->GetContext();
        
		{
			DEBUGUTILS_BEGINLABEL(context.Get<IQueue>()->Handle(), "MainQueue")

			context.Get<IFuture>()->SetHandle(clock.m_FrameIndex, context.Get<IQueue>()->Submit(context.Get<ICommandEncoder>()->End(clock.m_FrameIndex)));

			DEBUGUTILS_ENDLABEL(context.Get<IQueue>()->Handle())
		}
        
        // Present ?
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
        
		return m_GraphicsBackend->AccessInfrastructure();
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