#ifndef DATASTRUCTURE_ARRAY_LIST
#define DATASTRUCTURE_ARRAY_LIST

#include <vector>
#include <iterator>
#include <algorithm>
#include "../Abstract/Abstract_Linear_List.hpp"

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont = std::vector>
class ArrayListS : LinearList<T>
{
public:
    explicit ArrayListS();

    explicit ArrayListS(ArrayListS<T> const &);

    ~ArrayListS();

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    T &operator[](int const &) const;

    size_t find(T const &) const;

    void erase(int const &);

    void insert(int const &, T const &);

    Cont<T> &operator*();

    Cont<T> *operator->();

    friend std::ostream &operator<<(std::ostream &out, ArrayListS<T> const &x) {
        std::copy(std::begin(x.Container), std::end(x.Container), std::ostream_iterator<T>(out));
        return out;
    }

protected:
    Cont<T> Container;
};

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
ArrayListS<T, Cont>::ArrayListS()
        : Container{Cont < T > {}} {}

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
ArrayListS<T, Cont>::ArrayListS(ArrayListS<T> const &copy)
        : Container{copy.Container} {}

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
ArrayListS<T, Cont>::~ArrayListS()
{
    for (auto &&iter: this->Container) iter.~T();
    delete (this);
}

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
bool ArrayListS<T, Cont>::empty() const
{
    return this->Container.Size() == 0;
}

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
size_t ArrayListS<T, Cont>::size() const
{
    return this->Container.Size();
}

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
T &ArrayListS<T, Cont>::operator[](int const &x) const
{
    return this->Container[x];
}

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
size_t ArrayListS<T, Cont>::find(const T &x) const
{
    for (auto &&iter: this->Container) {
        if (iter == x) return &iter - &this->Container[0];
    }
    return -1;
}

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
void ArrayListS<T, Cont>::erase(int const &x)
{
    this->Container.erase(std::begin(this->Container) + x);
}

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
void ArrayListS<T, Cont>::insert(int const &index, const T &elem)
{
    this->Container.insert(std::begin(this->Container) + index, elem);
}

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
Cont<T> &ArrayListS<T, Cont>::operator*() { return *&Container; }

template<typename T,
        template<typename elem, typename =std::allocator<elem>> class Cont>
Cont<T> *ArrayListS<T, Cont>::operator->() { return &Container; }


#endif //DATASTRUCTURE_ARRAY_LIST_STL_HPP
