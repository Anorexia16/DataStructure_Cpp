#ifndef DATASTRUCTURE_POLYNOMIAL_C_HPP
#define DATASTRUCTURE_POLYNOMIAL_C_HPP

#include "../../Structure/Chain_Bidirectional_Circle.hpp"

class Polynomial_C {
public:
    Polynomial_C();

    Polynomial_C(long double *, size_t const &);

    explicit Polynomial_C(std::istream &&in);

    Polynomial_C(Polynomial_C const &) = default;

    ~Polynomial_C() = default;

    [[nodiscard]] size_t degree() const;

    [[nodiscard]] long double sub(long double const &) const;

    Polynomial_C operator+(Polynomial_C const &) const;

    Polynomial_C operator-(Polynomial_C const &) const;

    Polynomial_C operator*(Polynomial_C const &) const;

    Polynomial_C &operator+=(Polynomial_C const &);

    Polynomial_C &operator-=(Polynomial_C const &);

    Polynomial_C &operator*=(Polynomial_C const &);

    friend std::ostream &operator<<(std::ostream &&out, Polynomial_C const &poly) {

        return out;
    }

private:
    ChainBC<long double> Sequence;
};

Polynomial_C::Polynomial_C()
    :Sequence{256} {}

Polynomial_C::Polynomial_C(long double *ptr, const size_t &size)
        :Sequence{size} {
    NodeB_Iter<long double> iterator {Sequence.head()};
    for(auto i=0;i!=size;++iterator, ++i) {
        iterator.link_after(*new NodeB<long double>{ptr[i], &*iterator, iterator.next_ptr()});
        iterator.next().next().link_front(iterator.next());
    }
    Sequence.resize(size);
    if (size==0) {
        iterator.link_after(*new NodeB<long double>{0, &*iterator, iterator.next_ptr()});
        iterator.next().next().link_front(iterator.next());
        Sequence.resize(1);
    }
}

Polynomial_C::Polynomial_C(std::istream &&in)
        :Sequence{256} {
    NodeB_Iter<long double> iterator {Sequence.head()};
    long double temp;
    size_t size {};
    for(;in.good();++iterator, ++size) {
        in >> temp;
        iterator.link_after(*new NodeB<long double>{temp, &*iterator, iterator.next_ptr()});
        iterator.next().next().link_front(iterator.next());
    }
    Sequence.resize(size);
    if (Sequence.empty()) {
        iterator.link_after(*new NodeB<long double>{0, &*iterator, iterator.next_ptr()});
        iterator.next().next().link_front(iterator.next());
        Sequence.resize(1);
    }
}

size_t Polynomial_C::degree() const {
    return this->Sequence.size()-1;
}

long double Polynomial_C::sub(const long double &value) const {
    if (this->Sequence.size()==1) return this->Sequence.head_c()->next().value_c();
    long double res = 0;
    for(NodeB_Iter<long double>iter{this->Sequence.head_c()};
        iter!=this->Sequence.head_c();++iter) {
        res+=iter.value_c();
        res*=value;
    }
    res+=this->Sequence[this->degree()];
    return res;
}

Polynomial_C Polynomial_C::operator+(const Polynomial_C &poly) const {
    Polynomial_C res{};
    NodeB_Iter<long double> ti {this->Sequence.head_c()->next_ptr()};
    NodeB_Iter<long double> oi {poly.Sequence.head_c()->next_ptr()};
    NodeB_Iter<long double> ri {res.Sequence.head_c()};
    if (this->degree()<poly.degree()) {
        for (auto i=0; i!=poly.degree()-this->degree();++i,++oi,++ri) {
            ri.link_after(*new NodeB<long double>{oi.value_c(), &*ri, ri.next_ptr()});
            ri.next().next().link_front(ri.next());
        }
    } else if (this->degree()>poly.degree()) {
        for (auto i=0; i!=this->degree()-poly.degree();++i,++ti,++ri) {
            ri.link_after(*new NodeB<long double>{ti.value_c(), &*ri, ri.next_ptr()});
            ri.next().next().link_front(ri.next());
        }
    }
    for(;ti!=this->Sequence.head_c();++ti, ++oi, ++ri) {
        ri.link_after(*new NodeB<long double>{oi.value_c() + ti.value_c(), &*ri, ri.next_ptr()});
        ri.next().next().link_front(ri.next());
    }
    res.Sequence.resize(std::max(this->Sequence.size(), poly.Sequence.size()));
    return res;
}

Polynomial_C Polynomial_C::operator-(const Polynomial_C &poly) const {
    Polynomial_C res{};
    NodeB_Iter<long double> ti {this->Sequence.head_c()->next_ptr()};
    NodeB_Iter<long double> oi {poly.Sequence.head_c()->next_ptr()};
    NodeB_Iter<long double> ri {res.Sequence.head_c()};
    if (this->degree()<poly.degree()) {
        for (auto i=0; i!=poly.degree()-this->degree();++i,++oi,++ri) {
            ri.link_after(*new NodeB<long double>{-oi.value_c(), &*ri, ri.next_ptr()});
            ri.next().next().link_front(ri.next());
        }
    } else if (this->degree()>poly.degree()) {
        for (auto i=0; i!=this->degree()-poly.degree();++i,++ti,++ri) {
            ri.link_after(*new NodeB<long double>{ti.value_c(), &*ri, ri.next_ptr()});
            ri.next().next().link_front(ri.next());
        }
    }
    for(;ti!=this->Sequence.head_c();++ti, ++oi, ++ri) {
        ri.link_after(*new NodeB<long double>{ ti.value_c()-oi.value_c(), &*ri, ri.next_ptr()});
        ri.next().next().link_front(ri.next());
    }
    res.Sequence.resize(std::max(this->Sequence.size(), poly.Sequence.size()));
    return res;
}

Polynomial_C Polynomial_C::operator*(const Polynomial_C &poly) const {
    Polynomial_C res {};
    long double temp;

    return res;
}

Polynomial_C &Polynomial_C::operator+=(const Polynomial_C &poly) {
    NodeB_Iter<long double> ti {this->Sequence.head_c()->next_ptr()};
    NodeB_Iter<long double> oi {poly.Sequence.head_c()->next_ptr()};
    if(this->degree()<poly.degree()) {
        size_t i=0;
        for(;i!=poly.degree()-this->degree();++i, ++ti) {
            ti.link_after(*new NodeB<long double>{oi.value_c(), &*ti, ti.next_ptr()});
            ti.next().next().link_front(ti.next());
        }
        this->Sequence.resize(this->Sequence.size()+i);
    } else if (this->degree()>poly.degree()) {
        for (auto i=0; i!=this->degree()-poly.degree();++i, ++ti);
    }
    for(;ti!=this->Sequence.head_c();++ti, ++oi) {
        (*ti)() += oi.value_c();
    }
    return *this;
}

Polynomial_C &Polynomial_C::operator-=(const Polynomial_C &poly) {
    NodeB_Iter<long double> ti {this->Sequence.head_c()->next_ptr()};
    NodeB_Iter<long double> oi {poly.Sequence.head_c()->next_ptr()};
    if(this->degree()<poly.degree()) {
        size_t i=0;
        for(;i!=poly.degree()-this->degree();++i, ++ti) {
            ti.link_after(*new NodeB<long double>{-oi.value_c(), &*ti, ti.next_ptr()});
            ti.next().next().link_front(ti.next());
        }
        this->Sequence.resize(this->Sequence.size()+i);
    } else if (this->degree()>poly.degree()) {
        for (auto i=0; i!=this->degree()-poly.degree();++i, ++ti);
    }
    for(;ti!=this->Sequence.head_c();++ti, ++oi) {
        (*ti)() -= oi.value_c();
    }
    return *this;
}

Polynomial_C &Polynomial_C::operator*=(const Polynomial_C &) {
    return *this;
}

#endif //DATASTRUCTURE_POLYNOMIAL_C_HPP
