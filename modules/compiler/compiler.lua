-- @file compiler.lua
-- @brief Defines all Solutions Toolset Env.
-- @author Spices.

-- Define module
local module = {}

module.toolset = ""

-- @brief Set Clang.
module.SetClang = function()
	module.toolset = "clang"
end

-- @brief Get Toolset.
--
-- @return Returns Toolset.
module.GetToolset = function()
	return module.toolset
end

-- @brief module Initialize.
module.Initialize = function()

    -- Configuration: MSVC
	filter { "toolset:msc" }
        buildoptions { "/wd4838" }                 -- Disable Warning: 4838

		-- MSVC Specific Solution Macro Definitions.
		defines 
		{
			"NP_COMPILER_MSVC",                    -- Compiler: MSVC.
		}

	-- Configuration: GCC
    filter { "toolset:gcc" }
        buildoptions { "-Wno-narrowing" }          -- Disable Warning: 4838

		-- GCC Specific Solution Macro Definitions.
		defines 
		{
			"NP_COMPILER_GCC",                     -- Compiler: GCC.
		}

	-- Configuration: Clang
	filter { "toolset:clang" }
        buildoptions { "-Wno-narrowing" }          -- Disable Warning: 4838

		-- Clang Specific Solution Macro Definitions.
		defines 
		{
			"NP_COMPILER_CLANG",                   -- Compiler: Clang.
		}

end

return module