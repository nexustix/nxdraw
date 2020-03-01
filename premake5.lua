require("mingw64")

workspace "WS_nxpixel"
    configurations { "Debug", "Release" }
    platforms { "l64", "w64"}
    filter { "platforms:l64" }
        system "linux"
        architecture "x64"

    filter { "platforms:w64" }
        system "windows"
        architecture "x64"
        toolset ("mingw64")
        --entrypoint "WinMainCRTStartup"

project "nxpixel"
    location "build/nxpixel/"
    --kind "ConsoleApp"
    --kind "WindowedApp"
    kind "SharedLib"
    language "C"
    --targetdir "bin/%{cfg.buildcfg}"
    targetdir "lib/nxpixel"
    --links { "allegro", "allegro_ttf", "allegro_font", "allegro_color", "allegro_primitives" }
    links { "GL", "glfw", "m"}
    --links { "glfw" }

    --files { "./src/**.h", "./src/**.c" }
    files { "./src/engine/**.h", "./src/engine/**.c" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        --warnings "Extra"
        enablewarnings { "all" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
