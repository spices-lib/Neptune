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
		-- Define Game Assets Folder.
		'SANDBOX_ASSETS_PATH=std::string("%{wks.location}/SandBox/assets/")',

		-- Define Engine Use WebGPU API for Rendering, though we may support multiple Rendering API.
		"RENDERAPI_WEBGPU",

		-- Define Platform : Windows.
		"PLATFORM_WINDOWS"
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"%{wks.location}/Neptune/src",                        -- Engine Source Folder.
		"src",                                                -- SandBox Source Folder.
		"%{IncludeDir.emscripten}",                           -- Library: emscripten Header Folder.
		"%{IncludeDir.emscripten_glfw}/include",              -- Library: emscripten_glfw Header Folder.
		"%{IncludeDir.emscripten_glfw}/external",             -- Library: emscripten_glfw Header Folder.
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

	-- In Visual Studio, it only works when generated a new solution, remember update solution will not works.
    -- In Rider, it will not work, needs to add environment variables manually in project configurations setting.
	debugenvs 
	{  
	}

	-- The Solution Dependency
	links
	{
	    "imgui",                               -- Dependency: imgui
		"Neptune",                             -- Dependency: Neptune
	}

	linkoptions
	{
		"--use-port=contrib.glfw3",             -- Dependency: emscripten-glfw
        "-s USE_WEBGPU=1",                      -- Dependency: webgpu
        "-s ALLOW_MEMORY_GROWTH",               -- Allow Memory growth
        "-s WASM_BIGINT",                       -- Enable BigInt in JS
        "-s WASM=1"                             -- Output wasm
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
			"NEPTUNE_DEBUG",                   -- Debug Symbol.
			"TRACY_ENABLE",                    -- tracy Feature Enable.
			"TRACY_ON_DEMAND",                 -- Used if want profile on demand.
		}

		runtime "Debug"
		symbols "On"

	-- Configuration: Release.
	filter "configurations:Release"

		-- Release Specific Solution Macro Definitions.
		defines
		{
			"NEPTUNE_RELEASE",                 -- Release Symbol.
			"TRACY_ENABLE",                    -- tracy Feature Enable.
			"TRACY_ON_DEMAND",                 -- Used if want profile on demand.
		}

		runtime "Release"
		optimize "On"