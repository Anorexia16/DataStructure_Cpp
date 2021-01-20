#ifndef DATASTRUCTURE_CHAIN_BOX_SORT_HPP
#define DATASTRUCTURE_CHAIN_BOX_SORT_HPP

#include <functional>
#include "../../Structure/Chain_Unidirectional_Circle.hpp"

template<typename cls>
class Chain_Box_Sorter : virtual public ChainUC<cls> {
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
                                        std::function<Tp(const cls &)> const &func, const bool &reverse) {
    arg = (*this)(chain, arg, func, reverse);
}

template<typename cls>
template<typename Tp>
ChainUC<ChainUC<cls>>
Chain_Box_Sorter<cls>::operator()(const ChainUC<cls> &chain, std::function<Tp(cls const &)> const &func,
                                  bool const &reverse) {
    std::vector<Tp> cont{};
    size_t groups{};
    cls cal_temp;
    for (NodeU_Iter<cls> iterator{chain.head_c()->next_ptr()}; iterator != chain.head_c(); ++iterator) {
        cal_temp = func(iterator.value_c());
        for (auto const &vec_iter:cont)
            if (vec_iter != cal_temp) {
                cont.template emplace_back(cal_temp);
                ++groups;
            }
    }
    ChainUC<ChainUC<cls>> res{groups};
    for (NodeU_Iter<ChainUC<cls>> iterator{res.head()->next_ptr()}; iterator != res.head(); ++iterator) {
        (*iterator).resize(static_cast<size_t>(chain.size() / groups + 1));
    }
    Tp temp;
    bool fill;
    for (NodeU_Iter<cls> main_iter{chain.head_c()->next_ptr()}; main_iter != chain.head_c(); ++main_iter) {
        NodeU_Iter<ChainUC<cls>> build_iter{res.head()};
        temp = func(main_iter.value_c());
        fill = true;
        if (!reverse) {
            for (; build_iter.next_ptr() != res.head(); ++build_iter) {
                if ((build_iter == res.head() && temp < func(build_iter.next().value_c().head_c()->next()))
                || (temp > func(build_iter.value_c().head_c()->next()) && temp < func(build_iter.value_c().head_c()->next()))) {
                    build_iter.link(*new NodeU<ChainUC<cls>>{static_cast<size_t>(chain.size() / groups + 1), build_iter.next_ptr()});
                    build_iter.next().value_c().insert(temp, 0);
                    res.resize(res.size()+1);
                    fill = false;
                } else if (build_iter != res.head() && temp==func(build_iter.next().value_c().head_c()->next())) {
                    NodeU_Iter<cls> inner_iter {build_iter.next().value_c().head()};
                    bool inner_fill = true;
                    for(;inner_iter.next_ptr()!=build_iter.next().value_c().head();++inner_iter) {
                        if ((inner_iter==build_iter.next().value_c().head() && temp < func(inner_iter.next().value_c()))
                            || (temp>func(inner_iter.value_c())&&temp<=func(inner_iter.next().value_c()))) {
                            inner_iter.link(*new NodeU<cls> {temp, inner_iter.next_ptr()});
                            build_iter.next().value_c().resize(build_iter.next().value_c().size()+1);
                            inner_fill = false;
                        }
                    }
                    if (inner_fill) {
                        inner_iter.link(*new NodeU<cls> {temp, inner_iter.next_ptr()});
                        build_iter.next().value_c().resize(build_iter.next().value_c().size()+1);
                    }
                    fill = false;
                }
            }
            if (fill) {
                build_iter.link(*new NodeU<ChainUC<cls>>{static_cast<size_t>(chain.size() / groups + 1), build_iter.next_ptr()});
                build_iter.next().value_c().insert(temp, 0);
                res.resize(res.size()+1);
            }
        } else if (reverse) {
            for (; build_iter.next_ptr() != res.head(); ++build_iter) {
                if ((build_iter == res.head() && temp > func(build_iter.next().value_c().head_c()->next()))
                    || (temp < func(build_iter.value_c().head_c()->next()) && temp > func(build_iter.value_c().head_c()->next()))) {
                    build_iter.link(*new NodeU<ChainUC<cls>>{static_cast<size_t>(chain.size() / groups + 1), build_iter.next_ptr()});
                    build_iter.next().value_c().insert(temp, 0);
                    res.resize(res.size()+1);
                    fill = false;
                } else if (build_iter != res.head() && temp==func(build_iter.next().value_c().head_c()->next())) {
                    NodeU_Iter<cls> inner_iter {build_iter.next().value_c().head()};
                    bool inner_fill = true;
                    for(;inner_iter.next_ptr()!=build_iter.next().value_c().head();++inner_iter) {
                        if ((inner_iter==build_iter.next().value_c().head() && temp > func(inner_iter.next().value_c()))
                            || (temp<func(inner_iter.value_c())&&temp>=func(inner_iter.next().value_c()))) {
                            inner_iter.link(*new NodeU<cls> {temp, inner_iter.next_ptr()});
                            build_iter.next().value_c().resize(build_iter.next().value_c().size()+1);
                            inner_fill = false;
                        }
                    }
                    if (inner_fill) {
                        inner_iter.link(*new NodeU<cls> {temp, inner_iter.next_ptr()});
                        build_iter.next().value_c().resize(build_iter.next().value_c().size()+1);
                    }
                    fill = false;
                }
            }
        }
        if (fill) {
            build_iter.link(*new NodeU<ChainUC<cls>>{static_cast<size_t>(chain.size() / groups + 1), build_iter.next_ptr()});
            build_iter.next().value_c().insert(temp, 0);
            res.resize(res.size()+1);
        }
    }
    return res;
}

template<typename cls, typename Tp>
ChainUC<ChainUC<cls>> Chain_Box_Sort(ChainUC<cls> &&chain, std::function<Tp(cls const &)> const &func, bool const &reverse = false) {
    ChainUC<ChainUC<cls>> res {};
    if (!reverse) {
        Chain_Box_Sorter(chain, res, func, false);
    } else {
        Chain_Box_Sorter(chain, res, func, false);
    }
    return res;
}

#endif //DATASTRUCTURE_CHAIN_BOX_SORT_HPP
