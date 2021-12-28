#ifndef DATASTRUCTURE_MATRIX_INVERSE_HPP
#define DATASTRUCTURE_MATRIX_INVERSE_HPP

#include "Matrix.hpp"

template<typename tp>
Matrix<tp> Gauss_Jordan_Inverse(Matrix<tp> matrix) {
    if(matrix.Columns!=matrix.Rows) throw;


}

#endif //DATASTRUCTURE_MATRIX_INVERSE_HPP
