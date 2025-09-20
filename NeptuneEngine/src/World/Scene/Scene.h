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
    * Object that needs to be presented on screen must be added to a scene.
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
        Scene();

        /**
        * @brief Destructor Function.
        */
        ~Scene() override = default;

        /**
        * @brief Create a new empty entity in this world.
        * 
        * @param[in] name Entity name.
        */
        Entity CreateEntity(const std::string& name = "None");

        /**
        * @brief Create a new empty entity with a uuid in this world.
        * 
        * @param[in] uuid UUID.
        * @param[in] name Entity name.
        */
        Entity CreateEntityWithUUID(UUID uuid, const std::string& name = "None");

        /**
        * @brief Destroy a entity from this world.
        * 
        * @param[in] entity Entity.
        */
        void Destroy(const Entity& entity);

        /**
        * @brief Get World Entity by id(entt::entity).
        * 
        * @param[in] id Id(entt::entity)
        * 
        * @return Returns valid Entity if fined.
        */
        Entity QueryEntityByID(uint32_t id);

        /**
        * @brief Get WorldMarkFlags this frame.
        * 
        * @return Returns the WorldMarkFlags this frame.
        */
        SceneMarkFlags GetMarker() const { return m_Marker; }

        /**
        * @brief Mark WorldMarkFlags with flags.
        * 
        * @param[in] flags In flags.
        */
        void Mark(SceneMarkFlags flags) { m_Marker |= flags; }

        /**
        * @brief Reset WorldMarkFlags to Clean.
        */
        void ResetMark() { m_Marker = SceneMarkBits::Clean; }

        /**
        * @brief Clear WorldMarkFlags with flags.
        * 
        * @param[in] flags In flags.
        */
        void ClearMarkerWithBits(SceneMarkFlags flags);

        /**
        * @brief View all component in this world.
        * 
        * @tparam T Component.
        * @param[in] fn View function.
        */
        template<typename T, typename F>
        void ViewComponent(F&& fn);

        /**
        * @brief View all component in this world in ranges.
        * 
        * @tparam T Component.
        * @param[in] ranges view ranges.
        * @param[in] fn View function.
        */
        template<typename T, typename F>
        void ViewComponent(const std::vector<uint32_t>& ranges, F&& fn);

        /**
        * @brief View all component in this world in ranges.
        * 
        * @tparam T Component.
        * @param[in] ranges view ranges.
        * @param[in] floor ranges floor.
        * @param[in] ceil ranges ceil.
        * @param[in] fn View function.
        */
        template<typename T, typename F>
        void ViewComponent(const std::vector<uint32_t>& ranges, uint32_t floor, uint32_t ceil, F&& fn);

        /**
        * @brief View all root in this world.
        * 
        * @param fn View function.
        */
        template<typename F>
        void ViewRoot(F&& fn);

        /**
        * @brief Template Function.
        * Used for add specific component to entity.
        * 
        * @tparam T Specific component.
        * @param[in] e entity handle.
        * @param[in] args Component construct parameters.
        * 
        * @return Returns The specific component reference that added.
        */
        template<typename T, typename... Args>
        T& AddComponent(uint32_t e, Args&&... args);

        /**
        * @brief Template Function.
        * Used for replace specific component to entity.
        * 
        * @tparam T Specific component.
        * @param[in] e entity handle.
        * @param[in] args Component construct parameters.
        * 
        * @return Returns The specific component reference that replaced.
        */
        template<typename T, typename... Args>
        T& ReplaceComponent(uint32_t e, Args&&... args);
        
        /**
        * @brief Get Component owned by this entity.
        * 
        * @tparam T Which Component we will get.
        * @param[in] e entity handle.
        * 
        * @return Returns the specific Component.
        */
        template<typename T>
        T& GetComponent(uint32_t e);

        /**
        * @brief Remove Component owned from this entity.
        * 
        * @tparam T Which Component we will remove.
        * @param[in] e entity handle.
        */
        template<typename T>
        void RemoveComponent(uint32_t e);

        /**
        * @brief If Component is owned by this entity or not.
        * 
        * @tparam T Which Component we will search.
        * @param[in] e entity handle.
        * 
        * @return Returns true if found.
        */
        template<typename T>
        bool HasComponent(uint32_t e);

    private:

        /**
        * @brief Create empty entity with uuid.
        * 
        * @param[in] uuid UUID.
        */
        Entity CreateEmptyEntity(UUID uuid);

        /**
        * @brief Called On any Component Attached to this scene.
        * 
        * @param[in] entity Entity row pointer.
        * @param[in] component Specific Component reference.
        */
        template<typename T>
        void OnComponentAttached(Entity* entity, T& component);

        /**
        * @brief Called On any Component Detached from this scene.
        * 
        * @param[in] entity Entity row pointer.
        * @param[in] component Specific Component reference.
        */
        template<typename T>
        void OnComponentDetached(Entity* entity, T& component);

    protected:

        /**
        * @brief Mutex for world.
        */
        std::shared_mutex m_Mutex;

        /**
        * @brief This ECS Registry.
        */
        entt::registry m_Registry;

        /**
        * @brief Root entity.
        */
        uint32_t m_Root;

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
    void Scene::ViewComponent(F&& fn)
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        auto view = m_Registry.view<T>();

        for(auto e : view)
        {
            auto& comp = m_Registry.get<T>(e);

            if(fn(static_cast<uint32_t>(e), comp)) break;
        }
    }

    template <typename T, typename F>
    void Scene::ViewComponent(const std::vector<uint32_t>& ranges, F&& fn)
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        for(auto range : ranges)
        {
            auto e = static_cast<entt::entity>(range);
            auto& comp = m_Registry.get<T>(e);

            fn(range, comp);
        }
    }

    template<typename T, typename F>
    void Scene::ViewComponent(const std::vector<uint32_t>& ranges, uint32_t floor, uint32_t ceil, F&& fn)
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);
        
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
    void Scene::ViewRoot(F&& fn)
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);
        
        fn(m_Root);
    }

    template <typename T, typename ... Args>
    T& Scene::AddComponent(uint32_t e, Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.emplace<T>(static_cast<entt::entity>(e), std::forward<Args>(args)...);
    }

    template <typename T, typename ... Args>
    T& Scene::ReplaceComponent(uint32_t e, Args&&... args)
    {
        NEPTUNE_PROFILE_ZONE

        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.replace<T>(static_cast<entt::entity>(e), std::forward<Args>(args)...);
    }

    template <typename T>
    T& Scene::GetComponent(uint32_t e)
    {
        NEPTUNE_PROFILE_ZONE

        /**
        * @note lock cause bug here.
        */
        //std::shared_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.get<T>(static_cast<entt::entity>(e));
    }

    template <typename T>
    void Scene::RemoveComponent(uint32_t e)
    {
        NEPTUNE_PROFILE_ZONE

        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        m_Registry.remove<T>(static_cast<entt::entity>(e));
    }

    template <typename T>
    bool Scene::HasComponent(uint32_t e)
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.all_of<T>(static_cast<entt::entity>(e));
    }

    template<typename T>
    void Scene::OnComponentAttached(Entity* entity, T& component)
    {
        NEPTUNE_PROFILE_ZONE

        component.OnComponentAttached(*entity);
    }

    template <typename T>
    void Scene::OnComponentDetached(Entity* entity, T& component)
    {
        NEPTUNE_PROFILE_ZONE

        component.OnComponentDetached(*entity);
    }
}
