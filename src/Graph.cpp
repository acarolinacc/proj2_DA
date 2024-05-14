#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
using namespace std;


Graph::Graph() {}

Graph::~Graph() {
    for (auto& pair : nodes) {
        delete pair.second;
    }
}

void Graph::addNode(int index, double latitude = 0.0, double longitude = 0.0) {
    if (nodes.find(index) == nodes.end()) {
        nodes[index] = new Node(index, latitude, longitude);
    }
}

void Graph::addBidirectionalEdge(int srcIndex, int destIndex, double weight) {
    if (nodes.find(srcIndex) == nodes.end() || nodes.find(destIndex) == nodes.end()) {
        cerr << "Error: Node not found, cannot add edge." << endl;
        return;
    }
    adjacencyList[srcIndex].emplace_back(destIndex, weight);
    adjacencyList[destIndex].emplace_back(srcIndex, weight);
}

void Graph::addDirectionalEdge(int srcIndex, int destIndex, double weight) {
    if (nodes.find(srcIndex) == nodes.end() || nodes.find(destIndex) == nodes.end()) {
        cerr << "Error: Node not found, cannot add edge." << endl;
        return;
    }
    adjacencyList[srcIndex].emplace_back(destIndex, weight);
}

Node* Graph::findNode(int index) {
    auto it = nodes.find(index);
    return it != nodes.end() ? it->second : nullptr;
}

int Graph::createRealWorldGraph(const string& nodesFilePath, const string& edgesFilePath) {
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

    // Load edges
    getline(edgesFile, line); // Skip header if present
    string sourceIndex, destinyIndex, distance;
    while (getline(edgesFile, line)) {
        istringstream iss(line);
        getline(iss, sourceIndex, ',');
        getline(iss, destinyIndex, ',');
        getline(iss, distance, ',');
        addBidirectionalEdge(stoi(sourceIndex), stoi(destinyIndex), stod(distance));
    }

    nodesFile.close();
    edgesFile.close();
    return 0;
}

void Graph::displayGraph() {
    for (auto& node : adjacencyList) {
        cout << "Node " << node.first << " connects to:\n";
        for (auto& edge : node.second) {
            cout << "  - Node " << edge.dest << " with weight " << edge.weight << "\n";
        }
    }
}

int Graph::createToyGraph(const string& filePath) {
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

        addDirectionalEdge(src, dst, dist);
    }

    file.close();
    return 0;
}

int Graph::createExtraGraphs(const string &edgesFilePath) {
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

    // Create nodes if they don't exist
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

void Graph::clearNodes() {
    for (auto& pair : nodes) {
        delete pair.second;
    }

    nodes.clear();
}

std::unordered_map<int, Node *> Graph::getNodes() {
    return nodes;
}

std::unordered_map<int, std::vector<Edge>> Graph::getEdges() {
    return adjacencyList;
}
