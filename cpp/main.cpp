// main.cpp
#include <iostream>
#include "graph.h"

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

    string start, dst;
    cout << "\nEnter source location: ";
    cin >> start;

    cout << "Enter destination location: ";
    cin >> dst;

    while (true) {
        g.dijkstraAllPaths(start, dst);

        cout << "\n🚧 Do you want to block any road due to traffic? (yes/no): ";
        string choice;
        cin >> choice;

        if (choice != "yes") break;

        int count;
        cout << "Enter number of roads to block: ";
        cin >> count;

        cout << "Enter each blocked road in format: <from> <to>\n";
        for (int i = 0; i < count; ++i) {
            string u, v;
            cin >> u >> v;
            g.blockRoad(u, v);
        }

        cout << "\n✅ Updated alternate route calculation:\n";
    }

    cout << "\n🛑 Program ended.\n";
    return 0;
}
