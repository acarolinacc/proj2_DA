cmake_minimum_required(VERSION 3.23)
project(proj2_DA)

set(CMAKE_CXX_STANDARD 17)

add_executable(proj2_DA
        .idea/.gitignore
        .idea/modules.xml
        .idea/proj2_DA.iml
        .idea/vcs.xml
        .idea/workspace.xml
        src/Graph.cpp
        src/Graph.h
        src/Menu.cpp
        src/Menu.h
        src/Edge.cpp
        src/Edge.h
        src/Node.cpp
        src/Node.h
        src/Algorithms.cpp
        src/Algorithms.h
        src/MutablePriorityQueue.h
        main.cpp
        README.md)
