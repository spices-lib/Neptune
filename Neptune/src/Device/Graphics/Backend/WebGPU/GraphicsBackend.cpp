/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"

namespace Neptune::WebGPU {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(GraphicsBackendEnum::WebGPU)
    {
        NEPTUNE_PROFILE_ZONE
    }

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateSP<Context>();
        
        m_Context->Registry<IInstance>();
        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<IAdapter>();
        m_Context->Registry<IDevice>();
        
        m_Context->Registry<IQueue>();
        
        m_Context->Registry<IFuture>(MaxFrameInFlight);
        
        m_Context->Registry<ICommandEncoder>(MaxFrameInFlight);
    }

    void GraphicsBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        m_Context->UnRegistry();
    }

    Context& GraphicsBackend::GetContext() const
    {
        return *m_Context;
    }

    void GraphicsBackend::Wait() const
    {
        NEPTUNE_PROFILE_ZONE
        
        m_Context->Get<IQueue>()->OnSubmittedWorkDone();
    }

    std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
			default:                          NEPTUNE_CORE_ERROR("WebGPU do not support this RHI.")          return nullptr;
		}
	}

    std::unordered_map<std::string, std::any> GraphicsBackend::AccessInfrastructure() const
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