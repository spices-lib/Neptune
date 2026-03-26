/**
* @file RenderSystem.cpp.
* @brief The RenderSystem Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderSystem.h"
#include "Render/Frontend/RenderFrontend.h"

namespace Neptune {

    void RenderSystem::OnSystemInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderFrontend = RenderFrontend::Create(RenderBackendEnum::Vulkan);
    }

    void RenderSystem::OnSystemShutDown()
    {

    }

    void RenderSystem::Tick()
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderFrontend->BeginFrame();
        m_RenderFrontend->RenderFrame();
        m_RenderFrontend->EndFrame();
    }


}