#ifndef DATASTRUCTURE_CHAIN_RADIX_SORT_HPP
#define DATASTRUCTURE_CHAIN_RADIX_SORT_HPP

#include "../Structure/Chain_Unidirectional_Circle.hpp"
#include <cmath>

template<typename T, bool reverse>
class Chain_Radix_Sorter : public ChainUC<T> {
public:
    explicit Chain_Radix_Sorter(ChainUC <T> &, int const &, int (*)(T const &));

    Chain_Radix_Sorter(Chain_Radix_Sorter const &) = delete;

private:
    inline int get_key(T const &, int const &);

    void operator()(ChainUC <T> &);

    int (*Transformer)(T const &);

    int const Radix;

    int Minimum;
};

template<typename T, bool reverse>
Chain_Radix_Sorter<T, reverse>::Chain_Radix_Sorter(ChainUC <T> &op, int const &radix, int (*f)(T const &))
        : ChainUC<T>{0}, Radix{radix}, Transformer(f), Minimum{0} { (*this)(op); }

template<typename T, bool reverse>
int Chain_Radix_Sorter<T, reverse>::get_key(const T &x, int const &level) {
    return (int) std::floor((this->Transformer(x) - this->Minimum) / pow(this->Radix, level)) % this->Radix;
}

template<typename T, bool reverse>
void Chain_Radix_Sorter<T, reverse>::operator()(ChainUC <T> &op) {
    if (op.size() == 0) return;

    NodeU_Iter <T> limits_level_confirm = op.head()->next_ptr();
    int minimum = this->Transformer(limits_level_confirm.value_c());
    int maximum = this->Transformer(limits_level_confirm.value_c());
    for (; limits_level_confirm != op.head(); ++limits_level_confirm) {
        if (this->Transformer((*limits_level_confirm)()) > maximum)
            maximum = this->Transformer((*limits_level_confirm)());
        if (this->Transformer((*limits_level_confirm)()) < minimum)
            minimum = this->Transformer((*limits_level_confirm)());
    }
    this->Minimum = minimum;
    int const level = std::floor(std::log2(maximum - minimum) / std::log2(Radix)) + 1;

    NodeU_Iter <T> zone_Chain{op.head()->next_ptr()};
    NodeU_Iter <T> iterator{op.head()};
    T temp;
    bool flag;
    for (int rank = 0; rank != level; rank++) {
        iterator = op.head();
        for (; zone_Chain->next_ptr() != op.head();) {
            temp = zone_Chain->next().value_c();
            iterator.turn_to(op.head());
            flag = false;
            if (!reverse) {
                for (; iterator != zone_Chain; ++iterator) {
                    if ((get_key(temp, rank) >= get_key(iterator.value_c(), rank) &&
                         get_key(temp, rank) <= get_key(iterator->next().value_c(), rank)) ||
                        (iterator == op.head() && get_key(temp, rank) <= get_key(iterator->next().value_c(), rank))) {
                        iterator->link(*new NodeU<T>(temp, iterator->next_ptr()));
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    zone_Chain->link(*new NodeU<T>(temp, zone_Chain->next_ptr()));
                    zone_Chain = zone_Chain->next_ptr();
                }
                zone_Chain->link(zone_Chain->next_ptr()->next());
            } else if (reverse) {
                for (; iterator != zone_Chain; ++iterator) {
                    if ((get_key(temp, rank) <= get_key(iterator.value_c(), rank) &&
                         get_key(temp, rank) >= get_key(iterator->next().value_c(), rank)) ||
                        (iterator == op.head() && get_key(temp, rank) >= get_key(iterator->next().value_c(), rank))) {
                        iterator->link(*new NodeU<T>(temp, iterator->next_ptr()));
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    zone_Chain->link(*new NodeU<T>(temp, zone_Chain->next_ptr()));
                    zone_Chain = zone_Chain->next_ptr();
                }
                zone_Chain->link(zone_Chain->next_ptr()->next());
            }
        }
        zone_Chain->link(*op.head());
    }
}

template<typename T>
void Chain_Radix_Sort(ChainUC <T> &op, int const &radix, bool const &reverse = false,
                      int (*transformer)(T const &) = [](T const &x) { return (int) x; }) {
    if (!reverse) {
        Chain_Radix_Sorter<T, false>(op, radix, transformer);
    } else {
        Chain_Radix_Sorter<T, true>(op, radix, transformer);
    }
}

#endif //DATASTRUCTURE_CHAIN_RADIX_SORT_HPP
