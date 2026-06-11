-- @file workspace Premake.
-- @brief Defines all Solutions Building.
-- @author Spices.

local project  = require "project"
compiler       = require "compiler"
vendor         = require "vendor"
platform       = require "platform"

workspace "Neptune"
	startproject "Editor"              -- Start with Editor

	-- Configuration: Debug and Release.
	configurations
	{
		"Debug",
		"Release",
	}

	compiler.SetClang()
	compiler.Initialize()

	-- Web App
	filter "system:emscripten"
		architecture "wasm64"                 -- Architecture wasm64

	-- Windows App
	filter "system:windows"
		architecture "x64"                    -- Architecture x64
		toolset(compiler.GetToolset())        -- Toolset: Clang

-- Building Output Folder.
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project.Load()

vendor.LoadThirdPartyProjects()