/**
* @file LuaScript.h.
* @brief The LuaScript Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Scripts/ScriptInterface.h"

#include <sol/sol.hpp>

namespace Neptune::Lua {

    /**
    * @brief Lua Script Class.
    */
    class LuaScript : public ScriptInterface
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] file Script File. 
        */
        LuaScript(const std::string& file);

        /**
        * @brief Destructor Function.
        */
        ~LuaScript() override = default;

        /**
        * @brief This interface defines the behave on specific component on construct.
        */
        void OnConstruct() override;

        /**
        * @brief This interface defines the behave on specific component on attached.
        */
        void OnAttached() override;
        
        /**
        * @brief This interface defines the behave on specific component tick every frame.
        */
        void OnTick() override;

        /**
        * @brief This interface defines the behave on specific component on destroy.
        */
        void OnDestroy() override;

        /**
        * @brief This interface defines the behave on specific component on detached.
        */
        void OnDetached() override;
        
        /**
        * @brief This interface defines the behave on specific component event happened.
        * 
        * @param[in] e Event.
        */
        void OnEvent(Event& e) override;

    private:

        sol::protected_function GetBindFunction(sol::table& table, const std::string& name);

    private:

        sol::protected_function m_OnConstruct{ sol::lua_nil };
        sol::protected_function m_OnDestroy  { sol::lua_nil };
        sol::protected_function m_OnAttached { sol::lua_nil };
        sol::protected_function m_OnDetached { sol::lua_nil };
        sol::protected_function m_OnTick     { sol::lua_nil };
        sol::protected_function m_OnEvent    { sol::lua_nil };
    };
}