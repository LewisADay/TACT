-- premake5.lua
workspace "TACT"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "TACT"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Walnut/WalnutExternal.lua"
include "TACT"