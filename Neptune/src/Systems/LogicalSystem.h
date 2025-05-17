/**
* @file LogicalSystem.h.
* @brief The LogicalSystem Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "System.h"

namespace Neptune {

    /**
    * @brief LogicalSystem Class.
    * This class defines the LogicalSystem behaves.
    */
    class LogicalSystem : public System
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

        virtual void OnSystemInitialize() override {}
        virtual void OnSystemShutDown() override {}
        virtual void Tick() override {}
    };
}