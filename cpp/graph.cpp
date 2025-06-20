// Graph.cpp
#include "Graph.h"

void Graph::addEdge(string u, string v, int w, bool bidir) {
    adj[u].push_back({v, w});
    if (bidir)
        adj[v].push_back({u, w});
}

void Graph::printAdjList() {
    cout << "\n Adjacency List:\n";
    for (auto node : adj) {
        cout << node.first << " -> ";
        for (auto nbr : node.second) {
            cout << "(" << nbr.first << ", " << nbr.second << ") ";
        }
        cout << endl;
    }
}

void Graph::dijkstra(string src) {
    unordered_map<string, int> dist;

    for (auto node : adj) {
        dist[node.first] = INT_MAX;
    }

    dist[src] = 0;
    set<pair<int, string>> s;
    s.insert({0, src});

    while (!s.empty()) {
        auto top = *s.begin();
        string node = top.second;
        int nodeDist = top.first;
        s.erase(s.begin());

        for (auto neighbour : adj[node]) {
            string nbr = neighbour.first;
            int edgeWeight = neighbour.second;

            if (nodeDist + edgeWeight < dist[nbr]) {
                auto f = s.find({dist[nbr], nbr});
                if (f != s.end()) s.erase(f);

                dist[nbr] = nodeDist + edgeWeight;
                s.insert({dist[nbr], nbr});
            }
        }
    }

    cout << "\n Shortest distances from '" << src << "':\n";
    for (auto d : dist) {
        cout << d.first << " : " << d.second << endl;
    }
}
