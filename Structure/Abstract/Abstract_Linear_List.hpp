#ifndef DATASTRUCTURE_ABSTRACT_LINEAR_LIST_HPP
#define DATASTRUCTURE_ABSTRACT_LINEAR_LIST_HPP

#include <cstdio>

template<typename T>
class LinearList
{
public:
    virtual ~LinearList() = default;

    [[nodiscard]] virtual bool empty() const = 0;

    [[nodiscard]] virtual size_t size() const = 0;

    virtual size_t find(T const &) const = 0;

    virtual void erase(size_t const &) = 0;

    virtual void insert(size_t const &, T const &) = 0;

    virtual T &operator[](size_t const &) = 0;
};

#endif //DATASTRUCTURE_ABSTRACT_LINEAR_LIST_HPP
