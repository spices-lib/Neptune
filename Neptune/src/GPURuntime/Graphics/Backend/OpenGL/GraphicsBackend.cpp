/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"

namespace Neptune::OpenGL {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(GraphicsBackendEnum::OpenGL)
    {
        NEPTUNE_PROFILE_ZONE

        HandleResultDelegate::SetHandler([&](GLenum result) { HandleResult(result); });
    }

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateSP<Context>();

        m_Context->Registry<IWindowContext>(window ? window->Implement() : WindowImplement::Default, window ? window->NativeWindow() : nullptr);
        m_Context->Registry<IDebugUtilsObject>();

        m_Context->Registry<IGraphicFence>(MaxFrameInFlight);
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

        glFinish();
    }

    std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
            case RHI::ERHI::RenderPass:       return std::dynamic_pointer_cast<RHI::RHIRenderPass::Impl>    (CreateSP<RenderPass>           (*m_Context));
			case RHI::ERHI::DescriptorList:   return std::dynamic_pointer_cast<RHI::RHIDescriptorList::Impl>(CreateSP<DescriptorList>       (*m_Context));
			case RHI::ERHI::Pipeline:         return std::dynamic_pointer_cast<RHI::RHIPipeline::Impl>      (CreateSP<Pipeline>             (*m_Context));
			case RHI::ERHI::Shader:           return std::dynamic_pointer_cast<RHI::RHIShader::Impl>        (CreateSP<Shader>               (*m_Context));
			case RHI::ERHI::RenderTarget:     return std::dynamic_pointer_cast<RHI::RHIRenderTarget::Impl>  (CreateSP<RenderTarget>         (*m_Context));
			case RHI::ERHI::VertexBuffer:     return std::dynamic_pointer_cast<RHI::RHIVertexBuffer::Impl>  (CreateSP<VertexBuffer>         (*m_Context));
			case RHI::ERHI::IndexBuffer:      return std::dynamic_pointer_cast<RHI::RHIIndexBuffer::Impl>   (CreateSP<IndexBuffer>          (*m_Context));
            case RHI::ERHI::CmdList:          return std::dynamic_pointer_cast<RHI::RHICmdList::Impl>       (CreateSP<CmdList>              (*m_Context));
			case RHI::ERHI::CmdList2:         return std::dynamic_pointer_cast<RHI::RHICmdList2::Impl>      (CreateSP<CmdList2>             (*m_Context));
            case RHI::ERHI::Decoder:          NEPTUNE_CORE_ERROR("OpenGL do not support Decoder RHI.")       return nullptr;
            case RHI::ERHI::OpticalFlow:      NEPTUNE_CORE_ERROR("OpenGL do not support OpticalFlow RHI.")   return nullptr;
			default:                          NEPTUNE_CORE_ERROR("OpenGL do not support this RHI.")          return nullptr;
		}
	}

    std::unordered_map<std::string, std::any> GraphicsBackend::AccessInfrastructure() const
	{
        NEPTUNE_PROFILE_ZONE

		std::unordered_map<std::string, std::any> infrastructure;

		return infrastructure;
	}
}

#endif