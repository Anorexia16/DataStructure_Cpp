#ifndef DATASTRUCTURE_SELECT_SORT_HPP
#define DATASTRUCTURE_SELECT_SORT_HPP

template<typename Tp, bool reverse>
class Select_Sorter {};

template<typename Tp>
class Select_Sorter<Tp, true>
{
public:
    template<class Container>
    explicit Select_Sorter(Container &);
    
    Select_Sorter &operator=(Select_Sorter &&) noexcept = delete;
    
    Select_Sorter &operator=(Select_Sorter const &) = delete;
    
    Select_Sorter(Select_Sorter &&) noexcept = delete;
    
    Select_Sorter(Select_Sorter const &) = delete;

private:
    template<class Container>
    void operator()(Container &);
};

template<typename Tp>
template<class Container>
Select_Sorter<Tp, true>::Select_Sorter(Container &container)
{
    (*this)(container);
}

template<typename Tp>
template<class Container>
void Select_Sorter<Tp, true>::operator()(Container &container)
{
    if (container.size() == 0 || container.size() == 1) return;
    auto insert_iter = std::begin(container);
    auto iterator = std::begin(container);
    Tp temp = *std::begin(container);
    for(;iterator!=std::end(container);++iterator)
    {
        if (*iterator < temp)
        {
            insert_iter = iterator;
            temp = *insert_iter;
        }
    }
    std::inserter(*insert_iter, std::begin(container));
    std::erase(container, insert_iter);
    auto zone = std::begin(container);
    for (;;) {
        if (zone+1!=std::end(container)) break;
        temp = *(zone+1);
        iterator = zone;
        insert_iter = zone;
        for(; iterator!=std::end(container);++iterator)
        {
            if (*(iterator+1) < temp)
            {
                insert_iter = iterator;
                temp = *insert_iter;
            }
        }
        std::inserter(*(insert_iter+1), std::begin(container));
        std::erase(insert_iter+2);
    }
}

template<typename Tp>
class Select_Sorter<Tp, false>
{
public:
    template<class Container>
    explicit Select_Sorter(Container &);

    Select_Sorter &operator=(Select_Sorter &&) noexcept = delete;

    Select_Sorter &operator=(Select_Sorter const &) = delete;

    Select_Sorter(Select_Sorter &&) noexcept = delete;

    Select_Sorter(Select_Sorter const &) = delete;

private:
    template<class Container>
    void operator()(Container &);
};

template<typename Tp>
template<class Container>
Select_Sorter<Tp, false>::Select_Sorter(Container &container)
{
    (*this)(container);
}

template<typename Tp>
template<class Container>
void Select_Sorter<Tp, false>::operator()(Container &container)
{
    if (container.size() == 0 || container.size() == 1) return;
    auto insert_iter = std::begin(container);
    auto iterator = std::begin(container);
    Tp temp = *std::begin(container);
    for(;iterator!=std::end(container);++iterator)
    {
        if (*iterator > temp)
        {
            insert_iter = iterator;
            temp = *insert_iter;
        }
    }
    std::inserter(*insert_iter, std::begin(container));
    std::erase(container, insert_iter);
    auto zone = std::begin(container);
    for (;;) {
        if (zone+1!=std::end(container)) break;
        temp = *(zone+1);
        iterator = zone;
        insert_iter = zone;
        for(; iterator!=std::end(container);++iterator)
        {
            if (*(iterator+1) > temp)
            {
                insert_iter = iterator;
                temp = *insert_iter;
            }
        }
        std::inserter(*(insert_iter+1), std::begin(container));
        std::erase(insert_iter+2);
    }
}

template<typename Tp, size_t n>
void Select_Sort(std::array<Tp, n> &array, bool const &reverse = false)
{
    if (reverse)
    {
        Select_Sorter<Tp, true>{array};
    } else {
        Select_Sorter<Tp, false>{array};
    }
}

template<typename Tp>
void Select_Sort(std::initializer_list<Tp> &list, bool const &reverse = false)
{
    if (reverse)
    {
        Select_Sorter<Tp, true>{list};
    } else {
        Select_Sorter<Tp, false>{list};
    }
}

template<typename Tp, template<typename elem, typename = std::allocator<elem>> class Cont>
void Select_Sort(Cont<Tp> &cont, bool const &reverse = false)
{
    if (reverse)
    {
        Select_Sorter<Tp, true>{cont};
    } else {
        Select_Sorter<Tp, false>{cont};
    }
}

template<typename Tp, typename Iterable_cls>
void Select_Sort(Iterable_cls const &var, bool const &reverse = false)
{
    if (reverse)
    {
        Select_Sorter<Tp, true>{var};
    } else {
        Select_Sorter<Tp, false>{var};
    }
}

#endif //DATASTRUCTURE_SELECT_SORT_HPP
