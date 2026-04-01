/**
* @file RenderFrontEnd.cpp.
* @brief The RenderFrontend Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderFrontend.h"

#ifdef NP_PLATFORM_EMSCRIPTEN
#include "Render/Backend/WebGPU/RenderBackend.h"
#include "Render/Backend/WebGL/RenderBackend.h"
#endif

#ifdef NP_PLATFORM_WINDOWS
#include "Render/Backend/Vulkan/RenderBackend.h"
#include "Render/Backend/OpenGL/RenderBackend.h"
#endif

#include "Render/FrontEnd/Pass/BasePass.h"
#include "Render/FrontEnd/Pass/SlatePass.h"
#include "Render/FrontEnd/Pass/PrePass.h"
#include "Window/Window.h"
#include "Core/Event/WindowEvent.h"
#include "Render/FrontEnd/Pass/Pass.h"
#include "Render/Frontend/RHI/RHI.h"

namespace Neptune {

    SP<RenderFrontend> RenderFrontend::Create(RenderBackendEnum backend)
    {
        NEPTUNE_PROFILE_ZONE

        SP<RenderFrontend> sp = nullptr;

        switch(backend)
        {
#ifdef NP_PLATFORM_EMSCRIPTEN
            case RenderBackendEnum::WebGPU: sp = CreateSP<WebGPU::RenderBackend>(); break;
            case RenderBackendEnum::WebGL:  sp = CreateSP<WebGL::RenderBackend>();  break;
#endif

#ifdef NP_PLATFORM_WINDOWS
            case RenderBackendEnum::Vulkan: sp = CreateSP<Vulkan::RenderBackend>(); break;
            case RenderBackendEnum::OpenGL: sp = CreateSP<OpenGL::RenderBackend>(); break;
#endif
            
            default:
            {
                NEPTUNE_CORE_CRITICAL("Not Supported Render Backend.")
                return nullptr;
            }
        }

        RHI::RHIDelegate::SetCreator([p = sp.get()](RHI::ERHI e, void* payload) { return p->CreateRHI(e, payload); });

        sp->OnInitialize();

        return sp;
    }

    void RenderFrontend::OnInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        ConstructDefaultPasses();
    }

    void RenderFrontend::OnShutDown()
    {
        NEPTUNE_PROFILE_ZONE

        RHI::RHIDelegate::SetCreator(nullptr);

        m_RenderPasses.clear();
    }

    void RenderFrontend::RenderFrame(Scene* scene)
    {
        NEPTUNE_PROFILE_ZONE

        std::ranges::for_each(m_RenderPasses, [&](const auto& renderPass) {
            renderPass->OnRender(scene);
        });
    }

    void RenderFrontend::RecreateSwapChain()
    {
        NEPTUNE_PROFILE_ZONE

        const auto extent = Window::Instance().Extent();

        WindowResizeOverEvent event(extent.x, extent.y);

        Event::GetEventCallbackFn()(event);
    }

    void RenderFrontend::ConstructDefaultPasses(const glm::vec2& rtSize)
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderPasses = {};

        {
            auto pass = CreateSP<Render::PrePass>();
            pass->SetRTSize(rtSize);

            AddPass(pass);
        }

        {
            auto pass = CreateSP<Render::BasePass>();
            pass->SetRTSize(rtSize);

            AddPass(pass);
        }

        {
            auto pass = CreateSP<Render::SlatePass>();

            AddPass(pass);
        }
    }

    void RenderFrontend::ConstructSlatePass()
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderPasses.pop_back();

        auto slatePass = CreateSP<Render::SlatePass>();

        AddPass(slatePass);
    }

    void RenderFrontend::AddPass(SP<Render::Pass> pass)
    {
        NEPTUNE_PROFILE_ZONE

        pass->OnConstruct();

        m_RenderPasses.emplace_back(pass);
    }
}