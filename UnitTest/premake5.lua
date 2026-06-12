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
	{
		-- UnitTest needs test features directly
		platform.GetComputeFeatures(compiler.GetToolset()),
		platform.GetGraphicsFeatures(),
	}

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
			"--use-port=%{vendor.includes.emscripten_glfw}/port/emscripten-glfw3.py",     -- Dependency: emscripten-glfw
			"--use-port=%{vendor.includes.emdawnwebgpu}/../../emdawnwebgpu.port.py",      -- Dependency: WebGPU
			"-s USE_WEBGL2=1",                                                            -- Dependency: WebGL
	      --"-s USE_WEBGPU=1",                                                            -- This flag is deprecated(use emdawnwebgpu instead of official)
	        "--closure=1",                                                                -- Reduce code size
			"-s DISABLE_EXCEPTION_CATCHING",                                              -- Disable Exception catch
			"-s ALLOW_MEMORY_GROWTH",                                                     -- Allow Memory growth
			"-s WASM_BIGINT",                                                             -- Enable BigInt in JS
			"-s WASM=1",                                                                  -- Output wasm
			"-s STACK_SIZE=4194304",                                                      -- Expand stack size to 4M
			"-s TOTAL_MEMORY=64MB",                                                       -- Wasm total memory to 64M
		    "-s PROXY_TO_PTHREAD",                                                        -- Run in pthread(not main thread)
		    "-s ASYNCIFY=1",                                                              -- Async between Wasm and Js
			"-s PTHREAD_POOL_SIZE=12",                                                    -- Js thread size 12
			"-pthread",                                                                   -- Enable pthread(required in both link and compile)
			"-s USE_PTHREADS=1",                                                          -- Use pthread
			"-s EXIT_RUNTIME=1",                                                          -- Allow return in runtime
			"-s SHARED_MEMORY",                                                           -- Shared memory
			"-s OFFSCREENCANVAS_SUPPORT",                                                 -- Transform canvas to pthread
			"-s OFFSCREENCANVASES_TO_PTHREAD='nepnep'",                                   -- Agent canvas to pthread
			"-o %{cfg.targetdir}/%{prj.name}.js"                                          -- Generate js file
		}

		-- The Solution build options
		buildoptions
		{
			"-pthread",                                                                   -- Enable pthread
			"-matomics",                                                                  -- Enable atomics
    		"-mbulk-memory",                                                              -- Enable bulk-memory
		}

		-- Configuration: Debug
		filter {"system:emscripten", "configurations:Debug"}

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
		
		-- Platform: Emscripten
		filter {"configurations:Debug", "system:emscripten"}

			-- The Solution PostCommands
			postbuildcommands {

				-- Create target directory.
				--os.host() == "windows" and '' or 'mkdir -p "%{wks.location}/Nepnep/public/wasm/Debug/"',

				-- Copy js and wasm to Nepnep.
				--os.host() == "windows" and 'xcopy /Y /I "%{cfg.targetdir}\\" "%{wks.location}/Nepnep/public/wasm/Debug\\"'
				--	or 'cp -rf "%{cfg.targetdir}/." "%{wks.location}/Nepnep/public/wasm/Debug/"'
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

		-- Platform: Emscripten
		filter {"configurations:Release", "system:emscripten"}

			-- The Solution PostCommands
			postbuildcommands {

				-- Create target directory.
				--os.host() == "windows" and '' or 'mkdir -p "%{wks.location}/Nepnep/public/wasm/Release/"',

				-- Copy js and wasm to Nepnep.
				--os.host() == "windows" and 'xcopy /Y /I "%{cfg.targetdir}\\" "%{wks.location}/Nepnep/public/wasm/Release\\"'
				--	or 'cp -rf "%{cfg.targetdir}/." "%{wks.location}/Nepnep/public/wasm/Release/"'
			}
		