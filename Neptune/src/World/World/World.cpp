/**
* @file World.cpp.
* @brief The World Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "World.h"
#include "World/Entity.h"

namespace Neptune {

	Entity World::CreateEntity(const std::string& name)
	{
		NEPTUNE_PROFILE_ZONE;

		return CreateEntityWithUUID(UUID(), name);
	}

	Entity World::CreateEntityWithUUID(UUID uuid, const std::string& name)
	{
		NEPTUNE_PROFILE_ZONE;
		
		Entity entity = CreateEmptyEntity(uuid);
		entity.AddComponent<UUIDComponent>(uuid);
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(name);
		return entity;
	}

	void World::DestroyEntity(Entity& entity)
	{
		NEPTUNE_PROFILE_ZONE;

		std::unique_lock<std::shared_mutex> lock(m_Mutex);
		
		m_Registry.destroy(entity);
		m_RootEntityMap.erase(entity.GetUUID());
	}

	Entity World::QueryEntitybyID(uint32_t id)
	{
		NEPTUNE_PROFILE_ZONE;

		return id == -1 ? Entity() : Entity((entt::entity)id, this);
	}

	void World::ClearMarkerWithBits(WorldMarkFlags flags)
	{
		NEPTUNE_PROFILE_ZONE;

		if (m_Marker & flags)
		{
			m_Marker ^= flags;
		}
	}

	void World::RemoveFromRoot(Entity& entity)
	{
		NEPTUNE_PROFILE_ZONE;

		std::unique_lock<std::shared_mutex> lock(m_Mutex);

		m_RootEntityMap.erase(entity.GetUUID());
	}

	void World::AddToRoot(Entity& entity)
	{
		NEPTUNE_PROFILE_ZONE;

		std::unique_lock<std::shared_mutex> lock(m_Mutex);

		m_RootEntityMap[entity.GetUUID()] = entity;
	}

	bool World::IsRootEntity(Entity& entity)
	{
		NEPTUNE_PROFILE_ZONE;

		std::shared_lock<std::shared_mutex> lock(m_Mutex);

		return m_RootEntityMap.find(entity.GetUUID()) != m_RootEntityMap.end();
	}

	Entity World::CreateEmptyEntity(UUID uuid)
	{
		NEPTUNE_PROFILE_ZONE;
		
		std::unique_lock<std::shared_mutex> lock(m_Mutex);
		
		Entity entity(m_Registry.create(), this);
		m_RootEntityMap[uuid] = entity;
		return entity;
	}
}
