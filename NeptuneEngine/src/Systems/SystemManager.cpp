/**
* @file SystemManager.cpp.
* @brief The SystemManager Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "SystemManager.h"
#include "Core/Event/EventListener.h"

namespace Neptune {

    SystemManager::SystemManager()
    {
        // Set Global EventCallBack
        Event::SetEventCallbackFn(BIND_EVENT_FN(SystemManager::OnEvent));
    }

    SystemManager* SystemManager::PopSystem()
    {
        m_Systems.back()->OnSystemShutDown();
        m_Systems.pop_back();

        return this;
    }

    void SystemManager::PopAllSystems()
    {
        for(auto& system : m_Systems)
        {
            PopSystem();
        }
    }

    void SystemManager::Run() const
    {
        for(auto& system : m_Systems)
        {
            system->Tick();
        }
    }

    void SystemManager::OnEvent(Event& event) const
    {
        NEPTUNE_CORE_TRACE(event.ToString())

        for(auto& system : m_Systems)
        {
            EventListener::Dispatch(event, system.get());
        }
    }
}