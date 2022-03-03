#ifndef DATASTRUCTURE_DISCRETE_HPP
#define DATASTRUCTURE_DISCRETE_HPP

#include <Math_Types.hpp>
#include "iterator.hpp"
#include <sort.hpp>
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

template<typename iterator>
requires Bidirectional_Iteration<iterator>
bool next_permutation(iterator begin, iterator end)
{
    iterator left_iter = end, right_iter = end;
    --left_iter, --right_iter;
    for(--left_iter;; --right_iter, --left_iter)
    {
        if(*left_iter <= *right_iter)
        {
            decltype(remove_reference(*begin)) extra {*right_iter};
            iterator pos{right_iter};
            for(iterator max_iter=right_iter; max_iter != end; ++max_iter)
            {
                if(*max_iter < extra&&*max_iter>*left_iter)
                {
                    extra=*max_iter;
                    pos=max_iter;
                }
            }
            *pos = *left_iter;*left_iter = extra;
            quick_sort(right_iter, end);
            return true;
        }
        if(left_iter == begin) return false;
    }
}

#endif //DATASTRUCTURE_DISCRETE_HPP
