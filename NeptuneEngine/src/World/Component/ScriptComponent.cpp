/**
* @file ScriptComponent.cpp.
* @brief The ScriptComponent Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ScriptComponent.h"
#include "Scripts/ScriptInterface.h"
#include <ranges>

namespace Neptune {

    void ScriptComponent::AddScript(const SP<ScriptInterface>& script)
    {
        NEPTUNE_PROFILE_ZONE

        if (m_Scripts.contains(script->GetName()))
        {
            NEPTUNE_CORE_WARN("Script is existing on component.")
            return;
        }

        script->OnAttached();
        m_Scripts[script->GetName()] = script;
    }

    void ScriptComponent::RemoveScript(const std::string& name)
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Scripts.contains(name))
        {
            NEPTUNE_CORE_WARN("Script is not existing on component.")
            return;
        }

        m_Scripts[name]->OnDetached();
        m_Scripts.erase(name);
    }
    
    void ScriptComponent::OnTick() const
    {
        NEPTUNE_PROFILE_ZONE

        for (const auto& script : m_Scripts | std::views::values)
        {
            script->OnTick();
        }
    }

    void ScriptComponent::OnEvent(Event& e) const
    {
        NEPTUNE_PROFILE_ZONE

        for (const auto& script : m_Scripts | std::views::values)
        {
            script->OnEvent(e);
        }
    }

    void ScriptComponent::OnComponentDetached()
    {
        NEPTUNE_PROFILE_ZONE

        for (const auto& script : m_Scripts | std::views::values)
        {
            script->OnDestroy();
        }
    }
    
}