newaction {
	trigger = "clean",
	description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("Build/Bin")

        print("Removing intermediate binaries")
        os.rmdir("Build/Intermediate")

        print("Removing project files")
        os.rmdir("Build/Generated")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}

function IncludeThirdParty()
	includedirs { 
		"ThirdParty/lua542/include",
		"ThirdParty/raylib/include" 
	}
	--includedirs "ThirdParty/imgui"
end

function LinkThirdParty()
	libdirs "ThirdParty/raylib/"
	
	links {
        "raylib.lib",
        "winmm.lib"
    }
end

function RunThirdParty()
	group "ThirdParty"
	--include "ThirdParty/imgui"
end

workspace "Workspace"
	architecture "x86_64"
	platforms { "Win64" }
	configurations { "Debug", "Release" }
	startproject "Yet Another Zombie Game"
	
	-- General Settings
		
	cppdialect "C++20"
	
	-- Global Platform
	
	flags { "MultiProcessorCompile" }
	
	filter { "platforms:Win64" }
		defines { "WIN32", "_WIN32", "_CRT_SECURE_NO_WARNINGS" }
		systemversion "latest"
	
	-- Global Configurations
	
	filter { "configurations:Debug" }
		defines { "DEBUG", "_DEBUG" }
		symbols "On"
		optimize "Off"

	filter { "configurations:Release" }
		defines { "NDEBUG", "_UNICODE", "UNICODE" }
		symbols "Off"
		optimize "Speed"
	
project "Yet Another Zombie Game"
	language "C++"
	kind "ConsoleApp"
	
	location "Build/Generated"
	buildlog "Build/Logs/GameBuildLog.log"
	basedir "../../"
	objdir "Build/Intermediate/%{cfg.platform}_%{cfg.buildcfg}"
	targetdir "Build/Bin/%{cfg.platform}_%{cfg.buildcfg}"
	
	targetname "YAZG"
	
    pchheader("pch.h")
    pchsource("App/Source/Core/pch.cpp")

	includedirs { "App/Source" }
	
	-- General Build
		
	filter {}
		--flags { "NoPCH" }
		--clr "Off"
		--rtti "Off"
		--characterset "Unicode"
		staticruntime "Off"
		warnings "Default"
						
		-- Extra third party defines
		defines {
			--"IMGUI_DEFINE_MATH_OPERATORS",
		}
		
	-- Specific Build
		
	filter { "platforms:Win64" }
		system "Windows"
	
	postbuildcommands {
		"{COPYFILE} %{wks.location}ThirdParty/lua542/lua54.dll %{wks.location}Build/Bin/%{cfg.platform}_%{cfg.buildcfg}/",
		"{COPYFILE} %{wks.location}ThirdParty/raylib/raylib.dll %{wks.location}Build/Bin/%{cfg.platform}_%{cfg.buildcfg}/"
	}		

	-- Configurations
		
	filter { "configurations:Debug" }
		symbols "On"
		optimize "Off"
		omitframepointer "Off"
		exceptionhandling "On"

	filter { "configurations:Release" }
		flags { "LinkTimeOptimization", "NoRuntimeChecks" }
		symbols "Off"
		optimize "Speed"  -- /O2 instead of /Ox on MSVS with "Full".
		omitframepointer "On"
		exceptionhandling "Off"     

	-- General Files
		
	filter {}
        files { "App/Config/*.h", "App/Config/*.cpp" }
		files { "App/Source/Asset/*.h", "App/Source/Asset/*.cpp" }
		files { "App/Source/Core/*.h", "App/Source/Core/*.cpp" }
		files { "App/Source/Editor/*.h", "App/Source/Editor/*.cpp" }
		files { "App/Source/Entities/*.h", "App/Source/Entities/*.cpp" }
		files { "App/Source/Gui/*.h", "App/Source/Gui/*.cpp" }
		files { "App/Source/States/*.h", "App/Source/States/*.cpp" }
		files { "App/Source/Utility/*.h", "App/Source/Utility/*.cpp" }
		
	filter {}
	
	-- Shaders
	
	files { "App/Shaders/**.hlsl", "App/Shaders/**.hlsli" }
	
	-- Disable shader compiling as a build step, we compile shaders at runtime.
	filter "files:**.hlsl"
		buildaction "None"
		
	filter {}
	
	-- Third Party Files
	
	IncludeThirdParty()
	
	-- General Links
	
	libdirs {}
	
	links { }
	
	-- Specific Links
	
	filter { "platforms:Win64" }
		links { "Synchronization" }
						
	filter {}
		
	-- Third Party Links
	
	LinkThirdParty()
	
	-- Run Third Party Build Scripts
	
	RunThirdParty()