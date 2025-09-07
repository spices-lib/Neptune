/**
* @file ScriptComponent.cpp.
* @brief The ScriptComponent Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ScriptComponent.h"
#include "Scripts/ScriptInterface.h"

namespace Neptune {

    void ScriptComponent::AddScript(const SP<ScriptInterface>& script)
    {
        if (m_Scripts.contains(script))
        {
            NEPTUNE_CORE_WARN("Script is existing on component.")
            return;
        }

        script->OnConstruct();
        m_Scripts.insert(script);
    }

    void ScriptComponent::OnTick() const
    {
        for (const auto& script : m_Scripts)
        {
            script->OnTick();
        }
    }

    void ScriptComponent::OnEvent(Event& e) const
    {
        for (const auto& script : m_Scripts)
        {
            script->OnEvent(e);
        }
    }
}