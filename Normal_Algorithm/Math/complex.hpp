#ifndef DATASTRUCTURE_COMPLEX_HPP
#define DATASTRUCTURE_COMPLEX_HPP

#include <cmath>
#include <ostream>

class complex
{
public:
    explicit complex(long double const & = 0, long double const & = 0);

    complex(complex const &) = default;

    ~complex() = default;

    static long double Re(complex const &);

    static long double Im(complex const &);

    static long double Mod(complex const &);

    [[nodiscard]] long double re() const;

    [[nodiscard]] long double im() const;

    [[nodiscard]] long double mod() const;

    complex operator+(complex const &) const;

    complex operator-(complex const &) const;

    complex operator*(complex const &) const;

    complex operator/(complex const &) const;

    complex &operator+=(complex const &);

    complex &operator-=(complex const &);

    complex &operator*=(complex const &);

    complex &operator/=(complex const &);

    static long double Exp(complex const &);

    static long double Theta(complex const &);

    [[nodiscard]] long double exp() const;

    [[nodiscard]] long double theta() const;

    static complex Pow(complex const &, long const &);

    static std::vector<complex> Root(complex const &, long const &);

    [[nodiscard]] complex pow(long const &) const;

    [[nodiscard]] std::vector<complex> root(long const &) const;

    friend std::ostream &operator<<(std::ostream &&out, complex const &c)
    {
        out << complex::Re(c) << "i + " << complex::Im(c) << "j" << std::endl;
        return out;
    }

private:
    long double Real;
    long double Imaginary;
};

complex::complex(const long double &re, const long double &im)
    : Real{re}, Imaginary{im} {}

long double complex::Re(const complex &c)
{
    return c.Real;
}

long double complex::Im(const complex &c)
{
    return c.Imaginary;
}

long double complex::Mod(const complex &c)
{
    return std::sqrt(std::pow(c.Real, 2) + std::pow(c.Imaginary, 2));
}

long double complex::re() const
{
    return complex::Re(*this);
}

long double complex::im() const
{
    return complex::Im(*this);
}

long double complex::mod() const
{
    return complex::Mod(*this);
}

complex complex::operator+(const complex &c) const
{
    return complex{complex::Re(*this)+complex::Re(c),
                   complex::Im(*this)+complex::Im(c)};
}

complex complex::operator-(const complex &c) const
{
    return complex{complex::Re(*this)-complex::Re(c),
                   complex::Im(*this)-complex::Im(c)};
}

complex complex::operator*(const complex &c) const
{
    return complex{complex::Re(*this)*complex::Re(c)-complex::Im(*this)*complex::Im(c),
                   complex::Re(*this)*complex::Im(c)+complex::Im(*this)*complex::Re(c)};
}

complex complex::operator/(const complex &c) const
{
    return complex{(complex::Re(*this)*complex::Re(c)+complex::Im(*this)*complex::Im(c))/complex::Mod(c),
                   (complex::Im(*this)*complex::Re(c)-complex::Re(*this)*complex::Im(c))/complex::Mod(c)};
}

complex &complex::operator+=(const complex &c)
{
    this->Real+=complex::Re(c);
    this->Imaginary+=complex::Im(c);
    return *this;
}

complex &complex::operator-=(const complex &c)
{
    this->Real-=complex::Re(c);
    this->Imaginary-=complex::Im(c);
    return *this;
}

complex &complex::operator*=(const complex &c)
{
    this->Real *= complex::Re(c);
    this->Real -= complex::Im(c)*complex::Im(*this);
    this->Imaginary *= complex::Re(c);
    this->Imaginary += complex::Re(*this)*complex::Im(c);
    return *this;
}

complex &complex::operator/=(const complex &c)
{
    this->Real *= complex::Re(c);
    this->Real += complex::Im(*this)*complex::Im(c);
    this->Real /= complex::Mod(c);
    this->Imaginary *=complex::Re(c);
    this->Imaginary -=complex::Re(*this)*complex::Im(c);
    this->Imaginary /= complex::Mod(c);
    return *this;
}

long double complex::Exp(const complex &c)
{
    return std::log(complex::Mod(c));
}

long double complex::Theta(const complex &c)
{
    return std::acos(complex::Re(c)/complex::Mod(c));
}

long double complex::exp() const
{
    return complex::Exp(*this);
}

long double complex::theta() const
{
    return complex::Theta(*this);
}

complex complex::Pow(const complex &c, long const &x)
{
    return complex{std::exp(complex::Exp(c)*x)*std::cos(complex::Theta(c)*x),
                   std::exp(complex::Exp(c)*x)*std::sin(complex::Theta(c)*x)};
}

std::vector<complex> complex::Root(const complex &c, long const &x)
{
    long double const base = std::exp(complex::Exp(c)/x);
    long double const ark = complex::Theta(c)/x;
    long double const pi = std::atan(1) * 4;
    std::vector<complex> res {};
    for(auto i=0;i!=x;++i) res.emplace_back(complex{base*std::cos(ark+2*pi/x), base*std::sin(ark+2*pi/x)});
    return res;
}

complex complex::pow(long const &x) const
{
    return complex::Pow(*this, x);
}

std::vector<complex> complex::root(long const &x) const
{
    return complex::Root(*this, x);
}

#endif //DATASTRUCTURE_COMPLEX_HPP
