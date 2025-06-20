// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <set>
#include <climits>
#include <string>
using namespace std;

class Graph {
private:
    unordered_map<string, list<pair<string, int>>> adj;

public:
    void addEdge(string u, string v, int w, bool bidir = true);
    void printAdjList();
    void dijkstra(string src);
};

#endif
