/**
* @file RenderBackend.cpp.
* @brief The RenderBackend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "RenderBackend.h"
#include "Infrastructure/InfrastructureHeader.h"
#include "RHI/RHIHeader.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "Data/Clock.h"
#include "World/Component/Component.h"

namespace Neptune::Direct3D11 {

    RenderBackend::RenderBackend()
        : RenderFrontend(RenderBackendEnum::Direct3D11)
    {
        NEPTUNE_PROFILE_ZONE
        
        HandleResultDelegate::SetHandler([&](HRESULT result) { HandleResult(result); });
    }

    void RenderBackend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_Context = CreateSP<Context>();

        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<IDeviceContext>();
        m_Context->Registry<IFactory>();
        m_Context->Registry<IDevice>();
        
        m_Context->Registry<ISwapChain>();
        
        m_Context->Registry<IGraphicFence>();
        m_Context->Registry<IComputeFence>();
        
        m_Context->Registry<IGraphicCommandList>();
        m_Context->Registry<IComputeCommandList>();
        
        RenderFrontend::OnInitialize();
    }

    void RenderBackend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        RenderFrontend::OnShutDown();
    }

    Context& RenderBackend::GetContext() const
    {
        return *m_Context;
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

        return nullptr;
	}

    std::unordered_map<std::string, std::any> RenderBackend::AccessInfrastructure()
    {
        NEPTUNE_PROFILE_ZONE

        std::unordered_map<std::string, std::any> infrastructure;

        return infrastructure;
    }
}

#endif