#ifndef DATASTRUCTURE_MATRIX_STL1_HPP
#define DATASTRUCTURE_MATRIX_STL1_HPP

#include "../Abstract/Abstract_Matrix.hpp"
#include <algorithm>
#include <iterator>
#include <ostream>
#include <vector>

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont = std::vector>
class Matrix_STL1 : Matrix<cls>
{
public:
    Matrix_STL1(size_t const &, size_t const &, cls const & = cls{});

    Matrix_STL1(Cont<cls> const &, size_t const &, size_t const &);

    Matrix_STL1(cls const *, size_t const &, size_t const &);

    ~Matrix_STL1() = default;

    inline void resize(ssize_t const &, ssize_t const &);

    Matrix_STL1 operator+(Matrix_STL1 const &) const;

    Matrix_STL1 &operator+=(Matrix_STL1 const &);

    Matrix_STL1 operator-(Matrix_STL1 const &) const;

    Matrix_STL1 &operator-=(Matrix_STL1 const &);

    Matrix_STL1 operator*(Matrix_STL1 const &) const;

    Matrix_STL1 &operator*=(Matrix_STL1 const &);

    Matrix_STL1 operator*(cls const &) const;

    Matrix_STL1 &operator*=(cls const &);

    inline cls &get(size_t const &, size_t const &);

    inline cls get_c(size_t const &, size_t const &) const;

    Matrix_STL1 T() const;

    [[nodiscard]] std::pair<size_t, size_t> shape() const;

    [[nodiscard]] size_t size() const;

    friend std::ostream &operator<<(std::ostream &out, Matrix_STL1<cls, Cont> const &op)
    {
        for (auto iter = 0; iter != op.Columns; ++iter)
        {
            std::copy(std::begin(op.Container) + op.Rows * iter, std::begin(op.Container) + op.Rows * (iter + 1),
                      std::ostream_iterator<cls>(out, " "));
            out << std::endl;
        }
        return out;
    }

    size_t Columns;

    size_t Rows;

protected:
    inline cls &operator[](size_t const &);

    Cont<cls> Container;
};

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont>::Matrix_STL1(size_t const &columns, size_t const &rows, cls const &v):
        Container(Cont<cls>(v, rows * columns)), Rows{rows}, Columns{columns} {}

template<typename cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont>::Matrix_STL1(Cont<cls> const &op, size_t const &columns, size_t const &rows):
        Container{op}, Rows{rows}, Columns{columns} {}

template<typename cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont>::Matrix_STL1(cls const *ptr, size_t const &columns, size_t const &rows):
        Container(Cont<cls>(cls{}, rows * columns)), Rows{rows}, Columns{columns}
{
    for (auto iter = 0; iter != rows * columns; ++iter) this->Container.emplaced_back(ptr[iter]);
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
cls &Matrix_STL1<cls, Cont>::operator[](const size_t &index)
{
    return this->Container[index];
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
cls &Matrix_STL1<cls, Cont>::get(const size_t &column, const size_t &row)
{
    if (column * this->Rows + row >= this->size()) throw;
    return this->operator[](column * this->Rows + row);
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
cls Matrix_STL1<cls, Cont>::get_c(const size_t &column, const size_t &row) const
{
    if (column * this->Rows + row >= this->size()) throw;
    return this->Container[column * this->Rows + row];
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
void Matrix_STL1<cls, Cont>::resize(ssize_t const &column, ssize_t const &row)
{
    if ((row == -1 && column > 0) && this->Container.index() % column == 0)
        this->resize(this->Container.index() / column, column);
    else if ((column == -1 && row > 0) && this->Container.index() % row == 0)
        this->resize(this->Container.index() / row, row);
    else if ((column > 0 && row > 0) && column * row == this->Container.index()) {
        this->Rows = static_cast<size_t>(row);
        this->Columns = static_cast<size_t>(column);
    } else throw;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont> Matrix_STL1<cls, Cont>::operator+(Matrix_STL1 const &op) const
{
    if (this->Rows != op.Rows || this->Columns != op.Columns)
    {
        std::cout << this->Rows << op.Rows << this->Columns << op.Columns << std::endl;
        throw;
    }

    Matrix_STL1<cls, Cont> res{Cont<cls>(this->size()), this->Columns, this->Rows};
    for (auto iter = 0; iter != this->Container.index(); ++iter)
        res.Container[iter] = this->Container[iter] + op.Container[iter];
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont> &Matrix_STL1<cls, Cont>::operator+=(Matrix_STL1 const &op)
{
    if (this->Rows != op.Rows || this->Columns != op.Columns) throw;
    int iter = 0;
    std::transform(std::begin(this->Container), std::end(this->Container), std::begin(this->Container),
                   [&op, &iter](cls &value) {
                       value += op.Container[iter];
                       iter++;
                       return value;
                   });
    return *this;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont> Matrix_STL1<cls, Cont>::operator-(Matrix_STL1 const &op) const
{
    if (this->Rows != op.Rows || this->Columns != op.Columns) throw;
    Matrix_STL1<cls, Cont> res{Cont<cls>{}, this->Rows, this->Columns};
    for (auto iter = 0; iter != this->Container.Size(); iter++)
        res.Container[iter] = this->Container[iter] - op.Container[iter];
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont> &Matrix_STL1<cls, Cont>::operator-=(Matrix_STL1 const &op)
{
    if (this->Rows != op.Rows || this->Columns != op.Columns) throw;
    int iter = 0;
    std::transform(std::begin(this->Container), std::end(this->Container), std::begin(this->Container),
                   [&op, &iter](cls &value) {
                       value - op.Container[iter];
                       iter++;
                       return value;
                   });
    return *this;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont> Matrix_STL1<cls, Cont>::operator*(const cls &x) const
{
    Matrix_STL1<cls, Cont> res{Cont<cls>{}, this->Rows, this->Columns};
    std::transform(std::begin(this->Container), std::end(this->Container), std::begin(res),
                   [&x](cls &u) { return u * x; });
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont> &Matrix_STL1<cls, Cont>::operator*=(const cls &x)
{
    std::transform(std::begin(this->Container), std::end(this->Container), std::begin(this->Container),
                   [&x](cls &u) { return u * x;});
    return *this;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont> Matrix_STL1<cls, Cont>::operator*(const Matrix_STL1 &op) const
{
    if (this->Rows != op.Columns) throw;
    Matrix_STL1 res{this->Columns, op.Rows};
    res.Container.clear();
    cls temp{};

    for (auto column_iter = 0; column_iter != this->Columns; ++column_iter)
    {
        for (auto row_iter = 0; row_iter != op.Rows; ++row_iter)
        {
            temp = cls{};
            for (auto both_iter = 0; both_iter != op.Columns; ++both_iter)
            {
                temp += this->get_c(column_iter, both_iter) * op.get_c(both_iter, row_iter);
            }
            res.Container.emplace_back(temp);
        }
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont> &Matrix_STL1<cls, Cont>::operator*=(const Matrix_STL1 &op)
{
    if (this->Rows != op.Columns) throw;
    Cont<cls> res{};
    cls temp{};

    for (auto column_iter = 0; column_iter != this->Columns; ++column_iter)
    {
        for (auto row_iter = 0; row_iter != op.Rows; ++row_iter)
        {
            temp = cls{};
            for (auto both_iter = 0; both_iter != op.Columns; ++both_iter)
            {
                temp += this->get_c(both_iter + column_iter * this->Rows) * op.get_c(both_iter * op.Rows + row_iter);
            }
            res.emplace_back(temp);
        }
    }

    this->Rows = op.Rows;
    this->Container = res;
    return *this;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix_STL1<cls, Cont> Matrix_STL1<cls, Cont>::T() const
{
    Matrix_STL1<cls, Cont> res{Cont<cls>(this->size()), this->Rows, this->Columns};
    for (auto iter = 0; iter != this->size(); ++iter)
    {
        res.Container[iter] = this->Container[iter / this->Columns + iter % this->Columns * this->Rows];
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
std::pair<size_t, size_t> Matrix_STL1<cls, Cont>::shape() const
{
    return std::pair<size_t, size_t>{this->Columns, this->Rows};
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
size_t Matrix_STL1<cls, Cont>::size() const
{
    return this->Rows * this->Columns;
}

#endif //DATASTRUCTURE_MATRIX_STL1_HPP
