workspace "Biscuit"
	architecture "x64"
	startproject "Sandbox"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Biscuit/vendor/GLFW/include"
IncludeDir["Glad"] = "Biscuit/vendor/Glad/include"
IncludeDir["ImGui"] = "Biscuit/vendor/imgui"

include "Biscuit/vendor/GLFW"
include "Biscuit/vendor/Glad"
include "Biscuit/vendor/imgui"

project "Biscuit"
	location "Biscuit"
	kind "SharedLib"
	language "C++"

	pchheader "pch.h"
	pchsource "Biscuit/src/pch.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	postbuildcommands
	{
		"echo Copying DLL to: %{wks.location}bin\\" .. outputdir .. "\\Sandbox\\",
		"if not exist \"%{wks.location}bin\\" .. outputdir .. "\\Sandbox\" mkdir \"%{wks.location}bin\\" .. outputdir .. "\\Sandbox\"",
		"copy /Y \"%{cfg.buildtarget.directory}\\%{cfg.buildtarget.name}\" \"%{wks.location}bin\\" .. outputdir .. "\\Sandbox\\\""
	}


	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "10.0"

		defines
		{
			"BC_PLATFORM_WINDOWS",
			"BC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "BC_RELEASE"
		optimize "On"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "BC_DIST"
		optimize "On"
		buildoptions "/MD"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"Biscuit/vendor/spdlog/include",
		"Biscuit/vendor/GLFW/include",
		"Biscuit/src",
		"Biscuit/vendor/Glad/include",
		"Biscuit/vendor/imgui"
	}
	links
	{
		"Biscuit"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "10.0"

		defines
		{
			"BC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
	
	filter "configurations:Debug"
		defines "BC_DEBUG"
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "BC_RELEASE"
		optimize "On"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "BC_DIST"
		optimize "On"
		buildoptions "/MD"

