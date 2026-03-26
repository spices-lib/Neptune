/**
* @file LogicalSystem.cpp.
* @brief The LogicalSystem Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "LogicalSystem.h"
#include "World/World/World.h"
#include "World/Scene/Scene.h"
#include "World/Component/ScriptComponent.h"

#include <ranges>

namespace Neptune {
    
    void LogicalSystem::Tick()
    {
        NEPTUNE_PROFILE_ZONE

        // receive ui event or interface event.

        const auto world = World::Instance();

        if (world->TestFlag(WorldMarkBit::DynamicScriptTick))
        {
            NEPTUNE_PROFILE_ZONEN("DynamicScriptTick")

            const auto& scenes = world->GetScenes();

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

        const auto world = World::Instance();

        if (world->TestFlag(WorldMarkBit::DynamicScriptEvent))
        {
            NEPTUNE_PROFILE_ZONEN("DynamicScriptEvent")

            const auto& scenes = World::Instance()->GetScenes();

            for (const auto& scene : scenes | std::views::values)
            {
                scene->ViewComponent<ScriptComponent>([&](uint32_t e, const ScriptComponent& comp) {

                    comp.OnEvent(event);
                    return true;
                });
            }
        }
    }
}
