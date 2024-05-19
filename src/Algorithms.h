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

    /**
      * @brief Prim's algorithm.
      *
      * @details
      * Time complexity: O(E log V)
      *
      * V - number of vertices (or nodes) in the graph
      *
      * E - number of edges in the graph
      * @param graph The graph on which to run Prim's algorithm.
      * @return (std::set<Edge*>) The set of edges forming the minimum spanning tree.
      */
    static std::set<Edge*> prim(const Graph& graph);

    /**
     * @brief Triangular Approximation Heuristic for the TSP.
     *
     * @details
     * This function implements a heuristic approach to approximate the solution to the Travelling Salesman Problem (TSP) using a triangular inequality-based method.
     *
     * Time complexity: O(V^2)
     *
     * V - number of vertices (or nodes) in the graph
     * @param graph The graph representing the TSP.
     * @param path A vector that will be filled with the order of node IDs representing the approximate tour.
     * @return (double) The estimated cost of the TSP tour.
     */
    static double triangularApproximationHeuristic(Graph graph, std::vector<int>& path);

    /**
     * @brief Calculate the Haversine distance between two points on the Earth's surface.
     *
     * @details
     * This function computes the Haversine distance, which is the shortest distance over the Earth's surface, giving an "as-the-crow-flies" distance between two points (specified in latitude and longitude).
     *
     * Time complexity: O(1)
     * @param lat1 The latitude of the first point in degrees.
     * @param lon1 The longitude of the first point in degrees.
     * @param lat2 The latitude of the second point in degrees.
     * @param lon2 The longitude of the second point in degrees.
     * @return (double) The Haversine distance between the two points in kilometers.
     */
    static double calculateHaversineDistance(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Nearest Neighbor Heuristic for the TSP.
     *
     * @details
     * This function implements the nearest neighbor heuristic to approximate the solution to the Travelling Salesman Problem (TSP). It starts from a given node and repeatedly visits the nearest unvisited node until all nodes are visited.
     *
     * Time complexity: O(V^2)
     *
     * V - number of vertices (or nodes) in the graph
     * @param graph The graph representing the TSP.
     * @param path A vector that will be filled with the order of node IDs representing the approximate tour.
     * @return (double) The estimated cost of the TSP tour.
     */
    static double nearestNeighborHeuristic(Graph& graph, std::vector<int>& path);

    /**
     * @brief Depth-First Search (DFS) on a graph.
     *
     * @details
     * This function performs a Depth-First Search (DFS) starting from a given node index. It explores as far as possible along each branch before backtracking, marking nodes as visited to avoid cycles and repeated visits.
     *
     * Time complexity: O(V + E)
     *
     * V - number of vertices (or nodes) in the graph
     *
     * E - number of edges in the graph
     * @param currentIndex The index of the current node to start the DFS from.
     * @param Real The graph on which the DFS is performed.
     * @param visited An unordered set that keeps track of visited node indices to avoid revisiting nodes.
     */
    void DFS(int currentIndex, Graph& Real, unordered_set<int>& visited);

    /**
     * @brief Solve the Travelling Salesman Problem (TSP) using backtracking.
     *
     * @details
     * This function uses a backtracking approach to find the minimum cost Hamiltonian cycle (tour) in a given graph. It explores all possible tours and keeps track of the tour with the minimum cost.
     *
     * Time complexity: O(K ^ N)
     *
     * K - number of times the function calls itself
     * @param graph The graph representing the TSP.
     * @return (std::pair<std::vector<Node*>, double>) A pair containing the vector of nodes representing the minimum cost tour and a double containing said cost.
     */
    static std::pair<std::vector<Node*>, double> tspBacktracking(Graph& graph);

    /**
     * @brief Recursive backtracking helper function for TSP.
     *
     * @details
     * This function recursively explores all possible paths in the graph to find the minimum cost Hamiltonian cycle (tour). It updates the minimum cost and corresponding path whenever a complete tour with a lower cost is found.
     *
     * Time complexity: O(K ^ N)
     *
     * K - number of times the function calls itself
     * @param graph The graph representing the TSP.
     * @param node The current node being visited.
     * @param path The current path of nodes visited so far.
     * @param cost The current cost of the path.
     * @param min_cost A reference to the minimum cost found so far.
     * @param count The count of nodes visited in the current path.
     * @param min_path A reference to the vector storing the minimum cost path found so far.
     */
    static void backtrack(Graph& graph, Node* node, std::vector<Node*> path, double cost, double& min_cost, int count, std::vector<Node*>& min_path);

    /**
     * @brief Solves the Travelling Salesman Problem (TSP) for a real-world graph.
     *
     * @details
     * This function executes the TSP algorithm on a given graph representing real-world locations, starting from a specified node. It typically involves setting up the graph, running a TSP heuristic or exact algorithm, and potentially outputting or processing the results.
     *
     * Time complexity: O(V^2)
     *
     * V - number of vertices (or nodes) in the graph
     * @param Real The graph representing the real-world TSP problem.
     * @param start The starting node index for the TSP tour.
     */
    void runRealWorldTSP(Graph &Real, int start);

private:

    /**
     * @brief Nearest Neighbor Heuristic for the TSP.
     *
     * @details
     * This function implements the nearest neighbor heuristic to approximate the solution to the Travelling Salesman Problem (TSP). Starting from a given node, it repeatedly visits the nearest unvisited node until all nodes are visited.
     *
     * Time complexity: O(V^2)
     *
     * V - number of vertices (or nodes) in the graph
     * @param Real The graph representing the TSP.
     * @param start The starting node index for the TSP tour.
     * @param totalDistance A reference to a double that will be updated with the total distance of the approximate tour.
     * @return (std::vector<int>) A vector of node indices representing the order of nodes in the approximate TSP tour.
     */
    vector<int> nearestNeighborTSP(Graph &Real, int start, double &totalDistance);
};

#endif // ALGORITHMS_H
