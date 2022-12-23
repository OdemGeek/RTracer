-- premake5.lua
workspace "RTracer"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "RTracer"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "RTracer"