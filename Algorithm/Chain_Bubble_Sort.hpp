#ifndef DATASTRUCTURE_CHAIN_BUBBLE_SORT_HPP
#define DATASTRUCTURE_CHAIN_BUBBLE_SORT_HPP

#include "../Structure/Chain_Unidirectional_Circle.hpp"

template<typename T, bool reverse>
class Chain_Bubble_Sorter : public ChainUC<T> {
public:
    explicit Chain_Bubble_Sorter(ChainUC <T> &);

    Chain_Bubble_Sorter(Chain_Bubble_Sorter const &) = delete;

private:
    void operator()(ChainUC <T> &);
};

template<typename T, bool reverse>
Chain_Bubble_Sorter<T, reverse>::Chain_Bubble_Sorter(ChainUC <T> &op)
        :ChainUC<T>{0} { (*this)(op); }

template<typename T, bool reverse>
void Chain_Bubble_Sorter<T, reverse>::operator()(ChainUC <T> &op) {

    if (op.size() == 0 || op.size() == 1) return;
    bool sorted = false;
    NodeU_Iter <T> iterator{op.head()};
    NodeU_Iter <T> temp1{iterator->next().next_ptr()};
    NodeU_Iter <T> temp2{temp1->next_ptr()};

    while (!sorted) {
        sorted = true;
        iterator.turn_to(op.head());
        if (!reverse) {
            for (; iterator->next_ptr()->next_ptr() != op.head();) {
                if (iterator->next().next()() < iterator->next()()) {
                    temp1 = iterator->next().next_ptr();
                    temp2 = temp1->next_ptr();
                    iterator->next().next().link(iterator->next());
                    iterator->next().link(*temp2);
                    iterator->link(*temp1);
                    sorted = false;
                }
                ++iterator;
            }
        } else if (reverse) {
            for (; iterator->next_ptr()->next_ptr() != op.head();) {
                if (iterator->next().next()() > iterator->next()()) {
                    temp1 = iterator->next().next_ptr();
                    temp2 = temp1->next_ptr();
                    iterator->next().next().link(iterator->next());
                    iterator->next().link(*temp2);
                    iterator->link(*temp1);
                    sorted = false;

                }
                ++iterator;
            }
        }
    }
}

template<typename T>
void Chain_Bubble_Sort(ChainUC <T> &op, bool const &reverse) {
    if (!reverse) {
        Chain_Bubble_Sorter<T, false>{op};
    } else {
        Chain_Bubble_Sorter<T, true>{op};
    }
}

#endif //DATASTRUCTURE_CHAIN_BUBBLE_SORT_HPP
