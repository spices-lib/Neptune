@echo off

REM To build system directory
cd "../BuildSystem"

REM Build with configure
call python SolutionBuilder.py --build_system=premake --platform=windows --toolset=GNU --behave=build-release

PAUSE