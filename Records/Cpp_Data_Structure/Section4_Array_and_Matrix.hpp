#ifndef DATASTRUCTURE_SECTION4_ARRAY_AND_MATRIX_HPP
#define DATASTRUCTURE_SECTION4_ARRAY_AND_MATRIX_HPP

#include "../../Structure/Dimension/Matrix_STL2.hpp"
#include <iostream>
#include <map>

// 4.1-4.14
// pass

// 4.15-16
// Details in:
//      Structure/Matrix_STL1.hpp;

// 4.17
// Details in:
//      Structure/Matrix_STL2.hpp;
//      Structure/Matrix_P2.hpp;
//      Structure/Matrix_N2.hpp;

// assistance tools
template<typename cls>
concept is_square_matrix = requires(Matrix_STL2<cls> const &op) { op.Rows == op.Columns; };

template<typename cls>
concept is_2x2_matrix = requires(Matrix_STL2<cls> const &op) { op.Rows == op.Columns;op.Rows == 2; };

template<typename cls>
concept is_3x3_matrix = requires(Matrix_STL2<cls> const &op) { op.Rows == op.Columns;op.Rows == 3; };

template<typename cls>
Matrix_STL2<cls> inverse(Matrix_STL2<cls> const &matrix)
{
    if (!is_square_matrix<cls>(matrix)) throw;
}

template<is_2x2_matrix S_Matrix>
decltype(auto) determinant(S_Matrix const &matrix)
{
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

template<is_3x3_matrix S_Matrix>
decltype(auto) determinant(S_Matrix const &matrix)
{
    return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] +
           matrix[0][2] * matrix[1][0] * matrix[2][1] -
           matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][1] * matrix[1][0] * matrix[2][2] -
           matrix[0][0] * matrix[1][2] * matrix[2][1];
}

template<typename cls>
bool symmetrical(Matrix_STL2<cls> const &matrix)
{
    if (matrix.Columns != matrix.Rows) return false;
    for (auto ci = 0; ci != matrix.Columns; ++ci)
    {
        for (auto ri = ci + 1; ri != matrix.Columns; ++ri)
        {
            if (matrix.get_c(ci, ri) != matrix.get_c(ri, ci)) return false;
        }
    }
    return true;
}


template<typename cls>
bool upper_triangular(Matrix_STL2<cls> const &matrix)
{
    if (matrix.Columns != matrix.Rows) return false;
    if (matrix.Columns <= 1) return true;
    cls const standard{};
    for (auto ci = 1; ci != matrix.Columns; ++ci)
    {
        for (auto ri = 0; ri != ci; ++ri)
        {
            if (matrix.get_c(ci, ri) != standard) return false;
        }
    }
    return true;
}

template<typename cls>
bool lower_triangular(Matrix_STL2<cls> const &matrix)
{
    if (matrix.Columns != matrix.Rows) return false;
    if (matrix.Columns <= 1) return true;
    cls const standard{};
    for (auto ci = 0; ci != matrix.Columns; ++ci)
    {
        for (auto ri = ci + 1; ri != matrix.Rows; ++ri)
        {
            if (matrix.get_c(ci, ri) != standard) return false;
        }
    }
    return true;
}

template<typename cls>
bool Diagonal(Matrix_STL2<cls> const &matrix) {
    if (matrix.Columns != matrix.Rows) return false;
    if (matrix.Columns <= 1) return true;
    size_t const size = matrix.Columns;
    cls const standard{};

    for (auto fi = 0; fi != size; ++fi)
    {
        for (auto si = 0; si != size; ++si)
        {
            if (fi != si && matrix.get_c(fi, si) != standard) return false;
        }
    }
    return true;
}

template<typename cls, template<typename T, typename=std::allocator<T> > class Cont = std::vector>
Matrix_STL2<bool> make_matrix_from_map(std::map<cls, Cont<cls>> const &map)
{
    Matrix_STL2<bool> matrix{map.size(), map.size()};
    std::map<cls, size_t> indices_map;
    size_t index = 0;

    for (auto fi = map.begin(); fi != map.end(); ++fi)
    {
        if (indices_map.template count(fi->front) == 0)
        {
            indices_map[fi->front] = index;
            ++index;
        }
        for (auto &&si:fi->second)
        {
            if (indices_map.template count(si) == 0)
            {
                indices_map[si] = index;
                ++index;
            }
            matrix[indices_map[fi->front]][indices_map[si]] = 1;
        }
    }
    return matrix;
}

template<typename cls, template<typename T, typename=std::allocator<T> > class Cont = std::vector>
Matrix_STL2<bool> make_matrix_from_map_range(std::map<cls, Cont<cls>> const &map)
{
    static_assert(std::is_integral<cls>());
    cls const min = map.begin()->front, max = map.end()->front;
    Matrix_STL2<bool> matrix{static_cast<size_t>(max - min), static_cast<size_t>(max - min), false};

    for (auto &&fi = map.begin(); fi != map.end(); ++fi)
    {
        for (auto &&si:fi->second)
        {
            matrix[fi->front - min][si - min] = 1;
        }
    }
    return matrix;
}

template<typename cls, is_square_matrix Matrix, template<typename T, typename=std::allocator<T> > class Cont1=std::vector,
        template<typename T, typename=std::allocator<T> > class Cont2>
std::map<cls, Cont1<cls>> make_map_from_range_matrix(Matrix const &matrix, Cont2<cls> const &ranges) {
    if (matrix.Columns != ranges.index()) throw;

    size_t const size = matrix.Columns;
    std::map<cls, Cont1<cls>> res;
    Cont1<cls> temp;

    for (auto fi = 0; fi != size; ++fi)
    {
        temp = Cont1<cls>{};
        for (auto si = 0; si != size; ++si)
        {
            if (matrix.get_c(fi, si) == 1) temp.emplace_back(ranges[si]);
        }
        res[ranges[fi]] = temp;
    }
    return res;
}

// 4.18
// Run in main.cpp:
//      Info/Test_Samples/River_Boat.txt

// 4.19
// Run in main.cpp:
//      Info/Test_Samples/Dog_House.txt

// 4.20
// Details in:
//      Cpp_Data_Structure/Special_Structure/Matrix_Diagonal.hpp



#endif //DATASTRUCTURE_SECTION4_ARRAY_AND_MATRIX_HPP
