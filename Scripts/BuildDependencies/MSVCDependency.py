"""
@file MSVCDependency.py.
@brief The MSVCDependency Class Definitions.
@author Spices
"""

from Scripts.BuildSystem.Dependency import Dependency
import os
import subprocess
import winreg


class MSVCDependency(Dependency):
    """
    @brief Base class for solution MSVC dependency.
    """

    def __init__(self):
        """
        @brief Construct function.
        """
        super().__init__("msvc", ["git"])

        # MSVC tools we need to check
        self.requiredTools = ["cl.exe", "link.exe", "lib.exe", "nmake.exe"]

        # MSBuild executable name (varies by VS version)
        self.msbuildName = "MSBuild.exe"

        # Path to VS where tools are installed
        self.vsInstallPath = None
        self.vcToolsPath = None
        self.msbuildPath = None

    def ms_build_path(self) -> str:
        """
        @brief Get the MSBuild Path.
        @return Returns MSBuild Path.
        """
        return self.msbuildPath

    def _check(self) -> bool:
        """
        @brief Interface of Check whether this dependency is existing.
        @return Returns true if exising.
        """
        if not self.isWindows:
            print("MSVC tools are only available on Windows")
            return False

        # Try to find Visual Studio installation
        self._find_visual_studio()

        # Check MSVC tools
        vc_tools_ok = self._check_msvc_tools()

        # Check MSBuild
        msbuild_ok = self._check_msbuild()

        return vc_tools_ok and msbuild_ok

    def _install(self) -> bool:
        """
        @brief Interface of install this dependency.
        @return Returns true if install successfully.
        """
        print("Please install Microsoft Visual Studio with required components:")
        print("1. Download Visual Studio Installer from https://visualstudio.microsoft.com/")
        print("2. Run the installer and select these workloads:")
        print("   - 'Desktop development with C++' (for MSVC tools)")
        print("   - '.NET desktop build tools' or 'Visual Studio extension development' (for MSBuild)")
        print("3. After installation, run this script from a Developer Command Prompt")
        print("   or run 'vcvarsall.bat' to set up the environment")

        # Offer to open the download page
        if input("Open Visual Studio download page now? (y/n): ").lower() == 'y':
            import webbrowser
            webbrowser.open("https://visualstudio.microsoft.com/downloads/")

        return False

    def _check_msvc_tools(self) -> bool:
        """
        @brief Check MSVC compiler tools availability.
        @return True if all required tools are found.
        """
        if not self.vcToolsPath:
            print("Visual Studio C++ tools path not found")
            return False

        # Check if all required tools are present
        all_tools_found = True
        for tool in self.requiredTools:
            tool_path = os.path.join(self.vcToolsPath, tool)
            if not os.path.exists(tool_path):
                print(f"MSVC tool not found: {tool}")
                all_tools_found = False

        if not all_tools_found:
            print("Some MSVC tools are missing")
            return False

        # Verify compiler works
        """
        try:
            result = subprocess.run(["cl"], capture_output=True, text=True, shell=True)
            if "Microsoft (R) C/C++ Optimizing Compiler" not in result.stderr:
                print("MSVC tools found but environment not properly configured")
                return False
        except Exception as e:
            print(f"Error checking MSVC environment: {e}")
            return False
        """
        return True

    def _check_msbuild(self) -> bool:
        """
        @brief Check MSBuild availability.
        @return True if MSBuild is found and functional.
        """
        # Try to find MSBuild
        self._find_msbuild()

        if not self.msbuildPath:
            print("MSBuild not found")
            return False

        # Verify MSBuild version
        try:
            result = subprocess.run([self.msbuildPath, "/version"],
                                    capture_output=True, text=True)
            if result.returncode != 0:
                print("MSBuild found but not working correctly")
                return False

            print(f"Found MSBuild version: {result.stdout.strip()}")
            return True
        except Exception as e:
            print(f"Error checking MSBuild: {e}")
            return False

    def _find_visual_studio(self):
        """
        @brief Try to locate Visual Studio installation and VC tools path.
        """
        # Try via registry first
        try:
            with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE,
                                r"SOFTWARE\Microsoft\VisualStudio\SxS\VS7") as key:
                vs_path = winreg.QueryValueEx(key, "")[0]
                self.vsInstallPath = vs_path

                # Find VC tools path
                vc_path = os.path.join(vs_path, "VC", "Tools", "MSVC")
                if os.path.exists(vc_path):
                    # Get the latest version
                    versions = [d for d in os.listdir(vc_path) if os.path.isdir(os.path.join(vc_path, d))]
                    if versions:
                        latest_version = sorted(versions)[-1]  # Simple version sort
                        self.vcToolsPath = os.path.join(vc_path, latest_version, "bin", "Hostx64", "x64")
        except Exception:
            pass

        # If registry method failed, try vswhere
        if not self.vcToolsPath:
            try:
                program_files = os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)")
                vswhere = os.path.join(program_files, "Microsoft Visual Studio", "Installer", "vswhere.exe")

                if os.path.exists(vswhere):
                    result = subprocess.run([vswhere, "-latest", "-products", "*",
                                             "-requires", "Microsoft.VisualStudio.Component.VC.Tools.x86.x64",
                                             "-property", "installationPath"],
                                            capture_output=True, text=True)
                    vs_path = result.stdout.strip()
                    if vs_path:
                        self.vsInstallPath = vs_path

                        # Find VC tools path using vswhere
                        result = subprocess.run([vswhere, "-latest", "-products", "*",
                                                 "-requires", "Microsoft.VisualStudio.Component.VC.Tools.x86.x64",
                                                 "-find", "VC/Tools/MSVC/**/bin/Hostx64/x64/cl.exe"],
                                                capture_output=True, text=True)
                        tool_path = result.stdout.strip()
                        if tool_path:
                            self.vcToolsPath = os.path.dirname(tool_path)
            except Exception as e:
                print(f"Error finding Visual Studio with vswhere: {e}")

    def _find_msbuild(self):
        """
        @brief Try to locate MSBuild installation path.
        """
        # Check common installation paths
        possible_paths = [
            # VS 2017 and later
            os.path.join(os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)"),
                         "Microsoft Visual Studio", "2022", "*", "MSBuild", "Current", "Bin"),
            os.path.join(os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)"),
                         "Microsoft Visual Studio", "2019", "*", "MSBuild", "Current", "Bin"),
            os.path.join(os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)"),
                         "Microsoft Visual Studio", "2017", "*", "MSBuild", "15.0", "Bin"),

            # Standalone MSBuild (older versions)
            os.path.join(os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)"),
                         "MSBuild", "*", "Bin"),

            # .NET Framework paths
            os.path.join(os.environ.get("WINDIR", r"C:\Windows"), "Microsoft.NET", "Framework64", "v4.0.30319"),
            os.path.join(os.environ.get("WINDIR", r"C:\Windows"), "Microsoft.NET", "Framework", "v4.0.30319"),
        ]

        # Also check PATH
        path_dirs = os.environ.get("PATH", "").split(os.pathsep)
        possible_paths.extend(path_dirs)

        # Search for MSBuild.exe
        for path_pattern in possible_paths:
            try:
                # Handle paths with wildcards
                if '*' in path_pattern:
                    import glob
                    expanded_paths = glob.glob(path_pattern)
                    for expanded_path in expanded_paths:
                        msbuild_path = os.path.join(expanded_path, self.msbuildName)
                        if os.path.exists(msbuild_path):
                            self.msbuildPath = msbuild_path
                            return
                else:
                    msbuild_path = os.path.join(path_pattern, self.msbuildName)
                    if os.path.exists(msbuild_path):
                        self.msbuildPath = msbuild_path
                        return
            except Exception:
                continue

        # If not found, try using vswhere
        if self.vsInstallPath and not self.msbuildPath:
            try:
                program_files = os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)")
                vswhere = os.path.join(program_files, "Microsoft Visual Studio", "Installer", "vswhere.exe")

                if os.path.exists(vswhere):
                    result = subprocess.run([vswhere, "-latest", "-products", "*",
                                             "-requires", "Microsoft.Component.MSBuild",
                                             "-find", "MSBuild\**\Bin\MSBuild.exe"],
                                            capture_output=True, text=True)
                    msbuild_path = result.stdout.strip()
                    if msbuild_path:
                        self.msbuildPath = msbuild_path
            except Exception as e:
                print(f"Error finding MSBuild with vswhere: {e}")
