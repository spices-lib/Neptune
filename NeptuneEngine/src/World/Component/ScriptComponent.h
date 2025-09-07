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
        * @brief Constructor Function.
        * 
        * @param[in] script ScriptInterface.
        */
        void AddScript(const SP<ScriptInterface>& script);

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

    private:

        /**
        * @brief Scripts
        */
        std::set<SP<ScriptInterface>> m_Scripts;
    };
}