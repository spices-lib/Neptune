
#include "Pchheader.h"
/*
#include <sol/sol.hpp>

#include "Core/Log/Log.h"

class LuaBinding
{
    sol::protected_function m_update{sol::lua_nil}, m_render{sol::lua_nil};

    bool LoadMainScript(sol::state& lua)
    {
        try
        {
            auto result = lua.safe_script_file("./assets/Scripts/Lua/main.lua");
        }
        catch (const sol::error& err)
        {
            NEPTUNE_CORE_ERROR(err.what())
            return false;
        }

        sol::table main_lua = lua["main"];
        sol::optional<sol::table> bUpdateExists = main_lua[1];
        if (bUpdateExists == sol::nullopt)
        {
            NEPTUNE_CORE_ERROR("No update function")
        }

        sol::table update_script = main_lua[1];
        sol::function update = update_script["update"];

        sol::optional<sol::table> bRenderExists = main_lua[2];
        if (bRenderExists == sol::nullopt)
        {
            NEPTUNE_CORE_ERROR("No render function")
        }

        sol::table render_script = main_lua[1];
        sol::function render = render_script["render"];
        
        // entity.addComponent<ScriptComponent>();
        
        return true;
    }
    void update()
    {
        // if (!loaded) return;

        auto error = m_update(1, 2, 3);
        if (!error.valid())
        {
            sol::error err = error;
            NEPTUNE_CORE_ERROR(err.what());
        }
    }
    void render()
    {
        // if (!loaded) return;

        auto error = m_render(1, 2, 3);
        if (!error.valid())
        {
            sol::error err = error;
            NEPTUNE_CORE_ERROR(err.what());
        }
    }

    void main1()
    {
        auto lua = std::make_shared<sol::state>();

        if (!lua)
        {
            NEPTUNE_CORE_ERROR("Failed to create lua state")
            return;
        }

        lua->open_libraries(sol::lib::base, sol::lib::math, sol::lib::os, sol::lib::table, sol::lib::io, sol::lib::string);

        if (!addtoConetxt(lua))
        {
            NEPTUNE_CORE_ERROR("Failed to create lua state")
            return;
        }
    }
};
*/
