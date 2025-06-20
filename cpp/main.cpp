// main.cpp
#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
    Graph g;
    int edges;

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter each edge in format: <from> <to> <weight>\n";
    for (int i = 0; i < edges; ++i) {
        string u, v;
        int w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.printAdjList();

    string start;
    cout << "\nEnter source location for Dijkstra: ";
    cin >> start;

    g.dijkstra(start);

    return 0;
}
