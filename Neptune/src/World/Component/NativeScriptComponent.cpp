/**
* @file NativeScriptComponent.cpp.
* @brief The NativeScriptComponent Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "NativeScriptComponent.h"
#include "NativeScripts/NativeScript.h"

namespace Neptune {

    NativeScriptComponent::NativeScriptComponent(std::shared_ptr<NativeScript> script)
        : m_Script(script)
    {}

    void NativeScriptComponent::OnTick()
    {
        m_Script->OnTick();
    }

    void NativeScriptComponent::OnEvent(Event& e)
    {
        m_Script->OnEvent(e);
    }
}