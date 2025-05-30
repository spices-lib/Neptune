"""
@file BasicObject.py.
@brief The BasicObject Class Definitions.
@author Spices
"""

import platform


class BasicObject:
    """
    @brief Base class for all object.
    """

    def __init__(self):
        """
        @brief Construct function.
        """

        self.system = platform.system().lower()
        self.isWindows = self.system == "windows"
        self.isLinux = self.system == "linux"
        self.isMacos = self.system == "darwin"