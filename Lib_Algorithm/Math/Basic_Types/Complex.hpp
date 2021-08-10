#ifndef DATASTRUCTURE_COMPLEX_HPP
#define DATASTRUCTURE_COMPLEX_HPP

#include <cmath>
#include <ostream>

class Complex
{
public:
    explicit Complex(long double const & = 0, long double const & = 0);

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

Complex::Complex(const long double &re, const long double &im)
    : Real{re}, Imaginary{im} {}

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

#endif //DATASTRUCTURE_COMPLEX_HPP
