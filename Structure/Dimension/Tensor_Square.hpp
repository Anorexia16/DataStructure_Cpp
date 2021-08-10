#ifndef DATASTRUCTURE_TENSOR_SQUARE_HPP
#define DATASTRUCTURE_TENSOR_SQUARE_HPP

#include <array>
#include <vector>

template<typename, size_t, size_t ...>
struct Tensor_S{};


template<typename cls, size_t depth, size_t length ,size_t ...shape>
struct Tensor_S<cls, depth, length, shape...>
{
    Tensor_S() : Container()
    {
        for(size_t i = 0; i!= length; ++i) Container[i] = new Tensor_S<cls, depth+1, shape...> {};
    }

    inline cls &operator[]
    (std::initializer_list<size_t> const &idx)
    {
        return Container[*(idx.begin()+depth-1)]->operator[](idx);
    }

    Tensor_S<cls, depth+1, shape...>* Container[length];
};

template<typename cls, size_t depth, size_t length>
struct Tensor_S<cls, depth, length>
{
public:
    Tensor_S() : Container{} {}

    inline cls &operator[]
    (std::initializer_list<size_t> const &idx)
    {
        return Container[*(idx.begin()+depth-1)];
    }

    cls Container[length];
};

template<typename cls, size_t ...Shapes>
decltype(auto) make_tensor_s()
{
    return *new Tensor_S<cls, 1, Shapes...>{};
}

#endif //DATASTRUCTURE_TENSOR_SQUARE_HPP
