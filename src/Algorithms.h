#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <set>
#include <limits>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Graph.h"
#include "MutablePriorityQueue.h"


class Algorithms {
public:
    static std::set<Edge*> prim(const Graph& graph);
    static double triangularApproximationHeuristic(Graph graph, std::vector<int>& path);
    static double calculateHaversineDistance(double lat1, double lon1, double lat2, double lon2);
    static double nearestNeighborHeuristic(Graph& graph, std::vector<int>& path);
    vector<int> dijkstra(Graph& Real, int start);
    void DFS(int currentIndex, Graph& Real, unordered_set<int>& visited);


    double TSPRealWorld(Graph &Real, int startNodeIndex);

    void runRealWorldTSP(Graph &Real, int start);

private:
    static double toRadians(double degree);

    std::set<Edge *> duplicateEdges(const std::set<Edge *> &mst);

    std::vector<int> generateEulerCircuit(const std::set<Edge *> &doubledMst, Node *startNode);

    std::vector<int> createHamiltonianPath(const std::vector<int> &eulerCircuit);

    double transformMSTtoHamiltonianCycle(Graph graph, vector<int> &path);

    double transformMSTtoHamiltonianCycle(Graph graph, vector<int> &path, int startNodeIndex);

    vector<int> nearestNeighborTSP(Graph &Real, int start);

    vector<int> nearestNeighborTSP(Graph &Real, int start, double &totalDistance);
};

#endif // ALGORITHMS_H
