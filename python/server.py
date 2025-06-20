from itinerary_planner import ItineraryPlanner
import json
import random
import threading
import time
from flask import Flask, request, jsonify, send_from_directory
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

@app.route('/')
def serve_planner():
    return send_from_directory('.', 'planner.html')

# --- Data Setup ---
fw_matrix = [
    [0, 10, 15, 20, 25, 30, 35, 40, 45, 50],
    [10, 0, 35, 25, 30, 20, 15, 30, 40, 45],
    [15, 35, 0, 30, 20, 25, 40, 35, 25, 30],
    [20, 25, 30, 0, 15, 10, 20, 25, 30, 35],
    [25, 30, 20, 15, 0, 30, 35, 40, 45, 50],
    [30, 20, 25, 10, 30, 0, 15, 20, 25, 30],
    [35, 15, 40, 20, 35, 15, 0, 10, 20, 25],
    [40, 30, 35, 25, 40, 20, 10, 0, 15, 20],
    [45, 40, 25, 30, 45, 25, 20, 15, 0, 10],
    [50, 45, 30, 35, 50, 30, 25, 20, 10, 0]
]

node_index = {
    "Rishikesh": 0,
    "Haridwar": 1,
    "Neelkanth": 2,
    "Mussoorie": 3,
    "Nainital": 4,
    "Jim Corbett": 5,
    "Valley of Flowers": 6,
    "Auli": 7,
    "Badrinath": 8,
    "Chopta": 9
}

adjacency_list = [
    [1, 2],
    [0, 3, 5],
    [0, 4, 6],
    [1, 7],
    [2, 8],
    [1, 9],
    [2],
    [3],
    [4],
    [5]
]

planner = ItineraryPlanner(fw_matrix, node_index, adjacency_list)

# --- Simulate Dynamic Crowd Updates ---
statuses = ["Low", "Medium", "High"]
places = list(node_index.keys())

def simulate_crowd_updates():
    while True:
        new_crowd_status = {place: random.choice(statuses) for place in places}
        planner.set_crowd_status(new_crowd_status)
        print("Updated Crowd Status:", new_crowd_status)
        time.sleep(10)  # Update every 10 seconds

# Start simulation in background thread
threading.Thread(target=simulate_crowd_updates, daemon=True).start()

# --- API Endpoints ---

@app.route('/api/plan', methods=['POST'])
def plan():
    data = request.json
    start = data['start']
    destinations = data['destinations']
    total_time = data['total_time']

    result = planner.plan_route(start, start, destinations)

    return jsonify({
        'route': result.route,
        'total_time': result.total_time,
        'substitutions': result.substitutions
    })

@app.route('/api/crowd', methods=['GET'])
def get_crowd_status():
    return jsonify(planner.get_crowd_status())

# --- Run App ---
if __name__ == '__main__':
    app.run(debug=True)
