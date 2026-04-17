/**
* @file LogicalSystem.cpp.
* @brief The LogicalSystem Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "LogicalSystem.h"
#include "RenderSystem.h"
#include "Render/Frontend/RenderFrontend.h"
#include "World/World/World.h"
#include "World/Scene/Scene.h"
#include "World/Component/ScriptComponent.h"
#include "Core/Event/EngineEvent.h"
#include "Slate/Frontend/SlateFrontend.h"

#include <ranges>

namespace Neptune {
    
    void LogicalSystem::OnSystemInitialize()
    {
        NEPTUNE_PROFILE_ZONE

        m_SlateFrontend = SlateFrontend::Create(SlateBackendEnum::ImGui, RenderBackendEnum::Vulkan, WindowImplement::GLFW);
    }

    void LogicalSystem::OnSystemShutDown()
    {}

    void LogicalSystem::Tick()
    {
        NEPTUNE_PROFILE_ZONE

        const auto& world = World::Instance();

        const auto& scenes = world.GetScenes();

        if (world.TestFlag(WorldMarkBit::DynamicScriptTick))
        {
            NEPTUNE_PROFILE_ZONEN("DynamicScriptTick")

            for (const auto& scene : scenes | std::views::values)
            {
                scene->ViewComponent<ScriptComponent>([](uint32_t e, const ScriptComponent& comp) {

                    comp.OnTick();
                    return true;
                });
            }
        }
    }

    void LogicalSystem::OnEvent(Event& event)
    {
        NEPTUNE_PROFILE_ZONE

        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<EngineEvent>(BIND_EVENT_FN(LogicalSystem::OnEngineEvent));

        const auto& world = World::Instance();

        if (world.TestFlag(WorldMarkBit::DynamicScriptEvent))
        {
            NEPTUNE_PROFILE_ZONEN("DynamicScriptEvent")

            const auto& scenes = world.GetScenes();

            for (const auto& scene : scenes | std::views::values)
            {
                scene->ViewComponent<ScriptComponent>([&](uint32_t e, const ScriptComponent& comp) {

                    comp.OnEvent(event);
                    return true;
                });
            }
        }
    }

    bool LogicalSystem::OnEngineEvent(class EngineEvent& e) const
    {
        NEPTUNE_PROFILE_ZONE

        if (e.Has(EngineEventBit::InitSlateFrontend))
        {
            auto renderSystem = static_cast<RenderSystem*>(GetSystem(ESystem::Render));

            m_SlateFrontend->OnInitialize(renderSystem->GetRenderFrontend()->AccessInfrastructure());
        }

        if (e.Has(EngineEventBit::ShutdownSlateFrontend))
        {
            m_SlateFrontend->OnShutDown();
        }

        return false;
    }
}
