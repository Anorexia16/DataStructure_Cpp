#include "Structure/Dendroid/Dict_Trie_Tree.hpp"
#include "Lib_Algorithm/Math/Matrix_Algorithm/Matrix.hpp"
#include "Lib_Algorithm/Math/Matrix_Algorithm/Matrix_Inverse.hpp"
#include "Lib_Algorithm/Math/Basic_Types/Complex.hpp"

int main() {
    Dict dict {};
    dict.import({"as_inf", "acos", "acot"});
    dict.import({"inf", "pow", "sin", "sqrt"});
    dict.emplace("atan");
    dict.emplace("asin");
    dict.emplace("as_one_num");
    dict.init();
    dict.input('a');
    dict.input('s');
    auto vec1 = dict.release();
    dict.init();
    dict.input('s');
    auto vec2 = dict.release();

    Matrix<Complex> A {{{1, 1}, {2, -1}, {3, 2}, {-2, 1}, {1, -1}, {5, -1}, {1, 2},
                             {3, 0}, {0, -3}, {4, -1}, {2, 2}, {-1, 2}}, 3, 4};
    Matrix<Complex> B {{{1, -1}, {4, -1}, {5, 1}, {-2, 1}, {3, 2}, {0, 1}, {2, 0}, {-1, 5}, {6, -3}, {3, 2},
                            {1, 1}, {2, -1}, {2, -1}, {-3, -2}, {-2, 1}, {1, -2}}, 4, 4};
    auto C = A*B;
    return 0;
}