#include <iostream>
#include "src/Graph.h"
#include "src/Menu.h"

int main() {
    Graph g;
    Menu menu = Menu(g,0);
    menu.start();
    return 0;
}


/*
#include <iostream>
#include "src/Graph.h"
#include "src/Menu.h"

int main() {
    Graph graph;

    // Test loading a toy graph
    std::cout << "Loading toy graph (tourism.csv)..." << std::endl;
    if (graph.readToyGraph("../data/Toy-Graphs/Toy-Graphs/tourism.csv") == 0) {
        std::cout << "Toy graph loaded successfully:" << std::endl;
        graph.displayGraph();
    } else {
        std::cerr << "Failed to load toy graph." << std::endl;
    }

    graph.clearNodes();

    // Test loading an extra graph
    std::cout << "Loading extra graph (edges_25.csv)..." << std::endl;
    if (graph.readExtraGraphs("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_25.csv") == 0) {
        std::cout << "Extra graph loaded successfully:" << std::endl;
        graph.displayGraph();
    } else {
        std::cerr << "Failed to load extra graph." << std::endl;
    }

    graph.clearNodes();

    // Test loading a real-world graph
    std::cout << "Loading real-world graph (nodes.csv and edges.csv)..." << std::endl;
    if (graph.readRealWorldGraph("../data/Real-world Graphs/Real-world Graphs/graph1/nodes.csv", "../data/Real-world Graphs/Real-world Graphs/graph1/edges.csv") == 0) {
        std::cout << "Real-world graph loaded successfully:" << std::endl;
        graph.displayGraph();
    } else {
        std::cerr << "Failed to load real-world graph." << std::endl;
    }

    return 0;
}

 */