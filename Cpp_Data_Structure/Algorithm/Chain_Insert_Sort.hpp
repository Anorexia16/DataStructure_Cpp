#ifndef DATASTRUCTURE_CHAIN_INSERT_SORT_HPP
#define DATASTRUCTURE_CHAIN_INSERT_SORT_HPP

#include "../../Structure/Chain_Unidirectional_Circle.hpp"

template<typename T, bool reverse>
class Chain_Insert_Sorter : virtual public ChainUC<T>
{
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
void Chain_Insert_Sorter<T, reverse>::operator()(ChainUC <T> &op)
{
    if (op.size() == 0 || op.size() == 1) return;
    NodeU<T> *zone_Chain{op.Head->Next};
    NodeU<T> *iterator{op.Head};
    T temp = zone_Chain->Element;
    bool flag;
    for (; zone_Chain->Next != op.Head;)
    {
        temp = zone_Chain->Next->Element;
        iterator = op.Head;
        flag = false;
        if (!reverse)
        {
            for (; iterator != zone_Chain; iterator = iterator->Next)
            {
                if ((temp >= (iterator->Element) && temp <= iterator->Next->Element) ||
                    (iterator == op.Head && temp <= iterator->Next->Element)) {
                    iterator->Next = new NodeU<T> {temp, iterator->Next};
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                zone_Chain->Next = new NodeU<T> {temp, zone_Chain->Next};
                zone_Chain = zone_Chain->Next;
            }
            zone_Chain->Next = zone_Chain->Next->Next;
        } else if (reverse) {
            for (; iterator != zone_Chain; iterator=iterator->Next)
            {
                if ((temp <= iterator->Element && temp >= iterator->Next->Element) ||
                    (iterator == op.Head && temp >= iterator->Next->Element))
                {
                    iterator->Next = new NodeU<T> {temp, iterator->Next};
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                zone_Chain->Next = new NodeU<T>{temp, zone_Chain->Next};
                zone_Chain = zone_Chain->Next;
            }
            zone_Chain->Next = zone_Chain->Next->Next;
        }
    }
    zone_Chain->Next = op.Head;
}

template<typename T>
void Chain_Insert_Sort(ChainUC <T> &op, bool const &reverse = false)
{
    if (!reverse)
    {
        Chain_Insert_Sorter<T, false>{op};
    } else {
        Chain_Insert_Sorter<T, true>{op};
    }
}


#endif //DATASTRUCTURE_CHAIN_INSERT_SORT_HPP
