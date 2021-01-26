#ifndef DATASTRUCTURE_QUEUE_CIRCLE_HPP
#define DATASTRUCTURE_QUEUE_CIRCLE_HPP

#include <iostream>
#include <vector>
#include <array>
#include "Chain_Bidirectional_Circle.hpp"

template<typename Tp>
class Queue_CC {
public:
    explicit Queue_CC(size_t const & = 1);

    explicit Queue_CC(std::istream &&, size_t const & = 0);

    Queue_CC(std::initializer_list<Tp> const &, size_t const &);

    template<size_t n>
    explicit Queue_CC(std::array<Tp, n> const &, size_t const & = 0);

    template<template<typename elem, typename = std::allocator<elem>> class Cont>
    Queue_CC(Cont<Tp> const &, size_t const &);

    Queue_CC(const Tp *const &, size_t const &, size_t const & = 0);

    Queue_CC<Tp> &operator=(Queue_CC<Tp> &&) noexcept = default;

    Queue_CC<Tp> &operator=(Queue_CC<Tp> const &) = default;

    Queue_CC(Queue_CC<Tp> &&) noexcept = default;

    Queue_CC(Queue_CC<Tp> const &) = default;

    ~Queue_CC() = default;

    void enqueue(Tp const &);

    void dequeue();

    Tp first() const;

    [[nodiscard]] inline bool full() const;

    [[nodiscard]] inline bool empty() const;

    [[nodiscard]] inline size_t size() const;

protected:
    NodeB_Iter<Tp> First;

    NodeB_Iter<Tp> Rare;

    ChainBC<Tp> Container;

    size_t Capacity;

    size_t Size;
};

template<typename Tp>
Queue_CC<Tp>::Queue_CC(const size_t &capacity)
    :Container{capacity}, Capacity{capacity}, First{Container.head()}, Rare{Container.head()}, Size{0} {
    for (auto i = 0; i != capacity; ++i, ++Rare) {
        Rare.link_after(*new NodeB<Tp>{Tp{}, Rare, Rare.next_ptr()});
        Rare.next().next().link_front(Rare.next());
    }
    Container.resize(capacity);
}

template<typename Tp>
Queue_CC<Tp>::Queue_CC(std::istream &&in, const size_t &capacity)
    :Container{capacity}, Capacity{capacity}, First{Container.head()}, Rare{Container.head()}, Size{} {
    size_t size {};
    for(Tp temp;in.good();++size, ++Rare) {
        in >> temp;
        Rare.link_after(*new NodeB<Tp> {temp , Rare, Rare.next_ptr()});
        Rare.next().next().link_front(Rare.next());
    }
    if (capacity > 2 * size) {
        for(auto i=0;i!=capacity-size;++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp> {Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(capacity);
    } else {
        for(auto i=0;i!=size;++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp> {Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(2 * size);
    }
    Size = size;
}

template<typename Tp>
Queue_CC<Tp>::Queue_CC(const std::initializer_list<Tp> &list, const size_t &capacity)
    :Container{capacity}, Capacity{capacity}, First{Container.head()}, Rare{Container.head()}, Size{} {
    for (auto const &iterator:list) {
        Rare.link_after(*new NodeB<Tp> {iterator, &*Rare, Rare.next_ptr()});
        Rare.next().next().link_front(Rare.next());
        ++Rare;
    }
    size_t const size = std::cend(list) - std::cbegin(list);
    if (capacity > 2 * size) {
        for(auto i=0;i!=capacity-size;++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp> {Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(capacity);
    } else {
        for(auto i=0;i!=size;++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp> {Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(2 * size);
    }
    Size = size;
}

template<typename Tp>
template<size_t n>
Queue_CC<Tp>::Queue_CC(const std::array<Tp, n> &, const size_t &)
    :Container{capacity}, Capacity{capacity}, First{Container.head()}, Rare{Container.head()} {
    for (auto const &iterator:array) {
        Rare.link_after(*new NodeB<Tp> {iterator, &*Rare, Rare.next_ptr()});
        Rare.next().next().link_front(Rare.next());
        ++Rare;
    }
    size_t const size = std::cend(array) - std::cbegin(array);
    if (capacity > 2 * size) {
        for(auto i=0;i!=capacity-size;++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp> {Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(capacity);
    } else {
        for(auto i=0;i!=size;++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp> {Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(2 * size);
    }
    Size = size;
}

template<typename Tp>
template<template<typename elem, typename = std::allocator<elem>> class Cont>
Queue_CC<Tp>::Queue_CC(const Cont<Tp> &cont, const size_t &size)
    :Container{capacity}, Capacity{capacity}, First{Container.head()}, Rare{Container.head()} {
    for (auto const &iterator:cont) {
        Rare.link_after(*new NodeB<Tp> {iterator, &*Rare, Rare.next_ptr()});
        Rare.next().next().link_front(Rare.next());
        ++Rare;
    }
    size_t const size = std::cend(cont) - std::cbegin(cont);
    if (capacity > 2 * size) {
        for(auto i=0;i!=capacity-size;++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp> {Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(capacity);
    } else {
        for(auto i=0;i!=size;++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp> {Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(2 * size);
    }
    Size = size;
}

template<typename Tp>
Queue_CC<Tp>::Queue_CC(const Tp *const &ptr, const size_t &size, const size_t &capacity)
    :Container{capacity}, Capacity{capacity}, First{Container.head()}, Rare{Container.head()} {
    for (auto i = 0; i != size; ++i) {
        Rare.link_after(*new NodeB<Tp>{ptr[i], &*Rare, Rare.next_ptr()});
        Rare.next().next().link_front(Rare.next());
        ++Rare;
    }
    if (capacity > 2 * size) {
        for (auto i = 0; i != capacity-size; ++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp>{Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(capacity);
    } else {
        for (auto i = 0; i != size; ++i, ++Rare) {
            Rare.link_after(*new NodeB<Tp>{Tp{}, &*Rare, Rare.next_ptr()});
            Rare.next().next().link_front(Rare.next());
        }
        Container.resize(2 * size);
    }
    Size = size;
}

template<typename Tp>
void Queue_CC<Tp>::enqueue(const Tp &) {
    if (this->Rare.next_ptr()==this->Container.head()) {
        ++Rare;
    }
    (*(++Rare))() = value;
    ++this->Size;
}

template<typename Tp>
void Queue_CC<Tp>::dequeue() {
    if (this->empty()) throw;
    ++First;
    if (First == this->Container.head()) ++First;
    --this->Size;
}

template<typename Tp>
Tp Queue_CC<Tp>::first() const {
    return First.value_c();
}

template<typename Tp>
bool Queue_CC<Tp>::full() const {
    return (this->Rare.next_ptr()==this->Container.head() && this->First.prev_ptr()==this->Container.head())
           || this->First==this->Rare.next_ptr();}

template<typename Tp>
bool Queue_CC<Tp>::empty() const {
    return this->Size == 0;
}

template<typename Tp>
size_t Queue_CC<Tp>::size() const {
    return this->Size;
}

#endif //DATASTRUCTURE_QUEUE_CIRCLE_HPP
