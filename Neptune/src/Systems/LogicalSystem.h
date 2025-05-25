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
        virtual ~LogicalSystem() override = default;

        /**
        * @brief Interface of system initialize.
        */
        virtual void OnSystemInitialize() override {}

        /**
        * @brief Interface of system shutdown.
        */
        virtual void OnSystemShutDown() override {}

        /**
        * @brief Interface of system tick run.
        */
        virtual void Tick() override {}

        virtual void OnEvent(Event& event) override {};
    };
}