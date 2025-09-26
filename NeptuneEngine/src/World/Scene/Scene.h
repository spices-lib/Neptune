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
        * @brief View all component in this world.
        * 
        * @tparam T Component.
        * @param[in] fn View function.
        */
        template<typename T, typename F>
        void ViewComponent(F&& fn) const;

        /**
        * @brief View all component in this world in ranges.
        * 
        * @tparam T Component.
        * @param[in] ranges view ranges.
        * @param[in] fn View function.
        */
        template<typename T, typename F>
        void ViewComponent(const std::vector<uint32_t>& ranges, F&& fn) const;

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
        void ViewComponent(const std::vector<uint32_t>& ranges, uint32_t floor, uint32_t ceil, F&& fn) const;

        /**
        * @brief View all root in this world.
        * 
        * @param fn View function.
        */
        template<typename F>
        void ViewRoot(F&& fn) const;

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
        bool HasComponent(uint32_t e) const;

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
        void OnComponentAttached(Entity* entity, T& component) const;

        /**
        * @brief Called On any Component Detached from this scene.
        * 
        * @param[in] entity Entity row pointer.
        * @param[in] component Specific Component reference.
        */
        template<typename T>
        void OnComponentDetached(Entity* entity, T& component) const;

    protected:

        /**
        * @brief Mutex for world.
        */
        mutable std::shared_mutex m_Mutex;

        /**
        * @brief This ECS Registry.
        */
        entt::registry m_Registry;

        /**
        * @brief Root entity.
        */
        uint32_t m_Root;

        /**
        * Allow Entity access all data.
        */
        friend class Entity;
    };

    template <typename T, typename F>
    void Scene::ViewComponent(F&& fn) const
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        const auto view = m_Registry.view<T>();

        for(const auto e : view)
        {
            const auto& comp = m_Registry.get<T>(e);

            if(!std::invoke(fn, static_cast<uint32_t>(e), comp)) break;
        }
    }

    template <typename T, typename F>
    void Scene::ViewComponent(const std::vector<uint32_t>& ranges, F&& fn) const
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        for(const auto range : ranges)
        {
            const auto e = static_cast<entt::entity>(range);
            const auto& comp = m_Registry.get<T>(e);

            if (!std::invoke(fn, range, comp)) break;
        }
    }

    template<typename T, typename F>
    void Scene::ViewComponent(const std::vector<uint32_t>& ranges, uint32_t floor, uint32_t ceil, F&& fn) const
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);
        
        assert(ceil >= floor);
        assert(ceil <= ranges.size() - 1);

        for(int32_t i = floor; i < ceil; i++)
        {
            const auto e = static_cast<entt::entity>(ranges[i]);
            const auto& comp = m_Registry.get<T>(e);

            if (!std::invoke(fn, ranges[i], comp)) break;
        }
    }

    template<typename F>
    void Scene::ViewRoot(F&& fn) const
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);
        
        if (!std::invoke(fn, m_Root)) break;
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
    bool Scene::HasComponent(uint32_t e) const
    {
        NEPTUNE_PROFILE_ZONE

        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.all_of<T>(static_cast<entt::entity>(e));
    }

    template<typename T>
    void Scene::OnComponentAttached(Entity* entity, T& component) const
    {
        NEPTUNE_PROFILE_ZONE

        component.OnComponentAttached(*entity);
    }

    template <typename T>
    void Scene::OnComponentDetached(Entity* entity, T& component) const
    {
        NEPTUNE_PROFILE_ZONE

        component.OnComponentDetached(*entity);
    }
}
