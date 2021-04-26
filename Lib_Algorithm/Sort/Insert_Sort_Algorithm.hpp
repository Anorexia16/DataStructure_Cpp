#ifndef DATASTRUCTURE_INSERT_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_INSERT_SORT_ALGORITHM_HPP

#include "../../Generic_Paradigm/Iterable.hpp"

template<typename Tp, Iterable_Container Container>
void insert_sort(Container &container)
{
    if (container.size()==0) return;
    size_t const nums = container.size();
    Tp _extra {};
    size_t pos;

    for (size_t times=1; times!=nums; ++times)
    {
        pos = 0;
        for (; pos!=times; ++pos)
        {
            if (container[times] < container[pos]) break;
        }
        if (pos!=times)
        {
            _extra = container[times];
            for (size_t re_pos=times; re_pos!=pos;--re_pos)
                container[re_pos] = container[re_pos-1];
            container[pos] = _extra;
        }
    }
}

template<typename Tp, Iterable_Iterator iterator>
void insert_sort(iterator begin, iterator end)
{
    if (begin==end) return;
    iterator global_iterator = begin;
    iterator flow_iterator;
    Tp _extra {};
    ++global_iterator;

    for (;global_iterator!=end; ++global_iterator)
    {
        flow_iterator = begin;
        for(;flow_iterator!=global_iterator; ++flow_iterator)
        {
            if ((*flow_iterator)>(*global_iterator)) break;
        }
        if (flow_iterator!=global_iterator)
        {
            _extra = *global_iterator;
            for(iterator reverse_iterator=global_iterator;reverse_iterator!=flow_iterator;--reverse_iterator)
                *reverse_iterator = *(reverse_iterator-1);
            *flow_iterator = _extra;
        }
    }
}


#endif //DATASTRUCTURE_INSERT_SORT_ALGORITHM_HPP
