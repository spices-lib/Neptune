-- @file workspace Premake.
-- @brief Defines all Solutions Building.
-- @author Spices.

workspace "Neptune"
	startproject "NeptuneEditor"             -- Start with NeptuneEditor

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

-- Project: NeptuneEngine.
include "NeptuneEngine"

-- Project: NeptuneEditor.
include "NeptuneEditor"

-- Project: NeptuneRuntime.
include "NeptuneRuntime"

-- Project: NeptuneUnitTest.
include "NeptuneUnitTest"

-- Project Dependencies.
group "Dependencies"
if os.target() == "windows" then
	include "NeptuneEngine/vendor/GLFW"                 -- Dependency GLFW.
	include "NeptuneEngine/vendor/Glad"                 -- Dependency GLFW.
end
	include "NeptuneEngine/vendor/imgui"                -- Dependency imgui.
	include "NeptuneEngine/vendor/yaml-cpp"             -- Dependency yaml-cpp.
	include "NeptuneEngine/vendor/implot"               -- Dependency implot.
	include "NeptuneUnitTest/vendor/googletest"         -- Dependency googletest.
group ""