"""
@file PremakeBuildSystem.py.
@brief The PremakeBuildSystem Class Definitions.
@author Spices
"""
import sys

from BuildSystem import BuildSystem
from Scripts.BuildDependencies.PremakeDependency import PremakeDependency
from Scripts.BuildDependencies.EmsdkDependency import EmsdkDependency
from Scripts.BuildDependencies.GCCMakeDependency import GCCMakeDependency

if sys.platform == 'win32':
    from Scripts.BuildDependencies.MSVCDependency import MSVCDependency
    from Scripts.BuildDependencies.TracyDependency import TracyDependency

from pathlib import Path
import os
import subprocess


class PremakeBuildSystem(BuildSystem):
    """
    @brief Premake-based build system implementation
    """

    def __init__(self, solution_root: Path, platform: str = "emscripten", toolset: str = "GNU"):
        """
        @brief Construct function.
        @param[in] solution_root Solution root folder.
        @param[in] platform
        @param[in] toolset
        """
        super().__init__(solution_root, platform, toolset)
        self.dependencyGraph.add_node(PremakeDependency())

        if self.platform == "emscripten":
            self.dependencyGraph.add_node(EmsdkDependency())

        if self.platform == "windows":
            self.dependencyGraph.add_node(TracyDependency())

        if self.toolset == "GNU":
            self.dependencyGraph.add_node(GCCMakeDependency())
        elif self.toolset == "vs" and sys.platform == 'win32':
            self.dependencyGraph.add_node(MSVCDependency())

    def _generate(self) -> bool:
        """
        @brief Internal Generate build files using premake.
        @return Returns true in succeed.
        """
        premake = self.dependencyGraph.find("premake")
        premake_path = premake.path()

        print(f"\nGenerating solution ({'Emscripten' if self.platform == 'emscripten' else 'Native'})...")
        print(f"Solution root: {self.solutionDirectory}")

        os.chdir(self.solutionDirectory)

        args = [str(premake_path)]
        if self.platform == "emscripten":
            args.append("--os=emscripten")
        elif self.platform == "windows":
            args.append("--os=windows")
        elif self.platform == "linux":
            args.append("--os=linux")
        else:
            print("Not support platform.")
            sys.exit(1)

        if self.toolset == "GNU":
            args.append("gmake")
        elif self.toolset == "vs":
            args.append("vs2022")
        else:
            print("Not support toolset.")
            sys.exit(1)

        print("Running:", " ".join(args))
        try:
            subprocess.run(args, check=True)
            print("Solution generated successfully")
            return True
        except subprocess.CalledProcessError:
            print("Error: premake5 failed!")
            return False

    def _build(self, config: str = "debug") -> bool:
        """
        @brief Build the project using make.
        @return Returns true in succeed.
        """
        print(f"\nBuilding {config} configuration...")
        os.chdir(self.solutionDirectory)

        if self.toolset == "GNU":
            return self.build_gmake(config)
        elif self.toolset == "vs":
            print("Not support toolset.")
            sys.exit(1)

    def _clean(self) -> bool:
        """
        @brief Clean build artifacts.
        @return Returns true in succeed.
        """
        os.chdir(self.solutionDirectory)
        make_cmd = "make"

        try:
            subprocess.run([make_cmd, "clean"], check=True)
            print("Clean successfully")
            return True
        except subprocess.CalledProcessError:
            print("Error: clean failed!")
            return False

    def build_gmake(self, config: str) -> bool:
        """
        @brief build with gmake.
        @param[in] config
        @return Returns true in succeed.
        """
        make_cmd = "make"
        args = [make_cmd, f"config={config}"]

        print("Running:", " ".join(args))
        try:
            subprocess.run(args, check=True)
            print(f"{config} build completed successfully")
            return True
        except subprocess.CalledProcessError:
            print(f"Error: {config} build failed!")
            return False