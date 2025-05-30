"""
@file EmsdkDependency.py.
@brief The EmsdkDependency Class Definitions.
@author Spices
"""

from Scripts.BuildSystem.Dependency import Dependency
import os
from pathlib import Path
import subprocess

"""
@brief EMSDK search paths.
"""
searchPaths = [
    Path.home() / "emsdk",
    Path.home() / ".emsdk",
    Path.home() / "dev" / "emsdk",
    Path.home() / "Documents" / "emsdk",
    Path.home() / "workspace" / "emsdk",
    Path("/usr/local/emsdk"),
    Path("/opt/emsdk"),
    Path("C:\\emsdk"),
    Path("D:\\emsdk"),
]


class EmsdkDependency(Dependency):
    """
    @brief Base class for solution dependency.
    """

    def __init__(self):
        """
        @brief Construct function.
        """
        super().__init__("emsdk", ["git"])

    def _check(self) -> bool:
        """
        @brief Interface of Check whether this dependency is existing.
        @return Returns true if exising.
        """
        # 1. Check EMSDK environment variable
        if "EMSDK" in os.environ:
            return True

        # 2. Search common locations
        for path in searchPaths:
            emscripten_path = path / "upstream" / "emscripten"
            if emscripten_path.exists():
                os.environ["PATH"] = f"{emscripten_path}{os.pathsep}{os.environ.get('PATH', '')}"
                os.environ["EMSDK"] = str(path)
                return True

        return False

    def _install(self) -> bool:
        """
        @brief Interface of install this dependency.
        @return Returns true if install successfully.
        """
        install_dir = Path.home() / "emsdk"

        print(f"Installing Emscripten SDK to {install_dir}")
        install_dir.mkdir(parents=True, exist_ok=True)

        try:
            # Clone emsdk repository
            subprocess.run(["git", "clone", "https://github.com/emscripten-core/emsdk.git", str(install_dir)],
                           check=True)

            # Setup emsdk
            os.chdir(install_dir)
            subprocess.run(["./emsdk" if not self.isWindows else "emsdk.bat", "install", "latest"],
                           shell=not self.isWindows, check=True)
            subprocess.run(["./emsdk" if not self.isWindows else "emsdk.bat", "activate", "latest"],
                           shell=not self.isWindows, check=True)

            emscripten_path = install_dir / "upstream" / "emscripten"
            os.environ["PATH"] = f"{emscripten_path}{os.pathsep}{os.environ.get('PATH', '')}"
            os.environ["EMSDK"] = str(install_dir)

        except subprocess.CalledProcessError as e:
            print(f"Failed to install emsdk: {e}")
            return False
