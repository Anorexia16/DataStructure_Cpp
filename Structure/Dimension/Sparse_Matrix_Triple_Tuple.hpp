#ifndef DATASTRUCTURE_SPARSE_MATRIX_TRIPLE_TUPLE_HPP
#define DATASTRUCTURE_SPARSE_MATRIX_TRIPLE_TUPLE_HPP

#include <vector>

struct SMatrix_Tuple
{
    template<class Iterable_2Dim_Container>
    explicit SMatrix_Tuple(Iterable_2Dim_Container const &cont);

    std::vector<int[3]> Container;

    int &operator[](std::pair<int, int> const &);

    SMatrix_Tuple &T();
};

template<class Iterable_2Dim_Container>
SMatrix_Tuple::SMatrix_Tuple
(const Iterable_2Dim_Container &cont)
: Container{}
{
    int i=0, j=0;
    for(auto const &iter1:cont)
    {
        for(auto const &iter2:iter1) {
            if (iter2 != 0) Container.template emplace_back(int {i, j, iter2});
            ++j;
        }
        ++i;
    }
}

int &SMatrix_Tuple::operator[](const std::pair<int, int> &pair)
{
    int row = pair.first, column = pair.second;
    for(auto & iter: this->Container)
    {
        if (row == iter[0] && column == iter[1])
            return iter[2];
    }
    return *new int{};
}

SMatrix_Tuple &SMatrix_Tuple::T()
{
    int temp;
    for(auto & iter: this->Container)
    {
        temp = iter[0];
        iter[0] = iter[1];
        iter[1] = temp;
    }
    return *this;
}


#endif //DATASTRUCTURE_SPARSE_MATRIX_TRIPLE_TUPLE_HPP
