project "Confetti"
	language "C++"
	cppdialect "C++17"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (outputdir .. "/%{prj.name}/intermediates")
	
	filter "options:shared-library"
		kind "SharedLib"
		
		filter { "options:shared-library", "configurations:Debug" }
			postbuildcommands "{COPY} %{cfg.buildtarget.relpath} %{wks.location}/external/bin/debug"
		filter { "options:shared-library", "configurations:Release" }
			postbuildcommands "{COPY} %{cfg.buildtarget.relpath} %{wks.location}/external/bin/release"
		filter "options:shared-library"
				
		filter { "options:shared-library", "system:linux" }
			links "GL"
		filter { "options:shared-library", "system:windows" }
			links "opengl32"
		filter "options:shared-library"
		
		links {
			"glad",
			"LineWeaver"
		}
		
		defines	{
			"CONFETTI_BUILD"
		}
		
		disablewarnings {
			"4251"
		}
		
	filter "not options:shared-library"
		kind "StaticLib"
		
		defines	{
			"CONFETTI_STATIC"
		}
		
	filter {}

	includedirs {
		"include"
	}
	
	defines {
		"LINEWEAVER_STATIC"
	}

	files {
		"include/**.hpp",
		"src/**.cpp"
	}