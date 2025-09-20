/**
* @file RHISystem.cpp.
* @brief The RHISystem Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RHISystem.h"
#include "Render/Frontend/RenderFrontend.h"

namespace Neptune {

    void RHISystem::OnSystemInitialize()
    {
        m_RenderFrontend = RenderFrontend::Create(RenderBackendEnum::OpenGL);
    }
    void RHISystem::OnSystemShutDown()
    {

    }
    void RHISystem::Tick()
    {
        m_RenderFrontend->BeginFrame();
        m_RenderFrontend->RenderFrame();
        m_RenderFrontend->EndFrame();
    }


}