/**
* @file Scene.cpp.
* @brief The Scene Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Scene.h"
#include "World/Entity.h"

#include "World/Component/TagComponent.h"
#include "World/Component/TransformComponent.h"
#include "World/Component/UUIDComponent.h"

namespace Neptune {

    Entity Scene::CreateEntity(const std::string& name)
    {
        return CreateEntityWithUUID(UUID(), name);
    }

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
    {
        Entity entity = CreateEmptyEntity(uuid);

        entity.AddComponent<UUIDComponent>(uuid);
        entity.AddComponent<TransformComponent>();
        entity.AddComponent<TagComponent>(name);

        return entity;
    }

    void Scene::DestroyEntity(Entity& entity)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        m_RootEntityMap.erase(entity.GetUUID());

        uint32_t e = entity;
        m_Registry.destroy((entt::entity)e);
    }

    Entity Scene::QueryEntityByID(uint32_t id)
    {
        return Entity(id, this);
    }

    void Scene::ClearMarkerWithBits(SceneMarkFlags flags)
    {
        if (m_Marker & flags)
        {
            m_Marker ^= flags;
        }
    }

    void Scene::RemoveFromRoot(Entity& entity)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        m_RootEntityMap.erase(entity.GetUUID());
    }

    void Scene::AddToRoot(Entity& entity)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        m_RootEntityMap[entity.GetUUID()] = entity;
    }

    bool Scene::IsRootEntity(Entity& entity)
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        return m_RootEntityMap.find(entity.GetUUID()) != m_RootEntityMap.end();
    }

    Entity Scene::CreateEmptyEntity(UUID uuid)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        Entity entity((uint32_t)m_Registry.create(), this);
        m_RootEntityMap[uuid] = entity;

        return entity;
    }
}
