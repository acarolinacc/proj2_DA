#include "Menu.h"
using namespace std;

Menu::Menu(const Graph &graph, const int &graph_loaded): graph(graph), graph_loaded(graph_loaded) {}

void Menu::start(){
    bool running = true;

    cout << "\n|==================== TSP Explorer ====================|\n";
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
        cout << "| 2 - Execute Backtracking Solver                         |\n";
        cout << "| 3 - Apply Triangular Heuristic                          |\n";
        cout << "| 4 - Explore Additional Heuristics                       |\n";
        cout << "| 5 - Tackle Real-World TSP Scenarios                     |\n";
        cout << "| 6 - Program Assistance                                  |\n";
        cout << "| q - Exit Application                                    |\n";
        cout << "|                                                         |\n";
        cout << "| Select an option: ";
        getline(cin, choice);
        cout << "|                                                         |\n";


        if (choice == "1"){
            running = startLoadMenu();
        }

        else if(choice == "2"){
            running = startBacktrackingMenu();
        }

        else if (choice == "3"){
            running = startTriApproxMenu();
        }

        else if(choice == "4") {
            running = startOtherHeuristicsMenu();
        }

        else if(choice == "5") {
            running = startTSPRealWorldMenu();
        }

        else if(choice == "6")
            helpMainMenu();

        else if(choice == "q"){
            quitMessage();
            running = false;
        }
        else{
            cout << "| Not a valid input, please try again                      \n";
            cout << "|                                                          \n";
        }
    }

}

void Menu::helpMainMenu() {
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
    cout << "|                                                         |\n";
    cout << "| Usage Tips: Start by loading a graph to set up the      |\n";
    cout << "|     environment. Subsequently, you can execute the      |\n";
    cout << "|     algorithms to discover the shortest routes.         |\n";
    cout << "|                                                         |\n";
    cout << "|=========================================================|\n";
    cout << "|                                                         |\n";
}


void Menu::returnMessage() {
    cout << "\n|=========================================================|\n";
    cout << "|                                                         |\n";
    cout << "| Ready to navigate? Choose an option to proceed.         |\n";
    cout << "|                                                         |\n";
    cout << "|=========================================================|\n";
}

void Menu::quitMessage() {
    cout << "\n|=========================================================|\n";
    cout << "|                                                         |\n";
    cout << "| It's been a pleasure helping you navigate.              |\n";
    cout << "| Thank you for using TSP Explorer!                       |\n";
    cout << "| Have a great day!                                       |\n";
    cout << "|                                                         |\n";
    cout << "|=========================================================|\n";
}


bool Menu::feedbackLoop() {
    string helpChoice;
    while (true) {
        getline(cin, helpChoice);
        cout << "|                                                           |\n";

        if (helpChoice == "back") {
            returnMessage();
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

bool Menu::startLoadMenu() {
    bool running;

    cout << "|-----------------------------------------------------------|\n";
    cout << "|                                                           |\n";

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
        cout << "|                                                       |\n";

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
            returnMessage();
            return true;
        }

        else if(choice == "q"){
            quitMessage();
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
        running = feedbackLoop();
        cout << "|                                                                   |\n";
    }
}


bool Menu::toyGraphs(){

    cout << "|-----------------------------------------------------------|\n";
    cout << "|                                                           |\n";

    while (true){
        string choice;
        cout << "\n|=========================== Toy Graphs ===========================|\n";
        cout << "|                                                                   |\n";
        cout << "| 1 - Shipping                                                      |\n";
        cout << "| 2 - Stadiums                                                      |\n";
        cout << "| 3 - Tourism                                                       |\n";
        cout << "| r - Return to the previous page                                   |\n";
        cout << "| q - Quit the program                                              |\n";
        cout << "|                                                                   |\n";
        cout << "| Enter your choice: ";
        getline(cin, choice);
        cout << "|                                                                   |\n";

        if(choice == "1") {
            graph.clearNodes();
            graph.createToyGraph("../data/Toy-Graphs/Toy-Graphs/shipping.csv");
            graph_loaded = 1;
            break;
        }


        else if(choice == "2"){
            graph.clearNodes();
            graph.createToyGraph("../data/Toy-Graphs/Toy-Graphs/stadiums.csv");
            graph_loaded = 1;
            break;
        }

        else if(choice == "3"){
            graph.clearNodes();
            graph.createToyGraph("../data/Toy-Graphs/Toy-Graphs/tourism.csv");
            graph_loaded = 1;
            break;
        }

        else if(choice == "r"){
            returnMessage();
            return true;
        }

        else if(choice == "q"){
            quitMessage();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Try again: ";
        }
    }
    graphLoaded();
    returnMessage();
    return true;
}

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
        cout << "|                                                                   |\n";

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
            graph.createExtraGraphs("../data/Extra_Fully_Connected_Graphs/Extra_Fully_Connected_Graphs/edges_" + choice + ".csv");
            graph_loaded = 2;
            break;
        }

        else if(choice == "r"){
            returnMessage();
            return true;
        }

        else if(choice == "q"){
            quitMessage();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Try again: ";
        }
    }
    graphLoaded();
    returnMessage();
    return true;
}

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
        cout << "|                                                                   |\n";

        if(choice == "1") {
            graph.clearNodes();
            graph.createRealWorldGraph("../data/Real-world Graphs/Real-world Graphs/graph1/nodes.csv", "../data/Real-world Graphs/Real-world Graphs/graph1/edges.csv");
            graph_loaded = 31;
            break;
        }


        else if(choice == "2"){
            graph.clearNodes();
            graph.createRealWorldGraph("../data/Real-world Graphs/Real-world Graphs/graph2/nodes.csv", "../data/Real-world Graphs/Real-world Graphs/graph2/edges.csv");
            graph_loaded = 32;
            break;
        }

        else if(choice == "3"){
            graph.clearNodes();
            graph.createRealWorldGraph("../data/Real-world Graphs/Real-world Graphs/graph3/nodes.csv", "../data/Real-world Graphs/Real-world Graphs/graph3/edges.csv");
            graph_loaded = 33;
            break;
        }

        else if(choice == "r"){
            returnMessage();
            return true;
        }

        else if(choice == "q"){
            quitMessage();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Try again: ";
        }
    }
    graphLoaded();
    returnMessage();
    return true;
}

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
    } else if (graph_loaded == 31 || graph_loaded ==  32 || graph_loaded ==  33) {
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

bool Menu::startBacktrackingMenu() {
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
        cout << "|                                                         |\n";

        if(backtrackingChoice == "1"){
            // backtrackingAlgorithm();
        }

        else if(backtrackingChoice == "2"){
            algorithmDescription(1);
        }

        else if(backtrackingChoice == "r"){
            returnMessage();
            return true;
        }

        else if(backtrackingChoice == "q"){
            quitMessage();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options bellow:                         \n";
        }
    }
}

void Menu::algorithmDescription(int menu) {
    if (menu == 1) {
        cout << "\n|================ Algorithm Description ==================|\n";
        cout << "|                                                         |\n";
        cout << "| Backtracking is a brute-force approach that exhaustively|\n";
        cout << "| explores all possible paths to find the optimal solution.|\n";
        cout << "| It is computationally intensive but ensures the best    |\n";
        cout << "| result.                                                  |\n";
        cout << "|                                                         |\n";
        cout << "|=========================================================|\n\n";
        cout << "|                                                           |\n";
        cout << "\n|================= Backtracking Menu =====================|\n";
    }
    else if (menu == 2){
        cout << "\n|================ Algorithm Description ==================|\n";
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
        cout << "|=========================================================|\n\n";
        cout << "|                                                           |\n";
        cout << "\n|================= Triangular Approximation Heuristic Menu =====================|\n";
    }
    else if(menu == 3){
        cout << "\n|================ Algorithm Description ==================|\n";
        cout << "|                                                           |\n";
        cout << "|   The Real World Heuristic uses an DFS to check if there  |\n";
        cout << "|   is a path which travels along all the nodes, if such    |\n";
        cout << "|   exists then it will calculate the fastest way of doing. |\n";
        cout << "|=========================================================|\n\n";
        cout << "|                                                           |\n";
        cout << "\n|================= Other Heuristics Menu =====================|\n";
    }
}

// TO-DO : 4.1. Backtracking Algorithm
// void Menu::backtrackingAlgorithm() {}

bool Menu::startTriApproxMenu() {
    if(!verifyLoadedGraph()) return true;

    string triAproxChoice;

    cout << "\n|================= Triangular Approximation Heuristic Menu =====================|\n";

    while(true){
        cout << "|                                                           |\n";
        cout << "| 1 - Execute Algorithm                                   |\n";
        cout << "| 2 - Algorithm Details                                   |\n";
        cout << "| r - Return to Main Menu                                 |\n";
        cout << "| q - Exit Program                                        |\n";
        cout << "|                                                         |\n";
        cout << "| Select an option: ";
        getline(cin, triAproxChoice);
        cout << "|                                                           |\n";

        if(triAproxChoice == "1"){
            // triApproxAlgorithm();
        }

        else if(triAproxChoice == "2"){
            algorithmDescription(2);
        }

        else if(triAproxChoice == "r"){
            returnMessage();
            return true;
        }

        else if(triAproxChoice == "q"){
            quitMessage();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options bellow:                         \n";
        }
    }
}

// TO-DO : 4.2. Triangular Approximation Heuristic
// void Menu::triApproxAlgorithm() {}

// TO-DO : 4.3.Other Heuristics
bool Menu::startOtherHeuristicsMenu() {
    if(!verifyLoadedGraph()) return true;

    string otherHeuristicsChoice;

    cout << "\n|================= Other Heuristics Menu =====================|\n";
    cout << "|                                                           |\n";
    while(true){
        cout << "|                                                           |\n";
        cout << "| 1 - Execute Algorithm                                   |\n";
        cout << "| 2 - Algorithm Details                                   |\n";
        cout << "| r - Return to Main Menu                                 |\n";
        cout << "| q - Exit Program                                        |\n";
        cout << "|                                                         |\n";
        cout << "| Select an option: ";
        getline(cin, otherHeuristicsChoice);
        cout << "|                                                           |\n";

        if(otherHeuristicsChoice == "1"){
            // ourHeuristicsAlgorithm();
        }

        // ...

        else if(otherHeuristicsChoice == "2"){
            algorithmDescription(3);
        }

        else if(otherHeuristicsChoice == "r"){
            returnMessage();
            return true;
        }

        else if(otherHeuristicsChoice == "q"){
            quitMessage();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options bellow:                         \n";
        }
    }
}

// void Menu::ourHeuristicsAlgorithm() {}

//TO-DO : 4.4. TSP in the Real World

bool Menu::startTSPRealWorldMenu() {
    if(!verifyLoadedGraph()) return true;

    string TSPRealWorldChoice;

    cout << "\n|================= TSP in the Real World Menu =====================|\n";
    cout << "|                                                           |\n";
    while(true){
        cout << "|                                                           |\n";
        cout << "| 1 - Execute Algorithm                                   |\n";
        cout << "| 2 - Algorithm Details                                   |\n";
        cout << "| r - Return to Main Menu                                 |\n";
        cout << "| q - Exit Program                                        |\n";
        cout << "|                                                         |\n";
        cout << "| Select an option: ";
        getline(cin, TSPRealWorldChoice);
        cout << "|                                                           |\n";

        if(TSPRealWorldChoice == "1"){
            SelectionRealWorldNodeIndex();
        }

        else if(TSPRealWorldChoice == "2"){
            algorithmDescription(3);
        }

        else if(TSPRealWorldChoice == "r"){
            returnMessage();
            return true;
        }

        else if(TSPRealWorldChoice == "q"){
            quitMessage();
            return false;
        }

        else{
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options bellow:                         \n";
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
        cout << "| Shipping (0 -> 13)                                               |\n";
        cout << "| r - Return to Main Menu                                          |\n";
        cout << "| q - Exit Program                                                 |\n";
        cout << "|                                                                  |\n";
        cout << "| Please select a number according to the graph loaded             |\n";
        cout << "| Select an option: ";
        getline(cin, TSPRealWorldChoice);
        cout << "|                                                                  |\n";

        //Caso Graph 1
        if (stoi(TSPRealWorldChoice) >= 0 && stoi(TSPRealWorldChoice) <= 999 && graph_loaded == 31) {
            RealWorldCase(stoi(TSPRealWorldChoice), graph);
            return true;
        }
        //Caso Graph 2
        if (stoi(TSPRealWorldChoice) >= 0 && stoi(TSPRealWorldChoice) <= 4999 && graph_loaded == 32) {
            RealWorldCase(stoi(TSPRealWorldChoice), graph);
            return true;
        }
        //Caso Graph 3
        if (stoi(TSPRealWorldChoice) >= 0 && stoi(TSPRealWorldChoice) <= 9999 && graph_loaded == 33) {
            RealWorldCase(stoi(TSPRealWorldChoice), graph);
            return true;
        }
        //Caso Shipping
        if (stoi(TSPRealWorldChoice) >= 0 && stoi(TSPRealWorldChoice) <= 13 && graph_loaded == 1) {
            RealWorldCase(stoi(TSPRealWorldChoice), graph);
            return true;
        }

        if (TSPRealWorldChoice == "r") {
            returnMessage();
            return true;
        }

        if (TSPRealWorldChoice == "q") {
            quitMessage();
            return false;
        } else {
            cout << "| Invalid selection. Please enter a valid option.          |\n";
            cout << "|                                                           |\n";
            cout << "| Select one of the options bellow:                         \n";
        }
    }
}