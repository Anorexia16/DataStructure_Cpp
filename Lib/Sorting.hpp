#ifndef DATASTRUCTURE_SORTING_HPP
#define DATASTRUCTURE_SORTING_HPP

#include <Iterations.hpp>
#include <queue>

template <typename Tp>
Tp remove_reference(Tp &&var) {
    return Tp{var};
}

template <typename Tp>
Tp remove_reference(Tp &var) {
    return Tp{var};
}
template <typename Tp>
Tp remove_reference(Tp const &var) {
    return Tp{var};
}

template<Forward_Iterator_Tag iterator>
void bubble_sort(iterator begin, iterator end)
{
    if (begin==end) return;
    bool done_flag = false;
    decltype(remove_reference(*begin)) _extra{};

    while (!done_flag)
    {
        iterator pi=begin, li=begin;
        done_flag = true;
        for (++li; li!=end; ++pi,++li)
        {
            if (*pi>*li)
            {
                _extra = *pi;
                *pi = *li;
                *li = _extra;
                done_flag = false;
            }
        }
    }
}

template<Bidirectional_Iterator_Tag iterator>
void insert_sort(iterator begin, iterator end)
{
    if (begin==end) return;
    iterator outer_iterator = begin;
    iterator inner_iterator;
    decltype(remove_reference(*begin)) _extra {};
    ++outer_iterator;

    for (; outer_iterator != end; ++outer_iterator)
    {
        inner_iterator = begin;
        for(; inner_iterator != outer_iterator; ++inner_iterator)
        {
            if ((*inner_iterator) > (*outer_iterator)) break;
        }
        if (inner_iterator != outer_iterator)
        {
            _extra = *outer_iterator;
            iterator reverse_iterator=outer_iterator, pre_iterator=outer_iterator;
            for(--pre_iterator; reverse_iterator != inner_iterator; --reverse_iterator, --pre_iterator)
                *reverse_iterator = *(pre_iterator);
            *inner_iterator = _extra;
        }
    }
}

template<Bidirectional_Iterator_Tag iterator>
void select_sort(iterator begin, iterator end)
{
    if (begin==end) return;
    iterator inner_max;
    decltype(remove_reference(*begin)) extra{};

    for (iterator outer_iterator = begin; outer_iterator != end; ++outer_iterator)
    {
        inner_max = outer_iterator;
        for (iterator iter=outer_iterator; iter != end; ++iter)
        {
            if(*iter < *inner_max) inner_max = iter;
        }
        if (inner_max != outer_iterator)
        {
            extra = *inner_max;
            iterator pi=inner_max, li=inner_max;
            for (--pi; li != outer_iterator; --pi, --li)
                *li = *(pi);
            *outer_iterator = extra;
        }
    }
}

template<Random_Access_Iterator_Tag iterator>
void merge_sort(iterator begin, iterator end)
{
    if (begin == end) return;
    std::vector<decltype(remove_reference(*begin))> extra {};
    size_t index {}, li{}, ri{};
    ssize_t const nums {end-begin};
    extra.resize(nums);

    for(size_t length =1;length<=nums;length*=2) {
        for(size_t i=0;i<(nums-1)/length+1;i+=2) {
            while(li!=length&&(ri!=length||ri+length*i!=nums)) {
                if (*(begin+i*length+li)<=*(begin+ri+i*length)) {
                    extra[index++] = *(begin+i*length+li++);
                } else {
                    extra[index++] = *(begin+i*length+ri++);
                }
            }
            while(li!=length) extra[index++] = *(begin+i*length+li++);
            while(ri!=length||ri+length*i!=nums)
                extra[index++] = *(begin+i*length+ri++);
            for (size_t j=0;j!=li+ri;++j) {
                *(begin+i*length+j) = extra[j];
            }
            index=0;
            li=0;
            ri=0;
        }
    }
}

template<Random_Access_Iterator_Tag iterator>
void quick_sort(iterator begin, iterator end)
{
    std::queue<iterator> _begin_queue {};
    std::queue<iterator> _end_queue {};

    _end_queue.push(iterator{end});
    _begin_queue.push(iterator{begin});

    decltype(remove_reference(*begin)) _extra;
    decltype(remove_reference(*begin)) *_cmp;
    iterator _begin, _end, _les;

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

template<Random_Access_Iterator_Tag iterator>
decltype(auto) quick_find(iterator begin, iterator end, size_t pos) {
    if (pos >= end-begin) return decltype(remove_reference(*begin)) {};
    decltype(remove_reference(*begin)) extra {*(begin)};
    size_t bi{}, ei{end-begin-1}, b{}, e{end-begin-1};
    bool dir {true};
    while(true) {
        if (dir) {
            if (*(begin+e) < extra) {
                *(begin+b++) = *(begin+e);
                dir = false;
            } else {
                --e;
            }
        } else {
            if (*(begin+b) > extra) {
                *(begin+e--) = *(begin+b);
                dir = true;
            } else {
                ++b;
            }
        }
        if (b==e) {
            if (b > pos) {
                ei = b - 1;
                b = bi;
                e = ei;
            } else if (b < pos) {
                bi = b + 1;
                b = bi;
                e = ei;
            } else return extra;
        }
    }
}

#endif //DATASTRUCTURE_SORTING_HPP
