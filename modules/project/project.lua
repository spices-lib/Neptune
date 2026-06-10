-- @file project.lua.
-- @brief Defines all Solutions Projects.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- Projects
module.projects             = {
	["Neptune"]             = solution_root .. "/Neptune",            -- Project: Neptune
	["Editor"]              = solution_root .. "/Editor",             -- Project: Editor
	["Runtime"]             = solution_root .. "/Runtime",            -- Project: Runtime
    ["UnitTest"]            = solution_root .. "/UnitTest",           -- Project: UnitTest
}

-- @brief module Load.
module.Load = function()

    for name, path in pairs(module.projects) do
        include(path)
    end

end

return module