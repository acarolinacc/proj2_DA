
#ifndef PROJETO_2_MENU_H
#define PROJETO_2_MENU_H

#include <iostream>
#include <limits>
#include <string>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#include "Graph.h"
#include "Algorithms.h"

class Menu {
protected:
    Graph graph;
    Algorithms algorithms;
    int graph_loaded;
public:
    explicit Menu(const Graph &graph, const int &graph_loaded);

    void start();

    void helpMenu();

    void returnMenu();

    void quit();

    bool verifyLoadedGraph();

    bool messageLoop();

    static void algorithmDescription(int menu);

    bool LoadMenu();

    void helpLoadMenu();

    bool toyGraphs();

    bool extendedGraphs();

    bool realWorldGraphs();

    void graphLoaded();

    /*
     * -----------BACKTRACKING MENU----------- *
     */

    bool verifyGraphTypeBacktracking();

    bool backtrackingMenu();
    void backtrackingAlgorithm();


    /*
     * -----------TRIANGULAR APPROXIMATION HEURISTIC MENU----------- *
     */

    bool TriApproxMenu();

    /*
     * -----------OTHER HEURISTIC MENU----------- *
     */
    void otherHeuristicsAlgorithm();

    bool OtherHeuristicsMenu();

    /*
     * -----------TSPRealWorld----------- *
     */
    bool TSPRealWorldMenu();

    bool RealWorldCase(int StartIndexNode, Graph& Real, Algorithms& algorithms) ;

    bool SelectionRealWorldNodeIndex();

    void compareEfficiency();

};




#endif
