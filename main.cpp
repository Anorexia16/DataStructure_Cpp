#include <iostream>
#include "Structure/Matrix_STL2.hpp"
#include "Structure/Matrix_P2.hpp"
#include "Cpp_Data_Structure/Special_Structure/Matrix_Sparse_Chain.hpp"
#include "Structure/Node_Nonlinear.hpp"

int main() {
    Matrix_STL2<double> m2 {{1, 2, 3}, 1, 3};

    Matrix_STL2<double> n2 {{1, 4, 2, 5, 3, 6}, 3, 2};

    Matrix_P2<double> u {{1, 4, 2, 5, 3, 6}, 3, 2};

    Matrix_P2<double> v {{1, 2, 3}, 1, 3};

    std::cout << m2 << std::endl << n2 << std::endl << m2 * n2 << std::endl;

    std::cout << u << std::endl << v.T();
}