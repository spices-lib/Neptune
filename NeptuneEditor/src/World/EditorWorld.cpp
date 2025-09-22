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
#include <Scripts/DynamicScripts/Lua/LuaScript.h>

namespace Neptune::Editor {

    void EditorWorld::OnAttached()
    {
        CreateExampleScene();

        SetFlag(WorldMarkBit::DynamicScriptTick, true);
        SetFlag(WorldMarkBit::DynamicScriptEvent, true);
    }

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
            auto& comp = entity.AddComponent<ScriptComponent>();

            auto script = CreateSP<Neptune::Lua::LuaScript>("E:/OpenGLProjects/Neptune/NeptuneEngine/assets/Scripts/Lua/main.lua");
            comp.AddScript(script);
        }

        {
            auto entity = scene->CreateEntity("plane");
            entity.AddComponent<TransformComponent>();
        }
    }
}
