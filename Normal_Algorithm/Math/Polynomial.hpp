#ifndef DATASTRUCTURE_POLYNOMIAL_HPP
#define DATASTRUCTURE_POLYNOMIAL_HPP

#include <iostream>
#include <algorithm>

class Polynomial {
public:
    Polynomial();

    Polynomial(long double *, size_t const &);

    explicit Polynomial(std::istream &&in);

    Polynomial(Polynomial const &) = default;

    ~Polynomial() = default;

    [[nodiscard]] size_t degree() const;

    [[nodiscard]] long double sub(long double const &) const;

    Polynomial operator+(Polynomial const &) const;

    Polynomial operator-(Polynomial const &) const;

    Polynomial operator*(Polynomial const &) const;

    Polynomial &operator+=(Polynomial const &);

    Polynomial &operator-=(Polynomial const &);

    Polynomial &operator*=(Polynomial const &);

    friend std::ostream &operator<<(std::ostream &&out, Polynomial const &poly) {
        for(auto iter=std::begin(poly.Sequence);iter!=std::end(poly.Sequence);--iter){
            if (*iter!=0) {
                out << *iter;
                *iter != 0 ? out << "* x ^" << std::abs(*iter) << (*(iter+1) > 0 ? " + ": " - "): out << std::endl;
            }
        }
        return out;
    }

private:
    std::vector<long double> Sequence;
};

Polynomial::Polynomial()
    :Sequence{std::vector<long double>{0}} {}

Polynomial::Polynomial(std::istream &&in)
    :Sequence{std::vector<long double> {}} {
    std::move(std::istream_iterator<long double>(in), std::istream_iterator<long double>(), std::begin(Sequence));
    if (Sequence.empty()) Sequence.emplace_back(0);
}

Polynomial::Polynomial(long double *ptr, const size_t &size)
:Sequence{std::vector<long double> {}} {
    for(auto i=0;i!=size;++i) Sequence.emplace_back(ptr[i]);
    if (Sequence.empty()) Sequence.emplace_back(0);
}

size_t Polynomial::degree() const {
    return this->Sequence.size()-1;
}

long double Polynomial::sub(const long double &value) const {
    if (this->Sequence.size()==1) return this->Sequence[0];
    long double res = 0;
    for(auto iter=std::begin(this->Sequence);iter!=std::end(this->Sequence)-1;++iter) {
        res+=*iter;
        res*=value;
    }
    res+=this->Sequence[this->degree()];
    return res;
}

Polynomial Polynomial::operator+(const Polynomial &op) const {
    Polynomial res {};
    auto ti = std::cbegin(this->Sequence);
    auto oi = std::cbegin(this->Sequence);
    if (this->degree()<op.degree()) {
        for (auto i=0; i!=op.degree()-this->degree();++i) {
            res.Sequence.emplace_back(*oi);
            ++oi;
        }
    } else if (this->degree()>op.degree()) {
        for (auto i=0; i!=this->degree()-op.degree();++i) {
            res.Sequence.emplace_back(*ti);
            ++ti;
        }
    }
    for(;ti!=std::cend(this->Sequence);++ti, ++oi) {
        res.Sequence.emplace_back(*oi + *ti);
    }
    return res;
}

Polynomial Polynomial::operator-(const Polynomial &op) const {
    Polynomial res {};
    auto ti = std::cbegin(this->Sequence);
    auto oi = std::cbegin(this->Sequence);
    if (this->degree()<op.degree()) {
        for (auto i=0; i!=op.degree()-this->degree();++i) {
            res.Sequence.emplace_back(-*oi);
            ++oi;
        }
    } else if (this->degree()>op.degree()) {
        for (auto i=0; i!=this->degree()-op.degree();++i) {
            res.Sequence.emplace_back(*ti);
            ++ti;
        }
    }
    for(;ti!=std::cend(this->Sequence);++ti, ++oi) {
        res.Sequence.emplace_back(*ti-*oi);
    }
    return res;
}

Polynomial Polynomial::operator*(const Polynomial &op) const {
    Polynomial res {};
    long double temp;
    for (auto level=0;level!=this->degree()+op.degree();++level) {
        temp = 0;
        for(auto l_l=this->degree();l_l!=-1;--l_l) {
            temp += this->Sequence[l_l] * op.Sequence[level-l_l-1];
        }
        res.Sequence.emplace_back(temp);
    }
    return res;
}

Polynomial &Polynomial::operator+=(const Polynomial &op) {
    auto ti = std::begin(this->Sequence);
    auto oi = std::cbegin(this->Sequence);
    if (this->degree()<op.degree()) {
        auto iter = std::begin(this->Sequence);
        for (auto i=0; i!=op.degree()-this->degree();++i, ++iter) {
            this->Sequence.insert(iter, *oi);
            ++oi;
        }
    } else if (this->degree()>op.degree()) {
        for (auto i=0; i!=this->degree()-op.degree();++i)
            ++ti;
    }
    for(;ti!=std::end(this->Sequence);++ti, ++oi) {
        *ti += *oi;
    }
    return *this;
}

Polynomial &Polynomial::operator-=(const Polynomial &op) {
    auto ti = std::begin(this->Sequence);
    auto oi = std::cbegin(this->Sequence);
    if (this->degree()<op.degree()) {
        auto iter = std::begin(this->Sequence);
        for (auto i=0; i!=op.degree()-this->degree();++i, ++iter) {
            this->Sequence.insert(iter, -*oi);
            ++oi;
        }
    } else if (this->degree()>op.degree()) {
        for (auto i=0; i!=this->degree()-op.degree();++i)
            ++ti;
    }
    for(;ti!=std::end(this->Sequence);++ti, ++oi) {
        *ti -= *oi;
    }
    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &op) {
    std::vector<long double> res {};
    long double temp;
    for (auto level=0;level!=this->degree()+op.degree();++level) {
        temp = 0;
        for(auto l_l=this->degree();l_l!=-1;--l_l) {
            temp += this->Sequence[l_l] * op.Sequence[level-l_l-1];
        }
        res.emplace_back(temp);
    }
    this->Sequence = res;
    return *this;
}

#endif //DATASTRUCTURE_POLYNOMIAL_HPP
