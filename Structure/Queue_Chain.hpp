#ifndef DATASTRUCTURE_QUEUE_CHAIN_HPP
#define DATASTRUCTURE_QUEUE_CHAIN_HPP

#include <iostream>
#include <vector>
#include <array>
#include "Chain_Bidirectional_Circle.hpp"

template<typename Tp>
class Queue_C {
public:
    Queue_C();

    explicit Queue_C(std::istream &&);
    
    Queue_C(std::initializer_list<Tp> const &);

    template<size_t n>
    explicit Queue_C(std::array<Tp, n> const &);

    template<template<typename elem, typename = std::allocator<elem>> class Cont>
    explicit Queue_C(Cont<Tp> const &);

    Queue_C(const Tp * const &, size_t const &);
    
    Queue_C<Tp> &operator=(Queue_C<Tp> &&) noexcept = default;
    
    Queue_C<Tp> &operator=(Queue_C<Tp> const &) = default;
    
    Queue_C(Queue_C<Tp> &&) noexcept = default;
    
    Queue_C(Queue_C<Tp> const &) = default;
    
    ~Queue_C() = default;
    
    void enqueue(Tp const &);
    
    void dequeue();
    
    Tp first() const;
    
    [[nodiscard]] inline bool empty() const;
    
    [[nodiscard]] inline size_t size() const;

protected:
    ChainBC<Tp> Container;
};

template<typename Tp>
Queue_C<Tp>::Queue_C() 
    :Container{} {}

template<typename Tp>
Queue_C<Tp>::Queue_C(std::istream &&in)
    :Container{} {
    NodeB_Iter<Tp> bi {Container.head()};
    size_t size {};
    Tp temp;
    for(;in.good(); ++bi, ++size) {
        in >> temp;
        bi.link_after(*new NodeB<Tp>{temp, bi.next_ptr()});
        bi.next().next().link_front(bi.next());
    }
    this->Container.resize(size);
}

template<typename Tp>
Queue_C<Tp>::Queue_C(const std::initializer_list<Tp> &list)
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
Queue_C<Tp>::Queue_C(const std::array<Tp, n> &array)
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
Queue_C<Tp>::Queue_C(const Cont<Tp> &cont)
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
Queue_C<Tp>::Queue_C(const Tp *const &ptr, const size_t &size)
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
void Queue_C<Tp>::enqueue(const Tp &value) {
    NodeB_Iter<Tp> Head {this->Container.head()};
    Head.link_front(*new NodeB<Tp>{value, Head.prev_ptr(), &*Head});
    Head.prev_ptr()->prev_ptr()->link_after(Head.prev());
    this->Container.resize(this->size()+1);
}

template<typename Tp>
void Queue_C<Tp>::dequeue() {
    if (this->empty()) throw;
    NodeB_Iter<Tp> Head {this->Container.head()};
    Head.link_after(Head.next().next());
    Head.next().link_front(*Head);
    this->Container.resize(this->size()-1);
}

template<typename Tp>
Tp Queue_C<Tp>::first() const {
    return this->Container.head()->next().value_c();
}

template<typename Tp>
bool Queue_C<Tp>::empty() const {
    NodeB_Iter<Tp> Head {this->Container.head()};
    return static_cast<void*>(Head.next_ptr())==static_cast<void*>(Head);
}

template<typename Tp>
size_t Queue_C<Tp>::size() const {
    size_t size {};
    for(NodeB_Iter<Tp> si {this->Container.head()}
        ;si.next_ptr()!=this->Container.head();++si, ++size);
    return size;
}

#endif //DATASTRUCTURE_QUEUE_CHAIN_HPP
