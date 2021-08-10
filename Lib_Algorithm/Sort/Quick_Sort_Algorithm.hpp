#ifndef DATASTRUCTURE_QUICK_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_QUICK_SORT_ALGORITHM_HPP

#include <queue>

template<class cls>
concept Iterable_Container = requires (cls instance)
{
    instance.operator[](0);
    instance.index();
};

template<class cls>
concept Iterable_Iterator = requires (cls iterator)
{
    cls(iterator);
    iterator.operator=(iterator);
    iterator.operator-(-1);
    ++iterator;
    --iterator;
};

template<typename Tp, Iterable_Container Container>
void quick_sort(Container &container)
{
    std::queue<unsigned long long> _begin_queue {};
    std::queue<unsigned long long> _end_queue {};

    _end_queue.push(container.index());
    _begin_queue.push(0);

    Tp _extra;
    Tp *_cmp;
    unsigned long long _begin;
    unsigned long long _end;
    unsigned long long _les;

    while(!_begin_queue.empty())
    {
        _begin = _begin_queue.front();
        _end = _end_queue.front();
        _begin_queue.pop();
        _end_queue.pop();

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
            _begin_queue.push(_begin);
            _end_queue.push(_les);
        }
        if (_end-_les>1)
        {
            _begin_queue.push(_les + 1);
            _end_queue.push(_end);
        }
    }
}

template<typename Tp, Iterable_Iterator iterator>
void quick_sort(iterator begin, iterator end)
{
    std::queue<iterator> _begin_queue {};
    std::queue<iterator> _end_queue {};

    _end_queue.push(iterator{end});
    _begin_queue.push(iterator{begin});

    Tp _extra;
    Tp *_cmp;
    iterator _begin;
    iterator _end;
    iterator _les;

    while(!_begin_queue.empty())
    {
        _begin = _begin_queue.front();
        _end = _end_queue.front();
        _begin_queue.pop();
        _end_queue.pop();

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
            _begin_queue.push(_begin);
            _end_queue.push(_les);
        }
        if (_end-_les>1)
        {
            _begin_queue.push(_les + 1);
            _end_queue.push(_end);
        }
    }
}
#endif //DATASTRUCTURE_QUICK_SORT_ALGORITHM_HPP
