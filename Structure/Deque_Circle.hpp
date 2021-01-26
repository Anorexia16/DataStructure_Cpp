#ifndef DATASTRUCTURE_DEQUE_CIRCLE_HPP
#define DATASTRUCTURE_DEQUE_CIRCLE_HPP

#include <iostream>
#include <vector>
#include <array>
#include "Chain_Bidirectional_Circle.hpp"

template<typename Tp>
class Deque_CC {
public:
    explicit Deque_CC(size_t const & = 1);

    explicit Deque_CC(std::istream &&, size_t const & = 0);

    Deque_CC(std::initializer_list<Tp> const &, size_t const & = 0);

    template<size_t n>
    explicit Deque_CC(std::array<Tp, n> const &, size_t const & = 0);

    template<template<typename elem, typename = std::allocator<elem>> class Cont>
    explicit Deque_CC(Cont<Tp> const &, size_t const & = 0);

    Deque_CC(const Tp *const &, size_t const &, size_t const & = 0);

    Deque_CC<Tp> &operator=(Deque_CC<Tp> &&) noexcept = default;

    Deque_CC<Tp> &operator=(Deque_CC<Tp> const &) = default;

    Deque_CC(Deque_CC<Tp> &&) noexcept = default;

    Deque_CC(Deque_CC<Tp> const &) = default;

    ~Deque_CC() = default;

    void insert_head(Tp const &);

    void insert_tail(Tp const &);

    void delete_head();

    void delete_tail();

    Tp first() const;

    Tp end() const;

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
Deque_CC<Tp>::Deque_CC(const size_t &capacity)
    :Container{capacity}, Capacity{capacity}, First{Container.head()}, Rare{Container.head()}, Size{0} {
    for(auto i=0;i!=capacity;++i, ++Rare) {
        Rare.link_after(*new NodeB<Tp> {Tp{}, Rare, Rare.next_ptr()});
        Rare.next().next().link_front(Rare.next());
    }
    Container.resize(capacity);
}

template<typename Tp>
Deque_CC<Tp>::Deque_CC(std::istream &&in, const size_t &capacity)
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
Deque_CC<Tp>::Deque_CC(const std::initializer_list<Tp> &list, const size_t &capacity)
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
Deque_CC<Tp>::Deque_CC(const std::array<Tp, n> &array, size_t const &capacity)
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
Deque_CC<Tp>::Deque_CC(const Cont<Tp> &cont, const size_t &capacity)
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
Deque_CC<Tp>::Deque_CC(const Tp *const &ptr, const size_t &size, const size_t &capacity)
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
void Deque_CC<Tp>::insert_head(const Tp &value) {
    if (this->First.prev_ptr()==this->Container.head()) {
        --First;
    }
    (*(--First))() = value;
    ++this->Size;
}

template<typename Tp>
void Deque_CC<Tp>::insert_tail(const Tp &value) {
    if (this->Rare.next_ptr()==this->Container.head()) {
        ++Rare;
    }
    (*(++Rare))() = value;
    ++this->Size;
}

template<typename Tp>
void Deque_CC<Tp>::delete_head() {
    if (this->empty()) throw;
    ++First;
    if (First == this->Container.head()) ++First;
    --this->Size;
}

template<typename Tp>
void Deque_CC<Tp>::delete_tail() {
    if (this->empty()) throw;
    --Rare;
    if (First == this->Container.head()) --Rare;
    --this->Size;
}

template<typename Tp>
Tp Deque_CC<Tp>::first() const {
    return First.value_c();
}

template<typename Tp>
Tp Deque_CC<Tp>::end() const {
    return Rare.value_c();
}

template<typename Tp>
bool Deque_CC<Tp>::empty() const {
    return this->Size == 0;
}

template<typename Tp>
size_t Deque_CC<Tp>::size() const {
    return this->Size;
}

template<typename Tp>
bool Deque_CC<Tp>::full() const {
    return (this->Rare.next_ptr()==this->Container.head() && this->First.prev_ptr()==this->Container.head())
    || this->First==this->Rare.next_ptr();
}


#endif //DATASTRUCTURE_DEQUE_CIRCLE_HPP
