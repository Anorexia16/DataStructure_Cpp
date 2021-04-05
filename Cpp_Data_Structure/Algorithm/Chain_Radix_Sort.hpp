#ifndef DATASTRUCTURE_CHAIN_RADIX_SORT_HPP
#define DATASTRUCTURE_CHAIN_RADIX_SORT_HPP

#include "../../Structure/Chain_Unidirectional_Circle.hpp"
#include <cmath>

template<typename T, bool reverse>
class Chain_Radix_Sorter : public ChainUC<T>
{
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
int Chain_Radix_Sorter<T, reverse>::get_key(const T &x, int const &level)
{
    return (int) std::floor((this->Transformer(x) - this->Minimum) / pow(this->Radix, level)) % this->Radix;
}

template<typename T, bool reverse>
void Chain_Radix_Sorter<T, reverse>::operator()(ChainUC <T> &op)
{
    if (op.size() == 0) return;

    NodeU<T> *limits_level_confirm = op.Head->Next;
    int minimum = this->Transformer(limits_level_confirm->Element);
    int maximum = this->Transformer(limits_level_confirm->Element);
    for (; limits_level_confirm != op.Head; ++limits_level_confirm)
    {
        if (this->Transformer(limits_level_confirm->Element) > maximum)
            maximum = this->Transformer(limits_level_confirm->Element);
        if (this->Transformer(limits_level_confirm->Element) < minimum)
            minimum = this->Transformer(limits_level_confirm->Element);
    }
    this->Minimum = minimum;
    int const level = std::floor(std::log2(maximum - minimum) / std::log2(Radix)) + 1;

    NodeU<T> *zone_Chain{op.Head->Next};
    NodeU<T> *iterator;
    T temp;
    bool flag;
    for (int rank = 0; rank != level; ++rank)
    {
        for (; zone_Chain->Next!= op.Head;)
        {
            temp = zone_Chain->Next->Element;
            iterator = op.Head;
            flag = false;
            if (!reverse)
            {
                for (; iterator != zone_Chain; iterator = iterator->Next)
                {
                    if ((get_key(temp, rank) >= get_key(iterator->Element, rank) &&
                         get_key(temp, rank) <= get_key(iterator->Next->Element, rank)) ||
                        (iterator == op.Head && get_key(temp, rank) <= get_key(iterator->Next->Element, rank)))
                    {
                        iterator->Next = new NodeU<T> {temp, iterator->Next};
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    zone_Chain->Next = new NodeU<T>{temp, zone_Chain->Next};
                    zone_Chain = zone_Chain->Next;
                }
                zone_Chain->Next = zone_Chain->Next->Next;
            } else if (reverse) {
                for (; iterator != zone_Chain; ++iterator)
                {
                    if ((get_key(temp, rank) <= get_key(iterator->Element, rank) &&
                         get_key(temp, rank) >= get_key(iterator->Next->Element, rank)) ||
                        (iterator == op.head() && get_key(temp, rank) >= get_key(iterator->Next->Element, rank)))
                    {
                        iterator->Next = new NodeU<T>{temp, iterator->Next};
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
}

template<typename T>
void Chain_Radix_Sort(ChainUC <T> &op, int const &radix, bool const &reverse = false,
                      int (*transformer)(T const &) = [](T const &x) { return (int) x; })
{
    if (!reverse)
    {
        Chain_Radix_Sorter<T, false>(op, radix, transformer);
    } else {
        Chain_Radix_Sorter<T, true>(op, radix, transformer);
    }
}

#endif //DATASTRUCTURE_CHAIN_RADIX_SORT_HPP
