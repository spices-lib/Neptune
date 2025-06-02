"""
@file GitDependency.py.
@brief The GitDependency Class Definitions.
@author Spices
"""

from Scripts.BuildSystem.Dependency import Dependency
import os
import subprocess
import shutil
import urllib.request
import tempfile

"""
@brief Git download url.
"""
gitURL = {
    "windows": "https://github.com/git-for-windows/git/releases/download/v2.43.0.windows.1/Git-2.43.0-64-bit.exe",
    "darwin": None,
    "linux": None  # Usually available via package manager
}

class GitDependency(Dependency):
    """
    @brief Base class for solution GCC Make dependency.
    """

    def __init__(self):
        """
        @brief Construct function.
        """
        super().__init__("git", None)

        # Set the expected executable name based on platform
        self.gitExecutable = "git.exe" if self.isWindows else "git"

    def _check(self) -> bool:
        """
        @brief Interface of Check whether this dependency is existing.
        @return Returns true if exising.
        """
        if shutil.which(self.gitExecutable) is None:
            print("Git not found in PATH")
            return False

            # Verify Git version
        try:
            result = subprocess.run([self.gitExecutable, "--version"],
                                    capture_output=True, text=True)
            if result.returncode != 0:
                print("Git found but not working correctly")
                return False

            print(f"Found Git version: {result.stdout.strip()}")
            return True
        except Exception as e:
            print(f"Error checking Git: {e}")
            return False

    def _install(self) -> bool:
        """
        @brief Interface of install this dependency.
        @return Returns true if install successfully.
        """
        print(f"Attempting to install Git for {self.system}...")

        if self.system == "windows":
            return self._install_windows()
        elif self.system == "darwin":
            return self._install_macos()
        elif self.system == "linux":
            return self._install_linux()
        else:
            print(f"Unsupported system for Git auto-install: {self.system}")
            return False

    def _install_windows(self) -> bool:
        """
        @brief Install Git on Windows.
        @return Returns True if installation succeeds.
        """
        try:
            # Download Git installer
            url = gitURL["windows"]
            print(f"Downloading Git installer from {url}")

            temp_dir = tempfile.gettempdir()
            installer_path = os.path.join(temp_dir, "Git-Installer.exe")

            urllib.request.urlretrieve(url, installer_path)

            # Run the installer silently
            print("Running Git installer (this may take a few minutes)...")
            result = subprocess.run(
                [installer_path, "/VERYSILENT", "/NORESTART", "/NOCANCEL", "/SP-", "/CLOSEAPPLICATIONS",
                 "/RESTARTAPPLICATIONS"],
                stdout=subprocess.PIPE, stderr=subprocess.PIPE)

            # Clean up
            os.remove(installer_path)

            if result.returncode != 0:
                print("Git installation failed")
                return False

            # Refresh PATH
            self._refresh_path()

            return self._check()

        except Exception as e:
            print(f"Failed to install Git: {e}")
            return False

    def _install_macos(self) -> bool:
        """
        @brief Install Git on macOS.
        @return Returns True if installation succeeds.
        """
        try:
            # Try Xcode command line tools
            if subprocess.run(["xcode-select", "--install"],
                              stdout=subprocess.DEVNULL,
                              stderr=subprocess.DEVNULL).returncode == 0:
                return True

            # Try Homebrew if available
            if shutil.which("brew"):
                return subprocess.run(["brew", "install", "git"],
                                      stdout=subprocess.DEVNULL,
                                      stderr=subprocess.DEVNULL).returncode == 0
            return False
        except Exception:
            return False

    def _install_linux(self) -> bool:
        """
        @brief Install Git on Linux.
        @return Returns True if installation succeeds.
        """
        try:
            # Try common package managers
            if shutil.which("apt-get"):
                return subprocess.run(
                    ["sudo", "apt-get", "install", "-y", "git"],
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL
                ).returncode == 0
            elif shutil.which("dnf"):
                return subprocess.run(
                    ["sudo", "dnf", "install", "-y", "git"],
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL
                ).returncode == 0
            elif shutil.which("yum"):
                return subprocess.run(
                    ["sudo", "yum", "install", "-y", "git"],
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL
                ).returncode == 0
            elif shutil.which("pacman"):
                return subprocess.run(
                    ["sudo", "pacman", "-S", "--noconfirm", "git"],
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL
                ).returncode == 0
            return False
        except Exception:
            return False

    def _add_git_to_path(self):
        """
        @brief Add Git to system PATH on Windows.
        """
        if not self.isWindows:
            return

        try:
            # Default Git install location
            git_path = r"C:\Program Files\Git\cmd"

            # Get current PATH
            path = os.environ.get("PATH", "")

            # Add Git path if not already present
            if git_path not in path:
                os.environ["PATH"] = f"{git_path};{path}"

                # Update system environment
                import winreg
                with winreg.OpenKey(
                        winreg.HKEY_LOCAL_MACHINE,
                        r"SYSTEM\CurrentControlSet\Control\Session Manager\Environment",
                        0, winreg.KEY_ALL_ACCESS
                ) as key:
                    winreg.SetValueEx(key, "PATH", 0, winreg.REG_EXPAND_SZ, os.environ["PATH"])

                # Notify system about the change
                import ctypes
                ctypes.windll.user32.SendMessageTimeoutW(
                    0xFFFF, 0x1A, 0, "Environment", 0x0002, 5000, None)
        except Exception:
            pass

    def _refresh_path(self):
        """
        @brief Refresh PATH environment variable (Windows specific).
        """
        if self.isWindows:
            try:
                import ctypes
                from ctypes import wintypes

                HWND_BROADCAST = 0xFFFF
                WM_SETTINGCHANGE = 0x001A
                SMTO_ABORTIFHUNG = 0x0002

                ctypes.windll.user32.SendMessageTimeoutW(
                    HWND_BROADCAST, WM_SETTINGCHANGE, 0,
                    "Environment", SMTO_ABORTIFHUNG, 5000, None)
            except Exception as e:
                print(f"Warning: Could not refresh environment - {e}")
                print("You may need to restart your terminal or computer for changes to take effect")