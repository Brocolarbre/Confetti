project "ConfettiEngine"
	language "C++"
	cppdialect "C++20"

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
			"glad"
		}
		
		defines	{
			"CONFETTIENGINE_EXPORT"
		}
		
	filter "not options:shared-library"
		kind "StaticLib"
		
		defines	{
			"CONFETTIENGINE_STATIC"
		}
		
	filter {}

	includedirs {
		"include"
	}
	
	defines {

	}

	files {
		"include/**.hpp",
		"src/**.cpp"
	}