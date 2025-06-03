#!/bin/bash

# To build system directory
cd "..//BuildSystem"

# Build with configure
python3 SolutionBuilder.py --build_system=premake --platform=emscripten --toolset=GNU --behave=build-release

# Optional: Add a pause equivalent (Linux doesn't have PAUSE, so we can use read)
read -p "Press [Enter] to continue..."