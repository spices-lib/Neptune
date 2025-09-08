/**
* @file ScriptComponent.h.
* @brief The ScriptComponent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Component.h"

namespace Neptune {

    class ScriptInterface;

    /**
    * @brief ScriptComponent Class.
    * This class defines the specific behaves of ScriptComponent.
    */
    class ScriptComponent : public Component
    {
    public:

        /**
        * @brief Constructor Function.
        */
        ScriptComponent() = default;

        /**
        * @brief Add a script to this component.
        * 
        * @param[in] script ScriptInterface.
        */
        void AddScript(const SP<ScriptInterface>& script);

        /**
        * @brief Remove a script to this component.
        * 
        * @param[in] name Script Name.
        */
        void RemoveScript(const std::string& name);

        /**
        * @brief Destructor Function.
        */
        ~ScriptComponent() override = default;

        /**
        * @brief This method defines the behaves on specific component tick every frame.
        */
        void OnTick() const;

        /**
        * @brief This method defines the behaves on specific component event happened.
        * 
        * @param[in] e Event.
        */
        void OnEvent(Event& e) const;

        /**
        * @brief This interface defines the behaves on specific component detached.
        */
        void OnComponentDetached() override;

    private:

        /**
        * @brief Scripts map
        */
        std::map<std::string, SP<ScriptInterface>> m_Scripts;
    };
}