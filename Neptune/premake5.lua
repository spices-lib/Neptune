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
	multiprocessorcompile "On"

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

		-- Library: ImGuizmo Files.
		"vendor/ImGuizmo/ImGuizmo.cpp",
		"vendor/ImGuizmo/ImGuizmo.h",

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

		"TRACY_ENABLE",                  -- tracy Feature Enable.
		"TRACY_ON_DEMAND",               -- Used if want profile on demand.
		"TRACY_FIBERS",                  -- Enable fiber thread.
		"TRACY_IMPORT",                  -- Multi dll.
	}

	-- The Solution Additional Include Folder.
	includedirs
	{
		"src",                                                     -- Neptune Source Folder.
		"%{vendor.includes.NeptuneShader}",                        -- Neptune Shader Source Folder.
		"%{vendor.includes.glm}",                                  -- Library: glm Source Folder.
		"%{vendor.includes.stb_image}",                            -- Library: stb_image Source Folder.
		"%{vendor.includes.ImGui}",                                -- Library: ImGui Source Folder.
		"%{vendor.includes.entt}",                                 -- Library: entt Source Folder.
		"%{vendor.includes.yaml_cpp}",                             -- Library: yaml_cpp Source Folder.
		"%{vendor.includes.rapidyaml}",                            -- Library: rapidyaml Source Folder.
		"%{vendor.includes.ImPlot}",                               -- Library: ImPlot Source Folder.
		"%{vendor.includes.spdlog}",                               -- Library: spdlog Source Folder.
		"%{vendor.includes.ImGuizmo}",                             -- Library: ImGuizmo Source Folder.
		"%{vendor.includes.tracy}",                                -- Library: tracy Source Folder.
		"%{vendor.includes.IconFontCppHeaders}",                   -- Library: IconFontCppHeaders Source Folder.
	}

	-- The Solution Dependency
	links
	{
      --"imgui",                              -- Dependency: imgui (Do not known why can not link here as a lib)
		"yaml-cpp",                           -- Dependency: yaml-cpp
		"implot",                             -- Dependency: implot
	}

	-- Library: std_image is included this solution, do not use PreCompiler Header.
	filter "files:vendor/stb_image/**.cpp"
		enablepch "Off"

	-- Library: ImGuizmo is included this solution, do not use PreCompiler Header.
	filter "files:vendor/ImGuizmo/**.cpp"
		enablepch "Off"

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

		-- The Solution Additional Include Folder.
		includedirs
		{
            "%{vendor.includes.shaderc}",                              -- Library: shaderc Source Folder.
            "%{vendor.includes.shaderc}/libshaderc/include",           -- Library: shaderc libshaderc Source Folder.
            "%{vendor.includes.shaderc}/libshaderc_util/include",      -- Library: shaderc libshaderc_util Source Folder.
            "%{vendor.includes.glslang}",                              -- Library: glslang Source Folder.
			"%{vendor.includes.GLFW}",                                 -- Library: GLFW Source Folder.
			"%{vendor.includes.VulkanSDK}",                            -- Library: VulkanSDK Source Folder.
			"%{vendor.includes.Glad}",                                 -- Library: Glad Source Folder.
			"%{vendor.includes.WinPixEventRuntime}",                   -- Library: WinPixEventRuntime Source Folder.
			"%{vendor.includes.AdaptiveCpp}",                          -- Library: AdaptiveCpp Source Folder.
		}

		-- Windows Specific Solution Macro Definitions.
		defines
		{
			-- Use winsock2.h instead of winsock.h.
			"WIN32_LEAN_AND_MEAN",

			-- Use M_PI Macro.
			"_USE_MATH_DEFINES",

			-- NO MIN MAX Macro
			"NOMINMAX",
			
			-- Define Platform : Windows.
			"NP_PLATFORM_WINDOWS"
		}

		-- Windows nuget packages.
		nuget
		{
			"%{vendor.nugets.DirectX12AgilitySDK}",      -- Dependency: Direct3D12
			"%{vendor.nugets.WinPixEventRuntime}",       -- Dependency: WinPixEventRuntime
		}

		-- Windows Specific Solution Dependency.
		links
		{
			"%{vendor.libraries.VulkanSDK}",                           -- Dependency: VulkanSDK
			"%{vendor.libraries.dxgi}",                                -- Dependency: dxgi
			"%{vendor.libraries.d3d11}",                               -- Dependency: d3d11
			"%{vendor.libraries.d3d12}",                               -- Dependency: d3d12
			"%{vendor.libraries.WinPixEventRuntime}",                  -- Dependency: WinPixEventRuntime
			
			"ImGui_Vulkan",                                            -- Dependency: imgui
			"ImGui_OpenGL",                                            -- Dependency: imgui
			"ImGui_Direct3D11",                                        -- Dependency: imgui
			"ImGui_Direct3D12",                                        -- Dependency: imgui
			"GLFW",                                                    -- Dependency: GLFW
			"Glad",                                                    -- Dependency: Glad
			"tracy",                                                   -- Dependency: tracy
			"shaderc",                                                 -- Dependency：shaderc 
		}

		-- The Solution build options
		buildoptions 
		{ 
			"/utf-8",                             -- Using utf-8 encode
		}
    
        -- Configuration: Debug
        filter {"system:windows", "configurations:Debug"}

            -- Debug Specific Solution Dependency
            links
            {
                "%{vendor.libraries.shaderc_debug}",               -- Dependency: shaderc_debug
                "%{vendor.libraries.shaderc_utils_debug}",         -- Dependency: shaderc_utils_debug
            }
        
        -- Configuration: Release
        filter {"system:windows", "configurations:Release"}

            -- Release Specific Solution Dependency
            links
            {
                "%{vendor.libraries.shaderc_release}",             -- Dependency: shaderc_release
                "%{vendor.libraries.shaderc_utils_release}",       -- Dependency: shaderc_utils_release
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
		editAndContinue "Off"				-- 2.Use DebugInfoFormat: Zi (Program Database).

		-- The Solution Additional Include Folder.
		includedirs
		{
			"%{vendor.includes.emscripten}",                           -- Library: emscripten Header Folder.
			"%{vendor.includes.emscripten_glfw}/include",              -- Library: emscripten_glfw Header Folder.
			"%{vendor.includes.emscripten_glfw}/external",             -- Library: emscripten_glfw Header Folder.
			"%{vendor.includes.emdawnwebgpu}",                         -- Library: emdawnwebgpu Header Folder.
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

		-- The Solution build options
		buildoptions
		{
			"-pthread"       -- Enable pthread
		}

		-- The Solution make settings
		makesettings 
		{
            "LINKCMD = $(file > $(OBJDIR)objects.rsp,$(OBJECTS)) emar rcs $(TARGET) @$(OBJDIR)objects.rsp"   -- Enable response file
        }

	-- Configuration: Debug
	filter "configurations:Debug"

		-- Debug Specific Solution Macro Definitions.
		defines 
		{
			"NEPTUNE_DEBUG",                 -- Debug Symbol.
		}

		-- Debug Specific Solution Dependency
		links
		{}

		runtime "Debug"
		symbols "On"
		
	-- Configuration: Release.
	filter "configurations:Release"

		-- Release Specific Solution Macro Definitions.
		defines 
		{
			"NEPTUNE_RELEASE",               -- Release Symbol.
		}

		-- Release Specific Solution Dependency
		links
		{}

		runtime "Release"
		optimize "On"
