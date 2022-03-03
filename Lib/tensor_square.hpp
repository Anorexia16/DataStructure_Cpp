#ifndef DATASTRUCTURE_TENSOR_SQUARE_HPP
#define DATASTRUCTURE_TENSOR_SQUARE_HPP

#include "vector.hpp"
#ifndef ax_size
#define ax_size
typedef unsigned long long size_t;
typedef long long ssize_t;
#endif

namespace ax
{
    template<typename, size_t, size_t ...>
    struct tensor{};

    template<typename cls, size_t depth, size_t length ,size_t ...shape>
    struct tensor<cls, depth, length, shape...>
    {
        tensor();

        inline cls &operator[]
                (std::initializer_list<size_t> const &idx);

        tensor<cls, depth + 1, shape...>* Container[length];
    };

    template<typename cls, size_t depth, size_t length>
    struct tensor<cls, depth, length>
    {
        tensor();

        inline cls &operator[]
                (std::initializer_list<size_t> const &idx);

        cls Container[length];
    };

    template<typename cls, size_t depth, size_t length, size_t... shape>
    tensor<cls, depth, length, shape...>::tensor() : Container()
    {
        for(size_t i = 0; i!= length; ++i) Container[i] = new tensor<cls, depth + 1, shape...> {};
    }

    template<typename cls, size_t depth, size_t length>
    tensor<cls, depth, length>::tensor() : Container{} {}

    template<typename cls, size_t depth, size_t length>
    cls &tensor<cls, depth, length>::operator[](const std::initializer_list<size_t> &idx) {
        return Container[*(idx.begin()+depth-1)];
    }

    template<typename cls, size_t depth, size_t length, size_t... shape>
    cls &tensor<cls, depth, length, shape...>::operator[](const std::initializer_list<size_t> &idx) {
        return Container[*(idx.begin()+depth-1)]->operator[](idx);
    }

    template<typename cls, size_t ...Shapes>
    decltype(auto) make_tensor_s()
    {
        return *new tensor<cls, 1, Shapes...>{};
    }
}

#endif //DATASTRUCTURE_TENSOR_SQUARE_HPP
