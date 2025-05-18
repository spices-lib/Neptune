/**
* @file RHISystem.cpp.
* @brief The RHISystem Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RHISystem.h"
#include "Render/FrontEnd/RenderFrontEnd.h"

namespace Neptune {

    void RHISystem::OnSystemInitialize()
    {
        m_RenderFrontEnd = RenderFrontEnd::Create(RenderBackendEnum::WebGPU);
    }
    void RHISystem::OnSystemShutDown()
    {

    }
    void RHISystem::Tick()
    {
        m_RenderFrontEnd->BeginFrame();
        m_RenderFrontEnd->RenderFrame();
        m_RenderFrontEnd->EndFrame();
    }


}