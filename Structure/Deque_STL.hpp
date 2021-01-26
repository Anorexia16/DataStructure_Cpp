#ifndef DATASTRUCTURE_DEQUE_STL_HPP
#define DATASTRUCTURE_DEQUE_STL_HPP

#include <iostream>
#include <iterator>
#include <vector>
#include <array>

template<typename Tp>
class Deque_STL {
public:
    Deque_STL();

    explicit Deque_STL(std::istream &&);

    Deque_STL(std::initializer_list<Tp> const &);

    template<size_t n>
    explicit Deque_STL(std::array<Tp, n> const &);

    template<template<typename elem, typename = std::allocator<elem>> class Cont>
    explicit Deque_STL(Cont<Tp> const &);

    Deque_STL(const Tp * const &, size_t const &);

    Deque_STL<Tp> &operator=(Deque_STL<Tp> &&) noexcept = default;

    Deque_STL<Tp> & operator=(Deque_STL<Tp> const &) = default;

    Deque_STL(Deque_STL<Tp> &&) noexcept = default;

    Deque_STL(Deque_STL<Tp> const &) = default;

    void insert_head(Tp const &);

    void insert_tail(Tp const &);

    void delete_head();

    void delete_tail();

    Tp first() const;

    Tp end() const;

    [[nodiscard]] inline bool empty() const;

    [[nodiscard]] inline size_t size() const;

private:
    std::vector<Tp> Container;
};

template<typename Tp>
Deque_STL<Tp>::Deque_STL()
    :Container{} {}

template<typename Tp>
Deque_STL<Tp>::Deque_STL(std::istream &&in)
    :Container{} {
    std::move(std::istream_iterator<Tp>(in), std::istream_iterator<Tp>(), std::begin(Container));
}

template<typename Tp>
Deque_STL<Tp>::Deque_STL(const std::initializer_list<Tp> &list)
        :Container{} {
    std::copy(std::cbegin(list), std::cend(list), std::begin(Container));
}

template<typename Tp>
template<size_t n>
Deque_STL<Tp>::Deque_STL(const std::array<Tp, n> &array)
    :Container{} {
    std::copy(std::cbegin(array), std::cend(array), std::begin(Container));
}

template<typename Tp>
template<template<typename elem, typename = std::allocator<elem>> class Cont>
Deque_STL<Tp>::Deque_STL(const Cont<Tp> &cont)
    :Container{} {
    std::copy(std::cbegin(cont), std::cend(cont), std::begin(Container));
}

template<typename Tp>
Deque_STL<Tp>::Deque_STL(const Tp *const &ptr, const size_t &size)
    :Container{} {
    for(auto i=0;i!=size;++i) Container.template emplace_back(const_cast<Tp>(ptr[i]));
}

template<typename Tp>
void Deque_STL<Tp>::insert_head(const Tp &value) {
    this->Container.insert(value, std::begin(this->Container));
}

template<typename Tp>
void Deque_STL<Tp>::insert_tail(const Tp &value) {
    this->Container.template emplace_back(value);
}

template<typename Tp>
void Deque_STL<Tp>::delete_head() {
    this->Container.erase(std::rbegin(this->Container));
}

template<typename Tp>
void Deque_STL<Tp>::delete_tail() {
    this->Container.erase(std::begin(this->Container));
}

template<typename Tp>
Tp Deque_STL<Tp>::first() const {
    return *std::begin(this->Container);
}

template<typename Tp>
Tp Deque_STL<Tp>::end() const {
    return *std::rbegin(this->Container);
}

template<typename Tp>
bool Deque_STL<Tp>::empty() const {
    return this->Container.empty();
}

template<typename Tp>
size_t Deque_STL<Tp>::size() const {
    return this->Container.size();
}


#endif //DATASTRUCTURE_DEQUE_STL_HPP
