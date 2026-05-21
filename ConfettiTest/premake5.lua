project "ConfettiTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (outputdir .. "/%{prj.name}/intermediates")

	includedirs {
		"%{wks.location}/Confetti/include",
		"src"
	}
	
	links {
		"Confetti",
		"glfw3",
		"Windove"
	}
	
	filter "not options:shared-library"		
		filter { "not options:shared-library", "system:linux" }
			links "GL"
		filter { "not options:shared-library", "system:windows" }
			links "opengl32"
		filter "not options:shared-library"
		
		links {
			"glad"
		}
		
		defines {
			"CONFETTI_STATIC"
		}

	filter {}
	
	defines {
		"WINDOVE_STATIC"
	}
	
	files {
		"src/**.hpp",
		"src/**.cpp"
	}