/**
* @file ClockComponent.h.
* @brief The ClockComponent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "Data/Clock.h"

namespace Neptune {

    /**
    * @brief ClockComponent Class.
    * This class defines the specific behaves of ClockComponent.
    */
    class ClockComponent : public Component
    {
    public:

        /**
        * @brief Constructor Function.
        */
        ClockComponent() = default;

        /**
        * @brief Destructor Function.
        */
        ~ClockComponent() override = default;

        /**
        * @brief Get Clock.
        */
        Data::Clock& GetClock() { return m_Clock; }
        
        /**
        * @brief Get Clock.
        */
        const Data::Clock& GetClock() const { return m_Clock; }

    private:

        Data::Clock m_Clock;    // @brief This Clock.
    };
}