#ifndef DATASTRUCTURE_NODE_NONLINEAR_HPP
#define DATASTRUCTURE_NODE_NONLINEAR_HPP

#include <iostream>

template<typename cls>
class Node_Nonlinear {
public:
    Node_Nonlinear();

    explicit Node_Nonlinear(cls const &);

    Node_Nonlinear(cls const &, Node_Nonlinear<cls> *const &, std::initializer_list<Node_Nonlinear<cls>> const &);

    template<template<typename elem, typename = std::allocator<elem>> class Cont>
    Node_Nonlinear(cls const &, Node_Nonlinear<cls> *const &, Cont<Node_Nonlinear<cls>> const &);

    Node_Nonlinear(cls const &, Node_Nonlinear<cls> *const &, Node_Nonlinear<cls>* const &, size_t const &);
private:
    std::vector<Node_Nonlinear<cls> *> Destination{};
    Node_Nonlinear<cls> *Source;
    cls Value;
};

template<typename cls>
Node_Nonlinear<cls>::Node_Nonlinear()
    :Value{}, Source{nullptr}, Destination{} {

}

template<typename cls>
Node_Nonlinear<cls>::Node_Nonlinear(const cls &value)
    :Value{value}, Source{nullptr}, Destination{} {}

template<typename cls>
Node_Nonlinear<cls>::Node_Nonlinear(const cls &value, Node_Nonlinear<cls> *const &ptr,
                                    const std::initializer_list<Node_Nonlinear<cls>> &list)
    :Value{value}, Source{ptr}, Destination{} {
    std::copy(std::cbegin(list), std::cend(list), std::begin(Destination));
}

template<typename cls>
template<template<typename elem, typename = std::allocator<elem>> class Cont>
Node_Nonlinear<cls>::Node_Nonlinear(const cls &value, Node_Nonlinear<cls> *const &ptr, const Cont<Node_Nonlinear<cls>> &cont)
    :Value{value}, Source{ptr}, Destination{} {
    std::copy(std::cbegin(cont), std::cend(cont), std::begin(Destination));
}

template<typename cls>
Node_Nonlinear<cls>::Node_Nonlinear(const cls &value, Node_Nonlinear<cls> *const &ptr, Node_Nonlinear<cls> *const &array,
                                    const size_t &size)
    :Value{value}, Source{ptr}, Destination{} {
    for(auto i=0;i!=size;++i) Destination.template emplace_back(array[i]);
}

#endif //DATASTRUCTURE_NODE_NONLINEAR_HPP
