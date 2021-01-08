#ifndef DATASTRUCTURE_SECTION1_CPP_REVIEW_HPP // 数据结构与算法第一章习题练习
#define DATASTRUCTURE_SECTION1_CPP_REVIEW_HPP

#include <cmath>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>


// 1.1 因为交换函数中的参数仅仅只是对应值的拷贝，如果需要交换数需要采用他们的引用。
void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

// 1.2
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
int count(const CONT<T> &vec, const T &x) {
    int num = 0;
    for (auto &&iter: vec) {
        if (iter == x) {
            num += 1;
        }
    }
    return num;
}

// 1.3
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
void fill(CONT<T> vec, const T &x, int start, int end) {
    for (auto &&iter: vec) {
        iter = x;
    }
}

// 1.4
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
T inner_product(CONT<T> Vec1, CONT<T> Vec2) {
    T sum;
    if (Vec1.Size() == Vec2.Size()) {
        for (int i = 0; i != Vec1.Size(); i++) {
            sum += Vec1[i] * Vec2[i];
        }
    } else {
        throw;
    }
    return sum;
}

// 1.5
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
CONT<T> &iota(CONT<T> &x) {
    for (int i = 0; i != x.Size(); i++) {
        x[i] += i;
    }
}

// 1.6
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
bool is_sorted(CONT<T> const &x) {
    if (x.Size() < 2) {
        return true;
    }
    bool mod = x[0] > x[1];
    for (auto iter = 0; iter != x.Size() - 1; iter++) {
        if (mod ? (x[0] < x[1]) : (x[0] > x[1])) return false;
    }
    return true;
}

// 1.7
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
int mismatch(CONT<T> const &op1, CONT<T> const &op2) {
    for (int i = 0; i != (op1.Size() < op2.Size() ? op1.Size() : op2.Size()); i++) {
        if (op1[i] != op2[i]) {
            return i;
        }
    }
    return -1;
}

// 1.8
// No, one for int(int, int, int) and the other is float(int, int, int);

// 1.9
// 1-1, 1-2 ,error(no signification with parameter (int, int, float)), 1-2;

// 1.10
// pass

// 1.11
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
int count11(CONT<T> const &vec, const T &x) {
    if (x.Size() < 2) throw;
    int num = 0;
    for (auto &&iter: vec) {
        if (iter == x) {
            num += 1;
        }
    }
    return num;
}

// 1.12
template<class T>
void make2dArray(T **&x, int numberOfRows, const int *RowSize) {
    x = new T *[numberOfRows];
    for (int i = 0; i < numberOfRows; i++) {
        x[i] = new T[RowSize[i]];
    }
}

// 1.13
template<class T>
T *&changeLength1D(T *&x, int new_length, int old_length) {
    T *arr = new T[new_length];
    int length = old_length < new_length ? old_length : new_length;
    for (int i = 0; i < length; i++) {
        arr[i] = x[i];
    }
    x = arr;
}

// 1.14
template<class T>
T **&changeLength2D(T **&x, int rows, int columns, int old_rows, int old_columns) {
    T **arr = changeLength1D<T *>(x, rows, old_rows);
    int Col = old_rows < rows ? old_rows : rows;
    for (int i = 0; i != Col; i++) {
        arr[i] = changeLength1D<T>(arr[i], columns, old_columns);
    }
    x = arr;
}

// assistance class: currency
enum signType {
    plus, minus
};

class currency {
public:
    explicit currency(signType TheSign = plus, unsigned long TheDollars = 0, unsigned int TheCents = 0)
            : Sign{TheSign}, Dollars{TheDollars}, Cents{TheCents} {};

    ~currency() = default;

    void SetValue(signType, unsigned long const &, unsigned int const &);

    void SetValue(double);

    [[nodiscard]] signType getSign() const { return Sign; }

    [[nodiscard]] unsigned long getDollars() const { return Dollars; }

    [[nodiscard]] unsigned int getCents() const { return Cents; }

    friend std::ostream &operator<<(std::ostream &out, currency const &x);

    currency &value_from_stream(std::istream &in);

    currency &operator+=(currency const &x);

    currency operator+(currency const &x) const;

    currency operator-(currency const &x) const;

    currency operator-=(currency const &x);

    currency operator%(currency const &x) const;

    currency &operator%=(currency const &x);

    currency operator*(currency const &x) const;

    currency &operator*=(currency const &x);

    currency operator/(currency const &x) const;

    currency &operator/=(currency const &x);

    currency &operator=(double const &x);

    [[nodiscard]] double value() const;

private:
    explicit operator double();

    signType Sign;
    unsigned long Dollars;
    unsigned int Cents;
};

void currency::SetValue(signType theSign, unsigned long const &theDollars, unsigned int const &theCents) {
    this->Sign = theSign;
    this->Dollars = theDollars;
    this->Cents = theCents;
}

void currency::SetValue(double value) {
    this->Sign = (value >= 0) ? plus : minus;
    this->Dollars = std::floor(value);
    this->Cents = std::floor(100 * (value - std::floor(value)));
}

currency::operator double() {
    double value = this->Dollars + 0.01 * this->Cents;
    value = (this->Sign == plus) ? value : -value;
    return value;
}

std::ostream &operator<<(std::ostream &out, currency const &x) {
    out << (double) const_cast<currency &>(x);
    return out;
}

template<typename T, class CONT>
void fill(CONT vec, const T &x, int start, int end) {
    for (auto i = std::begin(vec) + start; i != std::begin(vec) + end; i++) {
        *i = x;
    }
}

double currency::value() const {
    double value = this->Dollars + 0.01 * this->Cents;
    value = (this->Sign == plus) ? value : -value;
    return value;
}

currency &currency::operator+=(currency const &x) {
    double value = this->value() + x.value();
    this->SetValue(value);
    return *this;
}

currency currency::operator+(currency const &x) const {
    double value = this->value() + x.value();
    currency temp{};
    temp.SetValue(value);
    return temp;
}

// 1.15
// 1)
std::pair<double, double> value_1151() {
    return std::pair<double, double>{std::pow(2, 32) - 1, std::pow(2, 32) - 0.01};
}

// 2)
std::pair<double, double> value_1152() {
    return std::pair<double, double>{INT_MAX, INT_MAX + 0.99};
}

// 3)
long int value_1153() {
    return UINT8_MAX / 2;
}

// 1.16 - 1.19
// 1)
currency &currency::value_from_stream(std::istream &in = std::cin) {
    double value;
    in >> value;
    this->SetValue(value);
    return *this;
}

currency currency::operator-(currency const &x) const {
    double value = this->value() - x.value();
    currency temp_currency;
    temp_currency.SetValue(value);
    return temp_currency;
}

currency currency::operator-=(currency const &x) {
    double value = this->value() - x.value();
    this->SetValue(value);
    return *this;
}

currency currency::operator%(currency const &x) const {
    double temp = this->value() - std::floor(this->value() / x.value()) * x.value();
    currency temp_currency;
    temp_currency.SetValue(temp);
    return temp_currency;
}

currency &currency::operator%=(currency const &x) {
    double temp = this->value() - std::floor(this->value() / x.value()) * x.value();
    this->SetValue(temp);
    return *this;
}

currency currency::operator*(currency const &x) const {
    double temp = this->value() * x.value();
    currency temp_currency;
    temp_currency.SetValue(temp);
    return temp_currency;
}

currency &currency::operator*=(currency const &x) {
    double temp = this->value() * x.value();
    this->SetValue(temp);
    return *this;
}

currency currency::operator/(currency const &x) const {
    double temp = this->value() / x.value();
    currency temp_currency;
    temp_currency.SetValue(temp);
    return temp_currency;
}

currency &currency::operator/=(currency const &x) {
    double temp = this->value() / x.value();
    this->SetValue(temp);
    return *this;
}

currency &currency::operator=(double const &x) {
    this->SetValue(x);
    return *this;
}

// 1.19
unsigned long long factorial(int const &x) {
    unsigned long long value = 1;
    for (auto iter = 0; iter != x; iter++) {
        value *= iter + 1;
    }
    return value;
}

// 1.20
unsigned long long fibonacci(int const &x) {
    /*TODO: do it. */
    return 0;
}

// 1.21
// 1) 8, 11

// 2) pass

// 3)
int f_1213(int const &x) {
    if (x % 2 == 0) {
        return x / 2;
    } else {
        return f_1213(3 * x + 1);
    }
}

// 4)
int f_1214(int const &x) {
    if (x % 2 == 0) {
        return x / 2;
    } else {
        return (3 * x + 1) / 2;
    }
}

// 1.22
unsigned long Ackermann(unsigned long i, unsigned long j) {
    if (i == 1 && j >= 1) {
        return std::pow(2, j);
    } else if (i >= 2 && j == 1) {
        return Ackermann(i - 1, 2);
    } else {
        return Ackermann(i - 1, Ackermann(i, j - 1));
    }
}

// 1.23
unsigned long gcd(unsigned long x, unsigned long y) {
    if (y == 0) {
        return x;
    } else {
        return gcd(x, x % y);
    }
}

// 1.24
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
bool belong(CONT<T> const &op, T const &x) {
    return std::any_of(std::begin(op), std::end(op), [](T const &elem) { return elem == x; })
}

// 1.25
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
std::vector<std::vector<int>> SubsetGeneration(CONT<T> const &x) {
    std::vector<int> subNum;
    std::vector<std::vector<int>> result;
    for (int i = 0; i != std::pow(2, x.Size()); i++) {
        subNum.emplace_back(i);
    }
    for (auto j = 0; j != subNum.size(); j++) {
        result.emplace_back(std::vector<int>{});
        for (int i = 0; i != x.Size(); i++) {
            if ((subNum[j] % (int) std::pow(2, i + 1)) / (int) std::pow(2, i) < 1) {
                result[j].emplace_back(0);
            } else {
                result[j].emplace_back(1);
            }
        }
    }
    return result;
}

// 1.26
template<template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
CONT<int> &GreyCode(int const &x, CONT<int> &container) {
    if (x == 1) {
        container.emplace_back(1);
    } else {
        GreyCode(x - 1, container);
        container.emplace_back(x);
        GreyCode(x - 1, container);
    }
}

// 1.27
template<typename T>
T accumulate(T const &op1, T const &op2, T const &op3) {
    return op1 + op2 + op3;
}

// 1.28
template<typename T>
T accumulate(T const &op1, T const &op2, T const &op3, T const &op4) {
    return op1 + op2 + op3 + op4;
}

// 1.29
template<typename T, template<typename elem, typename =std::allocator<elem>> class CONT = std::vector>
CONT<T> &copy(CONT<T> const &source, CONT<T> &target) {
    for (auto &&iter: source) {
        target.emplace_back(iter);
    }
}

// assistance function declared here
template<class T>
void permutations(T list[], int k, int m) {
    do {
        std::copy(list + k, list + m + 1, std::ostream_iterator<T>(std::cout, " "));
        std::cout << std::endl;
    } while (std::prev_permutation(list + k, list + m + 1));
}

// 1.30
template<typename T, template<typename elem, typename =std::allocator<elem>> class CONT = std::vector>
void permutations(CONT<T> &cont, int k, int m) {
    std::vector<std::vector<T>> temp;
    do {
        temp.emplace_back(std::vector<T>{});
        std::copy(cont.begin() + k, cont.begin() + m + 1, (*(std::end(temp) - 1)).begin());
    } while (std::prev_permutation(cont.begin() + k, cont.begin() + m + 1));

    std::sort(std::begin(temp), std::end(temp));
    for (auto &&iter: temp) {
        std::copy(std::begin(iter), std::end(iter), std::ostream_iterator<T>(std::cout, " "));
        std::cout << std::endl;
    }
}

// 1.31
template<typename T, template<typename elem, typename =std::allocator<elem>> class CONT = std::vector>
void permutations(CONT<T> &cont, int k, int m, std::ostream &out = std::cout) {
    do {
        copy(std::begin(cont), std::end(cont), std::ostream_iterator<T>(out, " "));
        out << std::endl;
    } while (std::prev_permutation(cont.begin() + k, cont.begin() + m + 1));
    do {
        copy(std::begin(cont), std::end(cont), std::ostream_iterator<T>(out, " "));
        out << std::endl;
    } while (std::next_permutation(cont.begin() + k, cont.begin() + m + 1));
}

// 1.32
// pass

// 1.33
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
int count_STL(const CONT<T> &vec, const T &x) {
    return std::count(std::begin(vec), std::end(vec), x);
}

// 1.34
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
void fill_STL(CONT<T> vec, const T &x) {
    std::fill(std::begin(vec), std::end(vec), x);
}

//1.35
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
CONT<T> &inner_product_STL(CONT<T> &Vec1, CONT<T> &Vec2) {
    return std::inner_product(std::begin(Vec1), std::end(Vec1), std::begin(Vec2));
}

// 1.36
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
void iota_STL(CONT<T> &x) {
    std::iota(std::begin(x), std::end(x), 1);
}

// 1.37
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
bool is_sorted_STL(CONT<T> const &x) {
    return std::is_sorted(std::begin(x), std::end(x));
}

// 1.38
template<typename T, template<typename elem, typename = std::allocator<elem>> class CONT = std::vector>
int mismatch_STL(CONT<T> const &op1, CONT<T> const &op2) {
    return std::mismatch(std::begin(op1), std::end(op1), std::begin(op2));
}

// 1.39 - 1.48
// pass

#endif //DATASTRUCTURE_SECTION1_CPP_REVIEW_HPP