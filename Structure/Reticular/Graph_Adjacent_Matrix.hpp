#ifndef DATASTRUCTURE_GRAPH_ADJACENT_MATRIX_HPP
#define DATASTRUCTURE_GRAPH_ADJACENT_MATRIX_HPP

#include <iostream>
#include "../Linear/Stack_Chain.hpp"
#include "../Linear/Queue_Chain.hpp"
#include "../Abstract/Abstract_Graph.hpp"

template<typename Tp, size_t num, bool bidirectional = true, bool is_weighted = false>
struct Adjacent_Matrix: public Graph<Tp>
{
    Adjacent_Matrix();

    [[nodiscard]] size_t vertices() const override;

    [[nodiscard]] size_t edges() const override;

    [[nodiscard]] size_t degree(size_t const &) const override;

    [[nodiscard]] size_t in_degree(size_t const &) const override;

    [[nodiscard]] size_t out_degree(size_t const &) const override;

    [[nodiscard]] bool exist_edge(size_t const &, size_t const &) const override;

    [[nodiscard]] bool directed() const override;

    [[nodiscard]] bool weighted() const override;

    void insert_edge(size_t const &, size_t const &, ssize_t const & = -1);

    void remove_edge(size_t const &, size_t const &);

    std::ostream &BFS(std::ostream &, size_t const &);

    std::ostream &DFS(std::ostream &, size_t const &);

    Tp Container[num][num];
};

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::Adjacent_Matrix()
:Container{} {}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::vertices() const {
    return num;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::edges() const {
    size_t n = 0;
    for (size_t i=0; i!=num; ++i)
        for (size_t j=0; j!=num; ++j)
            ++n;
    return bidirectional? n/2 : n;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::degree(const size_t &ver) const {
    size_t n = 0;
    if (bidirectional)
    {
        for(size_t i=0; i!=num; ++i) if (this->Container[ver-1][i]!=0) ++n;
    } else {
        for(size_t i=0; i!=num; ++i) if (this->Container[i][ver-1]!=0) ++n;
        for(size_t i=0; i!=num; ++i) if (this->Container[ver-1][i]!=0) ++n;
    }
    return n;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::in_degree(const size_t &ver) const {
    size_t n = 0;
    if (bidirectional)
    {
        for(size_t i=0; i!=num; ++i) if (this->Container[ver-1][i]!=0) ++n;
    } else {
        for(size_t i=0; i!=num; ++i) if (this->Container[i][ver-1]!=0) ++n;
    }
    return n;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::out_degree(const size_t &ver) const {
    size_t n = 0;
    if (bidirectional)
    {
        for(size_t i=0; i!=num; ++i) if (this->Container[ver-1][i]!=0) ++n;
    } else {
        for(size_t i=0; i!=num; ++i) if (this->Container[ver-1][i]!=0) ++n;
    }
    return n;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
bool Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::exist_edge(const size_t &i, const size_t &j) const {
    return this->Container[i-1][j-1] != 0;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
bool Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::directed() const {
    return !bidirectional;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
bool Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::weighted() const {
    return is_weighted;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
void Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::insert_edge(const size_t &i, const size_t &j, ssize_t const &weight) {
    if (i>num||j>num) throw;
    if (is_weighted) {
        if (weight <= -1) return;
        else {
            this->Container[i-1][j-1] = weight;
            if (bidirectional) this->Container[j-1][i-1] = weight;
        }
    } else {
        if (weight > 0) return;
        else {
            this->Container[i-1][j-1] = 1;
            if (bidirectional) this->Container[j-1][i-1] = 1;
        }
    }
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
void Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::remove_edge(const size_t &i, const size_t &j){
    if (i>= num||j>=num) throw;
    this->Container[i-1][j-1] = 0;
    if (bidirectional) this->Container[j-1][i-1] = 0;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
std::ostream &Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::BFS(std::ostream &out, const size_t &begin) {
    size_t _iter = begin - 1;
    std::cout <<  "breadth first search on graph:" <<std::endl << begin << ' ';
    bool traversed[num];
    traversed[_iter] = true;

    Queue_C<std::pair<size_t, size_t>> _queue {};
    size_t ci = 0;

    while(true)
    {
        if (Container[_iter][ci]==0&&traversed[ci]== true) {
            if (ci + 1 == num) {
                if (_queue.empty()) break;
                else {
                    _iter = _queue.front().first;
                    ci = _queue.front().second;
                    _queue.dequeue();
                }
            } else ++ci;
        } else {
            traversed[ci] = true;
            out << ci+1 << ' ';
            _queue.enqueue({ci, 0});
            if (ci+1!=num)
            {
                ++ci;
            } else {
                _iter = _queue.front().first;
                ci = _queue.front().second;
                _queue.dequeue();
            }
        }
    }
    out << std::endl;
    return out;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
std::ostream &Adjacent_Matrix<Tp, num, bidirectional, is_weighted>::DFS(std::ostream &out, const size_t &begin) {
    size_t _iter = begin - 1;
    std::cout <<  "depth first search on graph:" <<std::endl << begin << ' ';
    bool traversed[num];
    traversed[_iter] = true;

    Stack_C<std::pair<size_t, size_t>> _stack {};
    size_t ci = 0;

    while (true)
    {
        if (Container[_iter][ci]==0&&traversed[ci]== true)
        {
            if (ci + 1 == num)
            {
                if (_stack.empty()) break;
                else
                {
                    _iter = _stack.top().first;
                    ci = _stack.top().second;
                    _stack.pop();
                }
            } else ++ci;
        } else {
            if (ci+1!=num) _stack.push({_iter, ci+1});
            _iter = Container[_iter][ci];
            ci = 0;
            out << _iter+1 << ' ';
            traversed[_iter] = true;
        }
    }
    out << std::endl;
    return out;
}


#endif //DATASTRUCTURE_GRAPH_ADJACENT_MATRIX_HPP
