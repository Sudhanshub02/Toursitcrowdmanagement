// graph.cpp
#include "graph.h"

void Graph::addEdge(string u, string v, int w, bool bidir) {
    adj[u].push_back({v, w});
    if (bidir)
        adj[v].push_back({u, w});
}

void Graph::blockRoad(string u, string v) {
    blockedEdges.insert({u, v});
    blockedEdges.insert({v, u}); // assuming bidirectional block
}

void Graph::printAdjList() {
    cout << "Adjacency List:\n";
    for (auto &item : adj) {
        cout << item.first << " -> ";
        for (auto &nbr : item.second) {
            cout << "(" << nbr.first << ", " << nbr.second << ") ";
        }
        cout << endl;
    }
}

void Graph::dijkstraAllPaths(string src, string dst) {
    unordered_map<string, int> dist;
    parent.clear();

    for (auto &item : adj) {
        dist[item.first] = INT_MAX;
        parent[item.first].clear();
    }

    dist[src] = 0;
    set<pair<int, string>> s;
    s.insert({0, src});

    while (!s.empty()) {
        auto top = *s.begin();
        s.erase(s.begin());

        string u = top.second;

        for (auto &nbr : adj[u]) {
            string v = nbr.first;
            int w = nbr.second;

            if (blockedEdges.count({u, v})) continue; // ✅ Skip blocked roads

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v].clear();
                parent[v].push_back(u);
                s.insert({dist[v], v});
            } else if (dist[v] == dist[u] + w) {
                parent[v].push_back(u);
            }
        }
    }

    if (dist[dst] == INT_MAX) {
        cout << "⚠️ No path exists from " << src << " to " << dst << " due to blocked roads.\n";
        return;
    }

    cout << "Distance from " << src << " to " << dst << ": " << dist[dst] << endl;
    cout << "All minimum paths from " << src << " to " << dst << ":\n";

    vector<string> path;
    printAllPaths(src, dst, path);
}

void Graph::printAllPaths(string src, string dst, vector<string> &path) {
    path.push_back(dst);

    if (dst == src) {
        reverse(path.begin(), path.end());
        for (const auto &v : path) cout << v << " ";
        cout << endl;
        reverse(path.begin(), path.end());
    } else {
        for (const auto &p : parent[dst]) {
            printAllPaths(src, p, path);
        }
    }

    path.pop_back();
}
