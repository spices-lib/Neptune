/**
* @file GraphicsBackend.cpp.
* @brief The GraphicsBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_MACOS

#include "GraphicsBackend.h"

namespace Neptune::Metal {

    GraphicsBackend::GraphicsBackend()
        : GraphicsFrontend(GraphicsBackendEnum::Metal)
    {
        NEPTUNE_PROFILE_ZONE
    }

    void GraphicsBackend::OnInitialize(const Window* window)
    {
        NEPTUNE_PROFILE_ZONE

        GraphicsFrontend::OnInitialize();
    }

    void GraphicsBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        GraphicsFrontend::OnShutDown();
    }

    void RenderBackend::Wait()
    {
        NEPTUNE_PROFILE_ZONE
    }

    std::any GraphicsBackend::CreateRHI(RHI::ERHI e, void* payload)
	{
        NEPTUNE_PROFILE_ZONE

        return nullptr;
	}
}

#endif