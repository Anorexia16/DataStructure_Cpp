#ifndef DATASTRUCTURE_MATRIX_TRIDIAGONAL_HPP
#define DATASTRUCTURE_MATRIX_TRIDIAGONAL_HPP

#include <iostream>
#include <algorithm>
#include "../../Structure/Dimension/Matrix_STL2.hpp"
#include "../../Structure/Abstract/Abstract_Matrix.hpp"

template<typename cls>
class Matrix_Tridiagonal: virtual public Matrix<cls> {
public:
    explicit Matrix_Tridiagonal(size_t const & = 1);

    explicit Matrix_Tridiagonal(cls *const &, cls *const &, cls *const &, size_t const &);

    explicit Matrix_Tridiagonal(std::initializer_list<cls> const &, std::initializer_list<cls> const &,
            std::initializer_list<cls> const &);

    template<template<typename elem, typename=std::allocator<elem>>class Cont>
    Matrix_Tridiagonal(Cont<cls> const &, Cont<cls> const &, Cont<cls> const &);

    template<size_t m, size_t n, size_t l>
    Matrix_Tridiagonal(std::array<cls, m> const &, std::array<cls, n> const &, std::array<cls, l> const &);

    Matrix_Tridiagonal(Matrix_Tridiagonal<cls> const &) = default;

    ~Matrix_Tridiagonal() = default;

    [[nodiscard]] size_t size() const;

    [[nodiscard]] std::pair<size_t, size_t> shape() const;

    Matrix_STL2<cls> unpack() const;

    Matrix_Tridiagonal<cls> operator+(Matrix_Tridiagonal<cls> const &) const;

    Matrix_Tridiagonal<cls> operator-(Matrix_Tridiagonal<cls> const &) const;

    Matrix_Tridiagonal<cls> operator*(Matrix_Tridiagonal<cls> const &) const;

    Matrix_Tridiagonal<cls> &operator+=(Matrix_Tridiagonal<cls> const &);

    Matrix_Tridiagonal<cls> &operator-=(Matrix_Tridiagonal<cls> const &);

    Matrix_Tridiagonal<cls> &operator*=(Matrix_Tridiagonal<cls> const &);

    friend std::ostream &operator<<(std::ostream &&out, Matrix_Tridiagonal<cls> const &);

private:
    std::vector<cls> line1;
    std::vector<cls> line2;
    std::vector<cls> line3;
};

template<typename cls>
Matrix_Tridiagonal<cls>::Matrix_Tridiagonal(size_t const &size)
    :line1(cls{} , size-1), line2(cls {}, size), line3(cls {}, size) {}

template<typename cls>
Matrix_Tridiagonal<cls>::Matrix_Tridiagonal(cls *const &ptr1, cls *const &ptr2, cls *const &ptr3, const size_t &size)
    :line1{}, line2{}, line3{} {
    for (auto i=0;i!=size;++i) line1.template emplace_back(ptr1[i]);
    for (auto i=0;i!=size;++i) line2.template emplace_back(ptr2[i]);
    for (auto i=0;i!=size;++i) line3.template emplace_back(ptr3[i]);
}

template<typename cls>
Matrix_Tridiagonal<cls>::Matrix_Tridiagonal(const std::initializer_list<cls> &list1, const std::initializer_list<cls> &list2,
                                            const std::initializer_list<cls> &list3)
    :line1{}, line2{}, line3{} {
    static_assert(std::cend(list1)-std::cbegin(list1)==std::cend(list3)-std::cbegin(list3));
    static_assert((std::cend(list1)-std::cbegin(list1))+1==std::cend(list2)-std::cbegin(list2));
    std::copy(std::cbegin(list1), std::cend(list1), std::begin(line1));
    std::copy(std::cbegin(list2), std::cend(list2), std::begin(line2));
    std::copy(std::cbegin(list3), std::cend(list3), std::begin(line3));
}

template<typename cls>
template<template<typename elem, typename=std::allocator<elem>>class Cont>
Matrix_Tridiagonal<cls>::Matrix_Tridiagonal(const Cont<cls> &cont1, const Cont<cls> &cont2, const Cont<cls> &cont3)
        :line1{}, line2{}, line3{} {
    static_assert(std::cend(cont1) - std::cbegin(cont1) == std::cend(cont3) - std::cbegin(cont3));
    static_assert((std::cend(cont1) - std::cbegin(cont1)) + 1 == std::cend(cont2) - std::cbegin(cont2));
    std::copy(std::cbegin(cont1), std::cend(cont1), std::begin(line1));
    std::copy(std::cbegin(cont2), std::cend(cont2), std::begin(line2));
    std::copy(std::cbegin(cont3), std::cend(cont3), std::begin(line3));
}

template<typename cls>
template<size_t m, size_t n, size_t l>
Matrix_Tridiagonal<cls>::Matrix_Tridiagonal(const std::array<cls, m> &array1, const std::array<cls, n> &array2,
                                            const std::array<cls, l> &array3)
        :line1{}, line2{}, line3{} {
    static_assert(std::cend(array1) - std::cbegin(array1) == std::cend(array3) - std::cbegin(array3));
    static_assert((std::cend(array1) - std::cbegin(array1)) + 1 == std::cend(array2) - std::cbegin(array2));
    std::copy(std::cbegin(array1), std::cend(array1), std::begin(line1));
    std::copy(std::cbegin(array2), std::cend(array2), std::begin(line2));
    std::copy(std::cbegin(array3), std::cend(array3), std::begin(line3));
}

template<typename cls>
size_t Matrix_Tridiagonal<cls>::size() const {
    return this->line2.size()*this->line2.size();
}

template<typename cls>
std::pair<size_t, size_t> Matrix_Tridiagonal<cls>::shape() const {
    return std::pair<size_t, size_t>{this->line2.size(), this->line2.size()};
}

template<typename cls>
Matrix_STL2<cls> Matrix_Tridiagonal<cls>::unpack() const {
    size_t const size {this->line2.size()};
    Matrix_STL2<cls> res {size, size};
    for(auto i=0;i!=size-1;++i) res.get(i, i+1)=this->line1[i];
    for(auto i=0;i!=size;++i) res.get(i, i)=this->line2[i];
    for(auto i=0;i!=size-1;++i) res.get(i+1, i)=this->line3[i];
    return res;
}

template<typename cls>
Matrix_Tridiagonal<cls> Matrix_Tridiagonal<cls>::operator+(const Matrix_Tridiagonal<cls> &op) const {
    if(this->shape()!=op.shape()) throw;
    size_t const size = this->line2.size();
    Matrix_Tridiagonal<cls> res{size, size};
    for(auto i=0;i!=size-1;++i) res.line1[i]=this->line1[i]+op.line1[i];
    for(auto i=0;i!=size;++i) res.line2[i]=this->line2[i]+op.line2[i];
    for(auto i=0;i!=size-1;++i) res.line3[i]=this->line3[i]+op.line3[i];
    return res;
}

template<typename cls>
Matrix_Tridiagonal<cls> Matrix_Tridiagonal<cls>::operator-(const Matrix_Tridiagonal<cls> &op) const {
    if(this->shape()!=op.shape()) throw;
    size_t const size = this->line2.size();
    Matrix_Tridiagonal<cls> res{size, size};
    for(auto i=0;i!=size-1;++i) res.line1[i]=this->line1[i]-op.line1[i];
    for(auto i=0;i!=size;++i) res.line2[i]=this->line2[i]-op.line2[i];
    for(auto i=0;i!=size-1;++i) res.line3[i]=this->line3[i]-op.line3[i];
    return res;
}

template<typename cls>
Matrix_Tridiagonal<cls> Matrix_Tridiagonal<cls>::operator*(const Matrix_Tridiagonal<cls> &op) const {
    if(this->shape()!=op.shape()) throw;
    size_t const size = this->line2.size();
    Matrix_Tridiagonal<cls> res{size, size};
    return res;
}

template<typename cls>
Matrix_Tridiagonal<cls> &Matrix_Tridiagonal<cls>::operator+=(const Matrix_Tridiagonal<cls> &op) {
    if(this->shape()!=op.shape()) throw;
    size_t const size = this->line2.size();
    for(auto i=0;i!=size-1;++i) this->line1[i]+=op.line1[i];
    for(auto i=0;i!=size;++i) this->line2[i]+=op.line2[i];
    for(auto i=0;i!=size-1;++i) this->line3[i]+=op.line3[i];
    return *this;
}

template<typename cls>
Matrix_Tridiagonal<cls> &Matrix_Tridiagonal<cls>::operator-=(const Matrix_Tridiagonal<cls> &op) {
    if(this->shape()!=op.shape()) throw;
    size_t const size = this->line2.size();
    for(auto i=0;i!=size-1;++i) this->line1[i]-=op.line1[i];
    for(auto i=0;i!=size;++i) this->line2[i]-=op.line2[i];
    for(auto i=0;i!=size-1;++i) this->line3[i]-=op.line3[i];
    return *this;
}

template<typename cls>
Matrix_Tridiagonal<cls> &Matrix_Tridiagonal<cls>::operator*=(const Matrix_Tridiagonal<cls> &op) {
    if(this->shape()!=op.shape()) throw;
    return *this;
}

template<typename Tp>
std::ostream &operator<<(std::ostream &&out, const Matrix_Tridiagonal<Tp> &matrix) {
    size_t const size = matrix.line2.size();
    Tp const standard {};
    for(auto i=0;i!=size;++i) {
        for(auto j=0;j!=size;++j) {
            if (i+1==j) out << matrix.line3[i];
            else if (i==j) out << matrix.line2[i];
            else if (j+1==i) out << matrix.line1[i];
            else out << standard;
        }
        out << std::endl;
    }
    return out;
}

#endif //DATASTRUCTURE_MATRIX_TRIDIAGONAL_HPP
