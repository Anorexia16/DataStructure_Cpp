#ifndef DATASTRUCTURE_CHAIN_BIN_SORT_HPP
#define DATASTRUCTURE_CHAIN_BIN_SORT_HPP

# include "../Structure/Chain_Unidirectional_Circle.hpp"
# include <array>

template<typename T, bool reverse>
class Chain_Bin_Sorter : public ChainUC<T> {
public:
    explicit Chain_Bin_Sorter(ChainUC <T> &, int (*)(T const &));

    Chain_Bin_Sorter(Chain_Bin_Sorter &&) = delete;

private:
    void operator()(ChainUC <T> &);

    int (*Transform)(T const &);

    int Groups;

    int Minimum;
};

template<typename T, bool reverse>
Chain_Bin_Sorter<T, reverse>::Chain_Bin_Sorter(ChainUC <T> &op, int (*func)(T const &))
        :Groups{0}, Transform{func}, Minimum{0}, ChainUC<T>{0} { (*this)(op); }

template<typename T, bool reverse>
void Chain_Bin_Sorter<T, reverse>::operator()(ChainUC <T> &op) {
    // TODO: Design Bin Sort
}

template<typename T>
void Chain_Bin_Sort(ChainUC <T> &x, bool const &reverse = false,
                    int (*func)(T const &) = [](T const &x) { return ((int) x) / 5; }) {
    if (!reverse) {
        Chain_Bin_Sorter<T, false>(x, func);
    } else {
        Chain_Bin_Sorter<T, true>(x, func);
    }
}

#endif //DATASTRUCTURE_CHAIN_BIN_SORT_HPP
