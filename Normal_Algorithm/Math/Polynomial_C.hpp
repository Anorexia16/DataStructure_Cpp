#ifndef DATASTRUCTURE_POLYNOMIAL_C_HPP
#define DATASTRUCTURE_POLYNOMIAL_C_HPP

#include "../../Structure/Linear/Chain_Bidirectional_Circle.hpp"

class Polynomial_C
{
public:
    Polynomial_C();

    Polynomial_C(long double *, size_t const &);

    explicit Polynomial_C(std::istream &&in);

    Polynomial_C(Polynomial_C const &) = default;

    ~Polynomial_C() = default;

    [[nodiscard]] size_t degree() const;

    [[nodiscard]] long double sub(long double const &);

    Polynomial_C operator+(Polynomial_C const &) const;

    Polynomial_C operator-(Polynomial_C const &) const;

    Polynomial_C operator*(Polynomial_C const &) const;

    Polynomial_C &operator+=(Polynomial_C const &);

    Polynomial_C &operator-=(Polynomial_C const &);

    Polynomial_C &operator*=(Polynomial_C const &);

    friend std::ostream &operator<<(std::ostream &&out, Polynomial_C const &poly)
    {
        return out;
    }

private:
    ChainBC<long double> Sequence;
};

Polynomial_C::Polynomial_C()
    :Sequence{256} {}

Polynomial_C::Polynomial_C(long double *ptr, const size_t &size)
        :Sequence{size}
{
    NodeB<long double> *iterator {Sequence.Head};
    for(auto i=0;i!=size;++iterator, ++i)
    {
        iterator->Next = new NodeB<long double>{ptr[i], iterator, iterator->Next};
        iterator->Next->Next->Prev = iterator->Next;
    }
    Sequence.resize(size);
    if (size==0)
    {
        iterator->Next = new NodeB<long double>{0, iterator, iterator->Next};
        iterator->Next->Next->Prev = iterator->Next;
        Sequence.resize(1);
    }
}

Polynomial_C::Polynomial_C(std::istream &&in)
        :Sequence{256}
{
    NodeB<long double> *iterator {Sequence.Head};
    long double temp;
    size_t size {};
    for(;in.good();++iterator, ++size)
    {
        in >> temp;
        iterator->Next = new NodeB<long double>{temp, iterator, iterator->Next};
        iterator->Next->Next->Prev = iterator->Next;
    }
    Sequence.resize(size);
    if (Sequence.empty())
    {
        iterator->Next = new NodeB<long double>{0, iterator, iterator->Next};
        iterator->Next->Next->Prev = iterator->Next;
        Sequence.resize(1);
    }
}

size_t Polynomial_C::degree() const
{
    return this->Sequence.size()-1;
}

long double Polynomial_C::sub(const long double &value)
{
    if (this->Sequence.size()==1) return this->Sequence.Head->Next->Element;
    long double res = 0;
    for(NodeB<long double> *iter{this->Sequence.Head};
        iter!=this->Sequence.Head;++iter)
    {
        res+=iter->Element;
        res*=value;
    }
    res+=this->Sequence[this->degree()];
    return res;
}

Polynomial_C Polynomial_C::operator+(const Polynomial_C &poly) const
{
    Polynomial_C res{};
    NodeB<long double> *ti {this->Sequence.Head->Next};
    NodeB<long double> *oi {poly.Sequence.Head->Next};
    NodeB<long double> *ri {res.Sequence.Head};
    if (this->degree()<poly.degree())
    {
        for (auto i=0; i!=poly.degree()-this->degree(); ti=ti->Next, oi=oi->Next, ri=ri->Next)
        {
            ri->Next = new NodeB<long double>{oi->Element, ri, ri->Next};
            ri->Next->Next->Prev = ri->Next;
        }
    } else if (this->degree()>poly.degree())
    {
        for (auto i=0; i!=this->degree()-poly.degree();++i,ti=ti->Next,ri=ri->Next)
        {
            ri->Next = new NodeB<long double>{ti->Element, ri, ri->Next};
            ri->Next->Next->Prev = ri->Next;
        }
    }
    for(;ti!=this->Sequence.Head;ti=ti->Next, oi=oi->Next, ri=ri->Next)
    {
        ri->Next = new NodeB<long double>{oi->Element + ti->Element, ri, ri->Next};
        ri->Next->Next->Prev = ri->Next;
    }
    res.Sequence.resize(std::max(this->Sequence.size(), poly.Sequence.size()));
    return res;
}

Polynomial_C Polynomial_C::operator-(const Polynomial_C &poly) const
{
    Polynomial_C res{};
    NodeB<long double> *ti {this->Sequence.Head->Next};
    NodeB<long double> *oi {poly.Sequence.Head->Next};
    NodeB<long double> *ri {res.Sequence.Head};
    if (this->degree()<poly.degree())
    {
        for (auto i=0; i!=poly.degree()-this->degree();++i,++oi,++ri)
        {
            ri->Next = new NodeB<long double>{-oi->Element, ri, ri->Next};
            ri->Next->Next->Prev = ri->Next;
        }
    } else if (this->degree()>poly.degree())
    {
        for (auto i=0; i!=this->degree()-poly.degree();++i,ti=ti->Next,ri=ri->Next)
        {
            ri->Next = new NodeB<long double>{ti->Element, ri, ri->Next};
            ri->Next->Next->Prev = ri->Next;
        }
    }
    for(;ti!=this->Sequence.Head;ti=ti->Next, oi=oi->Next, ri=ri->Next)
    {
        ri->Next = new NodeB<long double>{-oi->Element + ti->Element, ri, ri->Next};
        ri->Next->Next->Prev = ri->Next;
    }
    res.Sequence.resize(std::max(this->Sequence.size(), poly.Sequence.size()));
    return res;
}

Polynomial_C Polynomial_C::operator*(const Polynomial_C &poly) const
{
    Polynomial_C res {};
    return res;
}

Polynomial_C &Polynomial_C::operator+=(const Polynomial_C &poly)
{
    NodeB<long double> *ti {this->Sequence.Head->Next};
    NodeB<long double> *oi {poly.Sequence.Head->Next};
    if(this->degree()<poly.degree())
    {
        size_t i=0;
        for(;i!=poly.degree()-this->degree();++i, ti=ti->Next)
        {
            ti->Next = new NodeB<long double>{oi->Element, ti, ti->Next};
            ti->Next->Next->Prev = ti->Next;
        }
        this->Sequence.resize(this->Sequence.size()+i);
    } else if (this->degree()>poly.degree()) {
        for (auto i=0; i!=this->degree()-poly.degree();++i, ti=ti->Next);
    }
    for(;ti!=this->Sequence.Head;ti=ti->Next, oi=oi->Next)
    {
        ti->Element += oi->Element;
    }
    return *this;
}

Polynomial_C &Polynomial_C::operator-=(const Polynomial_C &poly)
{
    NodeB<long double> *ti {this->Sequence.Head->Next};
    NodeB<long double> *oi {poly.Sequence.Head->Next};
    if(this->degree()<poly.degree())
    {
        size_t i=0;
        for(;i!=poly.degree()-this->degree();++i, ++ti)
        {
            ti->Next = new NodeB<long double>{-oi->Element, ti, ti->Next};
            ti->Next->Next->Prev = ti->Next;
        }
        this->Sequence.resize(this->Sequence.size()+i);
    } else if (this->degree()>poly.degree()) {
        for (auto i=0; i!=this->degree()-poly.degree();++i, ti=ti->Next);
    }
    for(;ti!=this->Sequence.Head;++ti, ++oi)
    {
        ti->Element -= oi->Element;
    }
    return *this;
}

Polynomial_C &Polynomial_C::operator*=(const Polynomial_C &)
{
    return *this;
}

#endif //DATASTRUCTURE_POLYNOMIAL_C_HPP
