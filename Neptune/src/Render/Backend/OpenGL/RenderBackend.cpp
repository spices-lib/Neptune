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
#include "World/Component/ClockComponent.h"

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

        m_Context->Registry<IGraphicFence>();

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

        auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

        {
            m_Context->Get<IGraphicFence>()->Wait(clock.m_FrameIndex);
        }
    }

    void RenderBackend::EndFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE

        {
            DEBUGUTILS_BEGINLABEL(0, "Present");

            const auto& window = Window::Instance();

            window.SwapBuffers();

            DEBUGUTILS_ENDLABEL();
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
			case RHI::ERHI::Shader:           return std::dynamic_pointer_cast<RHI::RHIShader::Impl>        (CreateSP<Shader>               (*m_Context));
			case RHI::ERHI::VertexBuffer:     return std::dynamic_pointer_cast<RHI::RHIVertexBuffer::Impl>  (CreateSP<VertexBuffer>         (*m_Context));
			default: return nullptr;
		}
	}
}

#endif