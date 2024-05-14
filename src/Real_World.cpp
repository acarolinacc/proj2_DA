#include "Menu.h"
#include "Graph.h"

#include <iostream>
#include <unordered_set>
#include <queue>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

struct CompareDistances {
    bool operator()(const pair<double, int>& a, const pair<double, int>& b) const {
        return a.first > b.first;
    }
};

void DFS(int currentIndex, Graph& Real, unordered_set<int>& visited) {
    visited.insert(currentIndex);
    auto edges = Real.getEdges()[currentIndex];
    for (auto& edge : edges) {
        if (visited.find(edge.dest) == visited.end()) {
            DFS(edge.dest, Real, visited);
        }
    }
}

vector<int> dijkstra(Graph& Real, int start) {
    unordered_map<int, double> distances;
    for (auto& nodePair : Real.getNodes()) {
        distances[nodePair.first] = numeric_limits<double>::infinity();
    }
    distances[start] = 0.0;

    priority_queue<pair<double, int>, vector<pair<double, int>>, CompareDistances> pq;
    pq.emplace(0.0, start);

    unordered_map<int, int> parent;

    while (!pq.empty()) {
        int currentIndex = pq.top().second;
        double currentDistance = pq.top().first;
        pq.pop();

        if (currentIndex == start && parent.size() == Real.getNodes().size() - 1) {
            break;
        }

        auto Edges =  Real.getEdges()[currentIndex];

        for (auto& edge : Edges) {
            double newDistance = currentDistance + edge.weight;
            if (newDistance < distances[edge.dest]) {
                distances[edge.dest] = newDistance;
                pq.emplace(newDistance, edge.dest);
                parent[edge.dest] = currentIndex;
            }
        }
    }
//Tá aqui algo de errado
    vector<int> path;
    int current = start;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }

    return path;
}

bool Menu::RealWorldCase(int StartIndexNode, Graph& Real) {
    unordered_set<int> visited;

    DFS(StartIndexNode, Real, visited);

    if (visited.size() == Real.getNodes().size()) {
        cout << "There is a path that goes through all the nodes.\n";
        cout << "Calculating now the fastest path. \n";

        vector<int> fastestPath = dijkstra(Real, StartIndexNode);
        cout << "Fastest Path: ";
        for (int node : fastestPath) {
            cout << node << " ";
        }
        cout << endl;
        return true;
    } else {
        cout << "There isn't a path that goes through all the nodes.\n";
        return false;
    }
}

