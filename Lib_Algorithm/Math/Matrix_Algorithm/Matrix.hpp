#ifndef DATASTRUCTURE_MATRIX_HPP
#define DATASTRUCTURE_MATRIX_HPP

#include <vector>

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont = std::vector>
class Matrix
{
public:
    Matrix(size_t const &, size_t const &, cls const & = cls{});
    Matrix(cls const *, size_t const &, size_t const &);
    Matrix(std::initializer_list<cls> const &, size_t const &, size_t const &);
    Matrix(Matrix const &) = default;
    ~Matrix() = default;

    inline Cont<cls> split();
    inline cls *split_arr();
    inline void resize(size_t const &, size_t const &);

    Matrix<cls> operator+(Matrix const &) const;
    Matrix<cls> &operator+=(Matrix const &);
    Matrix<cls> operator-(Matrix const &) const;
    Matrix<cls> &operator-=(Matrix const &);
    Matrix<cls> operator*(Matrix const &) const;
    Matrix<cls> &operator*=(Matrix const &);
    Matrix<cls> operator*(cls const &) const;
    Matrix<cls> &operator*=(cls const &);

    inline cls &get(size_t const &, size_t const &);
    inline cls get_c(size_t const &, size_t const &) const;

    Matrix<cls> T() const;

    [[nodiscard]] std::pair<size_t, size_t> shape() const;
    [[nodiscard]] size_t size() const;

    size_t Columns;
    size_t Rows;
    inline Cont<cls> &operator[](size_t const &);

protected:
    Cont<Cont<cls>> Container;
};

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix<cls, Cont>::Matrix(const size_t &column, const size_t &row, cls const &v)
: Columns{column}, Rows{row}
{
    Cont<Cont<cls>> cont;
    for (auto ci = 0; ci != column; ++ci)
    {
        cont.emplace_back(Cont<cls>{});
        for (auto vi = 0; vi != row; ++vi)
        {
            cont[ci].emplace_back(v);
        }
    }
    Container = cont;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix<cls, Cont>::Matrix(const cls *ptr, const size_t &column, const size_t &row)
: Columns{column}, Rows{row}
{
    Cont<Cont<cls>> cont;
    for (auto ci = 0; ci != column; ++ci)
    {
        cont.emplace_back(Cont<cls>{});
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
Matrix<cls, Cont>::Matrix(const std::initializer_list<cls> &list, const size_t &column, const size_t &row)
: Columns{column}, Rows{row}
{
    Cont<Cont<cls>> cont;
    for (auto ci = 0; ci != column; ++ci)
    {
        cont.emplace_back(Cont<cls>{});
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
std::pair<size_t, size_t> Matrix<cls, Cont>::shape() const
{
    return std::pair<size_t, size_t>(this->Columns, this->Rows);
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
size_t Matrix<cls, Cont>::size() const
{
    return this->Columns * this->Rows;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Cont<cls> Matrix<cls, Cont>::split()
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
cls *Matrix<cls, Cont>::split_arr()
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
void Matrix<cls, Cont>::resize(const size_t &column, const size_t &row)
{
    cls *cont = this->split_arr();
    this = Matrix<cls>{cont, column, row};
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix<cls> Matrix<cls, Cont>::operator+(const Matrix &op) const
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    Matrix<cls> res{this->Columns, this->Rows};
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
Matrix<cls> &Matrix<cls, Cont>::operator+=(const Matrix &op)
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
Matrix<cls> Matrix<cls, Cont>::operator-(const Matrix &op) const
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    Matrix<cls> res{this->Columns, this->Rows};
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
Matrix<cls> &Matrix<cls, Cont>::operator-=(const Matrix &op)
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
Matrix<cls> Matrix<cls, Cont>::operator*(const cls &op) const
{
    if (this->Columns != op.Rows) throw;
    Matrix<cls> res{this->Columns, this->Rows};
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
Matrix<cls> &Matrix<cls, Cont>::operator*=(const cls &op)
{
    if (this->Columns != op.Rows) throw;
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
cls &Matrix<cls, Cont>::get(const size_t &column, const size_t &row)
{
    return (*this)[column][row];
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
cls Matrix<cls, Cont>::get_c(const size_t &column, const size_t &row) const
{
    return *(std::begin(*(std::begin(this->Container) + column)) + row);
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Cont<cls> &Matrix<cls, Cont>::operator[](const size_t &index)
{
    return this->Container[index];
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix<cls> Matrix<cls, Cont>::T() const
{
    Matrix<cls> res{this->Rows, this->Columns};
    for (auto iter = 0; iter != this->size(); ++iter)
    {
        res[iter % this->Rows][iter / this->Rows] = this->get_c(iter / this->Rows, iter % this->Rows);
    }
    return res;
}

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Matrix<cls> Matrix<cls, Cont>::operator*(const Matrix &op) const
{
    if (this->Rows != op.Columns) throw;
    Matrix<cls> res{this->Columns, op.Rows};
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
Matrix<cls> &Matrix<cls, Cont>::operator*=(const Matrix &op)
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



#endif //DATASTRUCTURE_MATRIX_HPP
