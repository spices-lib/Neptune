-- @file common.lua.
-- @brief Defines all Solutions Common Includes.
-- @author Spices.

-- Define module
local module = {}

-- Includes
module.includes                           = {
	Neptune                               = "%{wks.location}/Neptune/src",                                               -- Include: Neptune
	NeptuneShader                         = "%{wks.location}/Neptune/assets/Shaders/src",                                -- Include: NeptuneShader
	glm                                   = "%{IncludeDir.VulkanSDK}",                                                   -- Include: glm
	stb_image                             = "%{wks.location}/Neptune/vendor/stb_image",                                  -- Include: stb_image
	ImGui                                 = "%{wks.location}/Neptune/vendor/imgui",                                      -- Include: ImGui
	entt                                  = "%{wks.location}/Neptune/vendor/entt/include",                               -- Include: entt
	yaml_cpp                              = "%{wks.location}/Neptune/vendor/yaml-cpp/include",                           -- Include: yaml_cpp
	rapidyaml                             = "%{wks.location}/Neptune/vendor/rapidyaml",                                  -- Include: rapidyaml
	ImPlot                                = "%{wks.location}/Neptune/vendor/implot",                                     -- Include: ImPlot
	spdlog                                = "%{wks.location}/Neptune/vendor/spdlog/include",                             -- Include: spdlog
	ImGuizmo                              = "%{wks.location}/Neptune/vendor/ImGuizmo",                                   -- Include: ImGuizmo
	IconFontCppHeaders                    = "%{wks.location}/Neptune/vendor/IconFontCppHeaders",                         -- Include: IconFontCppHeaders
  --googletest                            = "%{wks.location}/UnitTest/vendor/googletest/googletest/include",             -- Include: googletest
  --googlemock                            = "%{wks.location}/UnitTest/vendor/googletest/googlemock/include",             -- Include: googlemock
}

-- Library Directories Folder
module.library_dir                        = {}

-- Library Directories
module.librarys                           = {}

-- @brief Get Includes List.
-- 
-- @return Returns Includes List.
module.GetIncludes = function()
	local list = {}
    for name, path in pairs(module.includes) do
        table.insert(list, path)
    end
	return list
end

-- @brief Get librarys List.
-- 
-- @return Returns librarys List.
module.Getlibrarys = function()
	local list = {}
    for name, path in pairs(module.librarys) do
        table.insert(list, path)
    end
	return list
end

return module