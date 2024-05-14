#ifndef EDGE_H
#define EDGE_H

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
};

#endif // EDGE_H
