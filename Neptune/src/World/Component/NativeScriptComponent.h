/**
* @file NativeScriptComponent.h.
* @brief The NativeScriptComponent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Component.h"

namespace Neptune {

    class NativeScript;

    /**
    * @brief NativeScriptComponent Class.
    * This class defines the specific behaves of NativeScriptComponent.
    */
    class NativeScriptComponent : public Component
    {
    public:

        /**
        * @brief Constructor Function.
        */
        NativeScriptComponent() = default;

        /**
        * @brief Constructor Function.
        * @param[in] script NativeScript.
        */
        NativeScriptComponent(std::shared_ptr<NativeScript> script);

        /**
        * @brief Destructor Function.
        */
        virtual ~NativeScriptComponent() override = default;

        /**
        * @brief This interface defines the behaves on specific component tick every frame.
        */
        virtual void OnTick();

        /**
        * @brief This interface defines the behaves on specific component event happened.
        * @param[in] e Event.
        */
        virtual void OnEvent(Event& e);

    private:

        /**
        * @brief NativeScript
        */
        std::shared_ptr<NativeScript> m_Script;
    };
}