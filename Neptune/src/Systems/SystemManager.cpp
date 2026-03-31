/**
* @file SystemManager.cpp.
* @brief The SystemManager Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "SystemManager.h"
#include "Core/Event/EventListener.h"
#include "Systems/LogicalSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/RHISystem.h"

namespace Neptune {

    SystemManager::SystemManager()
    {
        NEPTUNE_PROFILE_ZONE

        // Set Global EventCallBack
        Event::SetEventCallbackFn(BIND_EVENT_FN(SystemManager::OnEvent));
    }

    void SystemManager::Initialize()
    {
        NEPTUNE_PROFILE_ZONE

        PushSystem<LogicalSystem>();
        PushSystem<RenderSystem>();
        PushSystem<RHISystem>();
    }

    void SystemManager::Shutdown()
    {
        NEPTUNE_PROFILE_ZONE

        while(!m_Systems.empty())
        {
            PopSystem();
        }
    }

    void SystemManager::PopSystem()
    {
        NEPTUNE_PROFILE_ZONE

        m_Systems.back()->OnSystemShutDown();
        m_Systems.pop_back();
    }

    void SystemManager::Run() const
    {
        NEPTUNE_PROFILE_ZONE

        for(auto& system : m_Systems)
        {
            system->Tick();
        }
    }

    void SystemManager::OnEvent(Event& event) const
    {
        NEPTUNE_PROFILE_ZONE

        NEPTUNE_CORE_TRACE(event.ToString())

        for(auto& system : m_Systems)
        {
            EventListener::Dispatch(event, system.get());
        }
    }
}