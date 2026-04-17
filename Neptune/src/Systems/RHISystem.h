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
        * 
        * @param[in] manager SystemManager.
        */
        explicit RHISystem(SystemManager* manager) 
            : System(ESystem::RHI, manager) 
        {}

        /**
        * @brief Destructor Function.
        */
        ~RHISystem() override = default;

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
    };
}