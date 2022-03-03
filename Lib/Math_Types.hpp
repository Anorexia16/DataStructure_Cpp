#ifndef DATASTRUCTURE_MATH_TYPES_HPP
#define DATASTRUCTURE_MATH_TYPES_HPP

#include <ostream>
#include <cmath>
#include <vector>

class Complex
{
public:
    Complex() = default;

    Complex(long double const &, long double const &);

    Complex(std::initializer_list<long double> const &);

    Complex(Complex const &) = default;

    ~Complex() = default;

    static long double Re(Complex const &);

    static long double Im(Complex const &);

    static long double Mod(Complex const &);

    [[nodiscard]] long double re() const;

    [[nodiscard]] long double im() const;

    [[nodiscard]] long double mod() const;

    Complex operator+(Complex const &) const;

    Complex operator-(Complex const &) const;

    Complex operator*(Complex const &) const;

    Complex operator/(Complex const &) const;

    Complex &operator+=(Complex const &);

    Complex &operator-=(Complex const &);

    Complex &operator*=(Complex const &);

    Complex &operator/=(Complex const &);

    static long double Exp(Complex const &);

    static long double Theta(Complex const &);

    [[nodiscard]] long double exp() const;

    [[nodiscard]] long double theta() const;

    static Complex Pow(Complex const &, long const &);

    static std::vector<Complex> Root(Complex const &, long const &);

    [[nodiscard]] Complex pow(long const &) const;

    [[nodiscard]] std::vector<Complex> root(long const &) const;

    friend std::ostream &operator<<(std::ostream &&out, Complex const &c)
    {
        out << Complex::Re(c) << "i + " << Complex::Im(c) << "j" << std::endl;
        return out;
    }

private:
    long double Real;
    long double Imaginary;
};

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont = std::vector>
class Matrix
{
public:
    Matrix(size_t const &, size_t const &, cls const & = cls{});
    Matrix(cls const *, size_t const &, size_t const &);
    Matrix(std::initializer_list<cls> const &, size_t const &, size_t const &);
    Matrix &operator=(Matrix const &) noexcept = default;
    Matrix &operator=(Matrix &&) noexcept = default;
    Matrix(Matrix const &) noexcept = default;
    Matrix(Matrix &&) noexcept = default;
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
    template<typename tp>
    inline void set(size_t const &, size_t const &, tp &&);

    Matrix<cls> T() const;

    [[nodiscard]] std::pair<size_t, size_t> shape() const;
    [[nodiscard]] size_t size() const;

    size_t Columns;
    size_t Rows;
    inline Cont<cls> &operator[](size_t const &);

protected:
    Cont<Cont<cls>> Container;
};

template<size_t Columns, size_t Rows, class cls = long double>
class Static_Matrix
{
public:
    explicit Static_Matrix(cls const & = cls{});
    explicit Static_Matrix(cls const *);
    Static_Matrix(std::initializer_list<cls> const &);
    Static_Matrix &operator=(Static_Matrix const &) noexcept = default;
    Static_Matrix &operator=(Static_Matrix &&) noexcept = default;
    Static_Matrix(Static_Matrix const &) noexcept = default;
    Static_Matrix(Static_Matrix &&) noexcept = default;
    ~Static_Matrix() = default;

    inline cls *split();

    template<size_t New_Columns, size_t New_Rows>
    inline Static_Matrix<New_Columns, New_Rows> resize();

    Static_Matrix<Columns,Rows, cls> operator+(Static_Matrix const &) const;
    Static_Matrix<Columns,Rows, cls> &operator+=(Static_Matrix const &);
    Static_Matrix<Columns,Rows, cls> operator-(Static_Matrix const &) const;
    Static_Matrix<Columns,Rows, cls> &operator-=(Static_Matrix const &);

    template<size_t C2, size_t R2, class tp>
    Static_Matrix<Columns,R2, cls> operator*(Static_Matrix<C2, R2, tp> const &) const;
    Static_Matrix<Columns,Rows, cls> operator*(cls const &) const;
    Static_Matrix<Columns,Rows, cls> &operator*=(cls const &);

    inline cls &get(size_t const &, size_t const &);
    inline cls get_c(size_t const &, size_t const &) const;
    template<typename tp>
    inline void set(size_t const &, size_t const &, tp &&);

    Static_Matrix<Rows, Columns, cls> T() const;

    [[nodiscard]] std::pair<size_t, size_t> shape() const;
    [[nodiscard]] size_t size() const;
    inline cls *&operator[](size_t const &);

protected:
    cls** Container;
};

template<class cls>
concept fo_type = requires(cls const &c) {c+c;c-c;c+=c;c-=c;};

template<class cls>
concept so_type = requires(cls const &c) {c*c;c/c;c%c;c*=c;c/=c;c%=c;};


struct Infinity {
    template<class cls>
    constexpr bool operator>
            (cls const &) const
    {return true;}

    template<class cls>
    constexpr bool operator<
            (cls const &) const
    {return false;}

    template<class cls>
    constexpr bool operator>=
            (cls const &)
    const {return true;}

    template<class cls>
    constexpr bool operator<=
            (cls const &) const
    {return false;}

    template<class cls>
    constexpr bool operator==
            (cls const &) const
    {return false;}

    template<class cls>
    constexpr bool operator!=
            (cls const &) const
    {return true;}

    constexpr bool operator>
            (Infinity const &) const
    {return false;}

    constexpr bool operator<
            (Infinity const &) const
    {return false;}

    constexpr bool operator>=
            (Infinity const &) const
    {return true;}

    constexpr bool operator<=
            (Infinity const &) const
    {return true;}

    constexpr bool operator==
            (Infinity const &) const
    {return true;}

    constexpr bool operator!=
            (Infinity const &) const
    {return false;}

    template<fo_type cls>
    Infinity operator+
            (cls const &) const
    {return Infinity{};}

    template<fo_type cls>
    Infinity operator-
            (cls const &) const
    {return Infinity{};}

    template<fo_type cls>
    Infinity &operator+=
            (cls const &)
    {return *this;}

    template<fo_type cls>
    Infinity &operator-=
            (cls const &)
    {return *this;}

    template<so_type cls>
    Infinity operator*
            (cls const &) const
    {return Infinity{};}

    template<so_type cls>
    Infinity operator/
            (cls const &) const
    {return Infinity{};}

    template<so_type cls>
    Infinity &operator*=
            (cls const &)
    {return *this;}

    template<so_type cls>
    Infinity &operator/=
            (cls const &)
    {return *this;}

    template<so_type cls>
    Infinity operator%
            (cls const &) const
    = delete;

    template<so_type cls>
    Infinity &operator%=
            (cls const &)
    = delete;

    Infinity operator+
            (Infinity const &) const
    {return Infinity{};}

    Infinity operator-
            (Infinity const &) const
    = delete;

    Infinity &operator+=
            (Infinity const &)
    {return *this;}

    Infinity &operator-=
            (Infinity const &)
    = delete;

    Infinity operator*
            (Infinity const &) const
    {return Infinity{};}

    Infinity operator/
            (Infinity const &) const
    = delete;

    Infinity operator%
            (Infinity const &) const
    = delete;

    Infinity &operator*=
            (Infinity const &)
    {return *this;}

    Infinity &operator/=
            (Infinity const &)
    = delete;

    Infinity &operator%=
            (Infinity const &)
    = delete;

    const Infinity operator++(int) const
    {return Infinity{};}

    const Infinity operator--(int) const
    {return Infinity{};}

    Infinity &operator++()
    {return *this;}

    Infinity &operator--()
    {return  *this;}

    template<so_type cls>
    cls dev(cls const &c)
    {return cls{};}

    template<so_type cls>
    cls &dev_r(cls &c)
    {c = cls{};return c;}
};

template<typename I, typename II>
struct pair{
    I first{};
    II second{};
};

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Columns, Rows, cls>::Static_Matrix(cls const &v)
{
    Container = new cls* [Columns];
    for (auto ci = 0; ci != Columns; ++ci)
    {
        Container[ci] = new cls [Rows];
        for (auto vi = 0; vi != Rows; ++vi)
        {
            Container[ci][vi] = v;
        }
    }
}

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Columns, Rows, cls>::Static_Matrix(const cls *ptr)
{
    Container = new cls* [Columns];
    for (auto ci = 0; ci != Columns; ++ci)
        Container[ci] = new cls [Rows];
    for(auto i=0;i!=Rows*Columns;++i)
        Container[i/Rows][i%Rows] = ptr[i];
}

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Columns, Rows, cls>::Static_Matrix(const std::initializer_list<cls> &list)
{
    Container = new cls* [Columns];
    for (auto ci = 0; ci != Columns; ++ci)
        Container[ci] = new cls [Rows];
    for(auto i=0;i!=Rows*Columns;++i)
        Container[i/Rows][i%Rows] = *(list.begin()+i);
}


template<size_t Columns, size_t Rows, class cls>
std::pair<size_t, size_t> Static_Matrix<Columns, Rows, cls>::shape() const
{
    return {Columns, Rows};
}

template<size_t Columns, size_t Rows, class cls>
size_t Static_Matrix<Columns, Rows, cls>::size() const
{
    return Columns * Rows;
}

template<size_t Columns, size_t Rows, class cls>
cls *Static_Matrix<Columns, Rows, cls>::split()
{
    cls *res = new cls[this->size()];
    size_t global_index = 0;
    for (auto &&ci: Container)
    {
        for (auto &&iter: ci)
        {
            res[global_index] = iter;
            ++global_index;
        }
    }
    return res;
}

template<size_t Columns, size_t Rows, class cls>
template<size_t New_Columns, size_t New_Rows>
Static_Matrix<New_Columns, New_Rows> Static_Matrix<Columns, Rows, cls>::resize()
{
    cls *cont = this->split_arr();
    return Static_Matrix<Columns, Rows, cls> {cont};
}

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Columns, Rows, cls> Static_Matrix<Columns, Rows, cls>::operator+(const Static_Matrix &op) const
{
    if (Columns != op.Columns || Rows != op.Rows) throw;
    Static_Matrix<Columns, Rows, cls> res{Columns, Rows};
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != Rows; ++ri)
        {
            res.Container[ci][ri] = Container[ci][ri] + op.Container[ci][ri];
        }
    }
    return res;
}

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Columns, Rows, cls> &Static_Matrix<Columns, Rows, cls>::operator+=(const Static_Matrix &op)
{
    if (Columns != op.Columns || Rows != op.Rows) throw;
    for (size_t ci = 0; ci != Columns; ++ci)
    {
        for (size_t ri = 0; ri !=Rows; ++ri)
        {
            Container[ci][ri] += op.Container[ci][ri];
        }
    }
    return *this;
}

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Columns, Rows, cls> Static_Matrix<Columns, Rows, cls>::operator-(const Static_Matrix &op) const
{
    if (Columns != op.Columns || Rows != op.Rows) throw;
    Static_Matrix<Columns, Rows, cls> res{Columns, Rows};
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != Rows; ++ri)
        {
            res.Container[ci][ri] = Container[ci][ri] - op.Container[ci][ri];
        }
    }
    return res;
}

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Columns, Rows, cls> &Static_Matrix<Columns, Rows, cls>::operator-=(const Static_Matrix &op)
{
    if (Columns != op.Columns ||Rows != op.Rows) throw;
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != this->Rows; ++ri)
        {
            Container[ci][ri] -= op.Container[ci][ri];
        }
    }
    return *this;
}

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Columns, Rows, cls> Static_Matrix<Columns, Rows, cls>::operator*(const cls &op) const
{
    if (Columns != op.Rows) throw;
    Static_Matrix<Columns, Rows, cls> res{Columns, Rows};
    for (size_t ci = 0; ci != op.Columns; ++ci)
    {
        for (size_t ri = 0; ri != Rows; ++ri)
        {
            res.Container[ci][ri] = Container[ci][ri] * op;
        }
    }
    return res;
}

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Columns, Rows, cls> &Static_Matrix<Columns, Rows, cls>::operator*=(const cls &op)
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

template<size_t Columns, size_t Rows, class cls>
cls &Static_Matrix<Columns, Rows, cls>::get(const size_t &column, const size_t &row)
{
    return Container[column][row];
}

template<size_t Columns, size_t Rows, class cls>
cls Static_Matrix<Columns, Rows, cls>::get_c(const size_t &column, const size_t &row) const
{
    return Container[column][row];
}

template<size_t Columns, size_t Rows, class cls>
cls *&Static_Matrix<Columns, Rows, cls>::operator[](const size_t &index)
{
    return Container[index];
}

template<size_t Columns, size_t Rows, class cls>
Static_Matrix<Rows, Columns, cls> Static_Matrix<Columns, Rows, cls>::T() const
{
    Static_Matrix<Rows, Columns, cls> res{this->Rows, this->Columns};
    for (auto iter = 0; iter != this->size(); ++iter)
    {
        res.Container[iter % this->Rows][iter / this->Rows] = get_c(iter / this->Rows, iter % this->Rows);
    }
    return res;
}

template<size_t Columns, size_t Rows, class cls>
template<size_t C2, size_t R2, class tp>
Static_Matrix<Columns, R2, cls> Static_Matrix<Columns, Rows, cls>::
operator*(const Static_Matrix<C2, R2, tp> &op) const
{
    if (Rows != C2) throw;
    Static_Matrix<Columns, R2, cls> res {};
    cls temp{};
    for (auto ci = 0; ci != Columns; ++ci) {
        for (auto ri = 0; ri != R2; ++ri) {
            temp = cls{};
            for (auto bi = 0; bi != C2; ++bi) {
                temp += get_c(ci, bi) * cls{op.get_c(bi, ri)};
            }
            res.Container[ci][ri] = temp;
        }
    }
    return res;
}

template<size_t Columns, size_t Rows, class cls>
template<typename tp>
void Static_Matrix<Columns, Rows, cls>::set(const size_t &ci, const size_t &ri, tp &&arg) {
    Container[ci][ri] = std::forward<>(arg);
}

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

template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
template<typename tp>
void Matrix<cls, Cont>::set(const size_t &ci, const size_t &ri, tp &&arg) {
    Container[ci][ri] = std::forward<>(arg);
}

Complex::Complex(const long double &re, const long double &im)
        : Real{re}, Imaginary{im} {}

Complex::Complex(std::initializer_list<long double> const &pair)
        : Real{*pair.begin()}, Imaginary{*(pair.begin()+1)} {}


long double Complex::Re(const Complex &c)
{
    return c.Real;
}

long double Complex::Im(const Complex &c)
{
    return c.Imaginary;
}

long double Complex::Mod(const Complex &c)
{
    return std::sqrt(std::pow(c.Real, 2) + std::pow(c.Imaginary, 2));
}

long double Complex::re() const
{
    return Complex::Re(*this);
}

long double Complex::im() const
{
    return Complex::Im(*this);
}

long double Complex::mod() const
{
    return Complex::Mod(*this);
}

Complex Complex::operator+(const Complex &c) const
{
    return Complex{Complex::Re(*this)+Complex::Re(c),
                   Complex::Im(*this)+Complex::Im(c)};
}

Complex Complex::operator-(const Complex &c) const
{
    return Complex{Complex::Re(*this)-Complex::Re(c),
                   Complex::Im(*this)-Complex::Im(c)};
}

Complex Complex::operator*(const Complex &c) const
{
    return Complex{Complex::Re(*this)*Complex::Re(c)-Complex::Im(*this)*Complex::Im(c),
                   Complex::Re(*this)*Complex::Im(c)+Complex::Im(*this)*Complex::Re(c)};
}

Complex Complex::operator/(const Complex &c) const
{
    return Complex{(Complex::Re(*this)*Complex::Re(c)+Complex::Im(*this)*Complex::Im(c))/Complex::Mod(c),
                   (Complex::Im(*this)*Complex::Re(c)-Complex::Re(*this)*Complex::Im(c))/Complex::Mod(c)};
}

Complex &Complex::operator+=(const Complex &c)
{
    this->Real+=Complex::Re(c);
    this->Imaginary+=Complex::Im(c);
    return *this;
}

Complex &Complex::operator-=(const Complex &c)
{
    this->Real-=Complex::Re(c);
    this->Imaginary-=Complex::Im(c);
    return *this;
}

Complex &Complex::operator*=(const Complex &c)
{
    this->Real *= Complex::Re(c);
    this->Real -= Complex::Im(c)*Complex::Im(*this);
    this->Imaginary *= Complex::Re(c);
    this->Imaginary += Complex::Re(*this)*Complex::Im(c);
    return *this;
}

Complex &Complex::operator/=(const Complex &c)
{
    this->Real *= Complex::Re(c);
    this->Real += Complex::Im(*this)*Complex::Im(c);
    this->Real /= Complex::Mod(c);
    this->Imaginary *=Complex::Re(c);
    this->Imaginary -=Complex::Re(*this)*Complex::Im(c);
    this->Imaginary /= Complex::Mod(c);
    return *this;
}

long double Complex::Exp(const Complex &c)
{
    return std::log(Complex::Mod(c));
}

long double Complex::Theta(const Complex &c)
{
    return std::acos(Complex::Re(c)/Complex::Mod(c));
}

long double Complex::exp() const
{
    return Complex::Exp(*this);
}

long double Complex::theta() const
{
    return Complex::Theta(*this);
}

Complex Complex::Pow(const Complex &c, long const &x)
{
    return Complex{std::exp(Complex::Exp(c)*x)*std::cos(Complex::Theta(c)*x),
                   std::exp(Complex::Exp(c)*x)*std::sin(Complex::Theta(c)*x)};
}

std::vector<Complex> Complex::Root(const Complex &c, long const &x)
{
    long double const base = std::exp(Complex::Exp(c)/x);
    long double const ark = Complex::Theta(c)/x;
    long double const pi = std::atan(1) * 4;
    std::vector<Complex> res {};
    for(auto i=0;i!=x;++i) res.emplace_back(Complex{base*std::cos(ark+2*pi/x), base*std::sin(ark+2*pi/x)});
    return res;
}

Complex Complex::pow(long const &x) const
{
    return Complex::Pow(*this, x);
}

std::vector<Complex> Complex::root(long const &x) const
{
    return Complex::Root(*this, x);
}

#endif //DATASTRUCTURE_MATH_TYPES_HPP
