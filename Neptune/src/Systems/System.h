/**
* @file System.h.
* @brief The System Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Core/Event/Event.h"
#include "Enum.h"

namespace Neptune {

    /**
    * @brief System Class.
    * This class defines the System behaves.
    */
    class System : public NonCopyable
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] system ESystem.
        * @param[in] manager SystemManager.
        */
        System(ESystem system, class SystemManager* manager) 
            : m_ESystem(system), m_Manager(manager) 
        {}

        /**
        * @brief Destructor Function.
        */
        ~System() override = default;

        /**
        * @brief Interface of system initialize.
        */
        virtual void OnSystemInitialize() = 0;

        /**
        * @brief Interface of system shutdown.
        */
        virtual void OnSystemShutDown() = 0;

        /**
        * @brief Interface of system tick run.
        */
        virtual void Tick() = 0;

        /**
        * @brief Get SystemManager System.
        * 
        * @param[in] system ESystem.
        * 
        * @return Returns System Pointer.
        */
        System* GetSystem(ESystem system) const;

    private:

        ESystem m_ESystem;               // @brief This ESystem.
        SystemManager* m_Manager;        // @brief SystemManager pointer.
    };
}