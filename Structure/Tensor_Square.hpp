#ifndef DATASTRUCTURE_TENSOR_SQUARE_HPP
#define DATASTRUCTURE_TENSOR_SQUARE_HPP

#include "../../../../Documents/GitHub/DataStructure/Lib/Operator.hpp"
#include <array>

template<typename, size_t ...>
class Tensor_S {
};

template<typename cls, size_t level>
class Tensor_S<cls, level> {
    using var = cls;
public:
    Tensor_S() : Container{std::array<cls, level>{cls{}, level}} {}

    virtual var &operator[](size_t const &index) { return this->Container[index]; }

protected:
    std::array<cls, level> Container;
};

template<typename cls, size_t level, size_t ...depth>
class Tensor_S<cls, level, depth...> : virtual private Tensor_S<cls, depth...> {
    using var = Tensor_S<cls, depth...>;
public:
    Tensor_S() : Container{std::array<var, level>(var(), level)} {}

    var &operator[](size_t const &index) { return this->Container[index]; }

protected:
    std::array<var, level> Container;
};

template<typename cls, typename ...Shapes>
decltype(auto) make_tensor_s(std::initializer_list<cls> const &list, Shapes const &...shapes) {
    if (std::end(list) - std::begin(list) != prod(shapes...)) throw;
    auto New = *new Tensor_S<cls, shapes...>{};
}

template<typename cls, typename ...Shapes>
decltype(auto) make_tensor_s(cls *const &ptr, Shapes const &...shapes) {
    auto New = *new Tensor_S<cls, shapes...>{};
}

#endif //DATASTRUCTURE_TENSOR_SQUARE_HPP
