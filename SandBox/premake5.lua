-- @file SandBox Premake.
-- @brief Defines details of the SandBox Solution Building.
-- @author Spices.

project "SandBox"
	kind "ConsoleApp"           -- Use exe.
	language "C++"				-- Use C++.
	cppdialect "C++17"			-- Use C++17.
	staticruntime "On"			-- Use Runtime Linrary: MTD.

	-- Building Output Folder.
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	-- Building Object Folder.
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- Enable Multi Processor Compile
	flags { "MultiProcessorCompile" }

	-- The Solution Files.
	files
	{
		-- SandBox Source Files.
		"src/**.h",
		"src/**.cpp",
	}

	-- Macros Definitions
	defines
	{
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"%{wks.location}/Neptune/src",                        -- Engine Source Folder.
		"src",                                                -- SandBox Source Folder.
		"%{IncludeDir.emscripten}",                           -- Library: emscripten Header Folder.
	}

	-- In Visual Studio, it only works when generated a new solution, remember update solution will not works.
    -- In Rider, it will not work, needs to add environment variables manually in project configurations setting.
	debugenvs 
	{  
	}

	-- The Solution Dependency
	links
	{
		"Neptune",                             -- Dependency: Neptune
	}

	-- The Solution PostCommands
	postbuildcommands {

		-- Copy wasm to Nepnep
		'xcopy /Y /I "%{cfg.targetdir}\\**.wasm" "..\\Nepnep\\static\\wasm\"'
	}

	-- Platform: Windows
	filter "system:windows"
		systemversion "latest"                 -- Use Lastest WindowSDK
		editAndContinue "Off"                  -- Use DebugInfoFormat: Zi (Program Database).

		-- Windows Specific Solution Macro Definitions.
		defines
		{
			-- Use winsock2.h instead of winsock.h.
			"WIN32_LEAN_AND_MEAN"
		}

	-- Configuration: Debug
	filter "configurations:Debug"

		-- Debug Specific Solution Macro Definitions.
		defines
		{
		}

		runtime "Debug"
		symbols "On"

	-- Configuration: Release.
	filter "configurations:Release"

		-- Release Specific Solution Macro Definitions.
		defines
		{
		}

		runtime "Release"
		optimize "On"