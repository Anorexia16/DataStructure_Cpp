#ifndef DATASTRUCTURE_LEGAL_POP_HPP
#define DATASTRUCTURE_LEGAL_POP_HPP

#include <functional>

template <typename Tp>
bool standard_close_to(Tp const &lhv, Tp const &rhv)
{
    Tp temp = rhv;
    return lhv==++temp;
}

template<typename cls, template<typename elem, typename = std::allocator<elem>> class Cont>
bool Legal_4Stack(Cont<cls> const &container)
{
    cls min {};
    cls var = *std::begin(container);
    cls max = *std::begin(container);
    ++min;

    decltype(auto) func = std::function<bool(cls const &, cls const &)>{standard_close_to<cls>};
    for(auto iterator=std::begin(container);iterator!=std::end(container);++iterator)
    {
        if (var == min)
        {
            var = *(iterator++);
            min = ++max;
        }
        if (func(var, *iterator))
        {
            --var;
        } else if (*iterator > var) {
            max = std::max(*iterator, max);
        } else if (*iterator < var) {
            return false;
        }
    }
    return true;
}

#endif //DATASTRUCTURE_LEGAL_POP_HPP
