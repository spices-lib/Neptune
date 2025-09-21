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
    * When we add an new Component, we need inherit from this.
    */
    class Component : public NonCopyable
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
        * @brief This interface defines the behaves on specific component attached.
        * 
        * @param[in] entity this component's Owner entity.
        */
        virtual void OnComponentAttached(uint32_t entity);

        /**
        * @brief This interface defines the behaves on specific component detached.
        */
        virtual void OnComponentDetached();

    protected:

        /**
        * @brief This component's Owner entity.
        */
        uint32_t m_Owner = 0;
    };

}
