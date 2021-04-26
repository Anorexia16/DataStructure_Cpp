#ifndef DATASTRUCTURE_OPERATOR_HPP
#define DATASTRUCTURE_OPERATOR_HPP

#include <functional>

template<typename ...Args>
decltype(auto) prod(Args const &... args)
{
    return (args*...);
}

template<typename ...Args>
decltype(auto) sum(Args const &... args)
{
    return (args+...);
}

template<typename ...Args>
bool all(Args const &... args)
{
    return (args&&...);
}

template<typename ...Args>
bool any(Args const &... args)
{
    return (args||...);
}

#endif //DATASTRUCTURE_OPERATOR_HPP
