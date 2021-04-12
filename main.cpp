#include <iostream>
#include "Structure/Reticular/Graph_Adjacent_List.hpp"
#include "Structure/Reticular/Graph_Adjacent_Matrix.hpp"

int main() {
    Adjacent_List<5, false, false> _gh1 {};
    _gh1.insert_edge(1,2);
    _gh1.insert_edge(1,3);
    _gh1.insert_edge(2,4);
    _gh1.insert_edge(2,4);
    _gh1.insert_edge(4,5);
    _gh1.BFS(std::cout, 1);
    _gh1.DFS(std::cout, 1);

    std::cout << "Debug Hook" << std::endl;
}