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


private:
    static double toRadians(double degree);
};

#endif // ALGORITHMS_H
