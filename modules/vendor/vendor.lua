-- @file dependency.lua.
-- @brief Defines all Solutions Dependencies.
-- @author Spices.

-- Define module
local module = {}

-- Solution Root
local solution_root = _MAIN_SCRIPT_DIR

-- @brief Get Vulkan SDK Path.
--
-- @return Returns Vulkan SDK Path.
local GetVulkanSDKPath = function()
    return "C:/VulkanSDK/1.4.321.1/Include"
end

-- @brief Get Emsdk Path.
--
-- @return Returns Emsdk Path.
local GetEmsdkPath = function()
    return "C:/emsdk"
end

-- @brief Get AdaptiveCpp Path.
--
-- @return Returns AdaptiveCpp Path.
local GetAdaptiveCppPath = function()
    return "C:/AdaptiveCpp"
end

-- Includes
local includes                        = {
    ["Neptune"]                       = solution_root .. "/Neptune/src",                                              -- Include: Neptune
    ["NeptuneShader"]                 = solution_root .. "/Neptune/assets/Shaders/src",                                -- Include: NeptuneShader
    ["emscripten"]                    = GetEmsdkPath() .. "/upstream/emscripten/cache/sysroot/include/",               -- Include: emscripten
    ["emscripten_glfw"]               = solution_root .. "/Neptune/vendor/emscripten-glfw/",                           -- Include: emscripten-glfw
    ["emdawnwebgpu"]                  = solution_root .. "/Neptune/vendor/emdawnwebgpu/webgpu/include",                -- Include: emdawnwebgpu
    ["GLFW"]                          = solution_root .. "/Neptune/vendor/GLFW/include",                               -- Include: GLFW
    ["VulkanSDK"]                     = GetVulkanSDKPath(),                                                            -- Include: VulkanSDK
    ["glm"]                           = GetVulkanSDKPath(),                                                            -- Include: glm
    ["Glad"]                          = solution_root .. "/Neptune/vendor/Glad/include",                               -- Include: Glad
    ["stb_image"]                     = solution_root .. "/Neptune/vendor/stb_image",                                  -- Include: stb_image
    ["ImGui"]                         = solution_root .. "/Neptune/vendor/imgui",                                      -- Include: ImGui
    ["entt"]                          = solution_root .. "/Neptune/vendor/entt/include",                               -- Include: entt
    ["yaml_cpp"]                      = solution_root .. "/Neptune/vendor/yaml-cpp/include",                           -- Include: yaml_cpp
    ["rapidyaml"]                     = solution_root .. "/Neptune/vendor/rapidyaml",                                  -- Include: rapidyaml
    ["ImPlot"]                        = solution_root .. "/Neptune/vendor/implot",                                     -- Include: ImPlot
    ["spdlog"]                        = solution_root .. "/Neptune/vendor/spdlog/include",                             -- Include: spdlog
    ["ImGuizmo"]                      = solution_root .. "/Neptune/vendor/ImGuizmo",                                   -- Include: ImGuizmo
    ["tracy"]                         = solution_root .. "/Neptune/vendor/tracy/public",                               -- Include: tracy
    ["IconFontCppHeaders"]            = solution_root .. "/Neptune/vendor/IconFontCppHeaders",                         -- Include: IconFontCppHeaders
    ["shaderc"]                       = solution_root .. "/Neptune/vendor/shaderc",                                    -- Include: shaderc
    ["glslang"]                       = GetVulkanSDKPath() ..  "/glslang",                                             -- Include: glslang
    ["WinPixEventRuntime"]            = solution_root .. "/packages/WinPixEventRuntime.1.0.240308001/include",         -- Include: WinPixEventRuntime
    ["AdaptiveCpp"]                   = GetAdaptiveCppPath() .. "/include",                                            -- Include: AdaptiveCpp
    ["googletest"]                    = solution_root .. "/UnitTest/vendor/googletest/googletest/include",             -- Include: googletest
    ["googlemock"]                    = solution_root .. "/UnitTest/vendor/googletest/googlemock/include",             -- Include: googlemock
}
module.includes                       = includes

-- Library Directories Folder
local library_dir                      = {
    ["VulkanSDK"]                      = includes.VulkanSDK .. "/../Lib",                                              -- Library Directries: VulkanSDK Folder
    ["VulkanSDKDLL"]                   = includes.VulkanSDK .. "/../Bin",                                              -- Library Directries: VulkanSDK dll Folder
    ["WinPixEventRuntime"]             = includes.WinPixEventRuntime .. "/../bin/x64",                                 -- Library Directries: WinPixEventRuntime Folder
}
module.library_dir                     = library_dir
    
-- Library Directories
module.libraries                       = {
    ["VulkanSDK"]                      = library_dir.VulkanSDK .. "/vulkan-1.lib",                                     -- Library Directries: VulkanSDK
    ["dxgi"]                           = "dxgi.lib",                                                                   -- Library Directries: dxgi
    ["d3d11"]                          = "d3d11.lib",                                                                  -- Library Directries: d3d11
    ["d3d12"]                          = "d3d12.lib",                                                                  -- Library Directries: d3d12
    ["WinPixEventRuntime"]             = library_dir.WinPixEventRuntime .. "/WinPixEventRuntime.lib",                  -- Library Directries: WinPixEventRuntime
    
    ["shaderc_debug"]                  = library_dir.VulkanSDK .. "/shaderc_sharedd.lib",                              -- Library Directries: shaderc_debug
    ["shaderc_utils_debug"]            = library_dir.VulkanSDK .. "/shaderc_utild.lib",                                -- Library Directries: shaderc_utils_debug
    
    ["shaderc_release"]                = library_dir.VulkanSDK .. "/shaderc_shared.lib",                               -- Library Directries: shaderc_release
    ["shaderc_utils_release"]          = library_dir.VulkanSDK .. "/shaderc_util.lib",                                 -- Library Directries: shaderc_utils_release
}

-- Nuget Dependencies
module.nugets                          = {
    ["DirectX12AgilitySDK"]            = "Microsoft.Direct3D.D3D12:1.618.5",                                           -- Nugets package: Direct3D12
    ["WinPixEventRuntime"]             = "WinPixEventRuntime:1.0.240308001",                                           -- Nugets package: WinPixEventRuntime
}

-- Desktop Third Party Projects
module.third_party_projects_desktos   = {
	["GLFW"]                          = solution_root .. "/Neptune/vendor/GLFW",          -- Dependency: GLFW
	["Glad"]                          = solution_root .. "/Neptune/vendor/Glad",          -- Dependency: Glad
	["tracy"]                         = solution_root .. "/Neptune/vendor/tracy",         -- Dependency: tracy
    ["shaderc"]                       = solution_root .. "/Neptune/vendor/shaderc",       -- Dependency: shaderc
}

-- Third Party Projects
module.third_party_projects          = {
	["imgui"]                        = solution_root .. "/Neptune/vendor/imgui",         -- Dependency: imgui
	["yaml-cpp"]                     = solution_root .. "/Neptune/vendor/yaml-cpp",      -- Dependency: yaml-cpp
	["implot"]                       = solution_root .. "/Neptune/vendor/implot",        -- Dependency: implot
    ["googletest"]                   = solution_root .. "/UnitTest/vendor/googletest",   -- Dependency: googletest
}

-- @brief Load Third Party Projects.
module.LoadThirdPartyProjects = function()

    -- Project Dependencies.
    group "Dependencies"
    if os.target() ~= "emscripten" then
        for name, path in pairs(module.third_party_projects_desktos) do
            include(path)
        end
    end
    for name, path in pairs(module.third_party_projects) do
        include(path)
    end
    group ""

end

return module