#ifndef DATASTRUCTURE_CHAIN_BOX_SORT_HPP
#define DATASTRUCTURE_CHAIN_BOX_SORT_HPP

#include <functional>
#include "../../Structure/Linear/Chain_Unidirectional_Circle.hpp"

template<typename cls>
class Chain_Box_Sorter : virtual public ChainUC<cls>
{
public:
    template<class Tp>
    explicit Chain_Box_Sorter(ChainUC<cls> const &, ChainUC<ChainUC<cls>> &,
                              std::function<Tp(cls const &)> const &, bool const &);

    Chain_Box_Sorter(Chain_Box_Sorter<cls> const &) = delete;

private:
    template<class Tp>
    ChainUC<ChainUC<cls>> operator()(ChainUC<cls> const &, std::function<Tp(cls const &)> const &, bool const &);
};

template<typename cls>
template<class Tp>
Chain_Box_Sorter<cls>::Chain_Box_Sorter(const ChainUC<cls> &chain, ChainUC<ChainUC<cls>> &arg,
                                        std::function<Tp(const cls &)> const &func, const bool &reverse)
{
    arg = (*this)(chain, arg, func, reverse);
}

template<typename cls>
template<typename Tp>
ChainUC<ChainUC<cls>>
Chain_Box_Sorter<cls>::operator()(const ChainUC<cls> &chain, std::function<Tp(cls const &)> const &func,
                                  bool const &reverse)
{
    std::vector<Tp> cont{};
    size_t groups{};
    cls cal_temp;
    for (NodeU<cls> *iterator{chain.Head->Next}; iterator != chain.Head; iterator = iterator->Next)
    {
        cal_temp = func(iterator->Element);
        for (auto const &vec_iter:cont)
            if (vec_iter != cal_temp)
            {
                cont.template emplace_back(cal_temp);
                ++groups;
            }
    }
    ChainUC<ChainUC<cls>> res{groups};
    for (NodeU<ChainUC<cls>> *iterator{res.Head->Next}; iterator != res.Head; iterator = iterator->Next)
    {
        iterator->Element.resize(static_cast<size_t>(chain.size() / groups + 1));
    }
    Tp temp;
    bool fill;
    for (NodeU<cls> *main_iter{chain.Head->Next}; main_iter != chain.Head; main_iter = main_iter->Next)
    {
        NodeU<ChainUC<cls>> *build_iter{res.Head};
        temp = func(main_iter->Element);
        fill = true;
        if (!reverse)
        {
            for (; build_iter->Next != res.Head; build_iter = build_iter->Next) {
                if ((build_iter == res.Head && temp < func(build_iter->Next->Element.Head->Next->Element))
                || (temp > func(build_iter->Element.Head->Next->Element) && temp < func(build_iter->Element.Head->Next->Element)))
                {
                    build_iter->Next = new NodeU<ChainUC<cls>>{static_cast<size_t>(chain.size() / groups + 1), build_iter->Next};
                    build_iter->Next->Element.insert(0, temp);
                    res.resize(res.size()+1);
                    fill = false;
                } else if (build_iter != res.Head && temp==func(build_iter->Next->Element.Head->Next->Element))
                {
                    NodeU<cls> *inner_iter {build_iter->Next->Element.Head};
                    bool inner_fill = true;
                    for(;inner_iter->Next != build_iter->Next->Element.Head; ++inner_iter)
                    {
                        if ((inner_iter== build_iter->Next->Element.Head && temp < func(inner_iter->Next->Element))
                            || (temp>func(inner_iter->Element)&&temp<=func(inner_iter->Next->Element)))
                        {
                            inner_iter->Next = new NodeU<cls> {temp, inner_iter->Next};
                            build_iter->Next->Element.resize(build_iter->Next->Element.size()+1);
                            inner_fill = false;
                        }
                    }
                    if (inner_fill)
                    {
                        inner_iter->Next = new NodeU<cls> {temp, inner_iter->Next};
                        build_iter->Next->Element.resize(build_iter->Next->Element.size()+1);
                    }
                    fill = false;
                }
            }
            if (fill)
            {
                build_iter->Next = new NodeU<ChainUC<cls>>{static_cast<size_t>(chain.size() / groups + 1), build_iter->Next};
                build_iter->Next->Element.insert(0, temp);
                res.resize(res.size()+1);
            }
        } else if (reverse) {
            for (; build_iter->Next != res.Head; build_iter = build_iter->Next) {
                if ((build_iter == res.Head && temp > func(build_iter->Next->Element.Head->Next->Element))
                    || (temp < func(build_iter->Element.Head->Next->Element)
                    && temp > func(build_iter->Element.Head->Next->Element)))
                {
                    build_iter->Next = new NodeU<ChainUC<cls>>{static_cast<size_t>(chain.size() / groups + 1), build_iter->Next};
                    build_iter->Next->Element.insert(0, temp);
                    res.resize(res.size()+1);
                    fill = false;
                } else if (build_iter != res.Head && temp==func(build_iter->Next->Element.Head->Next->Element))
                {
                    NodeU<cls> *inner_iter {build_iter->Next->Element.Head};
                    bool inner_fill = true;
                    for(;inner_iter->Next!= build_iter->Next->Element.Head ; inner_iter = inner_iter->Next)
                    {
                        if ((inner_iter== build_iter->Next->Element.Head && temp > func(inner_iter->Next->Element))
                            || (temp<func(inner_iter->Element)&&temp>=func(inner_iter->Next->Element)))
                        {
                            inner_iter->Next = new NodeU<cls> {temp, inner_iter->Next};
                            build_iter->Next->Element.resize(build_iter->Next->Element.size()+1);
                            inner_fill = false;
                        }
                    }
                    if (inner_fill)
                    {
                        inner_iter->Next = new NodeU<cls> {temp, inner_iter->Next};
                        build_iter->Next->Element.resize(build_iter->Next->Element.size()+1);
                    }
                    fill = false;
                }
            }
        }
        if (fill)
        {
            build_iter->Next = new NodeU<ChainUC<cls>>{static_cast<size_t>(chain.size() / groups + 1), build_iter->Next};
            build_iter->Next->Element.insert(temp, 0);
            res.resize(res.size()+1);
        }
    }
    return res;
}

template<typename cls, typename Tp>
ChainUC<ChainUC<cls>> Chain_Box_Sort(ChainUC<cls> &&chain, std::function<Tp(cls const &)> const &func, bool const &reverse = false)
{
    ChainUC<ChainUC<cls>> res {};
    if (!reverse)
    {
        Chain_Box_Sorter(chain, res, func, false);
    } else {
        Chain_Box_Sorter(chain, res, func, true);
    }
    return res;
}

#endif //DATASTRUCTURE_CHAIN_BOX_SORT_HPP
