#ifndef DATASTRUCTURE_RADIX_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_RADIX_SORT_ALGORITHM_HPP

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

#endif //DATASTRUCTURE_RADIX_SORT_ALGORITHM_HPP
