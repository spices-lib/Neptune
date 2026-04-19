/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"

namespace Neptune::OpenGL {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::OpenGL)
    {
        NEPTUNE_PROFILE_ZONE

        HandleOpenGLResultDelegate::SetHandler([&](GLenum result) {
			HandleOpenGLResult(
				result
			); 
		});
    }

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateSP<Context>();

        m_Context->Registry<IDebugUtilsObject>();

        m_Context->Registry<IGraphicFence>(MaxFrameInFlight);

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

        const auto& clock = scene->GetComponent<Component<Data::Clock>>(scene->GetRoot()).GetModel();

        {
            m_Context->Get<IGraphicFence>()->Wait(clock.m_FrameIndex);
        }

        {
            DEBUGUTILS_BEGINLABEL(0, "MainGraphicQueue")
        }
    }

    void RenderBackend::EndFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE

        {
            DEBUGUTILS_ENDLABEL()
        }

        {
            DEBUGUTILS_BEGINLABEL(0, "PresentQueue")

            const auto& window = Window::Instance();

            window.SwapBuffers();

            DEBUGUTILS_ENDLABEL()
        }
    }

    void RenderBackend::Wait()
    {
        NEPTUNE_PROFILE_ZONE

        glFinish();
    }

    std::any RenderBackend::CreateRHI(RHI::ERHI e, void* payload)
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

    std::unordered_map<std::string, std::any> RenderBackend::AccessInfrastructure()
	{
        NEPTUNE_PROFILE_ZONE

		std::unordered_map<std::string, std::any> infrastructure;

		return infrastructure;
	}
}

#endif