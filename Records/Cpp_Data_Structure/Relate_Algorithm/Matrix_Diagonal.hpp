#ifndef DATASTRUCTURE_MATRIX_DIAGONAL_HPP
#define DATASTRUCTURE_MATRIX_DIAGONAL_HPP

#include <iostream>
#include <algorithm>
#include "../../../Structure/Abstract/Abstract_Matrix.hpp"
#include "../../../Structure/Dimension/Matrix_STL2.hpp"

template<typename cls>
class Matrix_Diagonal: virtual public Static_Matrix<cls> {
public:
    explicit Matrix_Diagonal(size_t const & = 0);

    explicit Matrix_Diagonal(std::istream &&);
    
    Matrix_Diagonal(cls* const &, size_t const &);

    Matrix_Diagonal(std::initializer_list<cls> const &);
    
    template<size_t n>
    explicit Matrix_Diagonal(std::array<cls, n> const &);

    template<template<typename elem, typename=std::allocator<elem>>class Cont>
    explicit Matrix_Diagonal(Cont<cls> const &);
    
    Matrix_Diagonal(Matrix_Diagonal<cls> const &) = default;
    
    ~Matrix_Diagonal() = default;

    [[nodiscard]] std::pair<size_t, size_t> shape() const;

    [[nodiscard]] size_t size() const;

    Matrix_Diagonal<cls> operator+(Matrix_Diagonal<cls> const &) const;

    Matrix_Diagonal<cls> operator-(Matrix_Diagonal<cls> const &) const;

    Matrix_Diagonal<cls> operator*(Matrix_Diagonal<cls> const &) const;

    Matrix_Diagonal<cls> &operator+=(Matrix_Diagonal<cls> const &);

    Matrix_Diagonal<cls> &operator-=(Matrix_Diagonal<cls> const &);

    Matrix_Diagonal<cls> &operator*=(Matrix_Diagonal<cls> const &);

    Matrix_STL2<cls> unpack() const;

    friend std::ostream &operator<<(std::ostream &&, Matrix_Diagonal<cls> const &);
    
private:
    std::vector<cls> Container;
};

template<typename cls>
Matrix_Diagonal<cls>::Matrix_Diagonal(size_t const &size)
    :Container(cls {}, size) {}

template<typename cls>
Matrix_Diagonal<cls>::Matrix_Diagonal(std::istream &&in)
    :Container{} {
    std::copy(std::istream_iterator<cls>(std::forward<std::istream>(in)), std::istream_iterator<cls>(), std::begin(Container));
}

template<typename cls>
Matrix_Diagonal<cls>::Matrix_Diagonal(cls *const &ptr, const size_t &size)
    :Container{} {
    for (auto i=0;i!=size;++i) Container.template emplace_back(ptr[i]);
}

template<typename cls>
Matrix_Diagonal<cls>::Matrix_Diagonal(const std::initializer_list<cls> &list)
    :Container{} {
    std::copy(std::cbegin(list), std::cend(list), std::begin(Container));
}

template<typename cls>
template<size_t n>
Matrix_Diagonal<cls>::Matrix_Diagonal(const std::array<cls, n> &array)
    :Container{} {
    std::copy(std::cbegin(array), std::cend(array), std::begin(Container));
}

template<typename cls>
template<template<typename elem, typename=std::allocator<elem>>class Cont>
Matrix_Diagonal<cls>::Matrix_Diagonal(const Cont<cls> &cont)
    :Container{} {
    std::copy(std::cbegin(cont), std::cend(cont), std::begin(Container));
}

template<typename cls>
std::pair<size_t, size_t> Matrix_Diagonal<cls>::shape() const {
    return std::pair<size_t, size_t>{this->Container.size(), this->Container.size()};
}

template<typename cls>
size_t Matrix_Diagonal<cls>::size() const {
    return this->Container.size()*this->Container.size();
}

template<typename cls>
std::ostream &operator<<(std::ostream &&out, const Matrix_Diagonal<cls> &matrix) {
    size_t const size = matrix.Container.size();
    cls const standard {};
    for(auto i=0;i!=size;++i) {
        for(auto j=0;j!=size;++j) {
            out<< (i==j? matrix.Container[i]: standard);
        }
        out<<std::endl;
    }
    return out;
}

template<typename cls>
Matrix_Diagonal<cls> Matrix_Diagonal<cls>::operator+(const Matrix_Diagonal<cls> &op) const {
    if(this->shape()!=op.shape()) throw;
    Matrix_Diagonal<cls> res{};
    size_t const size = this->Container.size();
    for(auto i=0;i!=size;++i) {
        res.Container.template emplace_back(this->Container[i]+op.Container[i]);
    }
    return res;
}

template<typename cls>
Matrix_Diagonal<cls> Matrix_Diagonal<cls>::operator-(const Matrix_Diagonal<cls> &op) const {
    if(this->shape()!=op.shape()) throw;
    Matrix_Diagonal<cls> res{};
    size_t const size = this->Container.size();
    for(auto i=0;i!=size;++i) {
        res.Container.template emplace_back(this->Container[i]-op.Container[i]);
    }
    return res;
}

template<typename cls>
Matrix_Diagonal<cls> Matrix_Diagonal<cls>::operator*(const Matrix_Diagonal<cls> &op) const {
    if(this->shape()!=op.shape()) throw;
    Matrix_Diagonal<cls> res{};
    size_t const size = this->Container.size();
    for(auto i=0;i!=size;++i) {
        res.Container.template emplace_back(this->Container[i]*op.Container[i]);
    }
    return res;
}

template<typename cls>
Matrix_Diagonal<cls> &Matrix_Diagonal<cls>::operator+=(const Matrix_Diagonal<cls> &op) {
    if(this->shape()!=op.shape()) throw;
    size_t index {};
    std::transform(std::begin(this->Container), std::end(this->Container), std::begin(this->Container),
                   [&op, &index](cls const &value){value+=op[index++];return value;});
    return *this;
}

template<typename cls>
Matrix_Diagonal<cls> &Matrix_Diagonal<cls>::operator-=(const Matrix_Diagonal<cls> &op) {
    if(this->shape()!=op.shape()) throw;
    size_t index {};
    std::transform(std::begin(this->Container), std::end(this->Container), std::begin(this->Container),
                   [&op, &index](cls const &value){value-=op[index++];return value;});
    return *this;
}

template<typename cls>
Matrix_STL2<cls> Matrix_Diagonal<cls>::unpack() const {
    size_t const length = this->Container.size();
    Matrix_STL2<cls> res {length, length};
    for(auto i = 0; i!=length;++i) {
        res.get(i, i) = this->Container[i];
    }
    return res;
}

template<typename cls>
Matrix_Diagonal<cls> &Matrix_Diagonal<cls>::operator*=(const Matrix_Diagonal<cls> &op) {
    if(this->shape()!=op.shape()) throw;
    size_t index {};
    std::transform(std::begin(this->Container), std::end(this->Container), std::begin(this->Container),
                   [&op, &index](cls const &value){value*=op[index++];return value;});
    return *this;
}

#endif //DATASTRUCTURE_MATRIX_DIAGONAL_HPP
