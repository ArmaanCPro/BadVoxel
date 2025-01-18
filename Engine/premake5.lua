project "Engine"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "shaders/**.glsl", "shaders/**.jpg", "shaders/**.png",
      "vendor/stb_image/stb_image.h"
   }

   includedirs
   {
      "src",

      "vendor/glfw/include",
      "vendor/Glad/include",
      "vendor/stb_image"
   }

   defines
   {
      "GLFW_INCLUDE_NONE",
      "STB_IMAGE_IMPLEMENTATION"
   }

   links
   {
      "glfw",
      "Glad"
   }

   flags { "NoPCH" }

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS", "NOMINMAX" }
      buildoptions { "/utf-8" }

   filter "system:linux"
      links { "dl", "pthread" }

   filter "configurations:Debug"
      defines { "BV_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "BV_RELEASE" }
      runtime "Release"
      optimize "On"