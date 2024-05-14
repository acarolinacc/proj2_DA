#include "Node.h"
#include "Edge.h"
#include <algorithm>
#include <cmath>

Node::Node(int idx, double lat, double lon)
        : index(idx), latitude(lat), longitude(lon), visited(false), distance(INFINITY), mstDegree(0), path(nullptr) {}

Node::Node(int idx)
        : Node(idx, 0.0, 0.0) {}

void Node::addEdge(Edge* edge) {
    adjacencies.push_back(edge);
}

void Node::removeEdge(Edge* edge) {
    adjacencies.erase(std::remove(adjacencies.begin(), adjacencies.end(), edge), adjacencies.end());
}

int Node::getId() const {
    return index;
}

const std::vector<Edge*>& Node::getAdjacencies() const {
    return adjacencies;
}

double Node::getLatitude() const {
    return latitude;
}

double Node::getLongitude() const {
    return longitude;
}

bool Node::isVisited() const {
    return visited;
}

void Node::setVisited(bool visited) {
    this->visited = visited;
}

double Node::getDistance() const {
    return distance;
}

void Node::setDistance(double distance) {
    this->distance = distance;
}

Edge* Node::getPath() const {
    return path;
}

void Node::setPath(Edge* edge) {
    this->path = edge;
}

void Node::incrementMSTDegree() {
    ++mstDegree;
}

int Node::getMSTDegree() const {
    return mstDegree;
}

const std::vector<Edge*>& Node::getIncomingEdges() const {
    return incomingEdges;
}

void Node::addIncomingEdge(Edge* edge) {
    incomingEdges.push_back(edge);
}

bool Node::operator<(const Node& other) const {
    return distance < other.distance;
}
