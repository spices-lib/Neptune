/**
* @file EditorWorld.cpp.
* @brief The EditorWorld Class Implementation.
* @author Spices.
*/

#include "EditorWorld.h"

#include <World/Scene/Scene.h>
#include <World/Entity/Entity.h>
#include <World/Component/TransformComponent.h>
#include <World/Component/ScriptComponent.h>
#include <Scripts/NativeScripts/EngineClock.h>

namespace Neptune::Editor {

    void EditorWorld::OnAttached()
    {
        NEPTUNE_PROFILE_ZONE

        World::OnAttached();

        CreateExampleScene();

        SetFlag(WorldMarkBit::DynamicScriptTick, true);
        SetFlag(WorldMarkBit::DynamicScriptEvent, true);
    }

    void EditorWorld::OnDetached()
    {
        NEPTUNE_PROFILE_ZONE

        World::OnDetached();
    }

    void EditorWorld::Layout()
    {
        
    }

    void EditorWorld::CreateExampleScene()
    {
        NEPTUNE_PROFILE_ZONE

        const auto scene = CreateScene("main_level");

        auto& scriptComponent = scene->GetComponent<ScriptComponent>(scene->GetRoot());

        scriptComponent.AddScript(CreateSP<EngineClock>(scene));

        {
            auto entity = scene->Create("cube");
            entity.AddComponent<TransformComponent>();
        }

        {
            auto entity = scene->Create("plane");
            entity.AddComponent<TransformComponent>();
        }
    }
}
