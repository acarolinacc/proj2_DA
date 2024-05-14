#ifndef NODE_H
#define NODE_H

#include <vector>

class Edge;

class Node {
public:
    Node(int idx, double lat = 0.0, double lon = 0.0);
    Node(int idx);

    void addEdge(Edge* edge);
    void removeEdge(Edge* edge);

    int getId() const;
    const std::vector<Edge*>& getAdjacencies() const;
    double getLatitude() const;
    double getLongitude() const;
    bool isVisited() const;
    void setVisited(bool visited);
    double getDistance() const;
    void setDistance(double distance);
    Edge* getPath() const; // Alterado para Edge*
    void setPath(Edge* edge); // Alterado para Edge*
    void incrementMSTDegree();
    int getMSTDegree() const;
    const std::vector<Edge*>& getIncomingEdges() const;
    void addIncomingEdge(Edge* edge);
    bool operator<(const Node& other) const;
    int getQueueIndex() const {
        return queueIndex;
    }

    void setQueueIndex(int index) {
        queueIndex = index;
    }
    int queueIndex;
    Edge *findEdgeTo(Node *destination);


private:
    int index;
    double latitude, longitude;
    bool visited;
    double distance;
    Edge* path; // Alterado para Edge*
    std::vector<Edge*> adjacencies;
    std::vector<Edge*> incomingEdges;
    int mstDegree;
};

#endif // NODE_H
