-- @file Neptune Premake.
-- @brief Defines details of the Neptune Solution Building.
-- @author Spices.

project "Neptune"
	kind "StaticLib"          -- Use Lib as Dependency.
	language "C++"            -- Use C++.
	cppdialect "C++20"        -- Use C++20.
	staticruntime "On"        -- Use Runtime Library: MTD.

	-- Building Output Folder.
	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

	-- Building Object Folder.
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- Enable Multi Processor Compile
	flags { "MultiProcessorCompile" }

	pchheader "Pchheader.h"          -- PreCompiler Header File.
	pchsource "src/Pchheader.cpp"    -- PreCompiler Cpp File.

	-- The Solution Files.
	files
	{
		-- Engine Source Files.
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",

		-- Engine Shader Headers.
		"assets/Shaders/src/Header/**.h",

		-- Library: std_image Files.
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		
		-- Library: glm Files.
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",

		-- Library: ImGuizmo Files.
		"vendor/ImGuizmo/ImGuizmo.cpp",
		"vendor/ImGuizmo/ImGuizmo.h",

		-- Library: tracy Files.
		"vendor/tracy/public/TracyClient.cpp",
		"vendor/tracy/public/tracy/Tracy.hpp",

		-- Library: IconFontCppHeaders Files.
		"vendor/IconFontCppHeaders/**.h",
	}

	-- Macros Definitions
	defines
	{
		-- Define Engine Assets Folder.
		--'NEPTUNE_ASSETS_PATH=std::string("' .. path.translate(os.getcwd(), "/") .. '/assets/")',

		-- Define Engine Logs Folder.
		--'NEPTUNE_CONSOLElOGFILE_PATH=std::string("saved/ConsoleLog/")',

		-- Define Engine Extent Processes Folder.
		--'NEPTUNE_EXTENT_PROCESS_PATH=std::string("' .. path.translate(os.getcwd(), "/") .. '/../vendor/")',
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"src",                                                -- Engine Source Folder.
		"%{IncludeDir.stb_image}",                            -- Library: stb_image Source Folder.
		"%{IncludeDir.glm}",                                  -- Library: glm Source Folder.
		"%{IncludeDir.ImGui}",                                -- Library: ImGui Source Folder.
		"%{IncludeDir.entt}",                                 -- Library: entt Source Folder.
		"%{IncludeDir.yaml_cpp}",                             -- Library: yaml_cpp Source Folder.
		"%{IncludeDir.rapidyaml}",                            -- Library: rapidyaml Source Folder.
		"%{IncludeDir.ImPlot}",                               -- Library: ImPlot Source Folder.
		"%{IncludeDir.spdlog}",                               -- Library: spdlog Source Folder.
		"%{IncludeDir.ImGuizmo}",                             -- Library: ImGuizmo Source Folder.
		"%{IncludeDir.tracy}",                                -- Library: tracy Source Folder.
		"%{IncludeDir.IconFontCppHeaders}",                   -- Library: IconFontCppHeaders Source Folder.
	}

	-- The Solution Dependency
	links
	{
      --"imgui",                              -- Dependency: imgui (Do not known why can not link here as a lib)
		"yaml-cpp",                           -- Dependency: yaml-cpp
		"implot",                             -- Dependency: implot
	}

    -- The Solution build options
    buildoptions
    {
        "-pthread"       -- Enable pthread
    }

	-- Library: std_image is included this solution, do not use PreCompiler Header.
	filter "files:vendor/stb_image/**.cpp"
	flags { "NoPCH" }

	-- Library: ImGuizmo is included this solution, do not use PreCompiler Header.
	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	-- Library: tracy is included this solution, do not use PreCompiler Header.
	filter "files:vendor/tracy/public/**.cpp"
	flags { "NoPCH" }

	-- Platform: Windows
	filter "system:windows"
		systemversion   "latest"              -- Use Lastest WindowSDK

											  -- tracy use __FILE__ in constexpr, but MSVC do not support it by default.
											  -- There are two way to handle with that:
											  -- 1.Use a complex format of __LINE__:
											  --   #define _DBJ_CONCATENATE_(a, b) a ## b
											  --   #define _DBJ_CONCATENATE(a, b)  _DBJ_CONCATENATE_(a, b)
                                              --   #define CONSTEXPR_LINE long(_DBJ_CONCATENATE(__LINE__,U)) 
		editAndContinue "Off"				  -- 2.Use DebugInfoFormat: Zi (Program Database).

		-- Windows Specific Solution Macro Definitions.
		defines
		{
			-- Use winsock2.h instead of winsock.h.
			"WIN32_LEAN_AND_MEAN",

			-- Define Platform : Windows.
			"NP_PLATFORM_WINDOWS"
		}

		-- Windows Specific Solution Dependency.
		links
		{
			"imgui",                              -- Dependency: imgui
		}

	-- Platform: Emscripten
	filter "system:emscripten"
		systemversion   "latest"              -- Use Lastest WindowSDK

											-- tracy use __FILE__ in constexpr, but MSVC do not support it by default.
											-- There are two way to handle with that:
											-- 1.Use a complex format of __LINE__:
											--   #define _DBJ_CONCATENATE_(a, b) a ## b
											--   #define _DBJ_CONCATENATE(a, b)  _DBJ_CONCATENATE_(a, b)
											--   #define CONSTEXPR_LINE long(_DBJ_CONCATENATE(__LINE__,U)) 
		editAndContinue "Off"				  -- 2.Use DebugInfoFormat: Zi (Program Database).

		-- The Solution Additional Include Folder.
		includedirs
		{
			"%{IncludeDir.emscripten}",                           -- Library: emscripten Header Folder.
			"%{IncludeDir.emscripten_glfw}/include",              -- Library: emscripten_glfw Header Folder.
			"%{IncludeDir.emscripten_glfw}/external",             -- Library: emscripten_glfw Header Folder.
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
			"NEPTUNE_DEBUG",                 -- Debug Symbol.
			"TRACY_ENABLE",                  -- tracy Feature Enable.
			"TRACY_ON_DEMAND",               -- Used if want profile on demand.
		}

		runtime "Debug"
		symbols "On"

	-- Configuration: Release.
	filter "configurations:Release"

		-- Release Specific Solution Macro Definitions.
		defines 
		{
			"NEPTUNE_RELEASE",               -- Release Symbol.
			"TRACY_ENABLE",                  -- tracy Feature Enable.
			"TRACY_ON_DEMAND",               -- Used if want profile on demand.
		}

		runtime "Release"
		optimize "On"

	