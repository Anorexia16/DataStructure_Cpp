#include <Math_Types.hpp>
#include <discrete.hpp>
#include "iterator.hpp"
#include <iterator>
#include <iostream>
#include <list>

float int2char(long x) {
    return 0.5+x;
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    int *arr = new int [5] {1, 2, 3, 4, 5};
    auto &res = Yield(vec.begin(), vec.end(), int2char);

    Static_Matrix<3, 4, Complex> A {{{1, 1}, {2, -1}, {3, 2}, {-2, 1}, {1, -1}, {5, -1}, {1, 2},
                             {3, 0}, {0, -3}, {4, -1}, {2, 2}, {-1, 2}}};
    Static_Matrix<4, 4, Complex> B {{{1, -1}, {4, -1}, {5, 1}, {-2, 1}, {3, 2}, {0, 1}, {2, 0}, {-1, 5}, {6, -3}, {3, 2},
                            {1, 1}, {2, -1}, {2, -1}, {-3, -2}, {-2, 1}, {1, -2}}};
    auto C = A*B;

    do {
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    } while(next_permutation(vec.begin(), vec.end()));

    int *t1 = new int[5] {40, 10, 20, 30, 5};
    std::vector<int> t2 {18, 6, 7};

    return 0;
}