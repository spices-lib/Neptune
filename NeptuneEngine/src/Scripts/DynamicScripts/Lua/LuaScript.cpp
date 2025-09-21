/**
* @file LuaScript.cpp.
* @brief The LuaScript Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "LuaScript.h"

namespace Neptune::Lua {

    LuaScript::LuaScript(const std::string& file)
    {
        auto lua = std::make_shared<sol::state>();

        if (!lua)
        {
            NEPTUNE_CORE_ERROR("Failed to Create Lua State.")
            return;
        }

        lua->open_libraries(sol::lib::base, sol::lib::math, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::string);

        try
        {
            auto result = lua->safe_script_file(file);
        }
        catch (const sol::error& err)
        {
            NEPTUNE_CORE_ERROR(err.what())
            return;
        }

        sol::table main = (*lua)["main"];

        m_OnConstruct = GetBindFunction(main, 1, "OnConstruct");
        m_OnDestroy   = GetBindFunction(main, 2, "OnDestroy");
        m_OnAttached  = GetBindFunction(main, 3, "OnAttached");
        m_OnDetached  = GetBindFunction(main, 4, "OnDetached");
        m_OnTick      = GetBindFunction(main, 5, "OnTick");
        m_OnEvent     = GetBindFunction(main, 6, "OnEvent");
    }

    void LuaScript::OnConstruct()
    {
        if (!m_OnConstruct) return;

        auto error = m_OnConstruct();
        if (!error.valid())
        {
            sol::error err = error;
            NEPTUNE_CORE_ERROR(err.what())
        }
    }

    void LuaScript::OnAttached()
    {
        if (!m_OnAttached) return;

        auto error = m_OnAttached();
        if (!error.valid())
        {
            sol::error err = error;
            NEPTUNE_CORE_ERROR(err.what())
        }
    }

    void LuaScript::OnTick()
    {
        if (!m_OnTick) return;

        auto error = m_OnTick();
        if (!error.valid())
        {
            sol::error err = error;
            NEPTUNE_CORE_ERROR(err.what())
        }
    }

    void LuaScript::OnDestroy()
    {
        if (!m_OnDestroy) return;

        auto error = m_OnDestroy();
        if (!error.valid())
        {
            sol::error err = error;
            NEPTUNE_CORE_ERROR(err.what())
        }
    }

    void LuaScript::OnDetached()
    {
        if (!m_OnDetached) return;

        auto error = m_OnDetached();
        if (!error.valid())
        {
            sol::error err = error;
            NEPTUNE_CORE_ERROR(err.what())
        }
    }

    void LuaScript::OnEvent(Event& e)
    {
        if (!m_OnEvent) return;

        auto error = m_OnEvent();
        if (!error.valid())
        {
            sol::error err = error;
            NEPTUNE_CORE_ERROR(err.what())
        }
    }

    sol::protected_function LuaScript::GetBindFunction(sol::table& table, uint32_t position, const std::string& name)
    {
        sol::optional<sol::table> bExists = table[position];
        if (!bExists.has_value())
        {
            std::stringstream ss;
            ss << "Lua Method: [ " << name << " ] Not found in Script.";

            NEPTUNE_CORE_WARN(ss.str())
            return nullptr;
        }

        sol::optional<sol::protected_function> function = bExists.value()[name];
        if (!function.has_value())
        {
            std::stringstream ss;
            ss << "Lua Method: [ " << name << " ] Not found in Script.";

            NEPTUNE_CORE_WARN(ss.str())
            return nullptr;
        }

        return function.value();
    }
    
}
