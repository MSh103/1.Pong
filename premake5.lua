workspace "Pong"
    architecture "x64"
    configurations { "Debug", "Release" }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Application"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    location "App"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "App/source/**.h",
        "App/source/**.cpp",
        "resources/pong.ico",
        "resources/pong.rc"
    }

    includedirs
    {
        "Thirdparty/raylib/include/"
    }

    links
    {
        "Thirdparty/raylib/lib/raylib.lib",

        "winmm",
        "gdi32",
        "opengl32",
        "shell32",
        "user32",
        "kernel32"
    }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        targetname "Pong"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"