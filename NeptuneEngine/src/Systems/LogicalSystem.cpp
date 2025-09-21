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

        const auto& scenes = World::Instance()->GetScenes();
        
        for (const auto& scene : scenes | std::views::values)
        {
            scene->ViewComponent<ScriptComponent>([](uint32_t e, ScriptComponent& comp) {
                comp.OnTick();
                return false;
            });
        }
    }

    void LogicalSystem::OnEvent(Event& event)
    {
        const auto& scenes = World::Instance()->GetScenes();

        for (const auto& scene : scenes | std::views::values)
        {
            scene->ViewComponent<ScriptComponent>([&](uint32_t e, ScriptComponent& comp) {
                comp.OnEvent(event);
                return false;
            });
        }
    }
}
