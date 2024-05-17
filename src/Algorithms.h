#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <set>
#include <limits>
#include <vector>
#include <unordered_map>
#include "Graph.h"
#include "MutablePriorityQueue.h"

class Algorithms {
public:
    static std::set<Edge*> prim(const Graph& graph);
    static double triangularApproximationHeuristic(Graph graph, std::vector<int>& path);
    static double calculateHaversineDistance(double lat1, double lon1, double lat2, double lon2);
    static double nearestNeighborHeuristic(Graph& graph, std::vector<int>& path);

    static std::pair<std::vector<Node*>, double> tspBacktracking(Graph& graph);
    static void backtrack(Graph& graph, Node* node, std::vector<Node*> path, double cost, double& min_cost, int count, std::vector<Node*>& min_path);


private:
    static double toRadians(double degree);

    std::set<Edge *> duplicateEdges(const std::set<Edge *> &mst);

    std::vector<int> generateEulerCircuit(const std::set<Edge *> &doubledMst, Node *startNode);

    std::vector<int> createHamiltonianPath(const std::vector<int> &eulerCircuit);

};

#endif // ALGORITHMS_H
