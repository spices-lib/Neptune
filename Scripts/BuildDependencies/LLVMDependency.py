"""
@file LLVMDependency.py.
@brief The LLVMDependency Class Definitions.
@author Spices
"""

from Scripts.BuildSystem.Dependency import Dependency
import shutil

class LLVMDependency(Dependency):
    """
    @brief Base class for solution LLVM Clang dependency.
    """

    def __init__(self):
        """
        @brief Construct function.
        """
        super().__init__("LLVM", ["git"])

        # Set required commands
        self.requiredCommands = {
            "clang": "clang",
            "clangxx": "clang++",
            "lld": "lld",
            "llvmar": "llvm-ar",
            "llvmranlib": "llvm-ranlib"
        }

        # Additional commands for Windows
        if self.isWindows:
            self.requiredCommands["clang"] = "clang.exe"
            self.requiredCommands["clangxx"] = "clang++.exe"
            self.requiredCommands["lld"] = "lld.exe"
            self.requiredCommands["llvmranlib"] = "llvm-ranlib.exe"

    def _check(self) -> bool:
        """
        @brief Interface of Check whether this dependency is existing.
        @return Returns true if exising.
        """
        missing_tools = []
        
        for name, cmd in self.requiredCommands.items():
            if shutil.which(cmd) is None:
                missing_tools.append(cmd)
                print(f"{cmd} not found in PATH")

        if missing_tools:
            print(f"\nMissing LLVM tools: {', '.join(missing_tools)}")
            return False

        # Optional: Check clang version
        try:
            import subprocess
            result = subprocess.run(
                [self.requiredCommands["clang"], "--version"],
                capture_output=True,
                text=True,
                timeout=5
            )
            if result.returncode == 0:
                version_line = result.stdout.split('\n')[0]
                print(f"Found: {version_line}")
        except:
            pass

        return True

    def _install(self) -> bool:
        """
        @brief Interface of install this dependency.
        @return Returns true if install successfully.
        """
        print("Please install LLVM/Clang manually:")
        if self.isWindows:
            print("Option 1 - Install via Chocolatey:")
            print("  choco install llvm")
            print("Option 2 - Download installer from:")
            print("  https://github.com/llvm/llvm-project/releases")
            print("Option 3 - Install via MSYS2:")
            print("  pacman -S mingw-w64-ucrt-x86_64-clang")
            print("\nAfter installation:")
            print("  Add LLVM's bin directory (e.g., C:\\Program Files\\LLVM\\bin) to PATH")
            
        elif self.system == "linux":
            print("Ubuntu/Debian (20.04+):")
            print("  wget https://apt.llvm.org/llvm.sh")
            print("  chmod +x llvm.sh")
            print("  sudo ./llvm.sh 18")
            print("  sudo apt-get install clang-18 lld-18 libc++-18-dev libc++abi-18-dev")
            print("\nOr install via package manager:")
            print("  sudo apt-get install clang lld libc++-dev libc++abi-dev")
            print("\nFor other distributions:")
            print("  Fedora: sudo dnf install clang lld")
            print("  Arch: sudo pacman -S clang lld")
            
        elif self.system == "darwin":
            print("Option 1 - Install via Homebrew:")
            print("  brew install llvm")
            print("  echo 'export PATH=\"/usr/local/opt/llvm/bin:$PATH\"' >> ~/.zshrc")
            print("\nOption 2 - Use Xcode Command Line Tools:")
            print("  xcode-select --install")
            print("  (Note: Xcode provides an older version of Clang)")
            print("\nOption 3 - Download from:")
            print("  https://github.com/llvm/llvm-project/releases")

        return False
