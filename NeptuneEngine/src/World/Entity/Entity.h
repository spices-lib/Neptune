/**
* @file Entity.h.
* @brief The Entity Class Definitions.
* @author Spices.
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
        * 
        * @param[in] handle entity handle.
        * @param[in] scene Scene pointer.
        */
        Entity(uint32_t handle, Scene* scene)
                : m_Handle(handle)
                , m_Scene(scene)
        {}

        /**
        * @brief Destructor Function.
        */
        virtual ~Entity() = default;

        /**
        * @brief Used for add specific component to entity.
        * 
        * @tparam T Specific component.
        * @param[in] args Component construct parameters.
        * 
        * @return Returns The specific component reference that added.
        */
        template<typename T, typename... Args>
        T& AddComponent(Args&&... args);

        /**
        * @brief Used for replace specific component to entity.
        * 
        * @tparam T Specific component.
        * @param[in] args Component construct parameters.
        * 
        * @return Returns The specific component reference that replaced.
        */
        template<typename T, typename... Args>
        T& ReplaceComponent(Args&&... args);
        
        /**
        * @brief Get Component owned by this entity.
        * 
        * @tparam T Which Component we will get.
        * 
        * @return Returns the specific Component.
        */
        template<typename T>
        T& GetComponent() const;

        /**
        * @brief Remove Component owned from this entity.
        * 
        * @tparam T Which Component we will remove.
        */
        template<typename T>
        void RemoveComponent() const;

        /**
        * @brief Destroy this entity from Scene.
        */
        void Destroy() const;

        /**
        * @brief If Component is owned by this entity or not.
        * 
        * @tparam T Which Component we will search.
        * 
        * @return Returns true if found.
        */
        template<typename T>
        bool HasComponent() const;

        /**
        * @brief Get UUID form UUIDComponent.
        * 
        * @return Returns UUID.
        */
        const UUID& GetUUID() const;

        /**
        * @brief Empty Operation.
        * 
        * @return Returns m_EntityHandle's value.
        */
        operator uint32_t() const { return m_Handle; }

        /**
        * @brief Equal Operation.
        * 
        * @param[in] other Another Entity.
        * 
        * @return Returns true if equal.
        */
        bool operator ==(const Entity& other) const
        {
            return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
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
        uint32_t m_Handle;

        /**
        * @brief A specific scene Pointer.
        */
        Scene* m_Scene;
    };

    template <typename T, typename ... Args>
    T& Entity::AddComponent(Args&&... args)
    {
        if (HasComponent<T>())
        {
            std::stringstream ss;
            ss << "Entity: " << m_Handle << " already has such component.";

            NEPTUNE_CORE_WARN(ss.str())
            return GetComponent<T>();
        }

        T& component = m_Scene->AddComponent<T>(m_Handle, std::forward<Args>(args)...);
        m_Scene->OnComponentAttached<T>(this, component);
        return component;
    }

    template <typename T, typename ... Args>
    T& Entity::ReplaceComponent(Args&&... args)
    {
        if (!HasComponent<T>())
        {
            return AddComponent<T>(std::forward<Args>(args)...);
        }

        T& component = m_Scene->ReplaceComponent<T>(m_Handle, std::forward<Args>(args)...);
        m_Scene->OnComponentAttached<T>(this, component);
        return component;
    }

    template <typename T>
    T& Entity::GetComponent() const
    {
        return m_Scene->GetComponent<T>(m_Handle);
    }

    template <typename T>
    void Entity::RemoveComponent() const
    {
        if (!HasComponent<T>())
        {
            std::stringstream ss;
            ss << "Entity: " << m_Handle << " does not have such component.";

            NEPTUNE_CORE_WARN(ss.str())
            return;
        }

        T& component = GetComponent<T>();
            
        m_Scene->OnComponentDetached<T>(this, component);
        m_Scene->RemoveComponent<T>(m_Handle);
    }

    template <typename T>
    bool Entity::HasComponent() const
    {
        return m_Scene->HasComponent<T>(m_Handle);
    }
}
