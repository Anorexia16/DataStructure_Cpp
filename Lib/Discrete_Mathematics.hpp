#ifndef DATASTRUCTURE_DISCRETE_MATHEMATICS_HPP
#define DATASTRUCTURE_DISCRETE_MATHEMATICS_HPP

#include "Math_Types.hpp"
#include "Iterations.hpp"
#include <array>

template<class cls>
concept Forward_Iteration = requires (cls var) {
    var>var;var<var;var>=var;var<=var;var=var;
    var++;++var;cls(var);var=var;*var;
};

template<class cls>
concept Bidirectional_Iteration = requires (cls var) {
    var>var;var<var;var>=var;var<=var;var=var;
    var++;++var;var--;--var;
    cls(var);var=var;*var;
};

template<typename I, typename II, size_t Is, size_t IIs>
Static_Matrix<Is, IIs, pair<I, II>> &Cartesian_Product
(std::array<I, Is> const &C_Yield, std::array<I, IIs> const &R_Yield)
{
    auto &_res = *new Static_Matrix<Is, IIs, pair<I, II>> {};
    for(size_t i=0;i!=Is*IIs;++i)
    {
        _res.set(i/IIs, i%IIs, pair<I, II>{C_Yield[i/IIs], R_Yield[i%IIs]});
    }
    return _res;
}

template<typename Iter>
requires Bidirectional_Iteration<Iter>
bool next_permutation(Iter _begin, Iter _end)
{
    Iter _pre_iter = _end, _later_iter = _end;
    for(--_pre_iter;; --_later_iter, --_pre_iter)
    {
        if(*_pre_iter < *_later_iter)
        {
            decltype(*_pre_iter) max {*_pre_iter};
            for(auto _max_iter=_pre_iter; _max_iter != _end; ++_max_iter)
            {
                if(*_max_iter > max) max=*_max_iter;_later_iter=_max_iter;
            }
            *_later_iter = *_pre_iter;*_pre_iter = max;
            quick_sort<decltype(*_begin)>(++_pre_iter, _end);
            return true;
        }
        if(_pre_iter == _begin) return false;
    }
}



#endif //DATASTRUCTURE_DISCRETE_MATHEMATICS_HPP
