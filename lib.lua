-- @file Includes Premake.
-- @brief Defines all Solutions Includes.
-- @author Spices.

-- Includes
IncludeDir                                = {}
IncludeDir["emscripten"]                  = "C:/emsdk/upstream/emscripten/cache/sysroot/include/"                             -- Include: emscripten
IncludeDir["emscripten_glfw"]             = "%{wks.location}/Neptune/vendor/emscripten-glfw/"                                 -- Include: emscripten-glfw
IncludeDir["stb_image"]                   = "%{wks.location}/Neptune/vendor/stb_image"                                        -- Include: stb_image
IncludeDir["glm"]                         = "%{wks.location}/Neptune/vendor/glm"                                              -- Include: glm
IncludeDir["ImGui"]                       = "%{wks.location}/Neptune/vendor/imgui"                                            -- Include: ImGui
IncludeDir["entt"]                        = "%{wks.location}/Neptune/vendor/entt/include"                                     -- Include: entt
IncludeDir["yaml_cpp"]                    = "%{wks.location}/Neptune/vendor/yaml-cpp/include"                                 -- Include: yaml_cpp
IncludeDir["rapidyaml"]                   = "%{wks.location}/Neptune/vendor/rapidyaml"                                        -- Include: rapidyaml
IncludeDir["ImPlot"]                      = "%{wks.location}/Neptune/vendor/implot"                                           -- Include: ImPlot
IncludeDir["spdlog"]                      = "%{wks.location}/Neptune/vendor/spdlog/include"                                   -- Include: spdlog
IncludeDir["ImGuizmo"]                    = "%{wks.location}/Neptune/vendor/ImGuizmo"                                         -- Include: ImGuizmo
IncludeDir["tracy"]                       = "%{wks.location}/Neptune/vendor/tracy/public"                                     -- Include: tracy
IncludeDir["IconFontCppHeaders"]          = "%{wks.location}/Neptune/vendor/IconFontCppHeaders"                               -- Include: IconFontCppHeaders
IncludeDir["googletest"]                  = "%{wks.location}/Test/vendor/googletest/googletest/include"                       -- Include: googletest
IncludeDir["googlemock"]                  = "%{wks.location}/Test/vendor/googletest/googlemock/include"                       -- Include: googlemock

-- Library Directries Folder
LibraryDir                                = {}

-- Library Directries
Library                                   = {}