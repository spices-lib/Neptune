-- @file Includes Premake.
-- @brief Defines all Solutions Includes.
-- @author Spices.

-- Includes
IncludeDir                                = {}
IncludeDir["emscripten"]                  = "C:/emsdk/upstream/emscripten/cache/sysroot/include/"                        -- Include: emscripten
IncludeDir["emscripten_glfw"]             = "%{wks.location}/Neptune/vendor/emscripten-glfw/"                            -- Include: emscripten-glfw