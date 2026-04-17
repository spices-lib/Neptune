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

        PushSystem<LogicalSystem>(ESystem::Logical, this);
        PushSystem<RenderSystem>(ESystem::Render, this);
        PushSystem<RHISystem>(ESystem::RHI, this);
    }

    void SystemManager::Shutdown()
    {
        NEPTUNE_PROFILE_ZONE

        for (int i = m_Systems.size() - 1; i >= 0; --i)
        {
            m_Systems[i]->OnSystemShutDown();
            m_Systems[i] = nullptr;
        }
    }

    void SystemManager::Run() const
    {
        NEPTUNE_PROFILE_ZONE

        for(auto& system : m_Systems)
        {
            system->Tick();
        }
    }

    System* SystemManager::GetSystem(ESystem system) const
    {
        NEPTUNE_PROFILE_ZONE

        return m_Systems[static_cast<uint8_t>(system)].get();
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