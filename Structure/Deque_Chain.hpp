#ifndef DATASTRUCTURE_DEQUE_CHAIN_HPP
#define DATASTRUCTURE_DEQUE_CHAIN_HPP

#include <iostream>
#include <vector>
#include <array>
#include "Chain_Bidirectional_Circle.hpp"

template<typename Tp>
class Deque_C {
public:
    Deque_C();

    explicit Deque_C(std::istream &&);

    Deque_C(std::initializer_list<Tp> const &);

    template<size_t n>
    explicit Deque_C(std::array<Tp, n> const &);

    template<template<typename elem, typename = std::allocator<elem>> class Cont>
    explicit Deque_C(Cont<Tp> const &);

    Deque_C(const Tp *const &, size_t const &);

    Deque_C<Tp> &operator=(Deque_C<Tp> &&) noexcept = default;

    Deque_C<Tp> &operator=(Deque_C<Tp> const &) = default;

    Deque_C(Deque_C<Tp> &&) noexcept = default;

    Deque_C(Deque_C<Tp> const &) = default;

    ~Deque_C() = default;

    void insert_head(Tp const &);

    void insert_tail(Tp const &);

    void delete_head();

    void delete_tail();

    Tp first() const;

    Tp end() const;

    [[nodiscard]] inline bool empty() const;

    [[nodiscard]] inline size_t size() const;

protected:
    ChainBC<Tp> Container;
};

template<typename Tp>
Deque_C<Tp>::Deque_C()
    :Container{} {}

template<typename Tp>
Deque_C<Tp>::Deque_C(std::istream &&in)
    :Container{} {
    Tp temp{};
    size_t size {};
    for(NodeB_Iter<Tp> bi {Container.head()};in.good();++bi, ++size) {
        in >> temp;
        bi.link_after(*new NodeB<Tp>{temp, bi.next_ptr()});
        bi.next().next().link_front(bi.next());
    }
    this->Container.resize(size);
}

template<typename Tp>
Deque_C<Tp>::Deque_C(const std::initializer_list<Tp> &list)
        :Container{} {
    NodeB_Iter<Tp> bi {Container.head()};
    for(auto const &ci:list) {
        bi.link_after(*new NodeB<Tp> {ci, bi.next_ptr()});
        bi.next().next().link_front(bi.next());
        ++bi;
    }
    this->Container.resize(std::cend(list) - std::cbegin(list));
}

template<typename Tp>
template<size_t n>
Deque_C<Tp>::Deque_C(const std::array<Tp, n> &array)
        :Container{} {
    NodeB_Iter<Tp> bi {Container.head()};
    for(auto const &ci:array) {
        bi.link_after(*new NodeB<Tp> {ci, bi.next_ptr()});
        bi.next().next().link_front(bi.next());
        ++bi;
    }
    this->Container.resize(std::cend(array) - std::cbegin(array));
}

template<typename Tp>
template<template<typename elem, typename = std::allocator<elem>> class Cont>
Deque_C<Tp>::Deque_C(const Cont<Tp> &cont)
        :Container{} {
    NodeB_Iter<Tp> bi {Container.head()};
    for(auto const &ci:cont) {
        bi.link_after(*new NodeB<Tp> {ci, bi.next_ptr()});
        bi.next().next().link_front(bi.next());
        ++bi;
    }
    this->Container.resize(std::cend(cont)- std::cbegin(cont));
}

template<typename Tp>
Deque_C<Tp>::Deque_C(const Tp *const &ptr, const size_t &size)
        :Container{} {
    NodeB_Iter<Tp> bi {Container.head()};
    for(auto i=0;i!=size;++i) {
        bi.link_after(*new NodeB<Tp> {ptr[i], bi.next_ptr()});
        bi.next().next().link_front(bi.next());
        ++bi;
    }
    this->Container.resize(size);
}

template<typename Tp>
void Deque_C<Tp>::insert_head(const Tp &value) {
    NodeB_Iter<Tp> Head {this->Container.head()};
    Head.link_after(*new NodeB<Tp>{value, &*Head, Head.next_ptr()});
    Head.next_ptr()->next_ptr()->link_front(Head.next());
    this->Container.resize(this->size()-1);
}

template<typename Tp>
void Deque_C<Tp>::insert_tail(const Tp &value) {
    NodeB_Iter<Tp> Head {this->Container.head()};
    Head.link_front(*new NodeB<Tp>{value, Head.prev_ptr(), &*Head});
    Head.prev_ptr()->prev_ptr()->link_after(Head.prev());
    this->Container.resize(this->size()+1);
}

template<typename Tp>
void Deque_C<Tp>::delete_head() {
    if (this->empty()) throw;
    NodeB_Iter<Tp> Head {this->Container.head()};
    Head.link_after(Head.next().next());
    Head.next().link_front(*Head);
    this->Container.resize(this->size()-1);
}

template<typename Tp>
void Deque_C<Tp>::delete_tail() {
    if (this->empty()) throw;
    NodeB_Iter<Tp> Head {this->Container.head()};
    Head.link_front(Head.prev().prev());
    Head.prev().link_after(*Head);
    this->Container.resize(this->size()-1);
}

template<typename Tp>
Tp Deque_C<Tp>::first() const {
    return this->Container.head_c()->next().value_c();
}

template<typename Tp>
Tp Deque_C<Tp>::end() const {
    return this->Container.head_c()->prev().value_c();
}

template<typename Tp>
bool Deque_C<Tp>::empty() const {
    NodeB_Iter<Tp> Head {this->Container.head()};
    return static_cast<void*>(Head.next_ptr())==static_cast<void*>(Head);
}

template<typename Tp>
size_t Deque_C<Tp>::size() const {
    size_t size {};
    for(NodeB_Iter<Tp> si {this->Container.head()}
            ;si.next_ptr()!=this->Container.head();++si, ++size);
    return size;
}


#endif //DATASTRUCTURE_DEQUE_CHAIN_HPP
