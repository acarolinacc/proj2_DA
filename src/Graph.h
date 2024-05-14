#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <string>

#include "Node.h"
#include "Edge.h"

class Graph {
public:
    Graph();
    ~Graph();

    int readRealWorldGraph(const std::string& nodesFilePath, const std::string& edgesFilePath);
    int readExtraGraphs(const std::string& edgesFilePath);
    int readToyGraph(const std::string& filePath);

    void addNode(int index, double latitude, double longitude);
    void addNode(int index);
    void addBidirectionalEdge(int srcIndex, int destIndex, double weight);
    Node * findNode(int index) const;
    void displayGraph();
    void clearNodes();
    std::unordered_map<int, Node*> getNodes() const;


    // Haversine distance calculation
    double calculateHaversineDistance(double lat1, double lon1, double lat2, double lon2);

private:
    std::unordered_map<int, std::vector<Edge*>> adjacencyList;
    std::unordered_map<int, Node*> nodes;
};

#endif // GRAPH_H
