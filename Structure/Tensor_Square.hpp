#ifndef DATASTRUCTURE_TENSOR_SQUARE_HPP
#define DATASTRUCTURE_TENSOR_SQUARE_HPP

#include <array>
#include <vector>
#include "../Cpp_Data_Structure/Lib/Operator.hpp"

template<typename, size_t ...>
struct Tensor_S{};


template<typename cls, size_t length ,size_t ...shape>
struct Tensor_S<cls, length, shape...>
{
    Tensor_S() : Container()
    {
        for(size_t i = 0; i!= length; ++i) Container[i] = new Tensor_S<cls, shape...> {};
    }

    cls &operator[]
    (std::vector<size_t> idx)
    {
        return Container[*idx.begin()]->operator[](std::vector<size_t> {std::begin(idx) + 1, std::end(idx)});
    }

    std::array<Tensor_S<cls, shape...>* , length> Container;
};

template<typename cls, size_t length>
struct Tensor_S<cls, length>
{
public:
    Tensor_S() : Container{} {}

    cls &operator[]
    (std::vector<size_t> idx)
    {
        return Container[*idx.begin()];
    }

    std::array<cls, length> Container;
};

template<typename cls, size_t ...Shapes>
decltype(auto) make_tensor_s()
{
    return *new Tensor_S<cls, Shapes...>{};
}

#endif //DATASTRUCTURE_TENSOR_SQUARE_HPP
