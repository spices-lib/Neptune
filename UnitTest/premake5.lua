-- @file UnitTest Premake.
-- @brief Defines details of the UnitTest Solution Building.
-- @author Spices.

project "UnitTest"
	kind "ConsoleApp"           -- Use executeable program.
	language "C++"			    -- Use C++.
	cppdialect "C++20"		    -- Use C++20.
	staticruntime "On"		    -- Use Runtime Linrary: MTD.

	-- Building Output Folder.
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	-- Building Object Folder.
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- Enable Multi Processor Compile
	multiprocessorcompile "On"

	-- The Solution Files.
	files
	{
		-- Game Source Files.
		"src/**.h",
		"src/**.cpp",
	}

	-- Macros Definitions
	defines
	{}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"%{vendor.includes.Neptune}",                              -- Neptune Source Folder.
		"%{vendor.includes.googletest}",			               -- Library: googletest Source Folder.
		"%{vendor.includes.googlemock}",			               -- Library: googlemock Source Folder.
		"src",                                                     -- UnitTest Source Folder.
		"%{vendor.includes.glm}",                                  -- Library: glm Source Folder.
		"%{vendor.includes.entt}",                                 -- Library: entt Source Folder.
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
		"googlemock",                          -- Dependency: googlemock
	}

	-- Platform: Windows
	filter "system:windows"
		systemversion "latest"                 -- Use Lastest WindowSDK
		editAndContinue "Off"				   -- Use DebugInfoFormat: Zi (Program Database).
		
		-- The Solution Additional Include Folder.
		includedirs
		{}

		-- Windows Specific Solution Macro Definitions.
		defines
		{
			-- Use winsock2.h instead of winsock.h.
			"WIN32_LEAN_AND_MEAN",

			-- Define Platform : Windows.
			"NP_PLATFORM_WINDOWS"
		}

		-- The Solution build options
		buildoptions 
		{ 
			"/utf-8",                             -- Using utf-8 encode
		}

	-- Platform: Emscripten
	filter "system:emscripten"
		systemversion   "latest"              -- Use Lastest WindowSDK
		editAndContinue "Off"                 -- Use DebugInfoFormat: Zi (Program Database).

		-- The Solution Additional Include Folder.
		includedirs
		{
			"%{vendor.includes.emscripten}",                           -- Library: emscripten Header Folder.
			"%{vendor.includes.emscripten_glfw}/include",              -- Library: emscripten_glfw Header Folder.
			"%{vendor.includes.emscripten_glfw}/external",             -- Library: emscripten_glfw Header Folder.
		}

		-- Emscripten Specific Solution Macro Definitions.
		defines
		{
			-- Define Platform : Emscripten.
			"NP_PLATFORM_EMSCRIPTEN"
		}

		-- Emscripten Specific Solution Dependency.
		links
		{}

	-- Configuration: Debug
	filter "configurations:Debug"

		-- Debug Specific Solution Macro Definitions.
		defines
		{
			"NEPTUNE_DEBUG",                   -- Debug Symbol.
		}

		runtime "Debug"
		symbols "On"
		
	-- Configuration: Release.
	filter "configurations:Release"

		-- Release Specific Solution Macro Definitions.
		defines
		{
			"NEPTUNE_RELEASE",                 -- Release Symbol.
		}

		runtime "Release"
		optimize "On"
		