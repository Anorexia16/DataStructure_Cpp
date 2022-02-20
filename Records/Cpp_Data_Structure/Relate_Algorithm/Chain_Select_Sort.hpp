#ifndef DATASTRUCTURE_CHAIN_SELECT_SORT_HPP
#define DATASTRUCTURE_CHAIN_SELECT_SORT_HPP

#include "../../../Structure/Linear/Chain_Unidirectional_Circle.hpp"

template<typename T, bool reverse>
class Chain_Select_Sorter : public ChainUC<T>
{
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
void Chain_Select_Sorter<T, reverse>::operator()(ChainUC <T> &op)
{
    if (op.size() == 0 || op.size() == 1) return;
    NodeU<T> *zone_pointer;
    NodeU<T> *iterator{op.Head};
    NodeU<T> *pre_ptr{op.Head};
    T temp = op.Head->Next->Element;
    if (!reverse)
    {
        for (; iterator->Next != op.Head; iterator = iterator->Next)
        {
            if (iterator->Next->Element > temp)
            {
                pre_ptr = iterator;
                temp = pre_ptr->Next->Element;
            }
        }
    } else if (reverse)
    {
        for (; iterator->Next != op.Head; iterator = iterator->Next)
        {
            if (iterator->Next->Element < temp)
            {
                pre_ptr = iterator;
                temp = pre_ptr->Next->Element;
            }
        }
    }
    op.Head->Next = new NodeU <T>{pre_ptr->Next->Element, op.Head->Next};
    pre_ptr->Next = pre_ptr->Next->Next;
    zone_pointer = op.Head->Next;
    if (!reverse)
    {
        for (; zone_pointer->Next != op.Head;)
        {
            temp = zone_pointer->Next->Element;
            iterator = zone_pointer;
            pre_ptr = zone_pointer;
            for (; iterator->Next != op.Head; iterator = iterator->Next)
            {
                if (iterator->Next->Element > temp)
                {
                    pre_ptr = iterator;
                    temp = pre_ptr->Next->Element;
                }
            }
            op.Head->Next = new NodeU <T>{pre_ptr->Next->Element, op.Head->Next};
            pre_ptr->Next = pre_ptr->Next->Next;
        }
    } else if (reverse) {
        for (; zone_pointer->Next != op.Head;)
        {
            temp = zone_pointer->Next->Element;
            iterator = zone_pointer;
            pre_ptr = zone_pointer;
            for (; iterator->Next != op.Head; iterator = iterator->Next)
            {
                if (iterator->Next->Element < temp)
                {
                    pre_ptr = iterator;
                    temp = pre_ptr->Next->Element;
                }
            }
            op.Head->Next = new NodeU <T>{pre_ptr->Next->Element, op.Head->Next};
            pre_ptr->Next = pre_ptr->Next->Next;
        }
    }
}

template<typename T>
void Chain_Select_Sort(ChainUC <T> &op, bool const &reverse = false)
{
    if (!reverse)
    {
        Chain_Select_Sorter<T, false>{op};
    } else {
        Chain_Select_Sorter<T, true>{op};
    }
}

#endif //DATASTRUCTURE_CHAIN_SELECT_SORT_HPP
