"""
@file SolutionBuilder.py.
@brief The SolutionBuilder Class Definitions.
@author Spices
"""

from typing import Optional
import sys
import argparse
from pathlib import Path

# Get current Folder
currentFolder = Path(__file__).parent
# Get Solution Folder
solutionFolder = currentFolder.parent.parent

# Add to python path
sys.path.insert(0, str(solutionFolder))

from BuildSystem import BuildSystem
from PremakeBuildSystem import PremakeBuildSystem


class SolutionBuilder:
    """
    @brief High-level build system interface
    """

    def __init__(self):
        self.buildSystem: Optional[BuildSystem] = None

    def initialize_build_system(self, system: BuildSystem):
        """
        @brief Initialize the appropriate build system.
        @param[in] system BuildSystem
        """
        self.buildSystem = system

    def generate_solution(self) -> bool:
        """
        @brief Generate solution files.
        @return Returns true in succeed.
        """
        if self.buildSystem is None:
            print("Build System is None, Please call initialize_build_system first.")
            return False
        return self.buildSystem.generate()

    def build_solution(self, config: str = "debug") -> bool:
        """
        @brief Build the project.
        @param[in] config
        @return Returns true in succeed.
        """
        if self.buildSystem is None:
            print("Build System is None, Please call initialize_build_system first.")
            return False
        return self.buildSystem.build(config)

    def clean(self) -> bool:
        """
        @brief Clean build artifacts
        @return Returns true in succeed.
        """
        if self.buildSystem is None:
            print("Build System is None, Noting to clean.")
            return False
        return self.buildSystem.clean()

    def show_help(self) -> None:
        """Display help information"""
        print("""Build System Helper

Usage:
    python SolutionBuilder.py action [arguments]

action:
    --build_system      Which Build System in use, one of:
        premake       
        
    --platform          Generate files for a different operating system; one of:
        windows         .exe
        linux           Not support yet
        macos           Not support yet
        emscripten      .wasm .js
        
    --toolset        
        GNU             Generate GNU makefiles for POSIX, MinGW, and Cygwin
        vs              Generate Visual Studio project files
    
    --behave
        generate        Generate solution files
        build-debug     Build solution in debug
        build-release   Build solution in release
        clean           Clean solution build files

    --show_help          Show this help message
""")


def main() -> None:
    """
    @brief Build Solution with configuration.
    """
    parser = argparse.ArgumentParser(description='SolutionBuilder Args')
    parser.add_argument('--build_system', type=str, required=False)
    parser.add_argument('--platform', type=str, required=False)
    parser.add_argument('--toolset', type=str, required=False)
    parser.add_argument('--behave', type=str, required=False)
    parser.add_argument('--show_help', type=bool, required=False)
    args = parser.parse_args()

    builder = SolutionBuilder()

    if args.show_help:
        builder.show_help()
        sys.exit(1)

    if args.build_system == "premake":
        builder.initialize_build_system(PremakeBuildSystem(solutionFolder, args.platform, args.toolset))
    else:
        print("Not supported build system.")
        sys.exit(1)

    success = False

    if args.behave == "generate":
        success = builder.generate_solution()
    elif args.behave == "build-debug":
        success = builder.generate_solution()
        if success:
            success = builder.build_solution("debug")
    elif args.behave == "build-release":
        success = builder.generate_solution()
        if success:
            success = builder.build_solution("release")
    elif args.behave == "clean":
        success = builder.clean()
    else:
        print("Error: Unknown behave")
        sys.exit(1)

    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()