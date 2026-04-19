/**
* @file Component.h
* @brief The Component Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Core/Event/Event.h"

namespace Neptune {

    /**
    * @brief Component Class.
    * This class defines the basic behaves of component.
    * When we add a new Component, we need Specialization from this.
    */
    template<typename T>
    class Component : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Component() = default;

        /**
        * @brief Constructor Function.
        */
        template<typename T1>
        explicit Component(T1&& t) : m_Model(t) {}

        /**
        * @brief Destructor Function.
        */
        ~Component() override = default;

        /**
        * @brief This interface defines the behaves on specific component attached.
        * 
        * @param[in] entity this component's Owner entity.
        */
        virtual void OnComponentAttached(uint32_t entity) { m_Owner = entity; }

        /**
        * @brief This interface defines the behaves on specific component detached.
        */
        virtual void OnComponentDetached() {}

        /**
        * @brief Get Model.
        * 
        * @return Returns Model.
        */
        const T& GetModel() const { return m_Model; }

        /**
        * @brief Get Model.
        *
        * @return Returns Model.
        */
        T& GetModel() { return m_Model; }

        /**
        * @brief Set Model.
        *
        * @param[in] t T1.
        */
        template<typename T1>
        void SetModel(T1&& t) { m_Model = t; }

    protected:

        T m_Model;              // @brief This component's data model.

        uint32_t m_Owner = 0;   // @brief This component's Owner entity.
    };

}
