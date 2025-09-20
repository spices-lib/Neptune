-- @file NeptuneEditor Premake.
-- @brief Defines details of the NeptuneEditor Solution Building.
-- @author Spices.

project "NeptuneEditor"
	kind "ConsoleApp"           -- Use executeable program.
	language "C++"				-- Use C++.
	cppdialect "C++20"			-- Use C++20.
	staticruntime "On"			-- Use Runtime Library: MTD.

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
		'NEPTUNEEDITOR_ASSETS_PATH=std::string("%{wks.location}/NeptuneEditor/assets/")',

		"TRACY_ENABLE",                  -- tracy Feature Enable.
		"TRACY_ON_DEMAND",               -- Used if want profile on demand.
		"TRACY_FIBERS",                  -- Enable fiber thread.
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"%{IncludeDir.NeptuneEngine}",                        -- Engine Source Folder.
		"src",                                                -- UnitTest Source Folder.
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
		"%{IncludeDir.sol2}",                                 -- Library: sol2 Source Folder.
		"%{IncludeDir.Lua}",                                  -- Library: Lua Source Folder.
	}

	-- In Visual Studio, it only works when generated a new solution, remember update solution will not works.
    -- In Rider, it will not work, needs to add environment variables manually in project configurations setting.
	debugenvs 
	{
	}

	-- The Solution Dependency
	links
	{
		"NeptuneEngine",                       -- Dependency: NeptuneEngine
	}

	-- Platform: Windows
	filter "system:windows"
		systemversion "latest"                 -- Use Latest WindowSDK
		editAndContinue "Off"                  -- Use DebugInfoFormat: Zi (Program Database).

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
		systemversion   "latest"              -- Use Latest WindowSDK
		editAndContinue "Off"                 -- Use DebugInfoFormat: Zi (Program Database).

		-- The Solution Additional Include Folder.
		includedirs
		{
			"%{IncludeDir.emscripten}",                           -- Library: emscripten Header Folder.
			"%{IncludeDir.emscripten_glfw}/include",              -- Library: emscripten_glfw Header Folder.
			"%{IncludeDir.emscripten_glfw}/external",             -- Library: emscripten_glfw Header Folder.
			"%{IncludeDir.emdawnwebgpu}",                         -- Library: emdawnwebgpu Header Folder.
		}

		-- Emscripten Specific Solution Macro Definitions.
		defines
		{
			-- Define Platform : Emscripten.
			"NP_PLATFORM_EMSCRIPTEN"
		}

		-- Emscripten Specific Solution Dependency.
		links
		{
			"ImGui_WebGPU",                               -- Dependency: imgui
		}

		-- The Solution link options
		linkoptions
		{
			"--use-port=%{IncludeDir.emscripten_glfw}/port/emscripten-glfw3.py",     -- Dependency: emscripten-glfw
			"--use-port=%{IncludeDir.emdawnwebgpu}/../../../emdawnwebgpu.port.py",   -- Dependency: WebGPU
			"-pthread",                                                              -- Compile emscripten-glfw with pthread
			"-s USE_WEBGL2=1",                                                       -- Dependency: WebGL
	      --"-s USE_WEBGPU=1",                                                       -- This flag is deprecated
	        "--closure=1",                                                           -- Reduce code size
			"-s DISABLE_EXCEPTION_CATCHING",                                         -- Disable Exception catch
			"-s ALLOW_MEMORY_GROWTH",                                                -- Allow Memory growth
			"-s WASM_BIGINT",                                                        -- Enable BigInt in JS
			"-s WASM=1",                                                             -- Output wasm
			"-s STACK_SIZE=4194304",                                                 -- Expand stack size to 4M
			"-s TOTAL_MEMORY=64MB",                                                  -- Wasm total memory to 64M
		    "-s PROXY_TO_PTHREAD",                                                   -- Run in pthread(not main thread)
		    "-s ASYNCIFY=1",                                                         -- Async between Wasm and Js
			"-s PTHREAD_POOL_SIZE=12",                                               -- Js thread size 12
			"-s USE_PTHREADS=1",                                                     -- Use pthread
			"-s EXIT_RUNTIME=1",                                                     -- Allow return in runtime
			"-s SHARED_MEMORY",                                                      -- Shared memory
			"-s OFFSCREENCANVAS_SUPPORT",                                            -- Transform canvas to pthread
			"-s OFFSCREENCANVASES_TO_PTHREAD='nepnep'",                              -- Agent canvas to pthread
			"-o %{cfg.targetdir}/%{prj.name}.js"                                     -- Generate js file
		}

		-- The Solution build options
		buildoptions
		{
			"-pthread"       -- Enable pthread
		}

		-- Configuration: Debug
		filter "configurations:Debug"

			-- The Solution debug link options
			linkoptions
			{
				"-gsource-map",                                              -- Map Source to c++
				"-gseparate-dwarf=%{cfg.targetdir}/%{prj.name}.debug.wasm",  -- Generate debug symbol version wasm
				"--emit-symbol-map",                                         -- Export symbol
			}

	-- Configuration: Debug
	filter "configurations:Debug"

		-- Debug Specific Solution Macro Definitions.
		defines
		{
			"NEPTUNE_DEBUG",                   -- Debug Symbol.
		}

		runtime "Debug"
		symbols "On"

        -- The Solution PostCommands
        postbuildcommands {

            -- Create target directory.
            os.host() == "windows" and '' or 'mkdir -p "%{wks.location}/Nepnep/public/wasm/Debug/"',

            -- Copy js and wasm to Nepnep.
            os.host() == "windows" and 'xcopy /Y /I "%{cfg.targetdir}\\" "%{wks.location}/Nepnep/public/wasm/Debug\\"'
                or 'cp -rf "%{cfg.targetdir}/." "%{wks.location}/Nepnep/public/wasm/Debug/"'
        }

	-- Configuration: Release.
	filter "configurations:Release"

		-- Release Specific Solution Macro Definitions.
		defines
		{
			"NEPTUNE_RELEASE",                 -- Release Symbol.
		}

		runtime "Release"
		optimize "On"

        -- The Solution PostCommands
        postbuildcommands {

            -- Create target directory.
            os.host() == "windows" and '' or 'mkdir -p "%{wks.location}/Nepnep/public/wasm/Release/"',

            -- Copy js and wasm to Nepnep.
            os.host() == "windows" and 'xcopy /Y /I "%{cfg.targetdir}\\" "%{wks.location}/Nepnep/public/wasm/Release\\"'
                or 'cp -rf "%{cfg.targetdir}/." "%{wks.location}/Nepnep/public/wasm/Release/"'
        }