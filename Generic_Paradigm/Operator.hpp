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

template<class cls>
cls &copy(cls const &source) {
    return *new cls {source};
}

template<class cls>
cls &&move(cls &&source) {
    return cls{std::forward<>(source)};
}

#endif //DATASTRUCTURE_OPERATOR_HPP
