/**
* @file EditorWorld.cpp.
* @brief The EditorWorld Class Implementation.
* @author Spices.
*/

#include "EditorWorld.h"
#include <World/Scene/Scene.h>
#include <World/Entity/Entity.h>
#include <World/Component/TransformComponent.h>

namespace Neptune::Editor {
    
    void EditorWorld::Layout()
    {
        
    }

    void EditorWorld::CreateExampleScene()
    {
        NEPTUNE_PROFILE_ZONE

        const auto scene = CreateScene("main_level");

        {
            auto entity = scene->CreateEntity("cube");
            entity.AddComponent<TransformComponent>();
        }

        {
            auto entity = scene->CreateEntity("plane");
            entity.AddComponent<TransformComponent>();
        }
    }
}
