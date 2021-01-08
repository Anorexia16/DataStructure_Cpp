#ifndef DATASTRUCTURE_CHAIN_INSERT_SORT_HPP
#define DATASTRUCTURE_CHAIN_INSERT_SORT_HPP

#include "../Structure/Chain_Unidirectional_Circle.hpp"

template<typename T, bool reverse>
class Chain_Insert_Sorter : public ChainUC<T> {
public:
    explicit Chain_Insert_Sorter(ChainUC <T> &);

    Chain_Insert_Sorter(Chain_Insert_Sorter const &) = delete;

private:
    void operator()(ChainUC <T> &);
};

template<typename T, bool reverse>
Chain_Insert_Sorter<T, reverse>::Chain_Insert_Sorter(ChainUC <T> &op)
        : ChainUC<T>{0} { (*this)(op); }

template<typename T, bool reverse>
void Chain_Insert_Sorter<T, reverse>::operator()(ChainUC <T> &op) {
    if (op.size() == 0 || op.size() == 1) return;
    NodeU_Iter <T> zone_Chain{op.head()->next_ptr()};
    NodeU_Iter <T> iterator{op.head()};
    T temp = zone_Chain.value_c();
    bool flag;
    for (; zone_Chain->next_ptr() != op.head();) {
        temp = zone_Chain->next().value_c();
        iterator.turn_to(op.head());
        flag = false;
        if (!reverse) {
            for (; iterator != zone_Chain; ++iterator) {
                if ((temp >= (iterator.value_c()) && temp <= iterator->next().value_c()) ||
                    (iterator == op.head() && temp <= iterator->next_ptr()->value_c())) {
                    iterator->link(*new NodeU<T>(temp, iterator->next_ptr()));
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                zone_Chain->link(*new NodeU<T>(temp, zone_Chain->next_ptr()));
                ++zone_Chain;
            }
            zone_Chain->link(zone_Chain->next_ptr()->next());
        } else if (reverse) {
            for (; iterator != zone_Chain; ++iterator) {
                if ((temp <= iterator.value_c() && temp >= iterator->next().value_c()) ||
                    (iterator == op.head() && temp >= iterator->next_ptr()->value_c())) {
                    iterator->link(*new NodeU<T>(temp, iterator->next_ptr()));
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                zone_Chain->link(*new NodeU<T>(temp, zone_Chain->next_ptr()));
                ++zone_Chain;
            }
            zone_Chain->link(zone_Chain->next_ptr()->next());
        }
    }
    zone_Chain->link(*op.head());
}

template<typename T>
void Chain_Insert_Sort(ChainUC <T> &op, bool const &reverse = false) {
    if (!reverse) {
        Chain_Insert_Sorter<T, false>{op};
    } else {
        Chain_Insert_Sorter<T, true>{op};
    }
}


#endif //DATASTRUCTURE_CHAIN_INSERT_SORT_HPP
