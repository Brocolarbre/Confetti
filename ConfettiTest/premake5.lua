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
		"Windove",
		"glad",
		"LineWeaver"
	}

	filter "system:linux"
		links "GL"
	filter "system:windows"
		links "opengl32"
	filter {}
	
	filter "options:shared-library"
		disablewarnings {
			"4251",
			"4275"
		}
	
	filter "not options:shared-library"
		defines {
			"CONFETTI_STATIC"
		}

	filter {}
	
	defines {
		"LINEWEAVER_STATIC",
		"WINDOVE_STATIC"
	}
	
	files {
		"src/**.hpp",
		"src/**.cpp"
	}