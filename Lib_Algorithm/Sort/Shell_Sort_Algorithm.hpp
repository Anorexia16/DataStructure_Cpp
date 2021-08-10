#ifndef DATASTRUCTURE_SHELL_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_SHELL_SORT_ALGORITHM_HPP

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
void shell_sort(Container &container)
{
    if (container.size() == 0) return;
    size_t const nums = container.size();
    Tp _extra {};

    for (size_t gaps=nums/2; gaps>0; gaps/=2)
    {
        
    }
}

#endif //DATASTRUCTURE_SHELL_SORT_ALGORITHM_HPP
