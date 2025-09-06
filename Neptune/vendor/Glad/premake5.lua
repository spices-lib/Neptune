project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "On"
    systemversion "latest"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }
    
    includedirs
    {
        "%{IncludeDir.Glad}",                            -- Library: Glad Source Folder.
    }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"