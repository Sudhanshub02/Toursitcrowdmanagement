
from dataclasses import dataclass
from typing import Dict, List, Optional

@dataclass
class PlanResult:
    route: List[str]
    total_time: int
    substitutions: Dict[str, str]

class ItineraryPlanner:
    def __init__(self, 
                 fw_matrix: List[List[int]],
                 node_index: Dict[str, int],
                 adjacency_list: List[List[int]]):
        self.fw_matrix = fw_matrix
        self.node_index = node_index
        self.index_node = {v: k for k, v in node_index.items()}
        self.adjacency_list = adjacency_list
        self.crowd_status: Dict[str, str] = {}

    def set_crowd_status(self, status: Dict[str, str]):
        self.crowd_status = status

    def plan_route(self, start: str, end: str, desired: List[str]) -> PlanResult:
        current = start
        adjusted_route = []
        total_time = 0
        substitutions = {}

        for loc in desired:
            if self._is_overcrowded(loc):
                alternative = self._find_alternative(current, loc)
                if alternative:
                    adjusted_route.append(alternative)
                    substitutions[loc] = alternative
                    total_time += self._get_distance(current, alternative)
                    current = alternative
                continue
            
            adjusted_route.append(loc)
            total_time += self._get_distance(current, loc)
            current = loc

        total_time += self._get_distance(current, end)

        return PlanResult(
            route=adjusted_route,
            total_time=total_time,
            substitutions=substitutions
        )

    def _is_overcrowded(self, location: str) -> bool:
        return self.crowd_status.get(location, "Low") == "High"

    def _find_alternative(self, current: str, crowded: str) -> Optional[str]:
        current_idx = self.node_index[current]
        min_dist = float('inf')
        best_alt = None

        for node, idx in self.node_index.items():
            if node == crowded:
                continue
            if not self._is_overcrowded(node):
                distance = self.fw_matrix[current_idx][idx]
                if distance < min_dist:
                    min_dist = distance
                    best_alt = node

        return best_alt

    def _get_distance(self, from_node: str, to_node: str) -> int:
        return self.fw_matrix[self.node_index[from_node]][self.node_index[to_node]]
