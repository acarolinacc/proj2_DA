#ifndef EDGE_H
#define EDGE_H
#include <vector>
using namespace std;

class Node;

class Edge {
public:
    Edge(Node* src, Node* dest, double dist);

    Node* getDestination() const;
    Node* getSource() const;
    double getDistance() const;

private:
    Node* source;
    Node* destination;
    double distance;
    vector<Edge*> outgoingEdges;
    vector<Edge*> incomingEdges;
};

#endif // EDGE_H
