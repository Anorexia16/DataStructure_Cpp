#ifndef DATASTRUCTURE_MATRIX_STL2_HPP
#define DATASTRUCTURE_MATRIX_STL2_HPP

#include "../Abstract/Abstract_Matrix.hpp"
#include <algorithm>
#include <iterator>
#include <ostream>
#include <vector>

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont = std::vector>
class Matrix_STL2
{
public:
    Matrix_STL2(size_t const &, size_t const &, cls const & = cls{});

    Matrix_STL2(cls const *, size_t const &, size_t const &);

    Matrix_STL2(std::initializer_list<cls> const &, size_t const &, size_t const &);

    Matrix_STL2(Matrix_STL2 const &) = default;

    ~Matrix_STL2() = default;

    inline Cont<cls> expand();

    inline cls *expand_p();

    inline void resize(size_t const &, size_t const &);

    Matrix_STL2<cls> operator+(Matrix_STL2 const &) const;

    Matrix_STL2<cls> &operator+=(Matrix_STL2 const &);

    Matrix_STL2<cls> operator-(Matrix_STL2 const &) const;

    Matrix_STL2<cls> &operator-=(Matrix_STL2 const &);

    Matrix_STL2<cls> operator*(Matrix_STL2 const &) const;

    Matrix_STL2<cls> &operator*=(Matrix_STL2 const &);

    Matrix_STL2<cls> operator*(cls const &) const;

    Matrix_STL2<cls> &operator*=(cls const &);

    inline cls &get(size_t const &, size_t const &);

    inline cls const get_c(size_t const &, size_t const &) const;

    Matrix_STL2<cls> T() const;

    [[nodiscard]] std::pair<size_t, size_t> shape() const;

    [[nodiscard]] size_t size() const;

    friend std::ostream &operator<<(std::ostream &out, Matrix_STL2<cls> const &op)
    {
        for (auto &&iter: op.Container)
        {
            std::copy(std::begin(iter), std::end(iter), std::ostream_iterator<cls>(out, " "));
            out << std::endl;
        }
        return out;
    }

    size_t Columns;

    size_t Rows;

    inline Cont<cls> &operator[](size_t const &);

protected:
    Cont<Cont<cls>> Container;
};

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls, Cont>::Matrix_STL2(const size_t &column, const size_t &row, cls const &v)
        : Columns{column}, Rows{row}
{
    Cont<Cont<cls>> cont;
    for (auto ci = 0; ci != column; ++ci)
    {
        cont.emplace_back(Cont<cls>(v, row));
        for (auto vi = 0; vi != row; ++vi)
        {
            cont[ci].emplace_back(v);
        }
    }
    Container = cont;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls, Cont>::Matrix_STL2(const cls *ptr, const size_t &column, const size_t &row)
        : Columns{column}, Rows{row}
{
    Cont<Cont<cls>> cont;
    for (auto ci = 0; ci != column; ++ci)
    {
        cont.emplace_back(Cont<cls>(cls{}, row));
    }

    Container = cont;
    size_t global_index = 0;

    for (auto &&ci: this->Container)
    {
        for (auto vi = 0; vi != row; ++vi)
        {
            ci.emplace_back(ptr[global_index]);
            ++global_index;
        }
    }
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls, Cont>::Matrix_STL2(const std::initializer_list<cls> &list, const size_t &column, const size_t &row)
        : Columns{column}, Rows{row}
{
    Cont<Cont<cls>> cont;
    for (auto ci = 0; ci != column; ++ci)
    {
        cont.emplace_back(Cont<cls>(cls{}, row));
    }

    Container = cont;
    size_t global_index = 0;

    for (auto &&ci: Container)
    {
        for (auto vi = 0; vi != row; ++vi)
        {
            ci.emplace_back(*(std::begin(list) + global_index));
            ++global_index;
        }
    }
}


template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
std::pair<size_t, size_t> Matrix_STL2<cls, Cont>::shape() const
{
    return std::pair<size_t, size_t>(this->Columns, this->Rows);
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
size_t Matrix_STL2<cls, Cont>::size() const
{
    return this->Columns * this->Rows;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Cont<cls> Matrix_STL2<cls, Cont>::expand()
{
    Cont<cls> res{};
    for (auto &&ci: this->Container)
    {
        for (auto &&iter: ci)
        {
            res.emplace_back(iter);
        }
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
cls *Matrix_STL2<cls, Cont>::expand_p()
{
    cls *res = new cls[this->size()];
    size_t global_index = 0;
    for (auto &&ci: this->Container)
    {
        for (auto &&iter: ci)
        {
            res[global_index] = iter;
            ++global_index;
        }
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
void Matrix_STL2<cls, Cont>::resize(const size_t &column, const size_t &row)
{
    cls *cont = this->expand_p();
    this = Matrix_STL2<cls>{cont, column, row};
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls> Matrix_STL2<cls, Cont>::operator+(const Matrix_STL2 &op) const
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    Matrix_STL2<cls> res{this->Columns, this->Rows};
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != this->Rows; ++ri)
        {
            res.Container[ci][ri] = this->Container[ci][ri] + op.Container[ci][ri];
        }
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls> &Matrix_STL2<cls, Cont>::operator+=(const Matrix_STL2 &op)
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != this->Rows; ++ri)
        {
            this->Container[ci][ri] += op.Container[ci][ri];
        }
    }
    return *this;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls> Matrix_STL2<cls, Cont>::operator-(const Matrix_STL2 &op) const
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    Matrix_STL2<cls> res{this->Columns, this->Rows};
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != this->Rows; ++ri)
        {
            res.Container[ci][ri] = this->Container[ci][ri] - op.Container[ci][ri];
        }
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls> &Matrix_STL2<cls, Cont>::operator-=(const Matrix_STL2 &op)
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != this->Rows; ++ri)
        {
            this->Container[ci][ri] -= op.Container[ci][ri];
        }
    }
    return *this;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls> Matrix_STL2<cls, Cont>::operator*(const cls &op) const
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    Matrix_STL2<cls> res{this->Columns, this->Rows};
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != this->Rows; ++ri)
        {
            res.Container[ci][ri] = this->Container[ci][ri] * op;
        }
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls> &Matrix_STL2<cls, Cont>::operator*=(const cls &op)
{
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != this->Rows; ++ri)
        {
            this->Container[ci][ri] *= op;
        }
    }
    return *this;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
cls &Matrix_STL2<cls, Cont>::get(const size_t &column, const size_t &row)
{
    return (*this)[column][row];
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
cls const Matrix_STL2<cls, Cont>::get_c(const size_t &column, const size_t &row) const
{
    return *(std::begin(*(std::begin(this->Container) + column)) + row);
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Cont<cls> &Matrix_STL2<cls, Cont>::operator[](const size_t &index)
{
    return this->Container[index];
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls> Matrix_STL2<cls, Cont>::T() const
{
    Matrix_STL2<cls> res{this->Rows, this->Columns};
    for (auto iter = 0; iter != this->size(); ++iter)
    {
        res[iter % this->Rows][iter / this->Rows] = this->get_c(iter / this->Rows, iter % this->Rows);
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls> Matrix_STL2<cls, Cont>::operator*(const Matrix_STL2 &op) const
{
    if (this->Rows != op.Columns) throw;
    Matrix_STL2<cls> res{this->Columns, op.Rows};
    cls temp{};
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != op.Rows; ++ri)
        {
            temp = cls{};
            for (auto bi = 0; bi != op.Columns; ++bi)
            {
                temp += this->get_c(ci, bi) * op.get_c(bi, ri);
            }
            res.Container[ci][ri] = temp;
        }
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL2<cls> &Matrix_STL2<cls, Cont>::operator*=(const Matrix_STL2 &op)
{
    if (this->Rows != op.Columns) throw;
    auto res = Cont<Cont<cls>>(Cont<cls>(cls{}, this->Rows), this->Columns);
    cls temp{};

    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != op.Rows; ++ri)
        {
            temp = cls{};
            for (auto bi = 0; bi != op.Columns; ++bi)
            {
                temp += this->get_c(ci, bi) * op.get_c(bi, ri);
            }
            res[ci][ri] = temp;
        }
    }
    this->Rows = op.Rows;
    this->Container = res;
    return *this;
}


#endif //DATASTRUCTURE_MATRIX_STL2_HPP
