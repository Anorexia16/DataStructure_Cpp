#ifndef DATASTRUCTURE_ITERATIONS_HPP
#define DATASTRUCTURE_ITERATIONS_HPP

#include <functional>
#include <vector>
#include <map>

template<class IterationCls>
concept Forward_Iterator_Tag = requires (IterationCls iterator)
{
    IterationCls();IterationCls(iterator);iterator=iterator;
    iterator==iterator;iterator!=iterator;
    *iterator;&*iterator;*iterator=*iterator;
    iterator++;++iterator;*iterator++;
};

template<class IterationCls>
concept Bidirectional_Iterator_Tag =
Forward_Iterator_Tag<IterationCls> && requires (IterationCls iterator)
{
    iterator--;iterator++;*iterator--;
};

template<class IterationCls>
concept Random_Access_Iterator_Tag =
Bidirectional_Iterator_Tag<IterationCls> && requires (IterationCls iterator)
{
    iterator+1;1+iterator;iterator-1;iterator-iterator;
    iterator<iterator;iterator>iterator;iterator<=iterator;iterator>=iterator;
    iterator+=1;iterator-=1;iterator[0];
};

template<typename Tp, Forward_Iterator_Tag Iter, typename arg>
auto &Yield(Iter begin, Iter end, Tp (*func)(arg))
{
    auto &vector = *new std::vector<Tp>{};
    for(auto iter=begin;iter!=end;++iter)
    {
        vector.template emplace_back(func(*iter));
    }
    return vector;
}

template<typename Tp, Random_Access_Iterator_Tag Iter, typename arg>
auto &Yield(Iter begin, Iter end, Tp (*func)(arg))
{
    auto &vector = *new std::vector<Tp>{};
    vector.reserve(end - begin);
    for(auto iter=begin;iter!=end;++iter)
    {
        vector.template emplace_back(func(*iter));
    }
    return vector;
}

template<typename K_Tp, typename V_Tp>
std::pair<std::vector<K_Tp>, std::vector<V_Tp>>
map_items (std::map<K_Tp, V_Tp> const &map)
{
    std::vector<K_Tp> K_Container {};
    std::vector<V_Tp> V_Container {};
    K_Container.reserve(map.size());
    V_Container.reserve(map.size());
    for (auto const &iter: map)
    {
        K_Container.template emplace_back(iter.first);
        V_Container.template emplace_back(iter.second);
    }
    return {K_Container, V_Container};
}

template<typename K_Tp, typename V_Tp>
std::vector<K_Tp>
map_keys (std::map<K_Tp, V_Tp> const &map)
{
    std::vector<K_Tp> K_Container {};
    K_Container.reserve(map.size());
    for (auto const &iter: map)
    {
        K_Container.template emplace_back(iter.first);
    }
    return K_Container;
}

template<typename K_Tp, typename V_Tp>
std::vector<V_Tp>
map_values (std::map<K_Tp, V_Tp> const &map)
{
    std::vector<V_Tp> V_Container {};
    V_Container.reserve(map.size());
    for (auto const &iter: map)
    {
        V_Container.template emplace_back(iter.second);
    }
    return V_Container;
}

class Range;
#include <iterator>

class Range_iterator: std::iterator<std::forward_iterator_tag, long long> {
private:
    friend class Range;

    Range* Range;

    long long Value;
public:
    explicit Range_iterator(class Range const &);

    Range_iterator &operator=(const class Range_iterator&);

    long long &operator *();

    Range_iterator &operator++();

    const Range_iterator operator++(int);

    bool operator<(Range_iterator const &) const;

    bool operator>(Range_iterator const &) const;

    bool operator<=(Range_iterator const &) const;

    bool operator>=(Range_iterator const &) const;

    bool operator==(Range_iterator const &) const;

    bool operator!=(Range_iterator const &) const;
};

class Range {
private:
    long long Count;
    long long Start;
    long long End;

public:
    friend class Range_iterator;

    explicit Range(long long const & = 0);

    explicit Range(long long const &, long long const &);

    explicit Range(long long const &, long long const &, long long const &);

    Range_iterator begin();

    Range_iterator end();
};

Range::Range(const long long &end)
        : Start{0}, End{end}, Count{1} {if (end < 0) Count = -1;}

Range::Range(const long long &start, const long long &end)
        : Start{start}, End{end}, Count{} {if (end < start) Count=-1;}

Range::Range(const long long &start, const long long &end, const long long &count)
        : Start{start}, End{end}, Count{count} {if ((end - start) * count < 0) throw;}

Range_iterator Range::begin()
{
    return Range_iterator(*this);
}

Range_iterator Range::end()
{
    Range_iterator end_iter {*this};
    long long value {this->Start};
    for (;(value<this->End&&this->Count>0||value>this->End&&this->Count<0);) value += this->Count;
    end_iter.Value = value;
    return end_iter;
}

Range_iterator::Range_iterator(class Range const &range)
        : Range{const_cast<class Range *>(&range)}, Value{range.Start} {}

Range_iterator &Range_iterator::operator=(const class Range_iterator &iter)
= default;

long long &Range_iterator::operator*()
{
    return this->Value;
}

Range_iterator &Range_iterator::operator++()
{
    this->Value += this->Range->Count;
    return *this;
}

const Range_iterator Range_iterator::operator++(int)
{
    Range_iterator res {*this->Range};
    this->Value += this->Range->Count;
    return res;
}

bool Range_iterator::operator<(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value<op.Value;
}

bool Range_iterator::operator>(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value>op.Value;
}

bool Range_iterator::operator<=(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value<=op.Value;
}

bool Range_iterator::operator>=(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value>=op.Value;
}

bool Range_iterator::operator==(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value==op.Value;
}

bool Range_iterator::operator!=(const Range_iterator &op) const
{
    if (static_cast<void*>(this->Range) != static_cast<void *>(op.Range)) throw;
    return this->Value!=op.Value;
}

template<typename I, typename II>
std::pair<II, I> pair_reverse(std::pair<I, II> const &pair) {
    return std::pair<II, I>{pair.second, pair.first};
}

template<typename Tp, unsigned long long size>
Tp *diff(Tp const (&array) [size])
{
    Tp _res[size-1] {};
    for(unsigned long long i=0; i!=size-1; ++i)
    {
        _res[i] = array[i+1] - array[i];
    }
    return _res;
}

template<typename Tp, unsigned long long size>
Tp *&prefix_sum(Tp const (&array) [size])
{
    auto _res= new Tp[size] {array[0]};
    for (unsigned long long i =1; i!=size; ++i)
    {
        _res[i] = _res[i-1] + array[i];
    }
    return _res;
}

template<typename ...Args>
decltype(auto) prod(Args const &... args)
{
    return (args*...);
}

template<typename ...Args>
decltype(auto) sum(Args const &... args)
{
    return (args+...);
}

template<typename ...Args>
bool all(Args const &... args)
{
    return (args&&...);
}

template<typename ...Args>
bool any(Args const &... args)
{
    return (args||...);
}

template<class cls>
cls &copy(cls const &source) {
    return *new cls {source};
}

template<class cls>
cls &&move(cls &&source) {
    return cls{std::forward<>(source)};
}



#endif //DATASTRUCTURE_ITERATIONS_HPP
