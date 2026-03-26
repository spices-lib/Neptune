"""
@file GCCMakeDependency.py.
@brief The GCCMakeDependency Class Definitions.
@author Spices
"""

from Scripts.BuildSystem.Dependency import Dependency
import shutil


class GCCMakeDependency(Dependency):
    """
    @brief Base class for solution GCC Make dependency.
    """

    def __init__(self):
        """
        @brief Construct function.
        """
        super().__init__("gccmake", ["git"])

        # Set required commands
        self.requiredCommands = {
            "make": "make"
        }

    def _check(self) -> bool:
        """
        @brief Interface of Check whether this dependency is existing.
        @return Returns true if exising.
        """
        make_available = shutil.which(self.requiredCommands["make"]) is not None

        if not make_available:
            print(f"{self.requiredCommands['make']} not found in PATH")

        return make_available

    def _install(self) -> bool:
        """
        @brief Interface of install this dependency.
        @return Returns true if install successfully.
        """
        print("Please install GCC and Make manually:")
        if self.isWindows:
            print("1. Install MinGW-w64 from https://mingw-w64.org/doku.php")
            print("   or use Chocolatey: 'choco install mingw'")
            print("2. Add MinGW's bin directory to your PATH environment variable")
            print("3. Make sure 'gcc.exe' and 'mingw32-make.exe' are available")
        elif self.system == "linux":
            print("Run the following command:")
            print("sudo apt-get install build-essential")
        elif self.system == "darwin":
            print("Install Xcode command line tools:")
            print("xcode-select --install")

        return False
