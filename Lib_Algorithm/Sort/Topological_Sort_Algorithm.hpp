#ifndef DATASTRUCTURE_TOPOLOGICAL_SORT_ALGORITHM_HPP
#define DATASTRUCTURE_TOPOLOGICAL_SORT_ALGORITHM_HPP

#include "../../Structure/Reticular/Adjacent_Matrix.hpp"
#include "../../Structure/Linear/Queue_Chain.hpp"
#include <vector>

template<size_t num, bool weighted>
std::vector<size_t> topological_sort(Adjacent_Matrix<num, false, weighted> &Matrix)
{
    auto &matrix  = Matrix.Container;
    bool no_loop;
    size_t i=0;
    for (;i!=num; ++i)
    {
        no_loop = true;
        for(size_t j=0;j!=num; ++j) {
            if (matrix[j][i]!=0) {
                no_loop = false;
                break;
            }
        }
        if (no_loop) {
            break;
        }
    }
    if (!no_loop) return std::vector<size_t> {};

    std::vector<size_t> _res{i};
    Queue_C<unsigned int> _queue{};
    _res.reserve(num);


    for(size_t j=0; j!=num; ++j)
    {
        if (matrix[i][j]!=0) _queue.enqueue(j);
    }

    return _res;
}

#endif //DATASTRUCTURE_TOPOLOGICAL_SORT_ALGORITHM_HPP
