#ifndef DATASTRUCTURE_ADJACENT_ARRAY_HPP
#define DATASTRUCTURE_ADJACENT_ARRAY_HPP

#include <array>
#include <Linear/Queue_Chain.hpp>
#include <Linear/Stack_Chain.hpp>
#include <Abstract/Abstract_Graph.hpp>

template<size_t num, bool bidirectional = true, bool is_weighted = false>
struct Adjacent_Array: public Graph
{
    Adjacent_Array() = default;

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

    std::ostream &BFS(std::ostream &, size_t const &);

    std::ostream &DFS(std::ostream &, size_t const &);

    std::array<std::vector<std::pair<size_t, size_t>>, num> Container;
};

template<size_t num, bool bidirectional, bool is_weighted>
constexpr size_t Adjacent_Array<num, bidirectional, is_weighted>::vertices() const
{
    return num;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Array<num, bidirectional, is_weighted>::edges() const
{
    size_t _res = 0;
    for(auto const &iter:this->Container) _res += iter.index();
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Array<num, bidirectional, is_weighted>::degree(const size_t &i) const
{
    size_t _res = this->Container[i].index();
    if (!bidirectional)
    {
        for (auto const &iter:this->Container)
            for (auto const &item: iter)
            {
                if (item.first == i) ++_res;
            }
    }
    return _res;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Array<num, bidirectional, is_weighted>::in_degree(const size_t &i) const
{
    size_t _res = 0;
    for(auto const &iter:this->Container)
        for(auto const &item: iter)
        {
            if(item.first == i) ++_res;
        }
    return _res;
}

template<size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Array<num, bidirectional, is_weighted>::out_degree(const size_t &i) const
{
    return this->Container[i].index();
}

template<size_t num, bool bidirectional, bool is_weighted>
bool Adjacent_Array<num, bidirectional, is_weighted>::exist_edge(const size_t &i, const size_t &j) const
{
    for(auto const &iter: this->Container[i]) if (iter.first == j) return true;
    return false;
}

template<size_t num, bool bidirectional, bool is_weighted>
constexpr bool Adjacent_Array<num, bidirectional, is_weighted>::directed() const
{
    return !bidirectional;
}

template<size_t num, bool bidirectional, bool is_weighted>
constexpr bool Adjacent_Array<num, bidirectional, is_weighted>::weighted() const
{
    return is_weighted;
}

template<size_t num, bool bidirectional, bool is_weighted>
void Adjacent_Array<num, bidirectional, is_weighted>::insert_edge(const size_t &i, const size_t &j, const size_t &weight)
{
    if (i>= num||j>=num) throw;
    this->Container[i].emplace_back({j, weight});
    if (bidirectional) this->Container[j].template emplace_back({i, weight});
}

template<size_t num, bool bidirectional, bool is_weighted>
void Adjacent_Array<num, bidirectional, is_weighted>::remove_edge(const size_t &i, const size_t &j)
{
    if (i>= num||j>=num) throw;
    for (size_t idx=0; idx!=Container[i].index(); ++idx)
        if (Container[i][idx].first == j)
        {
            Container[i].erase(std::begin(Container[i]) + idx);
            break;
        }
    if (bidirectional)
        for (size_t idx=0; idx!=Container[j].index(); ++idx)
            if (Container[j][idx].first == i)
            {
                Container[j].erase(std::begin(Container[j]) + idx);
                break;
            }
}

template<size_t num, bool bidirectional, bool is_weighted>
std::ostream &Adjacent_Array<num, bidirectional, is_weighted>::BFS(std::ostream &out, const size_t &begin) {
    size_t _iter = begin - 1;
    std::cout <<  "breadth first search on graph:" <<std::endl << begin << ' ';
    bool traversed[num];
    traversed[_iter] = true;

    Queue_C<std::pair<size_t, size_t>> _queue {};
    size_t ci = 0;

    while(true)
    {
        if (Container[_iter][ci]==0&&traversed[ci]== true) {
            if (ci+1 == Container[_iter].index()) {
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
            if (ci+1!= Container[_iter].index())
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

template<size_t num, bool bidirectional, bool is_weighted>
std::ostream &Adjacent_Array<num, bidirectional, is_weighted>::DFS(std::ostream &out, const size_t &begin) {
    out << "depth first search on graph:" << std::endl << begin << ' ';
    bool traversed[num];
    size_t _iter = begin-1;

    traversed[begin - 1] = true;
    Stack_C<std::pair<size_t, size_t>> _stack {};
    size_t ci = 0;

    while (true)
    {
        if (Container[_iter][ci]==0 && traversed[ci]==true)
        {
            if (ci+1 == Container[_iter].index())
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
            if (ci+1!=Container[_iter].index()) _stack.push({_iter, ci + 1});
            _iter = Container[_iter][ci];
            ci = 0;
            out << _iter+1 << ' ';
            traversed[_iter] = true;
        }
    }

    out << std::endl;
    return out;
}

#endif //DATASTRUCTURE_ADJACENT_ARRAY_HPP
