#include "Menu.h"
#include <unordered_set>

using namespace std;
using namespace std::chrono;

Menu::Menu(const Graph &graph, const int &graph_loaded): graph(graph), graph_loaded(graph_loaded) {}

void Menu::start(){
    bool running = true;

    cout << "\n|==================== TSP Explorer =======================|\n";
    cout << "|                                                         |\n";
    cout << "|             - Welcome to TSP Explorer -                 |\n";
    cout << "|                                                         |\n";
    cout << "|=========================================================|\n";
    cout << "|                                                         |\n";

    while (running) {
        string choice;
        cout << "|                      MAIN MENU                          |\n";
        cout << "|                                                         |\n";
        cout << "| 1 - Load Graph Data                                     |\n";
        cout << "| 2 - Backtracking Algorithm                              |\n";
        cout << "| 3 - Triangular Approximation Heuristic                  |\n";
        cout << "| 4 - Explore Additional Heuristics                       |\n";
        cout << "| 5 - TSP in the Real World                               |\n";
        cout << "| 6 - Algorithm Comparison                                |\n";
        cout << "| 7 - Program Assistance                                  |\n";
        cout << "| q - Exit Application                                    |\n";
        cout << "|                                                         |\n";
        cout << "| Select an option: ";
        getline(cin, choice);
        cout << "                                                           \n";


        if (choice == "1"){
            running = LoadMenu();
        }

        else if(choice == "2"){
            running = backtrackingMenu();
        }

        else if (choice == "3"){
            running = TriApproxMenu();
        }

        else if(choice == "4") {
            running = OtherHeuristicsMenu();
        }

        else if(choice == "5") {
            running = TSPRealWorldMenu();
        }

        else if(choice == "6")
            compareEfficiency();

        else if(choice == "7")
            helpMenu();

        else if(choice == "q"){
            quit();
            running = false;
        }
        else{
            cout << "| Not a valid input, please try again                      \n";
            cout << "|                                                          \n";
        }
    }

}

/*
 * -----------LOAD MENU----------- *
 */

bool Menu::LoadMenu() {
    bool running;


    while (true) {
        string choice;
        cout << "\n|================= Load Graph Options ==================|\n";
        cout << "|                                                       |\n";
        cout << "| 1 - Toy Graph: Small, manageable datasets for testing |\n";
        cout << "| 2 - Fully Connected Graph: Larger, complex datasets   |\n";
        cout << "|     that simulate ideal conditions.                   |\n";
        cout << "| 3 - Real-World Graph: Graphs based on realistic       |\n";
        cout << "|     scenarios and routes.                             |\n";
        cout << "| 4 - Help: Need assistance?                            |\n";
        cout << "| r - Return: Go back to the previous menu.             |\n";
        cout << "| q - Quit: Exit the program.                           |\n";
        cout << "|                                                       |\n";
        cout << "| Please choose an option: ";
        getline(cin, choice);
        cout << "                                                       \n";

        if(choice == "1") {
            running = toyGraphs();
            if (!running) return false;
            break;
        }

        else if(choice == "2"){
            running = extendedGraphs();
            if (!running) return false;
            break;
        }

        else if(choice == "3"){
            running = realWorldGraphs();
            if (!running) return false;
            break;
        }

        else if(choice == "4"){
            helpLoadMenu();
        }

        else if(choice == "r"){
            returnMenu();
            return true;
        }

        else if(choice == "q"){
            quit();
            return false;
        }

        else {
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Try again: ";
        }
    }

    return true;
}


/*
 * -----------LOAD'S MESSAGES MENU----------- *
 */

void Menu::graphLoaded() {
    cout << "\n|================= Graph Load Successful =================|\n";
    cout << "|                                                         |\n";
    cout << "|   Graph loaded successfully and ready for processing!   |\n";
    cout << "|                                                         |\n";
    cout << "|=========================================================|\n\n";
}

bool Menu::verifyLoadedGraph() {
    if (graph_loaded == 0) {
        cout << "\n|====================== Load Warning ======================|\n";
        cout << "|                                                         |\n";
        cout << "|  No graph loaded. Please load a suitable graph before   |\n";
        cout << "|  attempting to execute the Backtracking algorithm.       |\n";
        cout << "|  Ideal choices are small graphs due to computational     |\n";
        cout << "|  demands.                                               |\n";
        cout << "|                                                         |\n";
        cout << "|=========================================================|\n\n";
        return false;
    }
    return true;
}

bool Menu::verifyGraphTypeBacktracking() {
    if (graph_loaded == 0) {
        cout << "\n|====================== Load Warning ======================|\n";
        cout << "|                                                         |\n";
        cout << "|  No graph loaded. Please load a suitable graph before   |\n";
        cout << "|  attempting to execute the Backtracking algorithm.       |\n";
        cout << "|  Ideal choices are small graphs due to computational     |\n";
        cout << "|  demands.                                               |\n";
        cout << "|                                                         |\n";
        cout << "|=========================================================|\n\n";
        return false;
    } else if (graph_loaded == 3) {
        cout << "\n|==================== Real-World Warning ==================|\n";
        cout << "|                                                         |\n";
        cout << "|  A real-world graph is currently loaded. This type of   |\n";
        cout << "|  graph may be too large for the Backtracking algorithm  |\n";
        cout << "|  given its high computational demands. Please consider  |\n";
        cout << "|  loading a smaller graph, like Toy or Extra Connected   |\n";
        cout << "|  graphs, for efficient processing.                      |\n";
        cout << "|                                                         |\n";
        cout << "|=========================================================|\n\n";
        return false;
    }
    return true;
}

/*
 * --------------------------------- *
 */



/*
 * -----------TOY GRAPHS MENU----------- *
 */

bool Menu::toyGraphs(){


    while (true){
        string choice;
        cout << "\n|=========================== Toy Graphs ============================|\n";
        cout << "|                                                                   |\n";
        cout << "| 1 - Shipping                                                      |\n";
        cout << "| 2 - Stadiums                                                      |\n";
        cout << "| 3 - Tourism                                                       |\n";
        cout << "| r - Return to the previous page                                   |\n";
        cout << "| q - Quit the program                                              |\n";
        cout << "|                                                                   |\n";
        cout << "| Enter your choice: ";
        getline(cin, choice);
        cout << "                                                                   \n";

        if(choice == "1") {
            graph.clearNodes();
            graph.readToyGraph("../data/Toy-Graphs/Toy-Graphs/shipping.csv");
            graph_loaded = 1;
            break;
        }


        else if(choice == "2"){
            graph.clearNodes();
            graph.readToyGraph("../data/Toy-Graphs/Toy-Graphs/stadiums.csv");
            graph_loaded = 1;
            break;
        }

        else if(choice == "3"){
            graph.clearNodes();
            graph.readToyGraph("../data/Toy-Graphs/Toy-Graphs/tourism.csv");
            graph_loaded = 1;
            break;
        }

        else if(choice == "r"){
            returnMenu();
            return true;
        }

        else if(choice == "q"){
            quit();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Try again: ";
        }
    }
    graphLoaded();
    returnMenu();
    return true;
}

/*
 * --------------------------------- *
 */



/*
 * -----------EXTENDED GRAPHS MENU----------- *
 */


bool Menu::extendedGraphs() {
    while (true){
        string choice;
        cout << "\n|========================== Extended Graphs ========================|\n";
        cout << "|                                                                   |\n";
        cout << "| Choose the number of edges to use from the following ranges:      |\n";
        cout << "|   | 25 | 50 | 100 | 200 | 300 | 400 | 500 | 600 | 700 | 800 | 900 |\n";
        cout << "|                                                                   |\n";
        cout << "| r - Return to the previous page                                   |\n";
        cout << "| q - Quit the program                                              |\n";
        cout << "|                                                                   |\n";
        cout << "| Enter your value: ";
        getline(cin, choice);
        cout << "                                                                   \n";

        int choiceNum;
        try {
            choiceNum = stoi(choice);
        } catch (const invalid_argument& e) {
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Try again: ";
            continue;
        }

        if ((choiceNum >= 100 && choiceNum <= 900 && choiceNum % 100 == 0) || choiceNum == 25 || choiceNum == 50) {
            graph.clearNodes();
            graph.readExtraGraphs("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_" + choice + ".csv");
            graph_loaded = 2;
            break;
        }

        else if(choice == "r"){
            returnMenu();
            return true;
        }

        else if(choice == "q"){
            quit();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Try again: ";
        }
    }
    graphLoaded();
    returnMenu();
    return true;
}

/*
 * --------------------------------- *
 */



/*
 * -----------REAL WORLD GRAPHS MENU----------- *
 */

bool Menu::realWorldGraphs() {

    cout << "\n|============================= WARNING =============================|\n";
    cout << "| Dense graph creation times may vary:                             |\n";
    cout << "| - Graph 1 may take several seconds.                              |\n";
    cout << "| - Graph 3 may require several minutes. Consider this before you  |\n";
    cout << "|   proceed!                                                       |\n";
    cout << "|===================================================================|\n";

    while (true){
        string choice;
        cout << "\n|========================= Real World Graphs =======================|\n";
        cout << "|                                                                   |\n";
        cout << "| 1 - Graph 1 (1000 nodes)                                          |\n";
        cout << "| 2 - Graph 2 (5000 nodes)                                          |\n";
        cout << "| 3 - Graph 3 (10000 nodes)                                         |\n";
        cout << "| r - Return to the previous page                                   |\n";
        cout << "| q - Quit the program                                              |\n";
        cout << "|                                                                   |\n";
        cout << "| Enter your choice: ";
        getline(cin, choice);
        cout << "                                                                   \n";

        if(choice == "1") {
            graph.clearNodes();
            graph.readRealWorldGraph("../data/Real-world Graphs/Real-world Graphs/graph1/nodes.csv", "../data/Real-world Graphs/Real-world Graphs/graph1/edges.csv");
            graph_loaded = 31;
            break;
        }


        else if(choice == "2"){
            graph.clearNodes();
            graph.readRealWorldGraph("../data/Real-world Graphs/Real-world Graphs/graph2/nodes.csv", "../data/Real-world Graphs/Real-world Graphs/graph2/edges.csv");
            graph_loaded = 32;
            break;
        }

        else if(choice == "3"){
            graph.clearNodes();
            graph.readRealWorldGraph("../data/Real-world Graphs/Real-world Graphs/graph3/nodes.csv", "../data/Real-world Graphs/Real-world Graphs/graph3/edges.csv");
            graph_loaded = 33;
            break;
        }

        else if(choice == "r"){
            returnMenu();
            return true;
        }

        else if(choice == "q"){
            quit();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Try again: ";
        }
    }
    graphLoaded();
    returnMenu();
    return true;
}

/*
 * --------------------------------- *
 */




/*
 * -----------ALGORITHMS' DESCRIPTION MENU----------- *
 */

void Menu::algorithmDescription(int menu) {
    if (menu == 1) {
        cout << "\n|================ Algorithm Description ====================|\n";
        cout << "|                                                           |\n";
        cout << "| Backtracking is a brute-force approach that exhaustively  |\n";
        cout << "| explores all possible paths to find the optimal solution. |\n";
        cout << "| It is computationally intensive but ensures the best      |\n";
        cout << "| result.                                                   |\n";
        cout << "|                                                           |\n";
        cout << "|===========================================================|\n\n";
        cout << "                                                           \n";
        cout << "\n|================= Backtracking Menu =====================|\n";
        cout <<   "|                                                         |\n";

    }
    else if (menu == 2){
        cout << "\n|================ Algorithm Description ====================|\n";
        cout << "|                                                           |\n";
        cout << "| The Triangular Approximation Heuristic is a greedy        |\n";
        cout << "| algorithm that tries to find the best solution by always  |\n";
        cout << "| choosing the nearest neighbour. Therefore, the result is  |\n";
        cout << "| not guaranteed to be the best solution, because it relies |\n";
        cout << "| on the assumption that the nearest neighbour is the best  |\n";
        cout << "| choice and also because even if the nearest neighbour     |\n";
        cout << "| isn't connected to the current node, it will still be     |\n";
        cout << "| chosen by an approximation.                               |\n";
        cout << "|                                                           |\n";
        cout << "|===========================================================|\n\n";
        cout << "                                                           \n";
        cout << "\n|========= Triangular Approximation Heuristic Menu =======|\n";
    }
    else if(menu == 3){
        cout << "\n|================= Algorithm Description ===================|\n";
        cout << "|                                                           |\n";
        cout << "| This heuristic algorithm applies the nearest neighbor     |\n";
        cout << "| approach to solve the TSP problem. Starting from a        |\n";
        cout << "| designated node, it iteratively selects the nearest       |\n";
        cout << "| unvisited node until all nodes are visited, forming a     |\n";
        cout << "| path. Finally, the algorithm returns to the starting      |\n";
        cout << "| node, completing the tour.                                |\n";
        cout << "|                                                           |\n";
        cout << "| This implementation handles both fully connected and      |\n";
        cout << "| disconnected graphs. In the case of disconnected graphs,  |\n";
        cout << "| the algorithm will attempt to find a path visiting all    |\n";
        cout << "| reachable nodes. If a complete path is not possible, an   |\n";
        cout << "| error message will be displayed.                          |\n";
        cout << "|                                                           |\n";
        cout << "|===========================================================|\n\n";
        cout << "                                                             \n";
        cout << "\n|=============== Other Heuristics Menu ===================|\n";

    }
    else if(menu == 4){
        cout << "\n|================= Algorithm Description ====================|\n";
        cout << "|                                                            |\n";
        cout << "| This algorithm addresses the TSP in real-world graphs,     |\n";
        cout << "| which are often not fully connected. The process involves  |\n";
        cout << "| a Depth-First Search (DFS) to ensure all nodes are         |\n";
        cout << "| reachable from the starting point. If a complete path is   |\n";
        cout << "| not possible, an error message is displayed. Otherwise,    |\n";
        cout << "| the Nearest Neighbor heuristic is used to find a feasible  |\n";
        cout << "| tour. This heuristic iteratively selects the closest       |\n";
        cout << "| unvisited node until all nodes are visited, then returns   |\n";
        cout << "| to the starting node. The algorithm also handles           |\n";
        cout << "| disconnected graphs by attempting to find a path visiting  |\n";
        cout << "| all reachable nodes.                                       |\n";
        cout << "|                                                            |\n";
        cout << "|============================================================|\n\n";
        cout << "                                                             \n";
        cout <<   "\n|============== TSP in the Real World Menu ===============|\n";
    }


}

/*
 * --------------------------------- *
 */




/*
 * -----------BACKTRACKING MENU----------- *
 */

bool Menu::backtrackingMenu() {
    if(!verifyGraphTypeBacktracking()) return true;

    string backtrackingChoice;

    cout << "\n|================= Backtracking Menu =====================|\n";
    cout << "|                                                         |\n";

    while (true) {
        cout << "| 1 - Execute Algorithm                                   |\n";
        cout << "| 2 - Algorithm Details                                   |\n";
        cout << "| r - Return to Main Menu                                 |\n";
        cout << "| q - Exit Program                                        |\n";
        cout << "|                                                         |\n";
        cout << "| Select an option: ";
        getline(cin, backtrackingChoice);
        cout << "                                                         \n";

        if(backtrackingChoice == "1"){
            backtrackingAlgorithm();
        }

        else if(backtrackingChoice == "2"){
            algorithmDescription(1);
        }

        else if(backtrackingChoice == "r"){
            returnMenu();
            return true;
        }

        else if(backtrackingChoice == "q"){
            quit();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options bellow:                         \n";
        }
    }
}

// 4.1. Backtracking Algorithm
void Menu::backtrackingAlgorithm() {
    auto start_time = chrono::high_resolution_clock::now();

    std::pair<std::vector<Node*>, double> minPathAndCost = Algorithms::tspBacktracking(graph);

    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time);

    std::vector<Node*> min_path = minPathAndCost.first;
    double min_cost = minPathAndCost.second;

    cout << "\n\nThe minimal path is as follows:\n";
    for (size_t i = 0; i < min_path.size(); ++i) {
        if (i > 0) {
            cout << " -> ";
        }
        cout << min_path[i]->getId();
    }
    cout << "\n";
    cout << "\nThe minimal distance of the path is: " << min_cost << " meters \n";
    cout << "\n";
    cout << "Time taken: " << duration.count() << " milliseconds\n\n";
}

/*
 * --------------------------------- *
 */




/*
 * -----------TRIANGULAR APPROXIMATION MENU----------- *
 */

// 4.2. Triangular Approximation Heuristic

bool Menu::TriApproxMenu() {
    if (!verifyLoadedGraph()) return true;

    string triAproxChoice;

    cout << "\n|========= Triangular Approximation Heuristic Menu =======|\n";

    while (true) {
        cout << "|                                                         |\n";
        cout << "| 1 - Execute Algorithm                                   |\n";
        cout << "| 2 - Algorithm Details                                   |\n";
        cout << "| r - Return to Main Menu                                 |\n";
        cout << "| q - Exit Program                                        |\n";
        cout << "|                                                         |\n";
        cout << "| Select an option: ";
        getline(cin, triAproxChoice);
        cout << "                                                           \n";

        if (triAproxChoice == "1") {
            vector<int> path;
            auto start = chrono::high_resolution_clock::now();
            double totalDistance = Algorithms::triangularApproximationHeuristic(graph, path);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;

            cout << " The approximate distance is " << totalDistance << " meters";
            for(int i = 0; i < 59 - 40; i++){
                cout << " ";
            }
            cout << "\n";

            cout << " Total time elapsed: " << elapsed.count() << " seconds";
            for(int i = 0; i < 59 - 29 - to_string(elapsed.count()).length(); i++){
                cout << " ";
            }
            int charCounter = 1;
            cout << "                                                           \n";
            cout << " The path is:                                              \n";
            cout << " ";
            for (size_t i = 0; i < path.size(); ++i) {
                charCounter += (4 + to_string(path[i]).length());
                if (charCounter > 58) {
                    for (int j = 0; j < 59 - charCounter + to_string(path[i]).length() + 4; ++j) {
                        cout << " ";
                    }
                    cout << "\n";
                    cout << " ";
                    charCounter = (1 + 4 + to_string(path[i]).length());
                }
                if (i == path.size() - 1) {
                    cout << path[i];
                    charCounter -= 4;
                } else {
                    cout << path[i] << " -> ";
                }
            }
            cout << "\n";
        } else if (triAproxChoice == "2") {
            algorithmDescription(2);
        } else if (triAproxChoice == "r") {
            returnMenu();
            return true;
        } else if (triAproxChoice == "q") {
            quit();
            return false;
        } else {
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options below:                          |\n";
        }
    }
}


/*
 * --------------------------------- *
 */




/*
 * -----------OTHER HEURISTICS MENU----------- *
 */

// 4.3.Other Heuristics
bool Menu::OtherHeuristicsMenu() {
    if(!verifyLoadedGraph()) return true;

    string otherHeuristicsChoice;

    cout << "\n|=============== Other Heuristics Menu ===================|\n";
    cout << "|                                                         |\n";
    while(true){
        cout << "|                                                         |\n";
        cout << "| 1 - Execute Nearest Neighbor Heuristic                  |\n";
        cout << "| 2 - Algorithm Details                                   |\n";
        cout << "| r - Return to Main Menu                                 |\n";
        cout << "| q - Exit Program                                        |\n";
        cout << "|                                                         |\n";
        cout << "| Select an option: ";
        getline(cin, otherHeuristicsChoice);
        cout << "                                                           \n";

        if(otherHeuristicsChoice == "1"){
            otherHeuristicsAlgorithm();
        }

        else if(otherHeuristicsChoice == "2"){
            algorithmDescription(3);
        }

        else if(otherHeuristicsChoice == "r"){
            returnMenu();
            return true;
        }

        else if(otherHeuristicsChoice == "q"){
            quit();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options bellow:                         \n";
        }
    }
}

void Menu::otherHeuristicsAlgorithm() {
    vector<int> path;
    auto start = std::chrono::high_resolution_clock::now();
    double distance = Algorithms::nearestNeighborHeuristic(graph, path);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "\n|========= Nearest Neighbor Heuristic =========|\n";
    cout << "                                              \n";
    cout << " Total distance: " << distance << " meters    \n";
    cout << " Time elapsed: " << duration << " ms          \n";
    cout << "                                              \n";
    cout << " Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << " \n";
    cout << "|==============================================|\n";
}

/*
 * --------------------------------- *
 */


/*
 * -----------TSP REAL WORLD MENU----------- *
 */

bool Menu::TSPRealWorldMenu() {
    if(!verifyLoadedGraph()) return true;

    string TSPRealWorldChoice;

    cout <<   "\n|============== TSP in the Real World Menu ===============|\n";
    while(true){
        cout << "|                                                         |\n";
        cout << "| 1 - Execute Algorithm                                   |\n";
        cout << "| 2 - Algorithm Details                                   |\n";
        cout << "| r - Return to Main Menu                                 |\n";
        cout << "| q - Exit Program                                        |\n";
        cout << "|                                                         |\n";
        cout << "| Select an option: ";
        getline(cin, TSPRealWorldChoice);
        cout << "                                                           \n";

        if(TSPRealWorldChoice == "1"){
            SelectionRealWorldNodeIndex();
        }

        else if(TSPRealWorldChoice == "2"){
            algorithmDescription(4);
        }

        else if(TSPRealWorldChoice == "r"){
            returnMenu();
            return true;
        }

        else if(TSPRealWorldChoice == "q"){
            quit();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options below:                         \n";
        }
    }
}

bool Menu::SelectionRealWorldNodeIndex() {
    if(!verifyLoadedGraph()) return true;

    string TSPRealWorldChoice;

    cout << "\n|================= TSP in the Real World Menu =====================|\n";
    cout << "|                                                                  |\n";
    while(true) {
        cout << "| Graph 1 (0 -> 999)                                               |\n";
        cout << "| Graph 2 (0 -> 4999)                                              |\n";
        cout << "| Graph 3 (0 -> 9999)                                              |\n";
        cout << "| r - Return to Main Menu                                          |\n";
        cout << "| q - Exit Program                                                 |\n";
        cout << "|                                                                  |\n";
        cout << "| Please select a number according to the graph loaded             |\n";
        cout << "| Select an option: ";
        getline(cin, TSPRealWorldChoice);
        cout << "                                                                  \n";

        // Graph 1
        if (stoi(TSPRealWorldChoice) >= 0 && stoi(TSPRealWorldChoice) <= 999 && graph_loaded == 31) {
            RealWorldCase(stoi(TSPRealWorldChoice), graph, algorithms);
            return true;
        }
        // Graph 2
        if (stoi(TSPRealWorldChoice) >= 0 && stoi(TSPRealWorldChoice) <= 4999 && graph_loaded == 32) {
            RealWorldCase(stoi(TSPRealWorldChoice), graph, algorithms);
            return true;
        }
        // Graph 3
        if (stoi(TSPRealWorldChoice) >= 0 && stoi(TSPRealWorldChoice) <= 9999 && graph_loaded == 33) {
            RealWorldCase(stoi(TSPRealWorldChoice), graph, algorithms);
            return true;
        }
        // Shipping
        /*
        if (stoi(TSPRealWorldChoice) >= 0 && stoi(TSPRealWorldChoice) <= 13 && graph_loaded == 1) {
            RealWorldCase(stoi(TSPRealWorldChoice), graph, algorithms);
            return true;
        }*/

        if (TSPRealWorldChoice == "r") {
            returnMenu();
            return true;
        }

        if (TSPRealWorldChoice == "q") {
            quit();
            return false;
        } else {
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options below:                         \n";
        }
    }
}

bool Menu::RealWorldCase(int StartIndexNode, Graph& Real, Algorithms& algorithms) {
    algorithms.runRealWorldTSP(Real, StartIndexNode);
    return true;
}


/*
 * --------------------------------- *
 */

void Menu::compareEfficiency() {
    cout << "\n|=============== Compare Efficiency Menu =================|\n";
    cout << "|                                                         |\n";

    cout << "| Select the algorithms you want to compare:              |\n";
    cout << "| 1 - Backtracking Algorithm                              |\n";
    cout << "| 2 - Triangular Approximation Heuristic                  |\n";
    cout << "| 3 - Nearest Neighbor Heuristic                          |\n";
    cout << "| 4 - Real-World TSP Algorithm                            |\n";
    cout << "| r - Return to Main Menu                                 |\n";
    cout << "|                                                         |\n";
    cout << "| Enter your choice (e.g., 1 2 3 for multiple selections): ";

    string choices;
    getline(cin, choices);

    if (choices == "r") {
        return;
    }

    vector<int> selectedAlgorithms;
    istringstream ss(choices);
    int choice;
    while (ss >> choice) {
        if (choice >= 1 && choice <= 4) {
            selectedAlgorithms.push_back(choice);
        }
    }

    if (selectedAlgorithms.empty()) {
        cout << "| Invalid selection. Returning to main menu.              |\n";
        return;
    }

    cout << "\n|================= Comparing Algorithms ==================|\n";
    cout <<   "                                                          \n";


    for (int algo : selectedAlgorithms) {
        auto start_time = chrono::high_resolution_clock::now();
        double totalDistance = 0.0;
        vector<int> tour;

        switch (algo) {
            case 1:
                cout << "| Running Backtracking Algorithm...                        \n";
                {
                    auto result = algorithms.tspBacktracking(graph);
                    totalDistance = result.second;
                    for (auto node : result.first) {
                        tour.push_back(node->getId());
                    }
                }
                break;
            case 2:
                cout << "| Running Triangular Approximation Heuristic...            \n";
                totalDistance = algorithms.triangularApproximationHeuristic(graph, tour);
                break;
            case 3:
                cout << "| Running Nearest Neighbor Heuristic...                    \n";
                totalDistance = algorithms.nearestNeighborHeuristic(graph, tour);
                break;
            case 4:
                cout << "| Running Real-World TSP Algorithm...                      \n";
                {
                    int startNode = 0;
                    algorithms.runRealWorldTSP(graph, startNode);
                }
                break;
            default:
                break;
        }

        auto stop_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time);

        cout << "| Algorithm " << algo << " completed.                     \n";
        cout << "| Total Distance: " << totalDistance << " meters          \n";
        cout << "| Time taken: " << duration.count() << " milliseconds     \n";
        cout << "| Path: ";
        for (size_t i = 0; i < tour.size(); ++i) {
            if (i > 0) {
                cout << " -> ";
            }
            cout << tour[i];
        }
        cout << "\n                                                         \n";
    }

    cout << "|=========================================================|\n";
}



/*
 * -----------MESSAGES MENUS----------- *
 */

bool Menu::messageLoop() {
    string helpChoice;
    while (true) {
        getline(cin, helpChoice);
        cout << "|                                                           |\n";

        if (helpChoice == "back") {
            returnMenu();
            return false;
        } else if (helpChoice == "stay"){
            return true;

        } else {
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Try again: ";
        }
    }
}

void Menu::helpMenu() {
    cout << "\n|===================== Help Overview =====================|\n";
    cout << "|                                                         |\n";
    cout << "| 1 - Load Graph: Allows you to import graph data from a  |\n";
    cout << "|     file. Available types: Toy Graphs, Fully-Connected  |\n";
    cout << "|     Graphs, and Real-World Graphs.                      |\n";
    cout << "| 2 - Backtracking Algorithm: Executes a complete search  |\n";
    cout << "|     to identify the shortest possible tour through all  |\n";
    cout << "|     nodes.                                              |\n";
    cout << "| 3 - Triangular Heuristic: Uses the triangular           |\n";
    cout << "|     inequality to estimate a near-optimal path with     |\n";
    cout << "|     improved efficiency.                                |\n";
    cout << "| 4 - Other Heuristics: Explore additional heuristic      |\n";
    cout << "|     strategies developed by our team to find efficient  |\n";
    cout << "|     routes across the graphs.                           |\n";
    cout << "| 5 - TSP in the Real World: Handles real-world graphs    |\n";
    cout << "|     which are often not fully connected. Ensures a      |\n>";
    cout << "|     feasible tour using Depth-First Search (DFS) to     |\n>";
    cout << "|     verify reachability and the Nearest Neighbor        |\n>";
    cout << "|     heuristic to find a practical route.                |\n>";
    cout << "|                                                         |\n>";
    cout << "| Usage Tips: Start by loading a graph to set up the      |\n>";
    cout << "|     environment. Subsequently, you can execute the      |\n>";
    cout << "|     algorithms to discover the shortest routes.         |\n>";
    cout << "|                                                         |\n>";
    cout << "|=========================================================|\n>";
    cout << "                                                         \n>";
}



void Menu::returnMenu() {
    cout << "\n|=========================================================|\n";
    cout << "|                                                         |\n";
    cout << "| Ready to navigate? Choose an option to proceed.         |\n";
    cout << "|                                                         |\n";
    cout << "|=========================================================|\n";
}

void Menu::quit() {
    cout << "\n|=========================================================|\n";
    cout << "|                                                         |\n";
    cout << "| It's been a pleasure helping you navigate.              |\n";
    cout << "| Thank you for using TSP Explorer!                       |\n";
    cout << "| Have a great day!                                       |\n";
    cout << "|                                                         |\n";
    cout << "|=========================================================|\n";
}

/*
 * -----------HELP MENU----------- *
 */

void Menu::helpLoadMenu() {
    bool running = true;
    while(running) {
        string helpChoice;

        cout << "\n|======================= Help: Graph Loading ======================|\n";
        cout << "|                                                                   |\n";
        cout << "| 1 - Toy Graph: Load small-scale graphs ideal for initial testing. |\n";
        cout << "| 2 - Fully Connected Graph: Load larger, fully connected graphs.   |\n";
        cout << "| 3 - Real World Graph: Load graphs simulating real-world scenarios.|\n";
        cout << "|                                                                   |\n";
        cout << "| Type 'back' to return to the previous menu                        |\n";
        cout << "| Enter your choice: ";
        running = messageLoop();
        cout << "|                                                                   |\n";
    }
}