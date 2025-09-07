/**
* @file LuaScript.h.
* @brief The LuaScript Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Scripts/ScriptInterface.h"

namespace Neptune {

    /**
    * @brief Lua Script Class.
    */
    class LuaScript : public ScriptInterface
    {
    public:

        /**
        * @brief Constructor Function.
        */
        LuaScript() = default;

        /**
        * @brief Destructor Function.
        */
        ~LuaScript() override = default;

        /**
        * @brief This interface defines the behave on specific component on construct.
        */
        void OnConstruct() override;
        
        /**
        * @brief This interface defines the behave on specific component tick every frame.
        */
        void OnTick() override;

        /**
        * @brief This interface defines the behave on specific component on destroy.
        */
        void OnDestroy() override;
        
        /**
        * @brief This interface defines the behave on specific component event happened.
        * 
        * @param[in] e Event.
        */
        void OnEvent(Event& e) override;
    };
}