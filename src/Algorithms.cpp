#include "Algorithms.h"
#include <queue>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <functional>
#include <chrono>

using namespace std;

const double EARTH_RADIUS = 6371000.0;
const double PI = 3.14159265358979323846;

struct NodeDistance {
    Node* node;
    double distance;
    NodeDistance(Node* node, double distance) : node(node), distance(distance) {}
    bool operator>(const NodeDistance& other) const {
        return distance > other.distance;
    }
};

struct CompareDistances {
    bool operator()(const pair<double, int>& a, const pair<double, int>& b) const {
        return a.first > b.first;
    }
};


/*
 * -----------Backtracking Algorithm----------- *
 */



/*
 * -----------Triangular Approximation Heuristic----------- *
 */

std::set<Edge*> Algorithms::prim(const Graph& graph) {
    auto nodes = graph.getNodes();
    if (nodes.empty()) {
        std::cerr << "The graph is empty." << std::endl;
        return {};
    }

    std::set<Edge*> mst;

    for (auto& pair : nodes) {
        Node* node = pair.second;
        node->setDistance(std::numeric_limits<double>::max());
        node->setPath(nullptr);
        node->setVisited(false);
    }

    Node* root = nullptr;
    int minIndex = std::numeric_limits<int>::max();
    for (auto& pair : nodes) {
        if (pair.first < minIndex) {
            minIndex = pair.first;
            root = pair.second;
        }
    }
    if (root == nullptr) {
        std::cerr << "Error: Unable to find a valid starting node." << std::endl;
        return {};
    }

    root->setDistance(0);
    MutablePriorityQueue<Node> q;
    q.insert(root);

    while (!q.empty()) {
        Node* v = q.extractMin();
        v->setVisited(true);

        for (Edge* e : v->getAdjacencies()) {
            Node* w = e->getDestination();
            if (!w->isVisited()) {
                double oldDist = w->getDistance();
                if (e->getDistance() < oldDist) {
                    w->setDistance(e->getDistance());
                    w->setPath(e);
                    if (oldDist == std::numeric_limits<double>::max()) {
                        q.insert(w);
                    } else {
                        q.decreaseKey(w);
                    }
                }
            }
        }

        if (v->getPath() != nullptr) {
            mst.insert(v->getPath());
            v->getPath()->getDestination()->incrementMSTDegree();
            v->getPath()->getSource()->incrementMSTDegree();
        }
    }

    return mst;
}

double Algorithms::calculateHaversineDistance(double lat1, double lon1, double lat2, double lon2) {
    auto toRadians = [](double degree) {
        return degree * PI / 180.0;
    };

    double radLat1 = toRadians(lat1);
    double radLon1 = toRadians(lon1);
    double radLat2 = toRadians(lat2);
    double radLon2 = toRadians(lon2);

    double deltaLat = radLat2 - radLat1;
    double deltaLon = radLon2 - radLon1;

    double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
               cos(radLat1) * cos(radLat2) *
               sin(deltaLon / 2) * sin(deltaLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double distance = EARTH_RADIUS * c;


    return distance;
}

double Algorithms::triangularApproximationHeuristic(Graph graph, vector<int>& path) {
    std::set<Edge*> mst = prim(graph);
    if (mst.empty() || mst.size() != graph.getNodes().size() - 1) {
        std::cerr << "Error: Minimum Spanning Tree not properly constructed." << std::endl;
        return -1.0;
    }

    std::unordered_map<Node*, std::vector<Node*>> adjList;
    for (Edge* edge : mst) {
        adjList[edge->getSource()].push_back(edge->getDestination());
        adjList[edge->getDestination()].push_back(edge->getSource());
    }

    std::vector<int> eulerCircuit;
    std::unordered_set<Node*> visited;
    std::function<void(Node*)> dfs = [&](Node* node) {
        visited.insert(node);
        eulerCircuit.push_back(node->getId());

        std::vector<Node*> sortedNeighbors = adjList[node];
        std::sort(sortedNeighbors.begin(), sortedNeighbors.end(),
                  [](Node* a, Node* b) { return a->getId() < b->getId(); });

        for (Node* neighbor : sortedNeighbors) {
            if (!visited.count(neighbor)) {
                dfs(neighbor);
            }
        }
    };

    dfs(graph.findNode(0));

    std::unordered_set<int> visitedNodes;
    std::vector<int> tempPath;
    for (int nodeId : eulerCircuit) {
        if (visitedNodes.insert(nodeId).second) {
            tempPath.push_back(nodeId);
        }
    }

    if (!tempPath.empty() && tempPath.front() != 0) {
        auto it = std::find(tempPath.begin(), tempPath.end(), 0);
        std::rotate(tempPath.begin(), it, tempPath.end());
    }
    tempPath.push_back(0);
    path = tempPath;

    double totalDistance = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        Node* currentNode = graph.findNode(path[i]);
        Node* nextNode = graph.findNode(path[i + 1]);
        Edge* edge = currentNode->findEdgeTo(nextNode);
        double distance = edge ? edge->getDistance() : calculateHaversineDistance(
                currentNode->getLatitude(), currentNode->getLongitude(),
                nextNode->getLatitude(), nextNode->getLongitude());
        totalDistance += distance;
    }

    return totalDistance;
}


/*
 * -----------Other Heuristics----------- *
 */


double Algorithms::nearestNeighborHeuristic(Graph& graph, vector<int>& path) {
    unordered_set<Node*> visited;
    double totalDistance = 0.0;

    if (graph.getNodes().empty()) {
        cerr << "Error: The graph is empty." << endl;
        return -1.0;
    }

    auto startNodeIt = graph.getNodes().find(0);
    if (startNodeIt == graph.getNodes().end()) {
        cerr << "Error: Start node with ID 0 not found." << endl;
        return -1.0;
    }
    Node* startNode = startNodeIt->second;

    Node* currentNode = startNode;
    path.push_back(currentNode->getId());
    visited.insert(currentNode);

    while (visited.size() < graph.getNodes().size()) {
        double minDistance = numeric_limits<double>::max();
        Node* nextNode = nullptr;

        for (Edge* edge : currentNode->getAdjacencies()) {
            Node* neighbor = edge->getDestination();
            if (visited.find(neighbor) == visited.end()) {
                double distance = edge->getDistance();
                if (distance < minDistance) {
                    minDistance = distance;
                    nextNode = neighbor;
                }
            }
        }

        if (!nextNode) {
            for (auto& pair : graph.getNodes()) {
                Node* neighbor = pair.second;
                if (visited.find(neighbor) == visited.end()) {
                    double distance = calculateHaversineDistance(
                            currentNode->getLatitude(), currentNode->getLongitude(),
                            neighbor->getLatitude(), neighbor->getLongitude()
                    );
                    if (distance < minDistance) {
                        minDistance = distance;
                        nextNode = neighbor;
                    }
                }
            }
        }

        if (nextNode) {
            path.push_back(nextNode->getId());
            visited.insert(nextNode);
            totalDistance += minDistance;
            currentNode = nextNode;
        } else {
            cerr << "Error: No next node found." << endl;
            return -1.0;
        }
    }

    double returnDistance = calculateHaversineDistance(
            currentNode->getLatitude(), currentNode->getLongitude(),
            startNode->getLatitude(), startNode->getLongitude()
    );
    totalDistance += returnDistance;
    path.push_back(startNode->getId());

    return totalDistance;
}

void Algorithms::backtrack(Graph &graph, Node* node, std::vector<Node*> path, double cost, double &min_cost, int count,vector<Node*> &min_path) {
    //base case
    if(count == (graph.getNodes().size() + 1) && node->getId() == 0){
        if(cost < min_cost){
            min_cost = cost;
            min_path = path;
        }
        //else skip? (pruning option)
        return;
    }

    for(const auto& e : node->getAdjacencies() ){
        Node* newNode = e->getDestination();

        if(!newNode->isVisited()){
            newNode->setVisited(true);
            path.push_back(newNode);


            backtrack(graph, newNode, path, cost + e->getDistance(), min_cost, count + 1, min_path);
            path.pop_back();
            newNode->setVisited(false);
        }

    }
}

std::pair<std::vector<Node*>, double> Algorithms::tspBacktracking( Graph &graph) {
    std::vector<Node*> min_path;

    for(auto& n : graph.getNodes()){
        n.second->setVisited(false);
    }

    Node* startingNode = graph.findNode(0);
    double min_cost = INT_MAX;

    std::vector<Node*> path{startingNode};

    backtrack(graph,startingNode,path,0,min_cost,1, min_path);

    std::pair<std::vector<Node*>, double> result (min_path,min_cost);
    return result;
}




/*
 * -----------TSP in the Real World----------- *
 */

void Algorithms::DFS(int currentIndex, Graph& Real, unordered_set<int>& visited) {
    visited.insert(currentIndex);
    auto edges = Real.getNodes().at(currentIndex)->getAdjacencies();
    for (auto& edge : edges) {
        if (visited.find(edge->getDestination()->getId()) == visited.end()) {
            DFS(edge->getDestination()->getId(), Real, visited);
        }
    }
}

vector<int> Algorithms::nearestNeighborTSP(Graph& Real, int start, double& totalDistance) {
    vector<int> tour;
    unordered_set<int> visited;
    int current = start;
    totalDistance = 0.0;

    while (visited.size() < Real.getNodes().size()) {
        visited.insert(current);
        tour.push_back(current);

        double minDistance = numeric_limits<double>::infinity();
        int nextNode = -1;
        auto edges = Real.getNodes().at(current)->getAdjacencies();
        for (auto& edge : edges) {
            int destID = edge->getDestination()->getId();
            if (visited.find(destID) == visited.end() && edge->getDistance() < minDistance) {
                minDistance = edge->getDistance();
                nextNode = destID;
            }
        }

        if (nextNode == -1) {
            break;
        }

        totalDistance += minDistance;
        current = nextNode;
    }

    if (!tour.empty()) {
        totalDistance += Real.getNodes().at(tour.back())->findEdgeTo(Real.getNodes().at(start))->getDistance();
        tour.push_back(start);
    }

    return tour;
}

void Algorithms::runRealWorldTSP(Graph& Real, int start) {
    unordered_set<int> visited;
    auto start_time = chrono::high_resolution_clock::now();

    DFS(start, Real, visited);

    if (visited.size() != Real.getNodes().size()) {
        cout << "Debug: No path exists to visit all nodes and return to the start." << endl;
        throw runtime_error("No path exists to visit all nodes and return to the start.");
    }

    double totalDistance = 0.0;
    vector<int> tspTour = nearestNeighborTSP(Real, start, totalDistance);

    if (tspTour.empty() || tspTour.front() != start) {
        cout << "Debug: No valid tour found." << endl;
        throw runtime_error("Error: No valid tour found.");
    }

    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time);

    cout << "TSP Tour: ";
    for (int node : tspTour) {
        cout << node << " ";
    }
    cout << endl;
    cout << "Total Distance: " << totalDistance << " meters" << endl;
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
}

