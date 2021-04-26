#include <iostream>
#include <sstream>
#include <vector>
#include "Structure/Dendroid/Red_Black_Tree.hpp"
#include "Structure/Dendroid/Binary_Tree.hpp"
#include "Normal_Algorithm/Sort/Quick_Sort_Algorithm.hpp"

int main() {
    std::vector<int> _vec {27, -2, 5, 13, 32, -7, 11, 2};
    quick_sort<int>(std::rbegin(_vec), std::rend(_vec));

    std::cout << "Debug Hook" << std::endl;
}