--对引擎本身进行改动时应该去除所有被注释的内容
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
IncludeDir["stb"] = "Biscuit/vendor/stb"
IncludeDir["Lua54"] = "Biscuit/vendor/Lua54/include"
IncludeDir["sol2"] = "Biscuit/vendor/sol2/sol2-develop/include"
IncludeDir["libdir"] = "Biscuit/vendor-bin"

--include "Biscuit/vendor/GLFW"
--include "Biscuit/vendor/Glad"
--include "Biscuit/vendor/imgui"

project "Biscuit"
	location "Biscuit"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		--"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.Lua54}",
		"%{IncludeDir.sol2}"
	}


	libdirs
	{
		"%{IncludeDir.libdir}"
	}
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"lua54.lib"
	}
	
	postbuildcommands
	{
		"echo Copying DLL to: %{wks.location}bin\\" .. outputdir .. "\\Sandbox\\",
		"if not exist \"%{wks.location}bin\\" .. outputdir .. "\\Sandbox\" mkdir \"%{wks.location}bin\\" .. outputdir .. "\\Sandbox\"",
		"copy /Y \"%{cfg.buildtarget.directory}\\%{cfg.buildtarget.name}\" \"%{wks.location}bin\\" .. outputdir .. "\\Sandbox\\\""
	}


	filter "system:windows"
		systemversion "10.0"

		defines
		{
			"BC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		symbols "on"
		runtime "Debug"

	filter "configurations:Release"
		defines "BC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BC_DIST"
		runtime "Release"
		optimize "on"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

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
		"Biscuit/vendor/imgui",
		"%{IncludeDir.glm}",		
		"%{IncludeDir.Lua54}",
		"%{IncludeDir.sol2}"
	}
	links
	{
		"Biscuit"
	}

	filter "system:windows"
		systemversion "10.0"

		defines
		{
			"BC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
	
	filter "configurations:Debug"
		defines "BC_DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "BC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BC_DIST"
		runtime "Release"
		optimize "on"

project "BiscuitPresetter"
	location "BiscuitPresetter"
	kind "ConsoleApp"
	language "C"

	targetdir ("BPbin/" .. outputdir .. "/%{prj.name}")
	objdir ("BPbin/int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.c"
	}

	filter "system:windows"
		systemversion "10.0"

		defines
		{
			"BC_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "BC_DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "BC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BC_DIST"
		runtime "Release"
		optimize "on"