#include "Edge.h"
#include "Node.h"

Edge::Edge(Node* src, Node* dest, double dist)
        : source(src), destination(dest), distance(dist) {}

Node* Edge::getDestination() const {
    return destination;
}

Node* Edge::getSource() const {
    return source;
}

double Edge::getDistance() const {
    return distance;
}
