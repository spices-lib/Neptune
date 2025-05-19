/**
* @file Scene.h.
* @brief The Scene Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Core/UUID.h"

#include <entt.hpp>
#include <shared_mutex>

namespace Neptune {

    /**
    * Forward Declare
    */
    class Entity;

    /**
    * @brief Scene Class.
    * This class defines the basic behaves of Scene.
    */
    class Scene : public NonCopyable
    {
    public:

        enum SceneMarkBits
        {
            Clean            = 0x00000001,
            MeshAddedToScene = 0x00000002,
            FlushStableFrame = 0x00000004,
            NeedUpdateTLAS   = 0x00000008,
            MAX              = 0x7FFFFFFF
        };

        typedef uint32_t SceneMarkFlags;

    public:

        /**
        * @brief Constructor Function.
        */
        Scene() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~Scene() = default;

        /**
        * @brief Create a new empty entity in this world.
        * @param[in] name Entity name.
        */
        Entity CreateEntity(const std::string& name = "None");

        /**
        * @brief Create a new empty entity with a uuid in this world.
        * @param[in] uuid UUID.
        * @param[in] name Entity name.
        */
        Entity CreateEntityWithUUID(UUID uuid, const std::string& name = "None");

        /**
        * @brief Destroy a entity from this world.
        * @param[in] entity Entity.
        */
        void DestroyEntity(Entity& entity);

        /**
        * @brief Get World Entity by id(entt::entity).
        * @param[in] id Id(entt::entity)
        * @return Returns valid Entity if fined.
        */
        Entity QueryEntityByID(uint32_t id);

        /**
        * @brief Get WorldMarkFlags this frame.
        * @return Returns the WorldMarkFlags this frame.
        */
        SceneMarkFlags GetMarker() const { return m_Marker; }

        /**
        * @brief Mark WorldMarkFlags with flags.
        * @param[in] flags In flags.
        */
        void Mark(SceneMarkFlags flags) { m_Marker |= flags; }

        /**
        * @brief Reset WorldMarkFlags to Clean.
        */
        void ResetMark() { m_Marker = SceneMarkBits::Clean; }

        /**
        * @brief Clear WorldMarkFlags with flags.
        * @param[in] flags In flags.
        */
        void ClearMarkerWithBits(SceneMarkFlags flags);

        /**
        * @brief View all component in this world.
        * @tparam T Component.
        * @param fn View function.
        */
        template<typename T, typename F>
        void ViewComponent(F&& fn);

        /**
        * @brief View all component in this world in ranges.
        * @tparam T Component.
        * @param[in] ranges view ranges.
        * @param fn View function.
        */
        template<typename T, typename F>
        void ViewComponent(const std::vector<uint32_t>& ranges, F&& fn);

        /**
        * @brief View all component in this world in ranges.
        * @tparam T Component.
        * @param[in] ranges view ranges.
        * @param[in] floor ranges floor.
        * @param[in] ceil ranges ceil.
        * @param fn View function.
        */
        template<typename T, typename F>
        void ViewComponent(const std::vector<uint32_t>& ranges, uint32_t floor, uint32_t ceil, F&& fn);

        /**
        * @brief View all root in this world.
        * @param fn View function.
        */
        template<typename F>
        void ViewRoot(F&& fn);

        /**
        * @brief Template Function.
        * Used for add specific component to entity.
        * @tparam T Specific component.
        * @param[in] e entt::entity.
        * @param[in] args Component construct parameters.
        * @return Returns The specific component reference that added.
        */
        template<typename T, typename... Args>
        T& AddComponent(uint32_t e, Args&&... args);

        /**
        * @brief Get Component owned by this entity.
        * @tparam T Which Component we will get.
        * @param[in] e entt::entity.
        * @return Returns the specific Component.
        */
        template<typename T>
        T& GetComponent(uint32_t e);

        /**
        * @brief Remove Component owned from this entity.
        * @tparam T Which Component we will remove.
        * @param[in] e entt::entity.
        */
        template<typename T>
        void RemoveComponent(uint32_t e);

        /**
        * @brief If Component is owned by this entity or not.
        * @tparam T Which Component we will search.
        * @param[in] e entt::entity.
        * @return Returns true if found.
        */
        template<typename T>
        bool HasComponent(uint32_t e);

        /**
        * @brief Remove a entity from this world root.
        * @param[in] entity Entity.
        */
        void RemoveFromRoot(Entity& entity);

        /**
        * @brief Add a entity to this world root.
        * @param[in] entity Entity.
        */
        void AddToRoot(Entity& entity);

        /**
        * @brief Determine if a entity is in root.
        * @param[in] entity Entity.
        */
        bool IsRootEntity(Entity& entity);

    private:

        /**
        * @brief Create empty entity with uuid.
        * @param[in] uuid UUID.
        */
        Entity CreateEmptyEntity(UUID uuid);

        /**
        * @brief Called On any Component Added to this world.
        * @param[in] entity Entity row pointer.
        * @param[in] component Specific Component reference.
        */
        template<typename T>
        void OnComponentAdded(Entity* entity, T& component);

    protected:

        /**
        * @brief Mutex for world.
        */
        std::shared_mutex m_Mutex;

        /**
        * @brief This variable handles all entity.
        */
        entt::registry m_Registry;

        /**
        * @brief This variable is a cache.
        * @noto Not in use now.
        * @todo use it.
        */
        std::unordered_map<UUID, uint32_t> m_RootEntityMap;

        /**
        * @brief World State this frame.
        */
        SceneMarkFlags m_Marker = SceneMarkBits::Clean;

        /**
        * Allow Entity access all data.
        */
        friend class Entity;
    };

    template <typename T, typename F>
    inline void Scene::ViewComponent(F&& fn)
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        auto view = m_Registry.view<T>();

        for(auto e : view)
        {
            auto& comp = m_Registry.get<T>(e);

            if(fn((uint32_t)e, comp)) break;
        }
    }

    template <typename T, typename F>
    inline void Scene::ViewComponent(const std::vector<uint32_t>& ranges, F&& fn)
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        for(auto range : ranges)
        {
            auto e = static_cast<entt::entity>(range);
            auto& comp = m_Registry.get<T>(e);

            fn(range, comp);
        }
    }

    template<typename T, typename F>
    inline void Scene::ViewComponent(const std::vector<uint32_t>& ranges, uint32_t floor, uint32_t ceil, F&& fn)
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        assert(floor >= 0);
        assert(ceil >= floor);
        assert(ceil <= ranges.size() - 1);

        for(int32_t i = floor; i < ceil; i++)
        {
            auto e = static_cast<entt::entity>(ranges[i]);
            auto& comp = m_Registry.get<T>(e);

            fn(ranges[i], comp);
        }
    }

    template<typename F>
    inline void Scene::ViewRoot(F&& fn)
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        for (auto entity : m_RootEntityMap)
        {
            fn(entity.second);
        }
    }

    template <typename T, typename ... Args>
    inline T& Scene::AddComponent(uint32_t e, Args&&... args)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.emplace<T>((entt::entity)e, std::forward<Args>(args)...);
    }

    template <typename T>
    inline T& Scene::GetComponent(uint32_t e)
    {
        /**
        * @note lock cause bug here.
        */
        //std::shared_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.get<T>((entt::entity)e);
    }

    template <typename T>
    inline void Scene::RemoveComponent(uint32_t e)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        m_Registry.remove<T>((entt::entity)e);
    }

    template <typename T>
    inline bool Scene::HasComponent(uint32_t e)
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.all_of<T>((entt::entity)e);
    }

    template<typename T>
    inline void Scene::OnComponentAdded(Entity* entity, T& component)
    {
        component.OnComponentAdded(*entity);
    }
}
