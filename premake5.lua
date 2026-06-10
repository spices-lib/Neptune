-- @file workspace Premake.
-- @brief Defines all Solutions Building.
-- @author Spices.

local compiler   = require "compiler"
local project    = require "project"
local dependency = require "dependency"

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
		architecture "wasm64"                 -- Architecture wasm64

	-- Windows App
	filter "system:windows"
		architecture "x64"                    -- Architecture x64
		toolset "clang"                       -- Use clang

	compiler.Initialize()

-- Building Output Folder.
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Libraries of this Solution.
include "lib.lua"

project.Load()

dependency.Load()