#ifndef DATASTRUCTURE_MATRIX_P2_HPP
#define DATASTRUCTURE_MATRIX_P2_HPP

#include "../Abstract/Abstract_Matrix.hpp"

template<typename cls>
class Matrix_P2 : virtual public Static_Matrix<cls>
{
public:
    Matrix_P2(size_t const &, size_t const &, cls const & = cls{});

    Matrix_P2(cls const *, size_t const &, size_t const &);

    Matrix_P2(std::initializer_list <cls> const &, size_t const &, size_t const &);

    Matrix_P2(Matrix_P2 const &) = default;

    ~Matrix_P2() = default;

    inline cls *expand();

    inline void resize(size_t const &, size_t const &);

    Matrix_P2<cls> operator+(Matrix_P2<cls> const &) const;

    Matrix_P2<cls> &operator+=(Matrix_P2<cls> const &);

    Matrix_P2<cls> operator-(Matrix_P2<cls> const &) const;

    Matrix_P2<cls> &operator-=(Matrix_P2<cls> const &);

    Matrix_P2<cls> operator*(Matrix_P2<cls> const &) const;

    Matrix_P2<cls> &operator*=(Matrix_P2<cls> const &);

    Matrix_P2<cls> operator*(cls const &) const;

    Matrix_P2<cls> &operator*=(cls const &);

    inline cls &get(size_t const &, size_t const &);

    inline cls get_c(size_t const &, size_t const &) const;

    Matrix_P2<cls> T() const;

    [[nodiscard]] std::pair <size_t, size_t> shape() const;

    [[nodiscard]] size_t size() const;

    friend std::ostream &operator<<(std::ostream &out, Matrix_P2<cls> const &op)
    {
        for (auto iter1 = 0; iter1 != op.Columns; ++iter1)
        {
            for (auto iter2 = 0; iter2 != op.Rows; ++iter2)
            {
                out << op.Container[iter1][iter2] << " ";
            }
            out << std::endl;
        }
        return out;
    }

    size_t Columns{};

    size_t Rows{};

    inline cls *&operator[](size_t const &);

protected:
    cls **Container;
};

template<typename cls>
Matrix_P2<cls>::Matrix_P2(const size_t &column, const size_t &row, cls const &v)
        : Columns{column}, Rows{row}, Container{new cls *[column]}
{
    for (auto ci = 0; ci != column; ci++)
    {
        this->Container[ci] = new cls[row];
        for (auto ri = 0; ri != row; ++ri)
        {
            this->Container[ci][ri] = v;
        }
    }
}

template<typename cls>
Matrix_P2<cls>::Matrix_P2(const cls *ptr, const size_t &column, const size_t &row)
        : Columns{column}, Rows{row}, Container{new cls *[column]}
{
    for (auto iter = 0; iter != column; ++iter)
    {
        this->Container[iter] = new cls[row];
        for (auto inserter = 0; inserter != row; ++inserter)
        {
            this->Container[iter][inserter] = ptr[iter * row + inserter];
        }
    }
}

template<typename cls>
Matrix_P2<cls>::Matrix_P2(const std::initializer_list <cls> &list, const size_t &column, const size_t &row)
        : Columns{column}, Rows{row}, Container{new cls *[column]}
{
    for (auto iter = 0; iter != column; ++iter)
    {
        this->Container[iter] = new cls[row];
        for (auto inserter = 0; inserter != row; ++inserter)
        {
            this->Container[iter][inserter] = *(std::begin(list) + iter * row + inserter);
        }
    }
}

template<typename cls>
cls *Matrix_P2<cls>::expand()
{
    cls *temp = new cls[this->size()];
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            temp[ci * this->Rows + ri] = this->Container[ci][ri];
        }
    }
    return temp;
}

template<typename cls>
cls *&Matrix_P2<cls>::operator[](const size_t &index)
{
    return this->Container[index];
}

template<typename cls>
cls &Matrix_P2<cls>::get(const size_t &column, const size_t &row)
{
    return this->Container[column][row];
}

template<typename cls>
cls Matrix_P2<cls>::get_c(const size_t &column, const size_t &row) const
{
    return this->Container[column][row];
}

template<typename cls>
std::pair <size_t, size_t> Matrix_P2<cls>::shape() const
{
    return std::pair < size_t, size_t > {this->Columns, this->Rows};
}

template<typename cls>
size_t Matrix_P2<cls>::size() const
{
    return this->Columns * this->Rows;
}

template<typename cls>
Matrix_P2<cls> Matrix_P2<cls>::operator+(const Matrix_P2<cls> &op) const
{
    if (this->Columns != op.Columns || this->Rows != op.Rows) throw;
    Matrix_P2<cls> res{this->Columns, this->Rows};
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            res.Container[ci][ri] =
                    this->Container[ci][ri] + op.Container[ci][ri];
        }
    }
    return res;
}

template<typename cls>
Matrix_P2<cls> &Matrix_P2<cls>::operator+=(const Matrix_P2<cls> &op)
{
    if (this->Columns != op.Columns || this->Rows != op.Rows) throw;
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            this->Container[ci][ri] += op.Container[ci][ri];
        }
    }
    return *this;
}

template<typename cls>
Matrix_P2<cls> Matrix_P2<cls>::operator-(const Matrix_P2<cls> &op) const
{
    if (this->Columns != op.Columns || this->Rows != op.Rows) throw;
    Matrix_P2<cls> res{this->Columns, this->Rows};
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            res.Container[ci][ri] =
                    this->Container[ci][ri] - op.Container[ci][ri];
        }
    }
    return res;
}

template<typename cls>
Matrix_P2<cls> &Matrix_P2<cls>::operator-=(const Matrix_P2<cls> &op)
{
    if (this->Columns != op.Columns || this->Rows != op.Rows) throw;
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            this->Container[ci][ri] -= op.Container[ci][ri];
        }
    }
    return *this;
}

template<typename cls>
Matrix_P2<cls> Matrix_P2<cls>::operator*(const cls &value) const
{
    Matrix_P2<cls> res{this->Columns, this->Rows};
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            res.Container[ci][ri] = this->Container[ci][ri] * value;
        }
    }
    return res;
}

template<typename cls>
Matrix_P2<cls> &Matrix_P2<cls>::operator*=(const cls &value)
{
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            this->Container[ci][ri] *= value;
        }
    }
    return *this;
}

template<typename cls>
void Matrix_P2<cls>::resize(const size_t &column, const size_t &row)
{
    cls *temp = this->resize();
    this = Matrix_P2<cls>{temp, column, row};
}

template<typename cls>
Matrix_P2<cls> Matrix_P2<cls>::T() const {
    Matrix_P2<cls> res{this->Rows, this->Columns};
    for (auto iter = 0; iter != this->size(); iter++)
    {
        res.get(iter % this->Rows, iter / this->Rows) = this->get_c(iter / this->Rows, iter % this->Rows);
    }
    return res;
}

template<typename cls>
Matrix_P2<cls> Matrix_P2<cls>::operator*(const Matrix_P2<cls> &op) const
{
    if (this->Rows != op.Columns) throw;
    Matrix_P2<cls> res{this->Columns, op.Rows};
    cls temp{};
    for (auto ci = 0; ci != this->Columns; ci++)
    {
        for (auto ri = 0; ri != op.Rows; ri++)
        {
            temp = cls{};
            for (auto bi = 0; bi != op.Columns; bi++)
            {
                temp += this->get_c(ci, bi) * op.get_c(bi, ri);
            }
            res.Container[ci][ri] = temp;
        }
    }
    return res;
}

template<typename cls>
Matrix_P2<cls> &Matrix_P2<cls>::operator*=(const Matrix_P2<cls> &op)
{
    if (this->Rows != op.Columns) throw;
    cls **ptr = new cls *[this->Columns];
    cls temp{};
    for (auto ticker = 0; ticker != this->Columns; ticker++)
    {
        ptr[ticker] = new cls[op.Rows];
    }

    for (auto ci = 0; ci != this->Columns; ci++)
    {
        for (auto ri = 0; ri != op.Rows; ri++)
        {
            temp = cls{};
            for (auto bi = 0; bi != op.Columns; bi++)
            {
                temp += this->get_c(ci, bi) * op.get_c(bi, ri);
            }
            ptr[ci][ri] = temp;
        }
    }

    this->Rows = op.Rows;
    this->Container = ptr;
    return *this;
}

#endif //DATASTRUCTURE_MATRIX_P2_HPP
