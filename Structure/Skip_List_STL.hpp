#ifndef DATASTRUCTURE_SKIP_LIST_STL_HPP
#define DATASTRUCTURE_SKIP_LIST_STL_HPP

#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Abstract_Linear_List.hpp"

template<class cls>
class Skip_List_S: virtual public LinearList<cls>
{
public:
    Skip_List_S();

    explicit Skip_List_S(std::istream &&);

    Skip_List_S(const cls * const &, size_t const &);

    Skip_List_S(std::initializer_list<cls> const &);

    template<size_t n>
    explicit Skip_List_S(std::array<cls, n> const &);

    template<template<typename Tp, typename = std::allocator<Tp>> class Cont>
    explicit Skip_List_S(Cont<cls> const &);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    size_t find(cls const &) const;

    void erase(size_t const &);

    void insert(size_t const &, cls const &);

    cls &operator[](size_t const &);

    friend std::ostream &operator<<(std::ostream &&out, Skip_List_S<cls> const &sl)
    {
        for(auto &&iter: sl.Container) out << iter;
        out << std::endl;
        return out;
    }

protected:
    std::vector<cls> Container;
};

template<class cls>
Skip_List_S<cls>::Skip_List_S()
    :Container{} {}

template<class cls>
Skip_List_S<cls>::Skip_List_S(std::istream &&in)
    :Container{}
{
    std::move(std::istream_iterator<cls>(in), std::istream_iterator<cls>(), std::begin(Container));
    Container = std::sort(Container.begin(), Container.end());
}

template<class cls>
Skip_List_S<cls>::Skip_List_S(const cls * const &array, const size_t &size)
    :Container{}
{
    for(auto i=0;i!=size;++i) Container.template emplace_back(const_cast<cls>(array[i]));
    std::sort(Container.begin(), Container.end());
    Container = std::sort(Container.begin(), Container.end());
}

template<class cls>
Skip_List_S<cls>::Skip_List_S(const std::initializer_list<cls> &list)
    :Container{}
{
    std::copy(std::cbegin(list), std::cend(list), std::begin(Container));
    Container = std::sort(Container.begin(), Container.end());
}

template<class cls>
template<size_t n>
Skip_List_S<cls>::Skip_List_S(const std::array<cls, n> &array)
    :Container{}
{
    std::copy(std::cbegin(array), std::cend(array), std::begin(Container));
    Container = std::sort(Container.begin(), Container.end());
}

template<class cls>
template<template<typename Tp, typename = std::allocator<Tp>> class Cont>
Skip_List_S<cls>::Skip_List_S(const Cont<cls> &cont)
{
    std::copy(std::cbegin(cont), std::cend(cont), std::begin(Container));
    Container = std::sort(Container.begin(), Container.end());
}

template<class cls>
bool Skip_List_S<cls>::empty() const
{
    return this->size()==0;
}

template<class cls>
size_t Skip_List_S<cls>::size() const
{
    return this->size();
}

template<class cls>
size_t Skip_List_S<cls>::find(const cls &value) const
{
    size_t const size = this->size();
    size_t begin_key{}, end_key{size-1};
    for(;begin_key!=end_key;)
    {
        if (value==this->Container[end_key])
        {
            for(--end_key;value!=this->Container[end_key];--end_key);
            return end_key+1;
        }else if (value<this->Container[end_key]) {
            end_key = (begin_key+end_key)/2;
        }else if (value>this->Container[end_key]) {
            begin_key= (begin_key+end_key)/2;
        }
    }
    return size;
}

template<class cls>
void Skip_List_S<cls>::erase(const size_t &index)
{
    this->Container.erase(std::begin(this->Container)+index);
}

template<class cls>
void Skip_List_S<cls>::insert(const size_t &index, const cls &value)
{
    this->Container.insert(this->Container.begin()+index, value);
    this->Container = std::sort(std::begin(this->Container), std::end(this->Container));
}

template<class cls>
cls &Skip_List_S<cls>::operator[](const size_t &index)
{
    return this->Container[index];
}

#endif //DATASTRUCTURE_SKIP_LIST_STL_HPP
