/**
* @file RHISystem.h.
* @brief The RHISystem Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "System.h"

namespace Neptune {

    /**
    * @brief RHISystem Class.
    * This class defines the RHISystem behaves.
    */
    class RHISystem : public System
    {
    public:

        /**
        * @brief Constructor Function.
        */
        RHISystem() : System() {}

        /**
        * @brief Destructor Function.
        */
        virtual ~RHISystem() override = default;

        virtual void OnSystemInitialize() override {}
        virtual void OnSystemShutDown() override {}
        virtual void Tick() override {}
    };
}