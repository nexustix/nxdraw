require("mingw64")

workspace "WS_nxdraw"
    configurations { "Debug", "Release" }
    platforms { "l64", "w64", "larm64"}
    filter { "platforms:l64" }
        system "linux"
        architecture "x64"

    filter { "platforms:larm64" }
        system "linux"
        architecture "ARM"

    filter { "platforms:w64" }
        system "windows"
        architecture "x64"
        toolset ("mingw64")
        --entrypoint "WinMainCRTStartup"

project "nxdraw"
    language "C"
    kind "SharedLib"
    targetdir "lib/%{cfg.shortname}/libnxdraw/"

    libdirs { "./trd/lib" }
    includedirs { "./trd/include" }

    --links { "GL", "glfw", "m"}
    

    files { "./src/_nxdraw/**.h", "./src/_nxdraw/**.c"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        --warnings "Extra"
        enablewarnings { "all" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"


    filter { "platforms:l64" }
        links { "GL", "glfw", }--"m"}

    filter { "platforms:w64" }
        links { "opengl32", "glfw3", }--"m"}
    

project "nxdrawdemo"
    language "C"
    kind "WindowedApp"
    targetdir "bin/%{cfg.shortname}/nxdrawdemo/"

    libdirs { "./lib/%{cfg.shortname}/libnxdraw/" }
    includedirs { "./src/_nxdraw/", "./trd/include" }

    links { "nxdraw" }

    files { "./src/nxdrawdemo/**.h", "./src/nxdrawdemo/**.c" }
    --links { "GL", "glfw", "m"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        enablewarnings { "all" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:l64" }
        links { "GL", "glfw", }--"m"}

    filter { "platforms:w64" }
        links { "opengl32", "glfw3", }--"m"}
