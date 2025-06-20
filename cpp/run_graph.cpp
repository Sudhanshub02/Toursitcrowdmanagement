#include <iostream>
#include <fstream>
#include <vector>
#include <utility> // for std::pair
#include "Graph.h" // Use either Graph.h or graph.h, not both

using namespace std;

int main() {
    Graph g(4);

    // Add edges: node1, node2, weight
    g.addEdge(0, 1, 5);  // Rishikesh - Laxman Jhula
    g.addEdge(1, 2, 8);  // Laxman Jhula - Neelkanth
    g.addEdge(2, 3, 10); // Neelkanth - Triveni Ghat
    g.addEdge(0, 3, 7);  // Rishikesh - Triveni Ghat

    ofstream out("../data/routes.json");

    out << "{\n";
    out << "  \"nodes\": [\n";
    out << "    {\"id\": 0, \"name\": \"Rishikesh\"},\n";
    out << "    {\"id\": 1, \"name\": \"Laxman Jhula\"},\n";
    out << "    {\"id\": 2, \"name\": \"Neelkanth\"},\n";
    out << "    {\"id\": 3, \"name\": \"Triveni Ghat\"}\n";
    out << "  ],\n";

    out << "  \"edges\": [\n";

    bool firstEdge = true;
    for (int i = 0; i < g.V; ++i) {
        for (auto& edge : g.adj[i]) {
            if (i < edge.first) {
                if (!firstEdge) out << ",\n";
                out << "    {\"from\": " << i << ", \"to\": " << edge.first
                    << ", \"weight\": " << edge.second << "}";
                firstEdge = false;
            }
        }
    }
    out << "\n  ]\n";
    out << "}\n";

    out.close();
    cout << "routes.json generated.\n";
    return 0;
}
