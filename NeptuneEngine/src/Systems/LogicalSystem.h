/**
* @file LogicalSystem.h.
* @brief The LogicalSystem Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "System.h"
#include "Core/Event/EventListener.h"

namespace Neptune {

    /**
    * @brief LogicalSystem Class.
    * This class defines the LogicalSystem behaves.
    */
    class LogicalSystem : public System, public EventListener
    {
    public:

        /**
        * @brief Constructor Function.
        */
        LogicalSystem() : System() {}

        /**
        * @brief Destructor Function.
        */
        ~LogicalSystem() override = default;

        /**
        * @brief Interface of system initialize.
        */
        void OnSystemInitialize() override {}

        /**
        * @brief Interface of system shutdown.
        */
        void OnSystemShutDown() override {}

        /**
        * @brief Interface of system tick run.
        */
        void Tick() override {}

        void OnEvent(Event& event) override {}
    };
}