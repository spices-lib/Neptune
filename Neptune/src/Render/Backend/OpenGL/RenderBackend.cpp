/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifndef NP_PLATFORM_EMSCRIPTEN

#include "RenderBackend.h"
#include "RHI/RHIHeader.h"

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

        RenderFrontend::OnInitialize();
    }

    void RenderBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        RenderFrontend::OnShutDown();
    }

    void RenderBackend::BeginFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE
    }

    void RenderBackend::EndFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE
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
			case RHI::ERHI::Shader:           return std::dynamic_pointer_cast<RHI::RHIShader::Impl>        (CreateSP<Shader>               ());
			case RHI::ERHI::VertexBuffer:     return std::dynamic_pointer_cast<RHI::RHIVertexBuffer::Impl>  (CreateSP<VertexBuffer>         ());
			default: return nullptr;
		}
	}
}

#endif