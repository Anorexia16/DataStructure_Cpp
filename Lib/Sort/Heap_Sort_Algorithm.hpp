#ifndef DATASTRUCTURE_HEAP_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_HEAP_SORT_ALGORITHM_HPP

#include "iterator.hpp"

template<Random_Access_Iterator_Tag iterator>
void heap_sort(iterator begin, iterator end)
{
    if (begin==end) return;
    size_t const length =end-begin;
    iterator global_iterator = begin + length/2-1;
    iterator flow_iterator;
    decltype(remove_reference(*begin)) _extra {};
    for(iterator iter= begin + length / 2 - 1;; --iter)
    {
        while (2*(iter - begin) + 1 < length) {
            if (*iter >= *(iter + 2 * (iter - begin) + 1)) {
                if (2*(iter - begin) + 2 < length && *iter < *(iter + 2 * (iter - begin) + 2)) {
                    _extra = *iter;
                    *iter = *(iter + 2 * (iter - begin) + 2);
                    *(iter + 2 * (iter - begin) + 2) = _extra;
                    iter = 2 * iter + 2;
                    continue;
                } else return;
            } else {
                if (2*(iter - begin) + 2 < length && *(iter + 2 * (iter - begin) + 1) < *(iter + 2 * (iter - begin) + 2)) {
                    _extra = *iter;
                    *iter = *(iter + 2 * (iter - begin) + 2);
                    *(iter + 2 * (iter - begin) + 2) = _extra;
                    iter = 2 * iter + 2;
                    continue;
                } else {
                    _extra = *iter;
                    *iter = *(iter + 2 * (iter - begin) + 1);
                    *(iter + 2 * (iter - begin) + 1) = _extra;
                    iter = 2 * iter + 1;
                    continue;
                }
            }
        }
    }
}


#endif //DATASTRUCTURE_HEAP_SORT_ALGORITHM_HPP
