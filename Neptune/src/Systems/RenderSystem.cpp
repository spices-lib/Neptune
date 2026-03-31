/**
* @file RenderSystem.cpp.
* @brief The RenderSystem Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RenderSystem.h"
#include "Render/Frontend/RenderFrontend.h"
#include "World/World/World.h"
#include "Core/Event/EngineEvent.h"
#include "Core/Event/SlateEvent.h"
#include "Core/Event/WindowEvent.h"

namespace Neptune {

    void RenderSystem::OnSystemInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderFrontend = RenderFrontend::Create(RenderBackendEnum::Vulkan);
    }

    void RenderSystem::OnSystemShutDown()
    {
        m_RenderFrontend->OnShutDown();
    }

    void RenderSystem::Tick()
    {
        NEPTUNE_PROFILE_ZONE

        auto scene = World::Instance().GetScenes().at("main_level").get();

        m_RenderFrontend->BeginFrame(scene);

        m_RenderFrontend->RenderFrame(scene);

        m_RenderFrontend->EndFrame(scene);
    }

    void RenderSystem::OnEvent(Event& event)
    {
        NEPTUNE_PROFILE_ZONE

        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<EngineEvent>(BIND_EVENT_FN(RenderSystem::OnEngineEvent));

        dispatcher.Dispatch<SlateResizeEvent>(BIND_EVENT_FN(RenderSystem::OnSlateResizeEvent));

        dispatcher.Dispatch<WindowResizeOverEvent>(BIND_EVENT_FN(RenderSystem::OnWindowResizeOverEvent));
    }

    bool RenderSystem::OnEngineEvent(EngineEvent& e)
    {
        NEPTUNE_PROFILE_ZONE

        if (e.Has(EngineEventBit::StopTheEngine))
        {
            m_RenderFrontend->Wait();
        }

        if (e.Has(EngineEventBit::InitSlateModule))
        {
            m_RenderFrontend->InitSlateModule();
        }

        if (e.Has(EngineEventBit::ShutdownSlateModule))
        {
            m_RenderFrontend->ShutdownSlateModule();
        }

        return false;
    }

    bool RenderSystem::OnSlateResizeEvent(SlateResizeEvent& e)
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderFrontend->ConstructDefaultPasses({ e.GetWidth(), e.GetHeight() });

        return false;
    }

    bool RenderSystem::OnWindowResizeOverEvent(WindowResizeOverEvent& e)
    {
        NEPTUNE_PROFILE_ZONE

        m_RenderFrontend->ConstructSlatePass();

        return false;
    }
}