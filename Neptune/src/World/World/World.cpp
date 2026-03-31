/**
* @file World.cpp.
* @brief The World Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "World.h"
#include "World/Scene/Scene.h"
#include "World/Object/Level.h"
#include "Core/Event/EngineEvent.h"
#include "Slate/SlateScope.h"
#include "Slate/Slate.h"

namespace Neptune {

    namespace {
        
        UP<World> S_Instance = nullptr;     // @brief World Instance.
    }

    World& World::Instance()
    {
        NEPTUNE_PROFILE_ZONE

        if (!S_Instance) 
        {
            S_Instance = CreateWorld();
        }

        return *S_Instance;
    }

    void World::OnAttached()
    {
        EngineEvent event(EngineEventBit::InitSlateModule);

        Event::GetEventCallbackFn()(event);
    }

    void World::OnDetached()
    {
        DestroyScene();

        EngineEvent event(EngineEventBit::ShutdownSlateModule);

        Event::GetEventCallbackFn()(event);

        S_Instance.reset();
    }

    void World::OnLayout()
    {
        Slate::SlateScope::BeginScope();

        std::for_each(m_Slates.begin(), m_Slates.end(), [](const auto& slate) {
            slate->OnTick();
        });

        Slate::SlateScope::EndScope();
    }

    void World::OnEvent(Event& e)
    {
        std::for_each(m_Slates.begin(), m_Slates.end(), [&](const auto& slate) {
            slate->OnEvent(e);
        });
    }

    Scene* World::CreateScene(const SP<Level>& level)
    {
        NEPTUNE_PROFILE_ZONE

        const auto& name = level->GetName();
        
        if (m_Scenes.contains(name))
        {
            std::stringstream ss;
            ss << "Scene: [ " << name << " ] already exists in world!";
            
            NEPTUNE_CORE_ERROR(ss.str())
            return nullptr;
        }
        
        m_Scenes.emplace(name, CreateUP<Scene>());
        return m_Scenes.at(name).get();
    }

    Scene* World::CreateScene(const std::string& name)
    {
        NEPTUNE_PROFILE_ZONE

        if (m_Scenes.contains(name))
        {
            std::stringstream ss;
            ss << "Scene: [ " << name << " ] already exists in world!";
            
            NEPTUNE_CORE_ERROR(ss.str())
            return nullptr;
        }

        m_Scenes.emplace(name, CreateUP<Scene>());
        return m_Scenes.at(name).get();
    }
    
    void World::DestroyScene()
    {
        m_Scenes.clear();
    }
}
