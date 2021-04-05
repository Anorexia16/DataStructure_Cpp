#ifndef DATASTRUCTURE_MATRIX_N2_HPP
#define DATASTRUCTURE_MATRIX_N2_HPP

#include "Abstract_Matrix.hpp"
#include "Chain_Bidirectional_Circle.hpp"

template<typename cls>
class Matrix_N2 : virtual public Matrix<cls>, virtual public ChainBC<cls>
{
public:
    Matrix_N2(size_t const &, size_t const &);

    Matrix_N2(cls const *, size_t const &, size_t const &);

    Matrix_N2(std::initializer_list<cls> const &, size_t const &, size_t const &);

    Matrix_N2(Matrix_N2 const &) = default;

    ~Matrix_N2() = default;

    inline cls *expand();

    inline void resize(size_t const &, size_t const &);

    Matrix_N2<cls> operator+(Matrix_N2<cls> const &) const;

    Matrix_N2<cls> &operator+=(Matrix_N2<cls> const &);

    Matrix_N2<cls> operator-(Matrix_N2<cls> const &) const;

    Matrix_N2<cls> &operator-=(Matrix_N2<cls> const &);

    Matrix_N2<cls> operator*(Matrix_N2<cls> const &) const;

    Matrix_N2<cls> &operator*=(Matrix_N2<cls> const &);

    Matrix_N2<cls> operator*(cls const &) const;

    Matrix_N2<cls> &operator*=(cls const &);

    inline cls &get(size_t const &, size_t const &);

    inline cls get_c(size_t const &, size_t const &) const;

    Matrix_N2<cls> T() const;

    [[nodiscard]] std::pair<size_t, size_t> shape() const;

    [[nodiscard]] size_t size() const;

    friend std::ostream &operator<<(std::ostream &out, Matrix_N2<cls> const &op) {
        for (auto iter1 = 0; iter1 != op.ColBmns; iter1++) {
            for (auto iter2 = 0; iter2 != op.Rows; iter2++) {
                out << op.Container[iter1][iter2] << " ";
            }
            out << std::endl;
        }
        return out;
    }

    size_t Columns;

    size_t Rows;

    inline ChainBC<cls> &operator[](size_t const &);

protected:
    ChainBC<ChainBC<cls>> Container;
};

template<typename cls>
Matrix_N2<cls>::Matrix_N2(const size_t &column, const size_t &row)
        :Columns{column}, Rows{row}, Container{ChainBC<ChainBC<cls>>(column)}
{
    NodeB<ChainBC<cls>> *Head{this->Container.Head};
    for (auto ci = 0; ci != column; ++ci)
    {
        Head->Next = new NodeB<ChainBC<cls>>{NodeB<cls>{row}, Head, Head->Next};
        Head->Next->Next->Prev = Head->Next;
        for (auto ri = 0; ri != row; ++ri)
        {
            NodeB<cls> *circle_head{Head->Next->Element.Head};
            circle_head->Next = new NodeB<cls>{cls{}, circle_head, circle_head->Next};
            circle_head->Next->Next->Prev = circle_head->Next;
        }
    }
}

template<typename cls>
Matrix_N2<cls>::Matrix_N2(const cls *ptr, const size_t &column, const size_t &row)
        : Columns{column}, Rows{row}, Container{ChainBC<ChainBC<cls>>(column)}
{
    NodeB<ChainBC<cls>> *Head{this->Container.Head};
    for (auto ci = 0; ci != column; ++ci)
    {
        Head->Next = new NodeB<ChainBC<cls>>{NodeB<cls>{row}, Head, Head->Next};
        Head->Next->Next->Prev = Head->Next;
        for (auto ri = 0; ri != row; ++ri)
        {
            NodeB<cls> *circle_head{Head->Next->Element.Head};
            circle_head->Next = new NodeB<cls>{*(ptr + ri + ci * row), circle_head, circle_head->Next};
            circle_head->Next->Next->Prev = circle_head->Next;
        }
    }
}

template<typename cls>
Matrix_N2<cls>::Matrix_N2(const std::initializer_list<cls> &list, const size_t &column, const size_t &row)
        : Columns{column}, Rows{row}, Container{ChainBC<ChainBC<cls>>(column)}
{
    NodeB<ChainBC<cls>> *Head{this->Container.Head};
    for (auto ci = 0; ci != column; ++ci)
    {
        Head->Next = new NodeB<ChainBC<cls>>{NodeB<cls>{row}, Head, Head->Next};
        Head->Next->Next->Prev = Head->Next;
        for (auto ri = 0; ri != row; ++ri)
        {
            NodeB<cls> *circle_head{Head->Next->Element.Head};
            circle_head->Next = new NodeB<cls>{*(std::begin(list) + ri + ci * row), circle_head, circle_head->Next};
            circle_head->Next->Next->Prev = circle_head->Next;
        }
    }
}

template<typename cls>
cls *Matrix_N2<cls>::expand()
{
    cls *res = new cls[this->Size];
    size_t gi = 0;
    NodeB<ChainBC<cls>> *ci{this->Container.Head->Next};
    for (; ci != this->Container.Head; ci = ci->Next)
    {
        NodeB<cls> *ri{ci->Element.Head->Next};
        for (; ri != ci->Element.Head; ri = ri->Next)
        {
            res[gi] = ri->Element;
            ++gi;
        }
    }
    return res;
}

template<typename cls>
void Matrix_N2<cls>::resize(const size_t &column, const size_t &row)
{
    cls *text = this->expand();
    this = Matrix_N2<cls>{text, column, row};
}

template<typename cls>
Matrix_N2<cls> Matrix_N2<cls>::operator+(const Matrix_N2<cls> &op) const
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    Matrix_N2 res{this->Columns, op.Rows};
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            res.get(ci, ri) = this->get_c(ci, ri) + op.get_c(ci, ri);
        }
    }
    return res;
}

template<typename cls>
Matrix_N2<cls> &Matrix_N2<cls>::operator+=(const Matrix_N2<cls> &op)
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            this->get_c(ci, ri) += op.get_c(ci, ri);
        }
    }
    return *this;
}

template<typename cls>
Matrix_N2<cls> Matrix_N2<cls>::operator-(const Matrix_N2<cls> &op) const
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    Matrix_N2 res{this->Columns, op.Rows};
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            res.get(ci, ri) = this->get_c(ci, ri) - op.get_c(ci, ri);
        }
    }
    return res;
}

template<typename cls>
Matrix_N2<cls> &Matrix_N2<cls>::operator-=(const Matrix_N2<cls> &op)
{
    if (this->Columns != op.Columns || this->Rows != this->Rows) throw;
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            this->get_c(ci, ri) -= op.get_c(ci, ri);
        }
    }
    return *this;
}

template<typename cls>
Matrix_N2<cls> Matrix_N2<cls>::operator*(const cls &v) const
{
    Matrix_N2 res{this->Columns, this->Rows};
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            res.get(ci, ri) = v * this->get_c(ci, ri);
        }
    }
    return res;
}

template<typename cls>
Matrix_N2<cls> &Matrix_N2<cls>::operator*=(const cls &v)
{
    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        for (auto ri = 0; ri != this->Rows; ++ri)
        {
            this->get_c(ci, ri) *= v;
        }
    }
    return *this;
}

template<typename cls>
cls &Matrix_N2<cls>::get(const size_t &column, const size_t &row)
{
    NodeB<ChainBC<cls>> *ci{this->Container.Head->Next};
    size_t cn = column, rn = row;
    for (; cn != 0; --cn)
    {
        ++ci;
    }
    NodeB<cls> *ri{ci->Element.Head->Next};
    for (; rn != 0; --rn)
    {
        ++ri;
    }
    return ri->Element;
}

template<typename cls>
cls Matrix_N2<cls>::get_c(const size_t &column, const size_t &row) const
{
    NodeB<ChainBC<cls>> *ci{this->Container.Head->Next};
    size_t cn = column, rn = row;
    for (; cn != 0; --cn)
    {
        ++ci;
    }
    NodeB<cls> *ri{ci->Element.Head->Next};
    for (; rn != 0; --rn)
    {
        ++ri;
    }
    return ri->Element;
}

template<typename cls>
std::pair<size_t, size_t> Matrix_N2<cls>::shape() const
{
    return std::pair<size_t, size_t>(this->Columns, this->Rows);
}

template<typename cls>
size_t Matrix_N2<cls>::size() const
{
    return this->Columns * this->Rows;
}

template<typename cls>
ChainBC<cls> &Matrix_N2<cls>::operator[](const size_t &index)
{
    NodeB<cls> *iter{this->Head};
    for (size_t temp = index; index != 0; --temp, iter = iter->Next);
    return iter->Element;
}

template<typename cls>
Matrix_N2<cls> Matrix_N2<cls>::T() const
{
    Matrix_N2<cls> res{this->Rows, this->Columns};
    for (auto iter = 0; iter != this->size(); ++iter)
    {
        res.get(iter % this->Rows, iter / this->Rows) = this->get_c(iter / this->Rows, iter % this->Rows);
    }
    return res;
}

template<typename cls>
Matrix_N2<cls> Matrix_N2<cls>::operator*(const Matrix_N2<cls> &op) const
{
    if (this->Rows != op.Columns) throw;
    Matrix_N2<cls> res{this->Columns, op.Rows};
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

template<typename cls>
Matrix_N2<cls> &Matrix_N2<cls>::operator*=(const Matrix_N2<cls> &op)
{
    if (this->Rows != op.Columns) throw;
    auto res = ChainBC<ChainBC<cls>>(this->Columns);
    NodeB<ChainBC<cls>> *Head{res.Head};

    for (auto ci = 0; ci != this->Columns; ++ci)
    {
        Head->Next = new NodeB<ChainBC<cls>>{NodeB<cls>{op.Rows}, Head, Head->Next};
        Head->Next->Next->Prev = Head->Next;
        for (auto ri = 0; ri != op.Rows; ++ri)
        {
            NodeB<cls> *circle_head{Head->Next->Element.Head};
            circle_head->Next = new NodeB<cls>{cls{}, circle_head, circle_head->Next};
            circle_head->Next->Next->Prev = circle_head->Next;
        }
    }
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


#endif //DATASTRUCTURE_MATRIX_N2_HPP
