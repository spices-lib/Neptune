"""
@file Dependency.py.
@brief The Dependency Class Definitions.
@author Spices
"""

from BasicObject import BasicObject
from pathlib import Path
from abc import ABC, abstractmethod


class Dependency(BasicObject, ABC):
    """
    @brief Base class for solution dependency.
    """

    def __init__(self, name: str, dependencies: [str] = None):
        """
        @brief Construct function.
        @param[in] name Dependency name.
        @param[in] dependencies This dependencies.
        """
        super().__init__()
        self.name = name

        if dependencies is None:
            self.dependencies = []
        else:
            self.dependencies = dependencies

        self.scriptDirectory = Path(__file__).parent
        self.solutionDirectory = self.scriptDirectory.parent.parent

    def check(self) -> bool:
        """
        @brief Check whether this dependency is existing.
        @return Returns true if exising.
        """
        return self._check()

    def install(self) -> bool:
        """
        @brief install this dependency.
        @return Returns true if install successfully.
        """
        return self._install()

    @abstractmethod
    def _check(self) -> bool:
        """
        @brief Interface of Check whether this dependency is existing.
        @return Returns true if exising.
        """
        raise NotImplementedError()

    @abstractmethod
    def _install(self) -> bool:
        """
        @brief Interface of install this dependency.
        @return Returns true if install successfully.
        """
        raise NotImplementedError()
