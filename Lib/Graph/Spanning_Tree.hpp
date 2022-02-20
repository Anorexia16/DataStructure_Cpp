#ifndef DATASTRUCTURE_SPANNING_TREE_HPP
#define DATASTRUCTURE_SPANNING_TREE_HPP

#include "../../Structure/Reticular/Adjacent_Matrix.hpp"
#include "../../Structure/Dendroid/Leftist_Tree.hpp"
#include <vector>
#include <array>
#include <queue>

template<size_t num>
std::array<std::pair<size_t, size_t>, num-1>
spanning_tree(Adjacent_Matrix<num, true, false> const &matrix)
{
    size_t _iter = 0;
    bool traversed[num] {};
    traversed[_iter] = true;

    std::queue<std::pair<size_t, size_t>> _queue {};
    std::array<std::pair<size_t, size_t>, num-1> _res {};
    auto &graph = matrix.Container;
    size_t ci = 0, index=0;

    while(true)
    {
        if (graph[_iter][ci]==0||traversed[ci]) {
            if (ci + 1 == num) {
                if (_queue.empty()) break;
                else {
                    _iter=_queue.front().first;
                    ci=_queue.front().second;
                    _queue.dequeue();
                }
            } else ++ci;
        } else {
            traversed[ci] = true;
            _res[index++]={_iter, ci};
            _queue.enqueue({ci, 0});
            if (ci+1!=num)
            {
                ++ci;
            } else {
                _iter=_queue.front().first;
                ci=_queue.front().second;
                _queue.dequeue();
            }
        }
    }
    return _res;
}


template<size_t num>
std::array<std::pair<size_t, size_t>, num-1>
spanning_tree(Adjacent_Matrix<num, true, true> const &matrix)
{
    if (num == 1) return std::array<std::pair<size_t, size_t>, num-1> {};
    if (num == 2) return std::array<std::pair<size_t, size_t>, num-1>
            {std::pair<size_t, size_t>{0, 1}};

    std::array<std::pair<size_t, size_t>, num-1> _res {};
    std::vector<std::pair<size_t, size_t>> _edges {};
    Leftist_Tree<Pair_Unit<ssize_t, size_t>> _weight_pro {};
    auto &graph = matrix.Container;
    bool inside[num] {};
    size_t index = 0;

    _edges.reserve(100*num);
    inside[0] = true;

    for(size_t i=0; i!=num; ++i) {
        if(graph[0][i]!=0) {
            _weight_pro.insert(Pair_Unit<ssize_t, size_t>{-static_cast<ssize_t>(graph[0][i]), index});
            _edges.template emplace_back(std::pair<size_t, size_t>{0, i});
            ++index;
        }
    }

    size_t _edge_index;
    for (size_t i=0;i!=num-1;) {
        _edge_index = _edges[_weight_pro.top().Value].second;
        if (inside[_edge_index]) {
            _weight_pro.pop();
        } else {
            _res[i] = _edges[_weight_pro.top().Value];
            ++_res[i].first;
            ++_res[i].second;
            inside[_edge_index] = true;
            _weight_pro.pop();
            for(size_t j=0; j!=num; ++j) {
                if (graph[_edge_index][j] != 0 && !inside[j]) {
                    _weight_pro.insert(Pair_Unit<ssize_t, size_t>{-static_cast<ssize_t>(graph[_edge_index][j]), index});
                    _edges.template emplace_back(std::pair<size_t, size_t>{_edge_index, j});
                    ++index;
                }
            }
            ++i;
        }
    }
    return _res;
}

#endif //DATASTRUCTURE_SPANNING_TREE_HPP
