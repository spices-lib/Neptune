/**
* @file World.cpp.
* @brief The World Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "World.h"
#include "World/Scene/Scene.h"
#include "World/Object/Level.h"

namespace Neptune {
    
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
    
}
