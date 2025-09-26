/**
* @file Scene.cpp.
* @brief The Scene Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Scene.h"
#include "World/Entity/Entity.h"
#include "World/Component/ScriptComponent.h"
#include "World/Component/TagComponent.h"
#include "World/Component/UUIDComponent.h"

namespace Neptune {
    
    Scene::Scene()
    {
        NEPTUNE_PROFILE_ZONE

        auto root = CreateEntity("SceneRoot");

        root.AddComponent<ScriptComponent>();

        m_Root = root;
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        NEPTUNE_PROFILE_ZONE

        return CreateEntityWithUUID(UUID(), name);
    }

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
    {
        NEPTUNE_PROFILE_ZONE

        Entity entity = CreateEmptyEntity(uuid);

        entity.AddComponent<UUIDComponent>(uuid);
        entity.AddComponent<TagComponent>(name);

        return entity;
    }

    void Scene::Destroy(const Entity& entity)
    {
        NEPTUNE_PROFILE_ZONE

        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        uint32_t e = entity;
        m_Registry.destroy(static_cast<entt::entity>(e));
    }

    Entity Scene::QueryEntityByID(const uint32_t id)
    {
        NEPTUNE_PROFILE_ZONE

        return { id, this };
    }

    Entity Scene::CreateEmptyEntity(const UUID uuid)
    {
        NEPTUNE_PROFILE_ZONE

        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        return { static_cast<uint32_t>(m_Registry.create()), this };
    }
}
