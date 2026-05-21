newoption {
	trigger = "shared-library",
	description = "Build as a shared library"
}

newoption {
	trigger = "static-crt",
	description = "Build with static crt linkage"
}

workspace "Confetti"
	platforms { "x86", "x64" }
	configurations { "Debug", "Release" }
	
	startproject "ConfettiTest"
	
	filter "platforms:x86"
		architecture "x86"
	
	filter "platforms:x64"
		architecture "x64"
	
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "On"
	
	filter {}
	
	filter "options:static-crt"
		staticruntime "On"
	
	filter "not options:static-crt"
		staticruntime "Off"
	
	filter {}
	
	outputdir = "%{wks.location}/build/%{cfg.system}/%{cfg.platform}/%{cfg.buildcfg}"
	
	includedirs "%{wks.location}/external/include"

	filter "system:linux"
		includedirs {
			"%{wks.location}/external/vcpkg_installed/x64-linux/include",
			"%{wks.location}/external/vcpkg_installed/x64-linux-release/include"
		}

	filter "system:windows"
		includedirs {
			"%{wks.location}/external/vcpkg_installed/x64-windows/include",
			"%{wks.location}/external/vcpkg_installed/x64-windows-static-md/include"
		}

	filter {}
	
	filter "configurations:Debug"
		libdirs "%{wks.location}/external/lib/debug"

		debugenvs "PATH=$(PATH);%{wks.location}/external/bin/debug"

		filter { "configurations:Debug", "system:linux" }
			libdirs {
				"%{wks.location}/external/vcpkg_installed/x64-linux/debug/lib",
				"%{wks.location}/external/vcpkg_installed/x64-linux-release/debug/lib"
			}

			removedebugenvs "PATH=$(PATH);%{wks.location}/external/bin/debug"
			debugenvs "PATH=$(PATH);%{wks.location}/external/bin/debug;%{wks.location}/external/vcpkg_installed/x64-linux/debug/bin"

		filter { "configurations:Debug", "system:windows" }
			libdirs {
				"%{wks.location}/external/vcpkg_installed/x64-windows/debug/lib",
				"%{wks.location}/external/vcpkg_installed/x64-windows-static-md/debug/lib"
			}

			removedebugenvs "PATH=$(PATH);%{wks.location}/external/bin/debug"
			debugenvs "PATH=$(PATH);%{wks.location}/external/bin/debug;%{wks.location}/external/vcpkg_installed/x64-windows/debug/bin"
		
	filter "configurations:Release"
		libdirs "%{wks.location}/external/lib/release"

		debugenvs "PATH=$(PATH);%{wks.location}/external/bin/release;"

		filter { "configurations:Release", "system:linux" }
			libdirs {
				"%{wks.location}/external/vcpkg_installed/x64-linux/lib",
				"%{wks.location}/external/vcpkg_installed/x64-linux-release/lib"
			}

			removedebugenvs "PATH=$(PATH);%{wks.location}/external/bin/release;"
			debugenvs "PATH=$(PATH);%{wks.location}/external/bin/release;%{wks.location}/external/vcpkg_installed/x64-linux/bin"

		filter { "configurations:Release", "system:windows" }
			libdirs {
				"%{wks.location}/external/vcpkg_installed/x64-windows/lib",
				"%{wks.location}/external/vcpkg_installed/x64-windows-static-md/lib"
			}

			removedebugenvs "PATH=$(PATH);%{wks.location}/external/bin/release;"
			debugenvs "PATH=$(PATH);%{wks.location}/external/bin/release;%{wks.location}/external/vcpkg_installed/x64-windows/bin"
		
	filter {}
	
	include "Confetti"
	include "ConfettiTest"