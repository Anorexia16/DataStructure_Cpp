#ifndef DATASTRUCTURE_CHAIN_SELECT_SORT_HPP
#define DATASTRUCTURE_CHAIN_SELECT_SORT_HPP

#include "../Structure/Chain_Unidirectional_Circle.hpp"

template<typename T, bool reverse>
class Chain_Select_Sorter : public ChainUC<T> {
public:
    explicit Chain_Select_Sorter(ChainUC <T> &);

    Chain_Select_Sorter(Chain_Select_Sorter const &) = delete;

private:
    void operator()(ChainUC <T> &);
};

template<typename T, bool reverse>
Chain_Select_Sorter<T, reverse>::Chain_Select_Sorter(ChainUC <T> &op)
        : ChainUC<T>{0} { (*this)(op); }

template<typename T, bool reverse>
void Chain_Select_Sorter<T, reverse>::operator()(ChainUC <T> &op) {
    if (op.size() == 0 || op.size() == 1) return;
    NodeU_Iter <T> zone_pointer{op.head()};
    NodeU_Iter <T> iterator{op.head()};
    NodeU_Iter <T> pre_ptr{op.head()};
    T temp = op.head()->next().value_c();
    if (!reverse) {
        for (; iterator->next_ptr() != op.head(); ++iterator) {
            if (iterator->next().value_c() > temp) {
                pre_ptr = iterator;
                temp = pre_ptr->next().value_c();
            }
        }
    } else if (reverse) {
        for (; iterator->next_ptr() != op.head(); ++iterator) {
            if (iterator->next().value_c() < temp) {
                pre_ptr = iterator;
                temp = pre_ptr->next().value_c();
            }
        }
    }
    op.head()->link(*new NodeU <T>{pre_ptr->next().value_c(), op.head()->next_ptr()});
    pre_ptr->link(pre_ptr->next_ptr()->next());
    zone_pointer = NodeU_Iter < T > {op.head()->next_ptr()};
    if (!reverse) {
        for (; zone_pointer->next_ptr() != op.head();) {
            temp = zone_pointer->next().value_c();
            iterator = zone_pointer;
            pre_ptr = zone_pointer;
            for (; iterator->next_ptr() != op.head(); ++iterator) {
                if (iterator->next().value_c() > temp) {
                    pre_ptr = iterator;
                    temp = pre_ptr->next().value_c();
                }
            }
            op.head()->link(*new NodeU <T>{pre_ptr->next().value_c(), op.head()->next_ptr()});
            pre_ptr->link(pre_ptr->next_ptr()->next());
        }
    } else if (reverse) {
        for (; zone_pointer->next_ptr() != op.head();) {
            temp = zone_pointer->next().value_c();
            iterator = zone_pointer;
            pre_ptr = zone_pointer;
            for (; iterator->next_ptr() != op.head(); ++iterator) {
                if (iterator->next().value_c() < temp) {
                    pre_ptr = iterator;
                    temp = pre_ptr->next().value_c();
                }
            }
            op.head()->link(*new NodeU <T>{pre_ptr->next().value_c(), op.head()->next_ptr()});
            pre_ptr->link(pre_ptr->next_ptr()->next());
        }
    }
}

template<typename T>
void Chain_Select_Sort(ChainUC <T> &op, bool const &reverse = false) {
    if (!reverse) {
        Chain_Select_Sorter<T, false>{op};
    } else {
        Chain_Select_Sorter<T, true>{op};
    }
}

#endif //DATASTRUCTURE_CHAIN_SELECT_SORT_HPP
