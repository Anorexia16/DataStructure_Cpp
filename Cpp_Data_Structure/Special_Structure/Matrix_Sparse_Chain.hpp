#ifndef DATASTRUCTURE_MATRIX_SPARSE_CHAIN_HPP
#define DATASTRUCTURE_MATRIX_SPARSE_CHAIN_HPP

#include "../../Structure/Linear/Chain_Unidirectional_Circle.hpp"
#include "../../Structure/Abstract/Abstract_Matrix.hpp"
#include <ostream>

template<typename cls>
class Matrix_SC: Matrix<cls> {
public:
    Matrix_SC(size_t const &, size_t const &);

    Matrix_SC(std::initializer_list<cls> const &, size_t const &, size_t const &);

    template<template<typename T, typename=std::allocator<T>>class Cont = std::vector>
    Matrix_SC(Cont<cls> const &, size_t const &, size_t const &);

    Matrix_SC(cls* const &, size_t const &, size_t const &);

    Matrix_SC(Matrix_SC<cls> const &) = default;

    ~Matrix_SC()=default;

    Matrix_SC<cls> operator+(Matrix_SC<cls> const &) const;

    Matrix_SC<cls> &operator+=(Matrix_SC<cls> const &);

    Matrix_SC<cls> operator-(Matrix_SC<cls> const &) const;

    Matrix_SC<cls> &operator-=(Matrix_SC<cls> const &);

    Matrix_SC<cls> operator*(Matrix_SC<cls> const &) const;

    Matrix_SC<cls> &operator*=(Matrix_SC<cls> const &);

    Matrix_SC<cls> operator*(cls const &) const;

    Matrix_SC<cls> &operator*=(cls const &);

private:
    ChainUC<std::pair<size_t, cls>> Container;

    size_t Columns;

    size_t Rows;
};

template<typename cls>
Matrix_SC<cls>::Matrix_SC(const size_t &column, const size_t &row)
    :Container{ChainUC<std::pair<size_t, cls>>{}}, Columns{column}, Rows{row} {}

template<typename cls>
Matrix_SC<cls>::Matrix_SC(const std::initializer_list<cls> &list, const size_t &column, const size_t &row)
    :Container{ChainUC<std::pair<size_t, cls>>{}}, Columns{column}, Rows{row} {
    if(list.size()!=column*row) throw;
    cls const empty {};
    size_t index {}, size{};
    NodeU_Iter<std::pair<size_t, cls>> bi {Container.head()};
    for(auto const & iter: list) {
        if (iter!=empty) {
            bi.link(*new NodeU<std::pair<size_t, cls>>{iter, bi.next_ptr()});
            ++size;
            ++bi;
        }
        ++index;
    }
    Container.resize(size);
}

template<typename cls>
template<template<typename T, typename=std::allocator<T>>class Cont>
Matrix_SC<cls>::Matrix_SC(const Cont<cls> &container, const size_t &column, const size_t &row)
    :Container{ChainUC<std::pair<size_t, cls>>{}}, Columns{column}, Rows{row} {
    if(container.size()!=column*row) throw;
    cls const empty {};
    size_t index {}, size{};
    NodeU_Iter<std::pair<size_t, cls>> bi {Container.head()};
    for(auto const & iter: container) {
        if (iter!=empty) {
            bi.link(*new NodeU<std::pair<size_t, cls>>{iter, bi.next_ptr()});
            ++size;
            ++bi;
        }
        ++index;
    }
    Container.resize(size);
}

template<typename cls>
Matrix_SC<cls>::Matrix_SC(cls *const &array, const size_t &column, const size_t &row)
    :Container{ChainUC<std::pair<size_t, cls>>{}}, Columns{column}, Rows{row} {
    cls const empty {};
    size_t index {}, size{};
    NodeU_Iter<std::pair<size_t, cls>> bi {Container.head()};
    for(auto iter=0; iter!=column*row;++iter, ++index) {
        if (array[iter]!=empty) {
            bi.link(*new NodeU<std::pair<size_t, cls>>{array[iter], bi.next_ptr()});
            ++size;
            ++bi;
        }
    }
    Container.resize(size);
}

template<typename cls>
Matrix_SC<cls> Matrix_SC<cls>::operator+(const Matrix_SC<cls> &op) const {
    Matrix_SC<cls> res {this->Columns, this->Rows};
    NodeU_Iter<std::pair<size_t, cls>> ri {res.Container.head()};
    NodeU_Iter<std::pair<size_t, cls>> ti {this->Container.head_c()->next_ptr()};
    NodeU_Iter<std::pair<size_t, cls>> oi {op.Container.head_c()->next_ptr()};
    for(;oi!=op.Container.head_c()&&ti!=this->Container.head_c();++ri) {
        if (ti.value_c().front < oi.value_c().front) {
            ri.link(*new NodeU<std::pair<size_t, cls>>{ti.value_c(), ri.next_ptr()});
            ++ti;
        } else if (ti.value_c().front > oi.value_c().front) {
            ri.link(*new NodeU<std::pair<size_t, cls>>{oi.value_c(), ri.next_ptr()});
            ++oi;
        } else {
            ri.link(*new NodeU<std::pair<size_t, cls>>{
                    std::pair<size_t, cls>(oi.value_c().front, oi.value_c().second + ti.value_c().second), ri.next_ptr()});
            ++oi;
            ++ti;
        }
    }
    if (ti!=this->Container.head_c()) {
        for (;ti!=this->Container.head_c();++ti, ++ri) {
            ri.link(*new NodeU<std::pair<size_t, cls>>{ti.value_c(), ri.next_ptr()});
        }
    } else if (oi!=op.Container.head_c()) {
        for(;oi!=op.Container.head_c();++oi, ++ri) {
            ri.link(*new NodeU<std::pair<size_t, cls>>{oi.value_c(), ri.next_ptr()});
        }
    }
    return res;
}

template<typename cls>
Matrix_SC<cls> &Matrix_SC<cls>::operator+=(const Matrix_SC<cls> &op) {
    NodeU_Iter<std::pair<size_t, cls>> ti {this->Container.head_c()->next_ptr()};
    NodeU_Iter<std::pair<size_t, cls>> oi {op.Container.head_c()->next_ptr()};
    for(;oi!=op.Container.head_c()&&ti!=this->Container.head_c();++ti) {
        if (ti.value_c().front > oi.value_c().front) {
            ti.link(*new NodeU<std::pair<size_t, cls>>{oi.value_c(), ti.next_ptr()});
            ++oi;
        } else if (ti.value_c().front == oi.value_c().front){
            ti.next().link(*new NodeU<std::pair<size_t, cls>>{
                    std::make_pair(oi.value_c().front, oi.value_c().second + ti.value_c().second), ti.next_ptr()->next_ptr()});
            ti.link(ti.next().next());
        }
    }
    if (oi!=op.Container.head_c()) {
        for(;oi!=op.Container.head_c();++oi, ++ti) {
            ti.link(*new NodeU<std::pair<size_t, cls>>{oi.value_c(), ti.next_ptr()});
        }
    }
    return *this;
}

template<typename cls>
Matrix_SC<cls> Matrix_SC<cls>::operator-(const Matrix_SC<cls> &op) const {
    Matrix_SC<cls> res {this->Columns, this->Rows};
    NodeU_Iter<std::pair<size_t, cls>> ri {res.Container.head()};
    NodeU_Iter<std::pair<size_t, cls>> ti {this->Container.head_c()->next_ptr()};
    NodeU_Iter<std::pair<size_t, cls>> oi {op.Container.head_c()->next_ptr()};
    for(;oi!=op.Container.head_c()&&ti!=this->Container.head_c();++ri) {
        if (ti.value_c().front < oi.value_c().front) {
            ri.link(*new NodeU<std::pair<size_t, cls>>{ti.value_c(), ri.next_ptr()});
            ++ti;
        } else if (ti.value_c().front > oi.value_c().front) {
            ri.link(*new NodeU<std::pair<size_t, cls>>{oi.value_c(), ri.next_ptr()});
            ++oi;
        } else {
            ri.link(*new NodeU<std::pair<size_t, cls>>{
                    std::pair<size_t, cls>(oi.value_c().front, ti.value_c().second - oi.value_c().second), ri.next_ptr()});
            ++oi;
            ++ti;
        }
    }
    if (ti!=this->Container.head_c()) {
        for (;ti!=this->Container.head_c();++ti, ++ri) {
            ri.link(*new NodeU<std::pair<size_t, cls>>{ti.value_c(), ri.next_ptr()});
        }
    } else if (oi!=op.Container.head_c()) {
        for(;oi!=op.Container.head_c();++oi, ++ri) {
            ri.link(*new NodeU<std::pair<size_t, cls>>{oi.value_c(), ri.next_ptr()});
        }
    }
    return res;
}

template<typename cls>
Matrix_SC<cls> &Matrix_SC<cls>::operator-=(const Matrix_SC<cls> &op) {
    NodeU_Iter<std::pair<size_t, cls>> ti {this->Container.head_c()->next_ptr()};
    NodeU_Iter<std::pair<size_t, cls>> oi {op.Container.head_c()->next_ptr()};
    for(;oi!=op.Container.head_c()&&ti!=this->Container.head_c();++ti) {
        if (ti.value_c().front > oi.value_c().front) {
            ti.link(*new NodeU<std::pair<size_t, cls>>{oi.value_c(), ti.next_ptr()});
            ++oi;
        } else if (ti.value_c().front == oi.value_c().front){
            ti.next().link(*new NodeU<std::pair<size_t, cls>>{
                    std::make_pair(oi.value_c().front, ti.value_c().second - oi.value_c().second), ti.next_ptr()->next_ptr()});
            ti.link(ti.next().next());
        }
    }
    if (oi!=op.Container.head_c()) {
        for(;oi!=op.Container.head_c();++oi, ++ti) {
            ti.link(*new NodeU<std::pair<size_t, cls>>{oi.value_c(), ti.next_ptr()});
        }
    }
    return *this;
}

template<typename cls>
Matrix_SC<cls> Matrix_SC<cls>::operator*(const Matrix_SC<cls> &op) const {
    Matrix_SC<cls> res {this->Columns, this->Rows};
    return res;
}

template<typename cls>
Matrix_SC<cls> &Matrix_SC<cls>::operator*=(const Matrix_SC<cls> &op) {
    return *this;
}

template<typename cls>
Matrix_SC<cls> Matrix_SC<cls>::operator*(const cls &value) const {
    Matrix_SC<cls> res {this->Columns, this->Rows};
    NodeU_Iter<std::pair<size_t, cls>> ri {res.Container.head()};
    NodeU_Iter<std::pair<size_t, cls>> ti {this->Container.head_c()->next_ptr()};
    for(;ti!=this->Container.head_c();++ri, ++ti) {
        ri.link(*new NodeU<std::pair<size_t, cls>>{std::make_pair(ti.value_c().front, ti.value_c().second * value), ri.next_ptr()});
    }
    return res;
}

template<typename cls>
Matrix_SC<cls> &Matrix_SC<cls>::operator*=(const cls &value) {
    NodeU_Iter<std::pair<size_t, cls>> ti {this->Container.head()};
    for(;ti!=this->Container.head_c();++ti) {
        ti.next().link(*new NodeU<std::pair<size_t, cls>>{
                std::make_pair(ti.value_c().front, ti.value_c() * value.second), ti.next_ptr()->next_ptr()});
        ti.link(ti.next().next());
    }
    return *this;
}

#endif //DATASTRUCTURE_MATRIX_SPARSE_CHAIN_HPP
