#ifndef DATASTRUCTURE_HEAP_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_HEAP_SORT_ALGORITHM_HPP

#include "../../Generic_Paradigm/Iterable.hpp"
#include "../../Structure/Dendroid/Max_Heap.hpp"

template<typename Tp, Iterable_Container Container>
void heap_sort(Container &container)
{
    if (container.size() == 0) return;
    size_t const nums = container.size();
    Tp _temp;
    size_t _i;
    for(size_t _j= container.size()/2-1;_j!=-1;--_j)
    {
        _i = _j;
        while (2 * _i + 1 < nums) {
            if (container[_i] >= container[2 * _i + 1]) {
                if (2*_i + 2 < nums && container[_i] < container[2 * _i + 2]) {
                    _temp = container[_i];
                    container[_i] = container[2*_i+2];
                    container[2*_i+2] = _temp;
                    _i = 2 * _i + 2;
                    continue;
                } else break;
            } else {
                if (2*_i + 2 < container.size() && container[2*_i+1] < container[2*_i+2]) {
                    _temp = container[_i];
                    container[_i] = container[2*_i+2];
                    container[2 *_i+2] = _temp;
                    _i = 2 * _i + 2;
                    continue;
                } else {
                    _temp = container[_i];
                    container[_i] = container[2*_i+1];
                    container[2*_i+1] = _temp;
                    _i = 2*_i+1;
                    continue;
                }
            }
        }
    }
}

template<typename Tp, Iterable_Iterator iterator>
void heap_sort(iterator begin, iterator end)
{
    if (begin==end) return;
    size_t const length =end-begin;
    iterator global_iterator = begin + length/2-1;
    iterator flow_iterator;
    Tp _extra {};
    for(iterator _i= begin + length/2-1;;--_i)
    {
        while (2*_i+1 < length) {
            if (*_i >= *(_i+2*(_i-begin)+1)) {
                if (2*(_i-begin)+2 < length && *_i < *(_i+2*(_i-begin)+2)) {
                    _extra = *_i;
                    *_i = *(_i+2*(_i-begin)+2);
                    *(_i+2*(_i-begin)+2) = _extra;
                    _i = 2 * _i + 2;
                    continue;
                } else return;
            } else {
                if (2*(_i-begin)+2 < length && *(_i+2*(_i-begin)+1) < *(_i+2*(_i-begin)+2)) {
                    _extra = *_i;
                    *_i = *(_i+2*(_i-begin)+2);
                    *(_i+2*(_i-begin)+2) = _extra;
                    _i = 2 * _i + 2;
                    continue;
                } else {
                    _extra = *_i;
                    *_i = *(_i+2*(_i-begin)+1);
                    *(_i+2*(_i-begin)+1) = _extra;
                    _i = 2*_i+1;
                    continue;
                }
            }
        }
    }
}


#endif //DATASTRUCTURE_HEAP_SORT_ALGORITHM_HPP
