-- @file Includes Premake.
-- @brief Defines all Solutions Includes.
-- @author Spices.

-- Includes
IncludeDir                                = {}
IncludeDir["Neptune"]                     = "%{wks.location}/Neptune/src"                                               -- Include: Neptune
IncludeDir["NeptuneShader"]               = "%{wks.location}/Neptune/assets/Shaders/src"                                -- Include: NeptuneShader
IncludeDir["emscripten"]                  = "C:/emsdk/upstream/emscripten/cache/sysroot/include/"                       -- Include: emscripten
IncludeDir["emscripten_glfw"]             = "%{wks.location}/Neptune/vendor/emscripten-glfw/"                           -- Include: emscripten-glfw
IncludeDir["emdawnwebgpu"]                = "%{wks.location}/Neptune/vendor/emdawnwebgpu/webgpu/include/webgpu"         -- Include: emdawnwebgpu
IncludeDir["GLFW"]                        = "%{wks.location}/Neptune/vendor/GLFW/include"                               -- Include: GLFW
IncludeDir["VulkanSDK"]                   = "C:/VulkanSDK/1.4.321.1/Include"                                            -- Include: VulkanSDK
IncludeDir["glm"]                         = "%{IncludeDir.VulkanSDK}"                                                   -- Include: glm
IncludeDir["Glad"]                        = "%{wks.location}/Neptune/vendor/Glad/include"                               -- Include: Glad
IncludeDir["stb_image"]                   = "%{wks.location}/Neptune/vendor/stb_image"                                  -- Include: stb_image
IncludeDir["ImGui"]                       = "%{wks.location}/Neptune/vendor/imgui"                                      -- Include: ImGui
IncludeDir["entt"]                        = "%{wks.location}/Neptune/vendor/entt/include"                               -- Include: entt
IncludeDir["yaml_cpp"]                    = "%{wks.location}/Neptune/vendor/yaml-cpp/include"                           -- Include: yaml_cpp
IncludeDir["rapidyaml"]                   = "%{wks.location}/Neptune/vendor/rapidyaml"                                  -- Include: rapidyaml
IncludeDir["ImPlot"]                      = "%{wks.location}/Neptune/vendor/implot"                                     -- Include: ImPlot
IncludeDir["spdlog"]                      = "%{wks.location}/Neptune/vendor/spdlog/include"                             -- Include: spdlog
IncludeDir["ImGuizmo"]                    = "%{wks.location}/Neptune/vendor/ImGuizmo"                                   -- Include: ImGuizmo
IncludeDir["tracy"]                       = "%{wks.location}/Neptune/vendor/tracy/public"                               -- Include: tracy
IncludeDir["IconFontCppHeaders"]          = "%{wks.location}/Neptune/vendor/IconFontCppHeaders"                         -- Include: IconFontCppHeaders
IncludeDir["shaderc"]                     = "%{wks.location}/Neptune/vendor/shaderc"                                    -- Include: shaderc
IncludeDir["glslang"]                     = "%{IncludeDir.VulkanSDK}/glslang"                                           -- Include: glslang
IncludeDir["googletest"]                  = "%{wks.location}/UnitTest/vendor/googletest/googletest/include"             -- Include: googletest
IncludeDir["googlemock"]                  = "%{wks.location}/UnitTest/vendor/googletest/googlemock/include"             -- Include: googlemock

-- Library Directories Folder
LibraryDir                                = {}
LibraryDir["VulkanSDK"]                   = "%{IncludeDir.VulkanSDK}/../Lib"                                            -- Library Directries: VulkanSDK Folder
LibraryDir["VulkanSDKDLL"]                = "%{IncludeDir.VulkanSDK}/../Bin"                                            -- Library Directries: VulkanSDK dll Folder

-- Library Directories
Library                                   = {}
Library["VulkanSDK"]                      = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"                                      -- Library Directries: VulkanSDK
Library["dxgi"]                           = "dxgi.lib"                                                                  -- Library Directries: dxgi
Library["d3d12"]                          = "d3d12.lib"                                                                 -- Library Directries: d3d12
Library["WinPixEventRuntime"]             = "WinPixEventRuntime.lib"                                                    -- Library Directries: WinPixEventRuntime

Library["shaderc_debug"]                  = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"                               -- Library Directries: shaderc_debug
Library["shaderc_utils_debug"]            = "%{LibraryDir.VulkanSDK}/shaderc_utild.lib"                                 -- Library Directries: shaderc_utils_debug

Library["shaderc_release"]                = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"                                -- Library Directries: shaderc_release
Library["shaderc_utils_release"]          = "%{LibraryDir.VulkanSDK}/shaderc_util.lib"                                  -- Library Directries: shaderc_utils_release


Nugets                                    = {}
Nugets["DirectX12AgilitySDK"]             = "Microsoft.Direct3D.D3D12:1.618.5"                                          -- Nugets package: Direct3D12
Nugets["WinPixEventRuntime"]              = "WinPixEventRuntime:1.0.240308001"                                          -- Nugets package: WinPixEventRuntime