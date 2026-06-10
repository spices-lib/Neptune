-- @file dependency.lua.
-- @brief Defines all Solutions Dependencies.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- desktop Dependencies
module.desktop                  = {
	["GLFW"]                    = solution_root .. "/Neptune/vendor/GLFW",          -- Dependency: GLFW
	["Glad"]                    = solution_root .. "/Neptune/vendor/Glad",          -- Dependency: Glad
	["tracy"]                   = solution_root .. "/Neptune/vendor/tracy",         -- Dependency: tracy
    ["shaderc"]                 = solution_root .. "/Neptune/vendor/shaderc",       -- Dependency: shaderc
}

-- common Dependencies
module.common                   = {
	["imgui"]                   = solution_root .. "/Neptune/vendor/imgui",         -- Dependency: imgui
	["yaml-cpp"]                = solution_root .. "/Neptune/vendor/yaml-cpp",      -- Dependency: yaml-cpp
	["implot"]                  = solution_root .. "/Neptune/vendor/implot",        -- Dependency: implot
    ["googletest"]              = solution_root .. "/UnitTest/vendor/googletest",   -- Dependency: googletest
}

-- @brief module Load.
module.Load = function()

    -- Project Dependencies.
    group "Dependencies"
    if os.target() ~= "emscripten" then
        for name, path in pairs(module.desktop) do
            include(path)
        end
    end
    for name, path in pairs(module.common) do
        include(path)
    end
    group ""

end

return module