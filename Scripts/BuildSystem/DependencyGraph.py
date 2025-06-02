"""
@file DependencyGraph.py.
@brief The DependencyGraph Class Definitions.
@author Spices
"""

from BasicObject import BasicObject
from Dependency import Dependency
from typing import Optional


class DependencyGraph(BasicObject):
    """
    @brief Handles dependency checking and installation
    """

    def __init__(self):
        """
        @brief Construct function.
        """
        super().__init__()
        self.nodes: dict = {}
        self.executed: bool = False

    def add_node(self, dependency: Dependency):
        """
        @brief Add a Dependency to this graph.
        @param[in] dependency Dependency.
        """
        self.nodes[dependency.name] = dependency
        self.executed = False

    def find(self, name: str) -> Optional[Dependency]:
        """
        @brief Find a Dependency from this graph.
        @param[in] name Dependency name.
        """
        return self.nodes.get(name)

    def execute(self):
        """
        @brief Execute all Dependency function by order.
        """
        visited: dict = {}
        for k, v in self.nodes.items():
            if k not in visited:
                self.__execute_internal(v, visited)
        self.executed = True

    def __execute_internal(self, dependency: Dependency, visited: dict):
        """
        @brief Execute a Dependency function by order.
        @param[in] dependency Dependency.
        @param[in] visited graph execute states.
        """
        visited[dependency.name] = True
        for dep in dependency.dependencies:
            if dep not in self.nodes:
                print(f"-------------------------------------------------------")
                print(f"Error: Missing dependency '{dep}' required by '{dependency.name}'")
                print(f"-------------------------------------------------------")
                continue

            if dep not in visited:
                self.__execute_internal(self.nodes[dep], visited)
        print("-------------------------------------------------------")
        print(f"Dependency: { dependency.name } checking.")
        if dependency.check():
            print("Prepared.")
        else:
            print("Installing................")
            if dependency.install():
                print("Install succeed.")
        print("-------------------------------------------------------")
