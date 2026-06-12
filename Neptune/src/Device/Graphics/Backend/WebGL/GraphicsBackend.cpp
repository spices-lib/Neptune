/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGL

#include "GraphicsBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"

namespace Neptune::WebGL {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(GraphicsBackendEnum::WebGL)
    {
        NEPTUNE_PROFILE_ZONE
    }

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateSP<Context>();
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
    }

    std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload) const
	{
        NEPTUNE_PROFILE_ZONE

        switch(e)
		{
			default:                          NEPTUNE_CORE_ERROR("WebGL do not support this RHI.")          return nullptr;
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