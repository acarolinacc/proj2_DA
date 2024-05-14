#include "Algorithms.h"
#include <queue>
#include <cmath>
#include <unordered_set>
#include <algorithm>
#include <iostream>

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

/*
 * -----------Triangular Approximation Heuristic----------- *
 */

std::set<Edge*> Algorithms::prim(const Graph& graph) {
    auto nodes = graph.getNodes();
    if (nodes.empty()) {
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

    cout << "Haversine distance between (" << lat1 << ", " << lon1 << ") and (" << lat2 << ", " << lon2 << ") is: " << distance << " meters." << endl;

    return distance;
}



double Algorithms::triangularApproximationHeuristic(Graph graph, vector<int>& path) {
    set<Edge*> mst = prim(graph);
    unordered_set<Node*> visited;
    double totalDistance = 0.0;

    if (mst.empty() || mst.size() != graph.getNodes().size() - 1) {
        cerr << "Error: Minimum Spanning Tree not properly constructed." << endl;
        return -1.0;
    }

    auto startEdge = *mst.begin();
    Node* startNode = startEdge->getSource();

    function<void(Node*)> dfs = [&](Node* node) {
        visited.insert(node);
        path.push_back(node->getId());

        cout << "Visiting node: " << node->getId() << endl;

        for (Edge* edge : node->getAdjacencies()) {
            Node* neighbor = edge->getDestination();
            if (visited.find(neighbor) == visited.end()) {
                totalDistance += edge->getDistance();
                cout << "Edge: " << node->getId() << " -> " << neighbor->getId() << ", Distance: " << edge->getDistance() << endl;
                dfs(neighbor);
            }
        }
    };

    dfs(startNode);
    path.push_back(startNode->getId());

    for (size_t i = 0; i < path.size() - 1; ++i) {
        Node* currentNode = graph.findNode(path[i]);
        Node* nextNode = graph.findNode(path[i + 1]);
        if (!currentNode || !nextNode) continue;

        double distance = calculateHaversineDistance(
                currentNode->getLatitude(), currentNode->getLongitude(),
                nextNode->getLatitude(), nextNode->getLongitude()
        );

        totalDistance += distance;
        cout << "Edge: " << currentNode->getId() << " -> " << nextNode->getId() << ", Distance: " << distance << endl;
    }

    cout << "Total distance: " << totalDistance << endl;

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
    Node* startNode = graph.getNodes().begin()->second;
    if (!startNode) {
        cerr << "Error: Start node not found." << endl;
        return -1.0;
    }

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