/**
* @file Entity.h.
* @brief The Entity Class Definitions.
* @author The Cherno.
*/

#pragma once
#include "Core/Core.h"
#include "World/Scene/Scene.h"

#include "World/Component/UUIDComponent.h"

namespace Neptune {

    /**
    * @brief Entity Class.
    * This class defines the specific behaves of Entity.
    */
    class Entity
    {
    public:

        /**
        * @brief Constructor Function.
        * Init class variable.
        * Usually call it.
        * 
        * @param[in] handle entity handle.
        * @param[in] scene Scene pointer.
        */
        Entity(uint32_t handle, Scene* scene)
                : m_EntityHandle(handle)
                , m_Scene(scene)
        {}

        /**
        * @brief Destructor Function.
        */
        virtual ~Entity() = default;

        /**
        * @brief Template Function.
        * Used for add specific component to entity.
        * 
        * @tparam T Specific component.
        * @param[in] args Component construct parameters.
        * 
        * @return Returns The specific component reference that added.
        */
        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            if (HasComponent<T>())
            {
                std::stringstream ss;
                ss << "Entity: " << m_EntityHandle << " already has such component.";

                NEPTUNE_CORE_WARN(ss.str())
                return GetComponent<T>();
            }

            T& component = m_Scene->AddComponent<T>(m_EntityHandle, std::forward<Args>(args)...);
            m_Scene->OnComponentAdded<T>(this, component);
            return component;
        }

        /**
        * @brief Get Component owned by this entity.
        * 
        * @tparam T Which Component we will get.
        * 
        * @return Returns the specific Component.
        */
        template<typename T>
        T& GetComponent() const
        {
            return m_Scene->GetComponent<T>(m_EntityHandle);
        }

        /**
        * @brief Remove Component owned from this entity.
        * 
        * @tparam T Which Component we will remove.
        */
        template<typename T>
        void RemoveComponent() const
        {
            m_Scene->RemoveComponent<T>(m_EntityHandle);
        }

        /**
        * @brief Remove a entity from this world root.
        */
        void RemoveFromRoot()
        {
            m_Scene->RemoveFromRoot(*this);
        }

        /**
        * @brief Add a entity to this world root.
        */
        void AddToRoot()
        {
            m_Scene->AddToRoot(*this);
        }

        /**
        * @brief If Component is owned by this entity or not.
        * 
        * @tparam T Which Component we will search.
        * 
        * @return Returns true if found.
        */
        template<typename T>
        bool HasComponent() const
        {
            return m_Scene->HasComponent<T>(m_EntityHandle);
        }

        /**
        * @brief Get UUID form UUIDComponent.
        * 
        * @return Returns UUID.
        */
        const UUID GetUUID() const { return GetComponent<UUIDComponent>().GetUUID(); }

        /**
        * @brief Empty Operation.
        * 
        * @return Returns m_EntityHandle's value.
        */
        operator uint32_t() const { return m_EntityHandle; }

        /**
        * @brief Equal Operation.
        * 
        * @param[in] other Another Entity.
        * 
        * @return Returns true if equal.
        */
        bool operator ==(const Entity& other) const
        {
            return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
        }

        /**
        * @brief Not equal Operation.
        * 
        * @param[in] other Another Entity.
        * 
        * @return Returns true if not equal.
        */
        bool operator !=(const Entity& other) const
        {
            return !operator==(other);
        }

    private:

        /**
        * @brief This entity's identify in ECS.
        */
        uint32_t m_EntityHandle;

        /**
        * @brief A specific scene Pointer.
        */
        Scene* m_Scene;
    };
}