#ifndef DATASTRUCTURE_BUBBLE_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_BUBBLE_SORT_ALGORITHM_HPP

template<class cls>
concept Iterable_Container = requires (cls instance)
{
    instance.operator[](0);
    instance.size();
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
void bubble_sort(Container &container)
{
    if (container.size() == 0) return;
    size_t const nums = container.size();
    bool done_flag = false;
    Tp _extra {};

    while(!done_flag)
    {
        done_flag = true;
        for (size_t times=1; times!=nums; ++times)
        {
            if (container[times]<container[times-1])
            {
                _extra = container[times];
                container[times] = container[times-1];
                container[times-1] = _extra;
                done_flag = false;
            }
        }
    }
}

template<typename Tp, Iterable_Iterator iterator>
void bubble_sort(iterator begin, iterator end)
{
    if (begin==end) return;
    bool done_flag = false;
    Tp _extra{};

    while (!done_flag)
    {
        done_flag = true;
        for (iterator iter=begin + 1; iter != end; ++iter)
        {
            if (*iter<*(iter-1))
            {
                _extra = *iter;
                *iter = *(iter-1);
                *(iter-1) = _extra;
                done_flag = false;
            }
        }
    }
}

#endif //DATASTRUCTURE_BUBBLE_SORT_ALGORITHM_HPP
