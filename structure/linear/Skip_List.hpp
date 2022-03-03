#ifndef DATASTRUCTURE_SKIP_LIST_HPP
#define DATASTRUCTURE_SKIP_LIST_HPP

#include <random>
#include <iostream>
#include "../Assistance/Node_Reticular.hpp"

size_t random_level(size_t const &size, int const &gap)
{
    size_t base = 1, level = 1;
    std::random_device rd;
    std::default_random_engine e {rd()};
    std::uniform_int_distribution<unsigned> u(0, gap - 1);
    while (u(e) % gap == 0)
    {
        base *= gap;
        ++level;
        if (base >= size) break;
    }
    return level;
}

template<typename  Tp>
class Skip_List {
public:
    explicit Skip_List(size_t const & = 2);

    explicit Skip_List(std::istream &&, size_t const & = 2);

    Skip_List(const Tp *const &, size_t const &, size_t const & = 2);

    template<class Iterable_Container>
    explicit Skip_List(Iterable_Container const &, size_t const & = 2);

    void insert (Tp const &);

    void erase (size_t const &);

    size_t find (Tp const &) const ;

    Tp get(size_t const &) const;

    Tp &operator[](size_t const &);

    friend std::ostream &operator<<(std::ostream &out, Skip_List<Tp> const &sl)
    {
        const NodeR<Tp>* oi {sl.head_c()->next_ptr()};
        for(;oi!=sl.head_c();oi = oi->next_ptr(0))
        {
            out << oi->value_c() << " ";
        }
        return out;
    }

protected:
    size_t const Gap;

    NodeR<Tp> *Head;

    size_t size;
};

template<typename Tp>
Skip_List<Tp>::Skip_List(size_t const &gap)
    :Head{new NodeR<Tp> {}}, size{}, Gap{gap} {}

template<typename Tp>
Skip_List<Tp>::Skip_List(std::istream &&in, size_t const &gap)
    :Head(new NodeR<Tp> {}), size{}, Gap{gap}
{
    Head->Destination.template emplace_back(Head);
    Head->Source.template emplace_back(Head);

    std::vector<Tp> vec {};
    Tp temp;
    for(;in.good();)
    {
        in >> temp;
        vec.template emplace_back(temp);
    }
    std::sort(std::begin(vec), std::end(vec));

    NodeR<Tp> *bi {Head};
    NodeR<Tp> *ci;
    for(auto const &iterator:vec)
    {
        ci = bi->Destination[0];
        bi->Destination.template emplace_back(new NodeR<Tp> {iterator, {bi}, {bi->Destination[0]}});
        bi->Destination.erase(bi->Destination.begin());
        ci->Source.erase(ci->Source.begin());
        ci->Source.template emplace_back(bi->Destination[0]);
        bi = bi->Destination[0];
        ++size;
    }
    if (gap >= 2 && gap < size)
    {
        size_t prod {gap};
        size_t time {};
        for(;prod<=size;prod*=gap, ++time)
        {
            NodeR<Tp> *li {Head};
            NodeR<Tp> *ti {Head};
            for (auto j=0;j!=size/prod+1;++j, li=ti)
            {
                for (auto i = 0; i != gap; ++i) ti = ti->Destination[time];
                li->Destination.template emplace_back(ti);
                ti->Source.template emplace_back(li);
            }
        }
    }
}

template<typename Tp>
Skip_List<Tp>::Skip_List(const Tp *const &ptr, const size_t &length, size_t const &gap)
    :Head{new NodeR<Tp> {}}, size{}, Gap{gap}
{
    Head->link_after(*Head);
    Head->link_front(*Head);

    std::vector<Tp> vec {};
    Tp temp;
    for(auto index=0;index!=length;++index)
    {
        vec.template emplace_back(ptr[index]);
    }
    std::sort(std::begin(vec), std::end(vec));

    NodeR<Tp> *bi {Head};
    NodeR<Tp> *ci;
    for(auto const &iterator:vec)
    {
        ci = bi->Destination[0];
        bi->Destination.template emplace_back(new NodeR<Tp> {iterator, {bi}, {bi->Destination[0]}});
        bi->Destination.erase(bi->Destination.begin());
        ci->Source.erase(ci->Source.begin());
        ci->Source.template emplace_back(bi->Destination[0]);
        bi = bi->Destination[0];
        ++size;
    }
    if (gap >= 2 && gap < size)
    {
        size_t prod {gap};
        size_t time {0};
        for(;prod<=size;prod*=gap, ++time)
        {
            NodeR<Tp> *li {Head};
            NodeR<Tp> *ti {Head};
            for (auto j=0;j!=size/prod+1;++j, li=ti)
            {
                for (auto i = 0; i != gap; ++i) ti = ti->Destination[time];
                li->Destination.template emplace_back(ti);
                ti->Source.template emplace_back(li);
            }
        }
    }
}

template<typename Tp>
template<class Iterable_Container>
Skip_List<Tp>::Skip_List(const Iterable_Container &cont, size_t const &gap)
        :Head(new NodeR<Tp> {}), size{}, Gap{gap}
{
    Head->link_after(*Head);
    Head->link_front(*Head);

    std::vector<Tp> vec {};
    for(auto const &iterator:cont) vec.template emplace_back(iterator);
    std::sort(std::begin(vec), std::end(vec));

    NodeR<Tp> *bi {Head};
    NodeR<Tp> *ci;
    for(auto const &iterator:vec)
    {
        ci = bi->Destination[0];
        bi->Destination.template emplace_back(new NodeR<Tp> {iterator, {bi}, {bi->Destination[0]}});
        bi->Destination.erase(bi->Destination.begin());
        ci->Source.erase(ci->Source.begin());
        ci->Source.template emplace_back(bi->Destination[0]);
        bi = bi->Destination[0];
        ++size;
    }
    if (gap >= 2 && gap < size)
    {
        size_t prod {gap};
        size_t time {0};
        for(;prod<=size;prod*=gap, ++time)
        {
            NodeR<Tp> *li {Head};
            NodeR<Tp> *ti {Head};
            for (auto j=0;j!=size/prod+1;++j, li=ti)
            {
                for (auto i = 0; i != gap; ++i) ti = ti->Destination[time];
                li->Destination.template emplace_back(ti);
                ti->Source.template emplace_back(li);
            }
        }
    }
}

template<typename Tp>
void Skip_List<Tp>::insert(const Tp &value)
{

}

template<typename Tp>
void Skip_List<Tp>::erase(const size_t &index)
{

}

template<typename Tp>
size_t Skip_List<Tp>::find(const Tp &value) const
{

}

template<typename Tp>
Tp Skip_List<Tp>::get(const size_t &index) const
{
    NodeR_Iter<Tp> ci {this->Head};
    for (auto i = 0;i!=index;++i, ci=ci.next_ptr(0));
    return ci.value_c();
}

template<typename Tp>
Tp &Skip_List<Tp>::operator[](const size_t &index)
{
    NodeR_Iter<Tp> ci {this->Head};
    for (auto i = 0;i!=index;++i, ci=ci.next_ptr(0));
    return (*ci)();
}


#endif //DATASTRUCTURE_SKIP_LIST_HPP
