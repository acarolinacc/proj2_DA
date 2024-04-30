#include <iostream>
#include "src/Graph.h"
#include "src/Menu.h"

int main() {
    Graph g;
    Menu menu = Menu(g,0);
    menu.start();
    return 0;
}
