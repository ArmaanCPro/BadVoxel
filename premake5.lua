workspace "BadVoxel"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Engine"
   
    flags
    {
        "MultiProcessorCompile"
    }

   -- Workspace-wide build options for MSVC
   filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }
        systemversion "latest"
        defines { "PL_WINDOWS" }
        toolset "msc"

    filter "system:linux"
        systemversion "latest"
        defines { "PL_LINUX"}
        toolset "gcc"

    filter "system:macosx"
        systemversion "latest"
        defines { "PL_MACOSX"}
        toolset "clang"

-- Directories
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Engine/premake5.lua"

group "Dependencies"
    include "Engine/vendor/glfw/premake5.lua"
    include "Engine/vendor/Glad/premake5.lua"
group ""