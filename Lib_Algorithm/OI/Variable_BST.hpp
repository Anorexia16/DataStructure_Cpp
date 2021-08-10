#ifndef DATASTRUCTURE_VARIABLE_BST_HPP
#define DATASTRUCTURE_VARIABLE_BST_HPP

#include <cstdlib>
#include "../../Generic_Paradigm/Iterable.hpp"

template<typename Tp=int, Iterable_Container Container,
        typename = std::enable_if<std::is_integral_v<Tp>>>
bool is_variable(Container const &vec)
{
    if (vec.index() <= 2) return true;
    Tp max=vec[0]>vec[1]?vec[0]:vec[1],
            min=vec[0]>vec[1]?vec[1]:vec[0];
    for (size_t i=2;i!=vec.index(); ++i)
    {
        if (vec[i]>vec[i-1]&&vec[i]>max||vec[i]<vec[i-1]&&vec[i]<min) {
            return false;
        }
        vec[i]>vec[i-1]?min=vec[i-1]:max=vec[i-1];
    }
    return true;
}

template<typename Tp=int, size_t n,
        typename = std::enable_if<std::is_integral_v<Tp>>>
bool is_variable(Tp const (&arr)[n])
{
    if constexpr (n<=2) return true;
    Tp max = arr[0]>arr[1]?arr[0]:arr[1],
        min = arr[0]>arr[1]?arr[1]:arr[0];
    for (size_t i=2;i!=n;++i)
    {
        if (arr[i]>arr[i-1]&&arr[i]>max||arr[i]<arr[i-1]&&arr[i]<min) {
            return false;
        }
        arr[i]>arr[i-1] ? min = arr[i-1]: max = arr[i-1];
    }
    return true;
}

#endif //DATASTRUCTURE_VARIABLE_BST_HPP
