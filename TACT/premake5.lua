project "TACT"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files
   {
      "src/**.h",
      "src/**.cpp",
      "../imnodes/imnodes.cpp",
      "../imnodes/imnodes.h",
      "../imnodes/imnodes_internal.h",
   }

   includedirs
   {
      -- Vendors
      "../Walnut/vendor/imgui",
      "../Walnut/vendor/glfw/include",

      -- Walnut
      "../Walnut/Walnut/src",

      -- Nodes
      "../imnodes",

      -- Json serialiser
      "../json/single_include",

      -- ImGUI backends
      "%{IncludeDir.VulkanSDK}",
      "%{IncludeDir.glm}",

      -- Local source includes
      "src",
   }

    links
    {
        "Walnut",
    }

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS" }

   filter "configurations:Debug"
      defines { "WL_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "WL_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      kind "WindowedApp"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"