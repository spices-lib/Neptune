"""
@file BuildSystem.py.
@brief The BuildSystem Class Definitions.
@author Spices
"""

from BasicObject import BasicObject
from DependencyGraph import DependencyGraph
from Scripts.BuildDependencies.GitDependency import GitDependency
from pathlib import Path
from abc import ABC, abstractmethod


class BuildSystem(BasicObject, ABC):
    """
    @brief Base class for build systems
    """

    def __init__(self, solution_root: Path, platform: str = "emscripten", toolset: str = "GNU"):
        """
        @brief Construct function.
        @param[in] solution_root Solution root folder.
        @param[in] platform
        @param[in] toolset
        """
        super().__init__()
        self.solutionDirectory = solution_root
        self.platform = platform
        self.toolset = toolset
        self.dependencyGraph = DependencyGraph()
        self.dependencyGraph.add_node(GitDependency())

    def generate(self) -> bool:
        """
        @brief Generate build files.
        @return Returns true if generate succeed.
        """
        self.__execute_dependency()
        self.clean()
        print("Generating Solution........................")
        if self._generate():
            print("Run Over..............................")
        return True

    def build(self, config: str = "debug") -> bool:
        """
        @brief Build the project.
        @param[in] config Build config.
        @return Returns true if build succeed.
        """
        self.generate()
        print("Building Solution........................")
        if self._build(config):
            print("Run Over..............................")
        return True

    def clean(self) -> bool:
        """
        @brief Clean build artifacts.
        @return Returns true if clean succeed.
        """
        print("Clean Solution........................")
        if self._clean():
            print("Run Over..............................")
        return True

    def __execute_dependency(self):
        """
        @brief Execute dependency graph.
        """
        if not self.dependencyGraph.executed:
            print("Executing DependencyGraph.............")
            self.dependencyGraph.execute()
            print("Run Over..............................")

    @abstractmethod
    def _generate(self) -> bool:
        """
        @brief Internal Build the project.
        @return Returns true if generate succeed.
        """
        raise NotImplementedError()

    @abstractmethod
    def _build(self, config: str = "debug") -> bool:
        """
        @brief Internal Build the project.
        @param[in] config Build config.
        @return Returns true if build succeed.
        """
        raise NotImplementedError()

    @abstractmethod
    def _clean(self) -> bool:
        """
        @brief Internal Clean build artifacts.
        @return Returns true if clean succeed.
        """
        raise NotImplementedError()
