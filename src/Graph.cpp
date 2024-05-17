#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <filesystem>

using namespace std;

/*
 * -----------GRAPH----------- *
 */

Graph::Graph() {}

Graph::~Graph() {
    for (auto& pair : nodes) {
        delete pair.second;
    }
}

void Graph::addNode(int index, double latitude, double longitude) {
    if (nodes.find(index) == nodes.end()) {
        nodes[index] = new Node(index, latitude, longitude);
    } else {
        std::cerr << "Node " << index << " already exists.\n";
    }
}

void Graph::addNode(int index) {
    addNode(index, 0.0, 0.0);
}

void Graph::addBidirectionalEdge(int srcIndex, int destIndex, double weight) {
    Node* srcNode = findNode(srcIndex);
    Node* destNode = findNode(destIndex);
    if (!srcNode || !destNode) {
        cerr << "Error: One or both nodes not found, cannot add edge.\n";
        return;
    }
    Edge* edgeToDest = new Edge(srcNode, destNode, weight);
    Edge* edgeToSrc = new Edge(destNode, srcNode, weight);
    srcNode->addEdge(edgeToDest);
    destNode->addEdge(edgeToSrc);

}

Node * Graph::findNode(int index) const {
    auto it = nodes.find(index);
    return it != nodes.end() ? it->second : nullptr;
}

/*
void Graph::displayGraph() {
    cout << "Graph nodes:\n";
    for (auto& pair : nodes) {
        Node* node = pair.second;
        cout << "Node " << node->getId() << " (Latitude: " << node->getLatitude() << ", Longitude: " << node->getLongitude() << ")\n";
        cout << "   Adjacent nodes:\n";
        for (auto& edge : node->getAdjacencies()) {
            Node* destNode = edge->getDestination();
            cout << "     - Node " << destNode->getId() << " with weight " << edge->getDistance() << "\n";
        }
        cout << endl;
    }

    cout << "Graph edges:\n";
    for (auto& pair : nodes) {
        Node* node = pair.second;
        cout << "Edges from Node " << node->getId() << ":\n";
        for (auto& edge : node->getAdjacencies()) {
            cout << "   - Node " << node->getId() << " to Node " << edge->getDestination()->getId() << " with weight " << edge->getDistance() << "\n";
        }
        cout << endl;
    }
}

void Graph::resetNodes() {
    for (auto& pair : nodes) {
        Node* node = pair.second;
        node->setVisited(false);
        node->setDistance(std::numeric_limits<double>::infinity());
        node->setPath(nullptr);
    }
}
*/

void Graph::clearNodes() {
    for (auto& pair : nodes) {
        delete pair.second;
    }
    nodes.clear();
}

unordered_map<int, Node*> Graph::getNodes() const {
    return nodes;
}

/*
 * -----------READ FILES----------- *
 */

int Graph::readExtraGraphs(const string &edgesFilePath) {
    ifstream file(edgesFilePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << edgesFilePath << endl;
        return 1;
    }

    filesystem::path filePath(edgesFilePath);
    string fileName = filePath.filename().string();

    size_t start = fileName.find_first_of("0123456789");
    size_t end = fileName.find_first_not_of("0123456789", start);
    int nodeCount = stoi(fileName.substr(start, end - start));

    for (int i = 0; i < nodeCount; i++) {
        if (findNode(i) == nullptr) {
            addNode(i);
        }
    }

    string line, sourceIndex, destinyIndex, distance;
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, sourceIndex, ',');
        getline(iss, destinyIndex, ',');
        getline(iss, distance, ',');

        int src = stoi(sourceIndex);
        int dst = stoi(destinyIndex);
        double dist = stod(distance);

        addBidirectionalEdge(src, dst, dist);
    }

    file.close();
    return 0;
}

int Graph::readRealWorldGraph(const string& nodesFilePath, const string& edgesFilePath) {
    ifstream nodesFile(nodesFilePath);
    ifstream edgesFile(edgesFilePath);
    if (!nodesFile.is_open() || !edgesFile.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    string line, index, latitude, longitude;
    getline(nodesFile, line);
    while (getline(nodesFile, line)) {
        istringstream iss(line);
        getline(iss, index, ',');
        getline(iss, longitude, ',');
        getline(iss, latitude, ',');
        addNode(stoi(index), stod(latitude), stod(longitude));
    }

    getline(edgesFile, line);
    string sourceIndex, destinyIndex, distance;
    while (getline(edgesFile, line)) {
        istringstream iss(line);
        getline(iss, sourceIndex, ',');
        getline(iss, destinyIndex, ',');
        getline(iss, distance, ',');

        int src = stoi(sourceIndex);
        int dst = stoi(destinyIndex);
        double dist = stod(distance);

        addBidirectionalEdge(src, dst, dist);
    }

    nodesFile.close();
    edgesFile.close();
    return 0;
}

int Graph::readToyGraph(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return 1;
    }

    string line;
    getline(file, line);

    string sourceIndex, destinyIndex, distance;
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, sourceIndex, ',');
        getline(iss, destinyIndex, ',');
        getline(iss, distance, ',');

        int src = stoi(sourceIndex);
        int dst = stoi(destinyIndex);
        double dist = stod(distance);

        if (findNode(src) == nullptr) {
            addNode(src);
        }
        if (findNode(dst) == nullptr) {
            addNode(dst);
        }

        addBidirectionalEdge(src, dst, dist);
    }

    file.close();
    return 0;
}

