-- @file workspace Premake.
-- @brief Defines all Solutions Building.
-- @author Spices.

workspace "Neptune"
	architecture "wasm64"              -- Platform wasm64
	startproject "SandBox"             -- Start with SandBox

	-- Configuration: Debug and Release.
	configurations
	{
		"Debug",
		"Release",
	}

-- Building Output Folder.
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Libraries of this Solution.
include "lib.lua"

-- Project: Neptune.
include "Neptune"

-- Project: SandBox.
include "SandBox"

-- Project: Test.
include "Test"

-- Project Dependencies.
group "Dependencies"
	include "Neptune/vendor/imgui"           -- Dependency imgui.
	include "Neptune/vendor/yaml-cpp"        -- Dependency yaml-cpp.
	include "Neptune/vendor/implot"          -- Dependency implot.
	include "Test/vendor/googletest"         -- Dependency googletest.
group ""