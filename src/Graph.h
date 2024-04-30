#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <string>

struct Node {
    int index;
    double latitude, longitude;
    Node(int idx, double lat = 0.0, double lon = 0.0) : index(idx), latitude(lat), longitude(lon) {}
};

struct Edge {
    int dest;
    double weight;
    Edge(int d, double w) : dest(d), weight(w) {}
};

class Graph {
public:
    Graph();
    ~Graph();

    int createRealWorldGraph(const std::string& nodesFilePath, const std::string& edgesFilePath);
    int createExtraGraphs(const std::string& edgesFilePath);
    int createToyGraph(const std::string& filePath);

    void addNode(int index, double latitude, double longitude);
    void addBidirectionalEdge(int srcIndex, int destIndex, double weight);
    Node* findNode(int index);
    void displayGraph();
    void clearNodes();

private:
    std::unordered_map<int, std::vector<Edge>> adjacencyList;
    std::unordered_map<int, Node*> nodes;
};

#endif // GRAPH_H
