
#ifndef PROJETO_2_MENU_H
#define PROJETO_2_MENU_H

#include <iostream>
#include <limits>
#include <string>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#include "Graph.h"

class Menu {
protected:
    Graph graph;
    int graph_loaded;
public:
    explicit Menu(const Graph &graph, const int &graph_loaded);

    void start();

    void helpMainMenu();

    void returnMessage();

    void quitMessage();

    bool verifyLoadedGraph();

    bool feedbackLoop();

    static void algorithmDescription(int menu);

    bool startLoadMenu();

    void helpLoadMenu();

    bool toyGraphs();

    bool extendedGraphs();

    bool realWorldGraphs();

    void graphLoaded();

    /*
     * -----------BACKTRACKING MENU----------- *
     */

    bool verifyGraphTypeBacktracking();

    bool startBacktrackingMenu();


    /*
     * -----------TRIANGULAR APPROXIMATION HEURISTIC MENU----------- *
     */

    bool startTriApproxMenu();

    /*
     * -----------OTHER HEURISTIC MENU----------- *
     */

    bool startOtherHeuristicsMenu();

    /*
     * -----------Real World Menu----------- *
     */
    bool startTSPRealWorldMenu();

    bool SelectionRealWorldNodeIndex();
    bool RealWorldCase(int StartIndexNode, Graph& Real);

};




#endif
