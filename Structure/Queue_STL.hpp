#ifndef DATASTRUCTURE_QUEUE_STL_HPP
#define DATASTRUCTURE_QUEUE_STL_HPP

#include <iostream>
#include <iterator>
#include <vector>
#include <array>

template<typename Tp>
class Queue_STL
{
public:
    Queue_STL();

    explicit Queue_STL(std::istream &&);

    Queue_STL(std::initializer_list<Tp> const &);

    template<size_t n>
    explicit Queue_STL(std::array<Tp, n> const &);

    template<template<typename elem, typename = std::allocator<elem>>class Cont>
    explicit Queue_STL(Cont<Tp> const &);

    Queue_STL(const Tp * const &, size_t const &);

    Queue_STL<Tp> &operator=(Queue_STL<Tp> &&) noexcept = default;

    Queue_STL<Tp> &operator=(Queue_STL<Tp> const &) = default;

    Queue_STL(Queue_STL<Tp> &&) noexcept = default;

    Queue_STL(Queue_STL<Tp> const &) = default;

    ~Queue_STL() = default;

    void enqueue(Tp const &);

    void dequeue();

    Tp first() const;

    [[nodiscard]] inline bool empty() const;

    [[nodiscard]] inline size_t size() const;

protected:
    std::vector<Tp> Container;
};

template<typename Tp>
Queue_STL<Tp>::Queue_STL()
    :Container{} {}

template<typename Tp>
Queue_STL<Tp>::Queue_STL(std::istream &&in)
    :Container{}
{
    std::move(std::istream_iterator<Tp>(in), std::istream_iterator<Tp>(), std::begin(Container));
}

template<typename Tp>
Queue_STL<Tp>::Queue_STL(const std::initializer_list<Tp> &list)
    :Container{}
{
    std::copy(std::cbegin(list), std::cend(list), std::begin(Container));
}

template<typename Tp>
template<size_t n>
Queue_STL<Tp>::Queue_STL(const std::array<Tp, n> &array)
    :Container{}
{
    std::copy(std::cbegin(array), std::cend(array), std::begin(Container));
}

template<typename Tp>
template<template<typename elem, typename = std::allocator<elem>>class Cont>
Queue_STL<Tp>::Queue_STL(const Cont<Tp> &cont)
    :Container{}
{
    std::copy(std::cbegin(cont), std::cend(cont), std::begin(Container));
}

template<typename Tp>
Queue_STL<Tp>::Queue_STL(const Tp *const &ptr, const size_t &size)
    :Container{}
{
    for(auto i=0;i!=size;++i) Container.template emplace_back(const_cast<Tp>(ptr[i]));
}

template<typename Tp>
void Queue_STL<Tp>::enqueue(const Tp &value)
{
    this->Container.template emplace_back(value);
}

template<typename Tp>
void Queue_STL<Tp>::dequeue()
{
    this->Container.erase(std::begin(this->Container));
}

template<typename Tp>
Tp Queue_STL<Tp>::first() const
{
    return this->Container[0];
}

template<typename Tp>
bool Queue_STL<Tp>::empty() const
{
    return this->Container.empty();
}

template<typename Tp>
size_t Queue_STL<Tp>::size() const
{
    return this->Container.size();
}

#endif //DATASTRUCTURE_QUEUE_STL_HPP
