/**
* @file SystemManager.cpp.
* @brief The SystemManager Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "SystemManager.h"

namespace Neptune {

    SystemManager* SystemManager::PopSystem()
    {
        m_Systems.back()->OnSystemShutDown();
        m_Systems.pop_back();

        return this;
    }

    void SystemManager::PopAllSystems()
    {
        for(int i = 0; i < m_Systems.size(); i++)
        {
            PopSystem();
        }
    }

    void SystemManager::Run()
    {
        for(int i = 0; i < m_Systems.size(); i++)
        {
            m_Systems[i]->Tick();
        }
    }
}