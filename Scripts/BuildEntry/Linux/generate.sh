#!/bin/bash

# Exit on error
set -e

# To build system directory
cd "../../BuildSystem"

# Build with configure
python3 SolutionBuilder.py --build_system=premake --platform=linux --toolset=GNU --behave=generate

# Optional: Add a pause equivalent (Linux doesn't have PAUSE, so we can use read)
# read -p "Press [Enter] to continue..."