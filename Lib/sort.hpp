#ifndef DATASTRUCTURE_SORT_HPP
#define DATASTRUCTURE_SORT_HPP

#include <iterator.hpp>
#include <queue>

namespace ax{
    template<forward_iterator iterator>
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

    template<bidirectional_iterator iterator>
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

    template<bidirectional_iterator iterator>
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

    template<random_access_iterator iterator>
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
                    if (*(begin+i*length+li)<= *(begin+ri+i*length)) {
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

    template<random_access_iterator iterator>
    void quick_sort(iterator begin, iterator end)
    {
        std::queue<iterator> bq {}, eq {};

        eq.push(iterator{end});
        bq.push(iterator{begin});

        decltype(remove_reference(*begin)) _extra, *_cmp;
        iterator bi, ei, _les;

        while(!bq.empty())
        {
            bi = bq.front();
            ei = eq.front();
            bq.pop();
            eq.pop();

            _extra = *(begin+ (ei - begin + bi - begin - 1) / 2);
            *(begin+ (ei - begin + bi - begin - 1) / 2) = *(ei - 1);
            *(ei - 1) = _extra;
            _cmp = &*(ei - 1);
            _les = bi;

            if (ei - bi == 2) {
                if(*(ei - 1)> *bi)
                {
                    _extra = *(ei - 1);
                    *(ei - 1) = *bi;
                    *bi = _extra;
                }
            } else {
                for (iterator _iter = bi; _iter != ei - 1; ++_iter) {
                    if (*_iter<= *_cmp) {
                        _extra = *_les;
                        *_les = *_iter;
                        *_iter = _extra;
                        ++_les;
                    }
                }
            }
            _extra = *(ei - 1);
            *(ei - 1) = *_les;
            *_les = _extra;
            if (_les - bi > 1)
            {
                bq.push(bi);
                eq.push(_les);
            }
            if (ei - _les > 1)
            {
                bq.push(_les + 1);
                eq.push(ei);
            }
        }
    }

    template<random_access_iterator iterator>
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
}

#endif //DATASTRUCTURE_SORT_HPP
