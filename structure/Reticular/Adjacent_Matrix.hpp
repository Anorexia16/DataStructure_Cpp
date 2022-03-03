#ifndef DATASTRUCTURE_ADJACENT_MATRIX_HPP
#define DATASTRUCTURE_ADJACENT_MATRIX_HPP

#include <Linear/Stack_Chain.hpp>
#include <Linear/Queue_Chain.hpp>
#include <Abstract/Abstract_Graph.hpp>
#include <vector>

template<size_t num, bool bidirectional = true, bool is_weighted = false>
struct Adjacent_Matrix: public Graph
{
    Adjacent_Matrix();

    [[nodiscard]] constexpr size_t vertices() const override;

    [[nodiscard]] size_t edges() const override;

    [[nodiscard]] size_t degree(size_t const &) const override;

    [[nodiscard]] size_t in_degree(size_t const &) const override;

    [[nodiscard]] size_t out_degree(size_t const &) const override;

    [[nodiscard]] bool exist_edge(size_t const &, size_t const &) const override;

    [[nodiscard]] constexpr bool directed() const override;

    [[nodiscard]] constexpr bool weighted() const override;

    void insert_edge(size_t const &, size_t const &, size_t const &) override;

    void remove_edge(size_t const &, size_t const &) override;

    std::vector<size_t> BFS(size_t const &);

    std::vector<size_t> DFS(size_t const &);

    unsigned int Container[num][num];
};

template<size_t num, bool bidirectional, bool is_weighted>
Adjacent_Matrix<num, bidirectional, is_weighted>::Adjacent_Matrix()
:Container{} {}

template<size_t num, bool bidirectional, bool is_weighted>
constexpr size_t Adjacent_Matrix<num, bidirectional, is_weighted>::vertices() const {
    return num;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Matrix<num, bidirectional, is_weighted>::edges() const {
    size_t n = 0;
    for (size_t i=0; i!=num; ++i)
        for (size_t j=0; j!=num; ++j)
            ++n;
    return bidirectional? n/2 : n;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Matrix<num, bidirectional, is_weighted>::degree(const size_t &ver) const {
    size_t n = 0;
    if (bidirectional)
    {
        for(size_t i=0; i!=num; ++i) if (this->Container[ver][i]!=0) ++n;
    } else {
        for(size_t i=0; i!=num; ++i) if (this->Container[i][ver]!=0) ++n;
        for(size_t i=0; i!=num; ++i) if (this->Container[ver][i]!=0) ++n;
    }
    return n;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Matrix<num, bidirectional, is_weighted>::in_degree(const size_t &ver) const {
    size_t n = 0;
    if (bidirectional)
    {
        for(size_t i=0; i!=num; ++i) if (this->Container[ver][i]!=0) ++n;
    } else {
        for(size_t i=0; i!=num; ++i) if (this->Container[i][ver]!=0) ++n;
    }
    return n;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Matrix<num, bidirectional, is_weighted>::out_degree(const size_t &ver) const {
    size_t n = 0;
    for(size_t i=0; i!=num; ++i) if (this->Container[ver][i]!=0) ++n;
    return n;
}

template<size_t num, bool bidirectional, bool is_weighted>
bool Adjacent_Matrix<num, bidirectional, is_weighted>::exist_edge(const size_t &i, const size_t &j) const {
    return this->Container[i][j] != 0;
}

template<size_t num, bool bidirectional, bool is_weighted>
constexpr bool Adjacent_Matrix<num, bidirectional, is_weighted>::directed() const {
    return !bidirectional;
}

template<size_t num, bool bidirectional, bool is_weighted>
constexpr bool Adjacent_Matrix<num, bidirectional, is_weighted>::weighted() const {
    return is_weighted;
}

template<size_t num, bool bidirectional, bool is_weighted>
void Adjacent_Matrix<num, bidirectional, is_weighted>::insert_edge(const size_t &i, const size_t &j, size_t const &weight) {
    if (i>num||j>num) throw;
    if (is_weighted) {
            this->Container[i][j] = weight;
            if (bidirectional) this->Container[j][i] = weight;
    }
}

template<size_t num, bool bidirectional, bool is_weighted>
void Adjacent_Matrix<num, bidirectional, is_weighted>::remove_edge(const size_t &i, const size_t &j){
    if (i>= num||j>=num) throw;
    this->Container[i][j] = 0;
    if (bidirectional) this->Container[j][i] = 0;
}

template<size_t num, bool bidirectional, bool is_weighted>
std::vector <size_t>Adjacent_Matrix<num, bidirectional, is_weighted>::BFS(const size_t &begin) {
    size_t _iter = begin;
    std::cout <<  "breadth first search on graph:" <<std::endl << begin << ' ';
    bool traversed[num];
    traversed[_iter] = true;

    Queue_C<std::pair<size_t, size_t>> _queue {};
    std::vector<size_t> _res {};
    _res.reserve(num);
    size_t ci = 0;

    while(true)
    {
        if (Container[_iter][ci]==0&&traversed[ci]==true) {
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
            _res.template emplace_back(ci);
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

template<size_t num, bool bidirectional, bool is_weighted>
std::vector<size_t> Adjacent_Matrix<num, bidirectional, is_weighted>::DFS(const size_t &begin) {
    size_t _iter = begin;
    std::cout <<  "depth first search on graph:" <<std::endl << begin << ' ';
    bool traversed[num];
    traversed[_iter] = true;

    Stack_C<std::pair<size_t, size_t>> _stack {};
    std::vector<size_t> _res {};
    _res.reserve(num);
    size_t ci = 0;

    while (true)
    {
        if (Container[_iter][ci]==0&&traversed[ci]==true)
        {
            if (ci+1==num)
            {
                if (_stack.empty()) break;
                else
                {
                    _iter=_stack.top().first;
                    ci=_stack.top().second;
                    _stack.pop();
                }
            } else ++ci;
        } else {
            if (ci+1!=num) _stack.push({_iter, ci+1});
            _iter=Container[_iter][ci];
            ci = 0;
            _res.template emplace_back(_iter);
            traversed[_iter]=true;
        }
    }

    return _res;
}


#endif //DATASTRUCTURE_ADJACENT_MATRIX_HPP
