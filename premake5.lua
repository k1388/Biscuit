workspace "Biscuit"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Biscuit"
	location "Biscuit"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
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
		}

	filter "configurations:Debug"
		defines "BC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BC_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "BC_DIST"
		optimize "On"
	
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
		"Biscuit/src"
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
			"BC_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "BC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BC_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "BC_DIST"
		optimize "On"
