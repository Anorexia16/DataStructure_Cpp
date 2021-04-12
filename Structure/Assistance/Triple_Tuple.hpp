#ifndef DATASTRUCTURE_TRIPLE_TUPLE_HPP
#define DATASTRUCTURE_TRIPLE_TUPLE_HPP

#include <vector>

template <typename Tp>
struct Triple_Node
{
    Triple_Node
    (Tp const &value, size_t const &row, size_t const &column)
    :Value{value}, Column_Num{column}, Row_Num{row} {}

    size_t Row_Num;

    size_t Column_Num;

    Tp Value;
};


template<typename Tp>
struct Triple_Tuple
{
    template<class Iterable_2Dim_Container>
    explicit Triple_Tuple
    (Iterable_2Dim_Container const &cont);

    Tp &operator[](std::pair<size_t, size_t> const &);

    std::vector<Tp> Container;

    std::vector<size_t[2]> Pos;
};

template<typename Tp>
template<class Iterable_2Dim_Container>
Triple_Tuple<Tp>::Triple_Tuple(const Iterable_2Dim_Container &cont)
: Container{}, Pos{}
{
    size_t i=0, j=0;
    Tp const empty {};
    for(auto const &row_iter: cont)
    {
        for(auto const &column_iter: row_iter)
        {
            if (column_iter != empty)
            {
                Container.template emplace_back(column_iter);
                Pos.template emplace_back(new size_t[2]{i, j});
            }
            ++j;
        }
        ++i;
    }
}

template<typename Tp>
Tp &Triple_Tuple<Tp>::operator[](const std::pair<size_t, size_t> &pair) {
    size_t idx = 0;
    for(auto const &row_iter: Pos)
    {
        if (row_iter[0] != pair.first || row_iter[1] != pair.second) ++idx;
        else return Container.operator[](idx);
    }
    return *new Tp{};
}

#endif //DATASTRUCTURE_TRIPLE_TUPLE_HPP
