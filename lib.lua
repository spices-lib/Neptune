-- @file Includes Premake.
-- @brief Defines all Solutions Includes.
-- @author Spices.

-- Includes
IncludeDir                                = {}
IncludeDir["NeptuneEngine"]               = "%{wks.location}/NeptuneEngine/src"                                               -- Include: NeptuneEngine
IncludeDir["emscripten"]                  = "C:/emsdk/upstream/emscripten/cache/sysroot/include/"                             -- Include: emscripten
IncludeDir["emscripten_glfw"]             = "%{wks.location}/NeptuneEngine/vendor/emscripten-glfw/"                           -- Include: emscripten-glfw
IncludeDir["emdawnwebgpu"]                = "%{wks.location}/NeptuneEngine/vendor/emdawnwebgpu/webgpu/include/webgpu"         -- Include: emdawnwebgpu
IncludeDir["GLFW"]                        = "%{wks.location}/NeptuneEngine/vendor/GLFW/include"                               -- Include: GLFW
IncludeDir["VulkanSDK"]                   = "C:/VulkanSDK/1.3.296.0/Include"                                                  -- Include: VulkanSDK
IncludeDir["VulkanMemoryAllocator"]       = "%{wks.location}/NeptuneEngine/vendor/VulkanMemoryAllocator/include"              -- Include: VulkanMemoryAllocator
IncludeDir["Glad"]                        = "%{wks.location}/NeptuneEngine/vendor/Glad/include"                               -- Include: Glad
IncludeDir["stb_image"]                   = "%{wks.location}/NeptuneEngine/vendor/stb_image"                                  -- Include: stb_image
IncludeDir["glm"]                         = "%{wks.location}/NeptuneEngine/vendor/glm"                                        -- Include: glm
IncludeDir["ImGui"]                       = "%{wks.location}/NeptuneEngine/vendor/imgui"                                      -- Include: ImGui
IncludeDir["entt"]                        = "%{wks.location}/NeptuneEngine/vendor/entt/include"                               -- Include: entt
IncludeDir["yaml_cpp"]                    = "%{wks.location}/NeptuneEngine/vendor/yaml-cpp/include"                           -- Include: yaml_cpp
IncludeDir["rapidyaml"]                   = "%{wks.location}/NeptuneEngine/vendor/rapidyaml"                                  -- Include: rapidyaml
IncludeDir["ImPlot"]                      = "%{wks.location}/NeptuneEngine/vendor/implot"                                     -- Include: ImPlot
IncludeDir["spdlog"]                      = "%{wks.location}/NeptuneEngine/vendor/spdlog/include"                             -- Include: spdlog
IncludeDir["ImGuizmo"]                    = "%{wks.location}/NeptuneEngine/vendor/ImGuizmo"                                   -- Include: ImGuizmo
IncludeDir["tracy"]                       = "%{wks.location}/NeptuneEngine/vendor/tracy/public"                               -- Include: tracy
IncludeDir["IconFontCppHeaders"]          = "%{wks.location}/NeptuneEngine/vendor/IconFontCppHeaders"                         -- Include: IconFontCppHeaders
IncludeDir["sol2"]                        = "%{wks.location}/NeptuneEngine/vendor/sol2/include"                               -- Include: sol2
IncludeDir["Lua"]                         = "%{wks.location}/NeptuneEngine/vendor/Lua/src"                                    -- Include: Lua
IncludeDir["googletest"]                  = "%{wks.location}/NeptuneUnitTest/vendor/googletest/googletest/include"            -- Include: googletest
IncludeDir["googlemock"]                  = "%{wks.location}/NeptuneUnitTest/vendor/googletest/googlemock/include"            -- Include: googlemock

-- Library Directories Folder
LibraryDir                                = {}
LibraryDir["VulkanSDK"]                   = "C:/VulkanSDK/1.3.296.0/Lib"                                                      -- Library Directries: VulkanSDK Folder
LibraryDir["VulkanSDKDLL"]                = "%{LibraryDir.VulkanSDK}/../Bin"                                                  -- Library Directries: VulkanSDK dll Folder

-- Library Directories
Library                                   = {}
Library["VulkanSDK"]                      = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"                                            -- Library Directries: VulkanSDK