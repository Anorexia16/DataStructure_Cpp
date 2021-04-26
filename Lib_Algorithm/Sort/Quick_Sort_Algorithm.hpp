#ifndef DATASTRUCTURE_QUICK_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_QUICK_SORT_ALGORITHM_HPP

#include "../../Generic_Paradigm/Iterable.hpp"
#include "../../Structure/Linear/Queue_Chain.hpp"

template<typename Tp, Iterable_Container Container>
void quick_sort(Container &container)
{
    Queue_C<unsigned long long> _begin_queue {};
    Queue_C<unsigned long long> _end_queue {};

    _end_queue.enqueue(container.size());
    _begin_queue.enqueue(0);

    Tp _extra;
    Tp *_cmp;
    unsigned long long _begin;
    unsigned long long _end;
    unsigned long long _les;

    while(!_begin_queue.empty())
    {
        _begin = _begin_queue.front();
        _end = _end_queue.front();
        _begin_queue.dequeue();
        _end_queue.dequeue();

        _extra = container[(_begin+_end-1)/2];
        container[(_begin+_end-1)/2] = container[_end-1];
        container[_end -1] = _extra;
        _cmp = &container[_end-1];
        _les = _begin;

        if (_end-_begin==2) {
            if(container[_end-1]>container[_begin])
            {
                _extra = container[_end-1];
                container[_end-1] = container[_begin];
                container[_begin] = _extra;
            }
        } else {
            for (unsigned long long _iter = _begin; _iter != _end - 1; ++_iter) {
                if (container[_iter] <= *_cmp) {
                    _extra = container[_les];
                    container[_les] = container[_iter];
                    container[_iter] = _extra;
                    ++_les;
                }
            }
        }
        _extra = container[_end-1];
        container[_end-1] = container[_les];
        container[_les] = _extra;
        if (_les-_begin>1)
        {
            _begin_queue.enqueue(_begin);
            _end_queue.enqueue(_les);
        }
        if (_end-_les>1)
        {
            _begin_queue.enqueue(_les + 1);
            _end_queue.enqueue(_end);
        }
    }
}

template<typename Tp, Iterable_Iterator iterator>
void quick_sort(iterator begin, iterator end)
{
    Queue_C<iterator> _begin_queue {};
    Queue_C<iterator> _end_queue {};

    _end_queue.enqueue(iterator{end});
    _begin_queue.enqueue(iterator{begin});

    Tp _extra;
    Tp *_cmp;
    iterator _begin;
    iterator _end;
    iterator _les;

    while(!_begin_queue.empty())
    {
        _begin = _begin_queue.front();
        _end = _end_queue.front();
        _begin_queue.dequeue();
        _end_queue.dequeue();

        _extra = *(begin+(_end-begin+_begin-begin-1)/2);
        *(begin+(_end-begin+_begin-begin-1)/2) = *(_end-1);
        *(_end -1) = _extra;
        _cmp = &*(_end-1);
        _les = _begin;

        if (_end-_begin==2) {
            if(*(_end-1)>*_begin)
            {
                _extra = *(_end-1);
                *(_end-1) = *_begin;
                *_begin = _extra;
            }
        } else {
            for (iterator _iter = _begin; _iter != _end - 1; ++_iter) {
                if (*_iter <= *_cmp) {
                    _extra = *_les;
                    *_les = *_iter;
                    *_iter = _extra;
                    ++_les;
                }
            }
        }
        _extra = *(_end-1);
        *(_end-1) = *_les;
        *_les = _extra;
        if (_les-_begin>1)
        {
            _begin_queue.enqueue(_begin);
            _end_queue.enqueue(_les);
        }
        if (_end-_les>1)
        {
            _begin_queue.enqueue(_les + 1);
            _end_queue.enqueue(_end);
        }
    }
}
#endif //DATASTRUCTURE_QUICK_SORT_ALGORITHM_HPP
