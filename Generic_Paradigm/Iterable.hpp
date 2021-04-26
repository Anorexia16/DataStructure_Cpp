#ifndef DATASTRUCTURE_ITERABLE_HPP
#define DATASTRUCTURE_ITERABLE_HPP

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

#endif //DATASTRUCTURE_ITERABLE_HPP
