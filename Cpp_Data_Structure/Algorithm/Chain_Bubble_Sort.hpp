#ifndef DATASTRUCTURE_CHAIN_BUBBLE_SORT_HPP
#define DATASTRUCTURE_CHAIN_BUBBLE_SORT_HPP

#include "../../Structure/Linear/Chain_Unidirectional_Circle.hpp"

template<typename T, bool reverse>
class Chain_Bubble_Sorter : public ChainUC<T>
{
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
void Chain_Bubble_Sorter<T, reverse>::operator()(ChainUC <T> &op)
{
    if (op.size() == 0 || op.size() == 1) return;
    bool sorted = false;
    NodeU<T> *iterator{op.Head};
    NodeU<T> *temp1{iterator->Next->Next};
    NodeU<T> *temp2{temp1->Next};

    while (!sorted)
    {
        sorted = true;
        iterator = op.Head;
        if (!reverse)
        {
            for (; iterator->Next->Next != op.Head;)
            {
                if (iterator->Next->Next->Element < iterator->Next->Element)
                {
                    temp1 = iterator->Next->Next;
                    temp2 = temp1->Next;
                    iterator->Next->Next->Next = iterator->Next;
                    iterator->Next->Next = temp2;
                    iterator->Next = temp1;
                    sorted = false;
                }
                iterator = iterator->Next;
            }
        } else if (reverse)
        {
            for (; iterator->Next->Next != op.Head;)
            {
                if (iterator->Next->Next->Element > iterator->Next->Element)
                {
                    temp1 = iterator->Next->Next;
                    temp2 = temp1->Next;
                    iterator->Next->Next->Next = iterator->Next;
                    iterator->Next->Next = temp2;
                    iterator->Next = temp1;
                    sorted = false;

                }
                iterator = iterator->Next;
            }
        }
    }
}

template<typename T>
void Chain_Bubble_Sort(ChainUC <T> &op, bool const &reverse)
{
    if (!reverse)
    {
        Chain_Bubble_Sorter<T, false>{op};
    } else {
        Chain_Bubble_Sorter<T, true>{op};
    }
}

#endif //DATASTRUCTURE_CHAIN_BUBBLE_SORT_HPP
