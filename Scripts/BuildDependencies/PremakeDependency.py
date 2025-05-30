"""
@file PremakeDependency.py.
@brief The PremakeDependency Class Definitions.
@author Spices
"""

from Scripts.BuildSystem.Dependency import Dependency
import urllib.request
import zipfile
import tarfile

"""
@brief Premake download url.
"""
premakeURL = {
    "windows": "https://github.com/premake/premake-core/releases/download/v5.0.0-beta6/premake-5.0.0-beta6-windows.zip",
    "linux": "https://github.com/premake/premake-core/releases/download/v5.0.0-beta6/premake-5.0.0-beta6-linux.tar.gz",
    "darwin": "https://github.com/premake/premake-core/releases/download/v5.0.0-beta6/premake-5.0.0-beta6-macosx.tar.gz"
}


class PremakeDependency(Dependency):
    """
    @brief Base class for solution dependency.
    """

    def __init__(self):
        """
        @brief Construct function.
        """
        super().__init__("premake", None)

        # Set dependency path
        self.dependencyPath = self.solutionDirectory / "vendor" / "premake" / \
            ("premake5.exe" if self.isWindows else "premake5")

    def path(self) -> str:
        """
        @brief Get this dependency path.
        @return Returns this dependency path.
        """
        return self.dependencyPath

    def _check(self) -> bool:
        """
        @brief Interface of Check whether this dependency is existing.
        @return Returns true if exising.
        """
        return self.dependencyPath.exists()

    def _install(self) -> bool:
        """
        @brief Interface of install this dependency.
        @return Returns true if install successfully.
        """

        # Make install directory
        install_dir = self.solutionDirectory / "vendor" / "premake"
        install_dir.mkdir(parents=True, exist_ok=True)

        try:
            url = premakeURL.get(self.system)
            if not url:
                print(f"Unsupported system for premake auto-install: {self.system}")
                return False

            print(f"Downloading premake5 from {url}")
            archive_path = install_dir / "premake_download.zip" \
                if self.isWindows else install_dir / "premake_download.tar.gz"

            # Download the file
            urllib.request.urlretrieve(url, archive_path)

            # Extract the archive
            if self.isWindows:
                with zipfile.ZipFile(archive_path, 'r') as zip_ref:
                    zip_ref.extractall(install_dir)
            else:
                with tarfile.open(archive_path, 'r:gz') as tar_ref:
                    tar_ref.extractall(install_dir)

            # Clean up
            archive_path.unlink()

            # On Linux/macOS, ensure the binary is executable
            if not self.isWindows:
                premake_bin = install_dir / "premake5"
                premake_bin.chmod(0o755)

            return True
        except Exception as e:
            print(f"Failed to install premake5: {e}")
            return False
