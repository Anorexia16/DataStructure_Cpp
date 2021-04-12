#ifndef DATASTRUCTURE_SET_STL_HPP
#define DATASTRUCTURE_SET_STL_HPP

#include <iostream>
#include <iterator>
#include <vector>
#include <array>

template<typename Tp>
class Set_STL
{
public:
    class SS_Iterator:std::iterator<std::random_access_iterator_tag, Tp> {
    public:
        explicit SS_Iterator(class Set_STL const &);

        SS_Iterator(SS_Iterator const &) noexcept = default;

        SS_Iterator &operator=(SS_Iterator const &) noexcept = default;

        Tp &operator*() const;

        Tp *operator->() const;

        SS_Iterator &operator++();

        SS_Iterator &operator--();

        const SS_Iterator operator++(int) const;

        const SS_Iterator operator--(int) const;

        bool operator<(SS_Iterator const &) const;

        bool operator>(SS_Iterator const &) const;

        bool operator<=(SS_Iterator const &) const;

        bool operator>=(SS_Iterator const &) const;

        bool operator==(SS_Iterator const &) const;

        bool operator!=(SS_Iterator const &) const;

        ptrdiff_t operator-(SS_Iterator const &) const;

        SS_Iterator operator+(size_t const &) const;

        SS_Iterator operator-(size_t const &) const;

        SS_Iterator &operator+=(size_t const &);

        SS_Iterator &operator-=(size_t const &);

        Set_STL *Set;

        size_t Count {};
    };

    class SSR_Iterator:std::iterator<std::random_access_iterator_tag, Tp>
    {
    public:
        explicit SSR_Iterator(class Set_STL const &);

        SSR_Iterator(SSR_Iterator const &) noexcept = default;

        SSR_Iterator &operator=(SSR_Iterator const &) noexcept = default;

        Tp &operator*() const;

        Tp *operator->() const;

        SSR_Iterator &operator++();

        SSR_Iterator &operator--();

        const SSR_Iterator operator++(int) const;

        const SSR_Iterator operator--(int) const;

        bool operator<(SSR_Iterator const &) const;

        bool operator>(SSR_Iterator const &) const;

        bool operator<=(SSR_Iterator const &) const;

        bool operator>=(SSR_Iterator const &) const;

        bool operator==(SSR_Iterator const &) const;

        bool operator!=(SSR_Iterator const &) const;

        ptrdiff_t operator-(SSR_Iterator const &) const;

        SSR_Iterator operator+(size_t const &) const;

        SSR_Iterator operator-(size_t const &) const;

        SSR_Iterator &operator+=(size_t const &);

        SSR_Iterator &operator-=(size_t const &);

        Set_STL *Set;

        size_t Count {};
    };

    Set_STL() = default;

    explicit Set_STL(std::istream &&);

    template<size_t n>
    explicit Set_STL(std::array<Tp, n> const &);

    template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
    explicit Set_STL(Cont<cls> const &);

    Set_STL(std::initializer_list<Tp> const &);

    Set_STL(Tp * const &, size_t const &);

    SS_Iterator begin();

    SS_Iterator end();

    SSR_Iterator rbegin();

    SSR_Iterator rend();

    [[nodiscard]] size_t size() const;

    [[nodiscard]] bool empty() const;

    Tp get(size_t const &) const;

    void insert(Tp const &);

    void erase (Tp const &);

    size_t find(Tp const &) const;

    bool exist(Tp const &) const;

    Tp &operator[](size_t const &);

    friend std::ostream &operator<<(std::ostream &out, Set_STL<Tp> const &set)
    {
        std::copy(std::begin(set.Container), std::end(set.Container), std::ostream_iterator<Tp>(out, " "));
        return out;
    }

protected:
    std::vector<Tp> Container;
};

template<typename Tp>
Set_STL<Tp>::Set_STL(std::istream &&in)
{
    std::vector<Tp> cont {};
    std::move(std::istream_iterator<Tp>(in), std::istream_iterator<Tp>(), std::begin(cont));
    for (auto && iterator: cont)
    {
        this->insert(iterator);
    }
}

template<typename Tp>
template<size_t n>
Set_STL<Tp>::Set_STL(const std::array<Tp, n> &array)
{
    for (auto && iterator: array)
    {
        this->insert(iterator);
    }
}

template<typename Tp>
template<class cls, template<typename elem, typename = std::allocator<elem>> class Cont>
Set_STL<Tp>::Set_STL(const Cont<cls> &cont)
{
    for (auto && iterator: cont)
    {
        this->insert(iterator);
    }
}

template<typename Tp>
Set_STL<Tp>::Set_STL(const std::initializer_list<Tp> &list)
{
    for (auto && iterator: list)
    {
        this->insert(iterator);
    }
}

template<typename Tp>
Set_STL<Tp>::Set_STL(Tp *const &ptr, const size_t &size)
{
    for (size_t index = 0;index!=size;++index)
    {
        this->insert(ptr[size]);
    }
}

template<typename Tp>
typename Set_STL<Tp>::SS_Iterator Set_STL<Tp>::begin()
{
    return Set_STL::SS_Iterator(*this);
}

template<typename Tp>
typename Set_STL<Tp>::SS_Iterator Set_STL<Tp>::end()
{
    Set_STL::SS_Iterator res {*this};
    res.Count = this->Container.size();
    return res;
}

template<typename Tp>
typename Set_STL<Tp>::SSR_Iterator Set_STL<Tp>::rbegin()
{
    Set_STL::SSR_Iterator res {*this};
    res.Count = this->Container.size() - 1;
    return res;
}

template<typename Tp>
typename Set_STL<Tp>::SSR_Iterator Set_STL<Tp>::rend()
{
    Set_STL::SSR_Iterator res {*this};
    res.Count = -1;
    return res;
}

template<typename Tp>
size_t Set_STL<Tp>::size() const
{
    return this->Container.size();
}

template<typename Tp>
bool Set_STL<Tp>::empty() const
{
    return this->Container.empty();
}

template<typename Tp>
void Set_STL<Tp>::insert(const Tp &value)
{
    for(auto && iterator: this->Container)
    {
        if (iterator == value) return;
    }
    this->Container.template emplace_back(value);
}

template<typename Tp>
void Set_STL<Tp>::erase(const Tp &value)
{
    for(auto iterator = std::begin(this->Container); iterator!=std::end(this->Container);++iterator)
    {
        if (*iterator == value)
        {
            this->Container.erase(iterator);
            return;
        }
    }
}

template<typename Tp>
size_t Set_STL<Tp>::find(const Tp &value) const
{
    size_t index {};
    for(auto const &iterator: this->Container)
    {
        if (iterator==value)
        {
            return index;
        } else {
            ++index;
        }
    }
    throw;
}

template<typename Tp>
bool Set_STL<Tp>::exist(const Tp &value) const
{
    for(auto const &iterator: this->Container)
    {
        if (iterator==value) return true;
    }
    return false;
}

template<typename Tp>
Tp Set_STL<Tp>::get(const size_t &index) const
{
    return this->Container[index];
}

template<typename Tp>
Tp &Set_STL<Tp>::operator[](const size_t &index)
{
    return this->Container[index];
}

template<typename Tp>
Set_STL<Tp>::SS_Iterator::SS_Iterator(const Set_STL &set)
{
    this->Set = const_cast<Set_STL<Tp> *>(&set);
}

template<typename Tp>
Tp &Set_STL<Tp>::SS_Iterator::operator*() const
{
    return (*this->Set)[Count];
}

template<typename Tp>
Tp *Set_STL<Tp>::SS_Iterator::operator->() const
{
    return &(*this->Set)[Count];
}

template<typename Tp>
typename Set_STL<Tp>::SS_Iterator &Set_STL<Tp>::SS_Iterator::operator++()
{
    ++this->Count;
    return *this;
}

template<typename Tp>
typename Set_STL<Tp>::SS_Iterator &Set_STL<Tp>::SS_Iterator::operator--()
{
    --this->Count;
    return *this;
}

template<typename Tp>
const typename Set_STL<Tp>::SS_Iterator Set_STL<Tp>::SS_Iterator::operator++(int) const
{
    Set_STL::SS_Iterator res {*this} ;
    ++res.Count;
    return res;
}

template<typename Tp>
const typename Set_STL<Tp>::SS_Iterator Set_STL<Tp>::SS_Iterator::operator--(int) const
{
    Set_STL::SS_Iterator res {*this} ;
    --res.Count;
    return res;}

template<typename Tp>
bool Set_STL<Tp>::SS_Iterator::operator<(const Set_STL::SS_Iterator &op) const
{
    return (*this->Set)[this->Count] < (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SS_Iterator::operator>(const Set_STL::SS_Iterator &op) const
{
    return (*this->Set)[this->Count] > (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SS_Iterator::operator<=(const Set_STL::SS_Iterator &op) const
{
    return (*this->Set)[this->Count] <= (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SS_Iterator::operator>=(const Set_STL::SS_Iterator &op) const
{
    return (*this->Set)[this->Count] >= (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SS_Iterator::operator==(const Set_STL::SS_Iterator &op) const
{
    return (*this->Set)[this->Count] == (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SS_Iterator::operator!=(const Set_STL::SS_Iterator &op) const
{
    return (*this->Set)[this->Count] != (*op.Set)[op.Count];
}

template<typename Tp>
ptrdiff_t Set_STL<Tp>::SS_Iterator::operator-(const Set_STL::SS_Iterator &op) const
{
    return this->Count-op.Count;
}

template<typename Tp>
typename Set_STL<Tp>::SS_Iterator Set_STL<Tp>::SS_Iterator::operator+(const size_t &diff) const
{
    Set_STL::SS_Iterator res {*this};
    res.Count += diff;
    return res;
}

template<typename Tp>
typename Set_STL<Tp>::SS_Iterator Set_STL<Tp>::SS_Iterator::operator-(const size_t &diff) const
{
    Set_STL::SS_Iterator res {*this};
    res.Count -= diff;
    return res;
}

template<typename Tp>
typename Set_STL<Tp>::SS_Iterator &Set_STL<Tp>::SS_Iterator::operator+=(const size_t &diff)
{
    this->Count += diff;
    return *this;
}

template<typename Tp>
typename Set_STL<Tp>::SS_Iterator &Set_STL<Tp>::SS_Iterator::operator-=(const size_t &diff)
{
    this->Count -= diff;
    return *this;
}

template<typename Tp>
Set_STL<Tp>::SSR_Iterator::SSR_Iterator(const Set_STL &set)
:Set{const_cast<Set_STL<Tp> *>(&set)} {}

template<typename Tp>
Tp &Set_STL<Tp>::SSR_Iterator::operator*() const
{
    return (*this->Set)[this->Count];
}

template<typename Tp>
Tp *Set_STL<Tp>::SSR_Iterator::operator->() const
{
    return &(*this->Set)[this->Count];
}

template<typename Tp>
typename Set_STL<Tp>::SSR_Iterator &Set_STL<Tp>::SSR_Iterator::operator++()
{
    --this->Count;
    return *this;
}

template<typename Tp>
typename Set_STL<Tp>::SSR_Iterator &Set_STL<Tp>::SSR_Iterator::operator--()
{
    ++this->Count;
    return *this;
}

template<typename Tp>
const typename Set_STL<Tp>::SSR_Iterator Set_STL<Tp>::SSR_Iterator::operator++(int) const
{
    Set_STL::SSR_Iterator res {*this};
    --res.Count;
    return res;
}

template<typename Tp>
const typename Set_STL<Tp>::SSR_Iterator Set_STL<Tp>::SSR_Iterator::operator--(int) const
{
    Set_STL::SSR_Iterator res {*this};
    ++res.Count;
    return res;}

template<typename Tp>
bool Set_STL<Tp>::SSR_Iterator::operator<(const Set_STL::SSR_Iterator &op) const
{
    return (*this->Set)[this->Count] < (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SSR_Iterator::operator>(const Set_STL::SSR_Iterator &op) const
{
    return (*this->Set)[this->Count] > (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SSR_Iterator::operator<=(const Set_STL::SSR_Iterator &op) const
{
    return (*this->Set)[this->Count] <= (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SSR_Iterator::operator>=(const Set_STL::SSR_Iterator &op) const
{
    return (*this->Set)[this->Count] >= (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SSR_Iterator::operator==(const Set_STL::SSR_Iterator &op) const
{
    return (*this->Set)[this->Count] == (*op.Set)[op.Count];
}

template<typename Tp>
bool Set_STL<Tp>::SSR_Iterator::operator!=(const Set_STL::SSR_Iterator &op) const
{
    return (*this->Set)[this->Count] != (*op.Set)[op.Count];
}

template<typename Tp>
ptrdiff_t Set_STL<Tp>::SSR_Iterator::operator-(const Set_STL::SSR_Iterator &op) const
{
    return op.Count-this->Count;
}

template<typename Tp>
typename Set_STL<Tp>::SSR_Iterator Set_STL<Tp>::SSR_Iterator::operator+(const size_t &diff) const
{
    Set_STL::SSR_Iterator res {*this};
    res.Count -= diff;
    return res;
}

template<typename Tp>
typename Set_STL<Tp>::SSR_Iterator Set_STL<Tp>::SSR_Iterator::operator-(const size_t &diff) const
{
    Set_STL::SSR_Iterator res {*this};
    res.Count += diff;
    return res;}

template<typename Tp>
typename Set_STL<Tp>::SSR_Iterator &Set_STL<Tp>::SSR_Iterator::operator+=(const size_t &diff)
{
    this->Count -= diff;
    return *this;
}

template<typename Tp>
typename Set_STL<Tp>::SSR_Iterator &Set_STL<Tp>::SSR_Iterator::operator-=(const size_t &diff)
{
    this->Count += diff;
    return *this;
}


#endif //DATASTRUCTURE_SET_STL_HPP
