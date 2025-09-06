/**
* @file Component.h
* @brief The Component Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"

namespace Neptune {

    /**
    * @brief Component Class.
    * This class defines the basic behaves of component.
    * When we add an new Component, we need inherit from this.
    */
    class Component
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Component() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~Component() = default;

        /**
        * @brief This interface defines the behaves on specific component added.
        * 
        * @param[in] entity this component's Owner entity.
        */
        virtual void OnComponentAdded(uint32_t entity);

    protected:

        /**
        * @brief This component's Owner entity.
        */
        uint32_t m_Owner = 0;
    };

}
