project "ConfettiStudio"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (outputdir .. "/%{prj.name}/intermediates")

	includedirs {
		"%{wks.location}/ConfettiEngine/include",
		"src"
	}
	
	filter "configurations:Debug"
		links {
			"imguid"
		}

	filter "configurations:Release"
		links {
			"imgui"
		}

	filter {}
	
	links {
		"ConfettiEngine",
		"glfw3",
		"Windove"
	}
	
	filter "not options:shared-library"
		filter { "not options:shared-library", "configurations:Debug" }
			links "libglew32d"
		filter { "not options:shared-library", "configurations:Release" }
			links "libglew32"
		filter "not options:shared-library"
		
		filter { "not options:shared-library", "system:linux" }
			links "GL"
		filter { "not options:shared-library", "system:windows" }
			links "opengl32"
		filter "not options:shared-library"
		
		links {

		}
		
		defines {
			"CONFETTIENGINE_STATIC"
		}

	filter {}
	
	defines {
		"WINDOVE_STATIC"
	}
	
	files {
		"src/**.hpp",
		"src/**.cpp"
	}