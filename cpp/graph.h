// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <set>
#include <climits>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    unordered_map<string, list<pair<string, int>>> adj;
    unordered_map<string, vector<string>> parent;
    set<pair<string, string>> blockedEdges;

    void printAllPaths(string src, string dst, vector<string> &path);

public:
    void addEdge(string u, string v, int w, bool bidir = true);
    void blockRoad(string u, string v);
    void printAdjList();
    void dijkstraAllPaths(string src, string dst);
};

#endif // GRAPH_H
