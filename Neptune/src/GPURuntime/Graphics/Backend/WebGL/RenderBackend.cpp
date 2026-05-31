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

namespace Neptune::WebGL {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::WebGL)
    {
        NEPTUNE_PROFILE_ZONE
    }

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateSP<Context>();
    }

    void RenderBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        m_Context->UnRegistry();
    }

    Context& RenderBackend::GetContext() const
    {
        return *m_Context;
    }

    void RenderBackend::Wait() const
    {
        NEPTUNE_PROFILE_ZONE
    }

    std::any RenderBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
			default:                          NEPTUNE_CORE_ERROR("WebGL do not support this RHI.")          return nullptr;
		}
	}

    std::unordered_map<std::string, std::any> RenderBackend::AccessInfrastructure() const
	{
        NEPTUNE_PROFILE_ZONE

		std::unordered_map<std::string, std::any> infrastructure;

		return infrastructure;
	}
}

#endif