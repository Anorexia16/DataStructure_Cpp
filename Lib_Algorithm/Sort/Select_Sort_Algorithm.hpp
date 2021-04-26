#ifndef DATASTRUCTURE_SELECT_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_SELECT_SORT_ALGORITHM_HPP

#include "../../Generic_Paradigm/Iterable.hpp"

template<typename Tp, Iterable_Container Container>
void select_sort(Container &container)
{
    if (container.size() == 0) return;
    size_t const nums = container.size();
    Tp _extra {};
    size_t pos;

    for (size_t times=0; times!=nums; ++times)
    {
        _extra = container[times];
        pos = times;
        for (size_t i=times; i!=nums; ++i)
        {
            if (container[i] < _extra)
            {
                _extra = container[i];
                pos = i;
            }
        }
        if (pos != times)
        {
            for (size_t re_pos=pos; re_pos!=times; --re_pos)
                container[re_pos] = container[re_pos-1];
            container[times] = _extra;
        }
    }
}

template<typename Tp, Iterable_Iterator iterator>
void select_sort(iterator begin, iterator end)
{
    if (begin==end) return;
    iterator global_iterator = begin;
    iterator flow_iterator;
    Tp _extra {};

    for (;global_iterator!=end; ++global_iterator)
    {
        flow_iterator = global_iterator;
        _extra = *flow_iterator;
        for (iterator iter=global_iterator; iter!=end; ++iter)
        {
            if(*iter < _extra)
            {
                _extra = *iter;
                flow_iterator = iter;
            }
        }
        if (flow_iterator!=global_iterator)
        {
            for (iterator reverse_iterator=flow_iterator;reverse_iterator!=global_iterator;--reverse_iterator)
                *reverse_iterator = *(reverse_iterator-1);
            *global_iterator = _extra;
        }
    }
}

#endif //DATASTRUCTURE_SELECT_SORT_ALGORITHM_HPP
