-- @file workspace Premake.
-- @brief Defines all Solutions Building.
-- @author Spices.

workspace "Neptune"
	startproject "Editor"              -- Start with Editor

	-- Configuration: Debug and Release.
	configurations
	{
		"Debug",
		"Release",
	}

	-- Web App
	filter "system:emscripten"
		architecture "wasm64"

	-- Windows App
	filter "system:windows"
		architecture "x64"

-- Building Output Folder.
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Libraries of this Solution.
include "lib.lua"

-- Project: Neptune.
include "Neptune"

-- Project: Editor.
include "Editor"

-- Project: Runtime.
include "Runtime"

-- Project: UnitTest.
include "UnitTest"

-- Project Dependencies.
group "Dependencies"
if os.target() == "windows" then
	include "Neptune/vendor/GLFW"                 -- Dependency GLFW.
	include "Neptune/vendor/Glad"                 -- Dependency Glad.
	include "Neptune/vendor/tracy"                -- Dependency tracy.
end
	include "Neptune/vendor/imgui"                -- Dependency imgui.
	include "Neptune/vendor/yaml-cpp"             -- Dependency yaml-cpp.
	include "Neptune/vendor/implot"               -- Dependency implot.
	include "Neptune/vendor/shaderc"              -- Dependency shaderc.
	include "UnitTest/vendor/googletest"          -- Dependency googletest.
group ""