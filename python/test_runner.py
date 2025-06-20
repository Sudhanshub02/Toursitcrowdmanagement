
from itinerary_planner import ItineraryPlanner
from graph_data import FW_MATRIX, NODE_INDEX, ADJACENCY_LIST
import json

with open("crowd_status.json") as f:
    crowd_data = json.load(f)

with open("user_input.json") as f:
    user_input = json.load(f)

planner = ItineraryPlanner(FW_MATRIX, NODE_INDEX, ADJACENCY_LIST)
planner.set_crowd_status(crowd_data)

result = planner.plan_route(
    start=user_input["start"],
    end=user_input["end"],
    desired=user_input["desired"]
)

print("Final Route:", result.route)
print("Total Travel Time:", result.total_time)
print("Substitutions Made:", result.substitutions)
