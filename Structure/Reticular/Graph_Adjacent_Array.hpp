#ifndef DATASTRUCTURE_GRAPH_ADJACENT_ARRAY_HPP
#define DATASTRUCTURE_GRAPH_ADJACENT_ARRAY_HPP

#include <array>
#include <vector>
#include "../Abstract/Abstract_Graph.hpp"

template<typename Tp, size_t num, bool bidirectional = true, bool is_weighted = false>
struct Adjacent_Array: public Graph<Tp>
{
    Adjacent_Array() = default;

    [[nodiscard]] size_t vertices() const;

    [[nodiscard]] size_t edges() const;

    [[nodiscard]] size_t degree(size_t const &) const;

    [[nodiscard]] size_t in_degree(size_t const &) const;

    [[nodiscard]] size_t out_degree(size_t const &) const;

    [[nodiscard]] bool exist_edge(size_t const &, size_t const &) const;

    [[nodiscard]] bool directed() const;

    [[nodiscard]] bool weighted() const;

    void insert_edge(size_t const &, size_t const &, ssize_t const & = -1);

    void remove_edge(size_t const &, size_t const &);

    std::array<std::vector<std::pair<size_t, size_t>>, num> Container;
};

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Array<Tp, num, bidirectional, is_weighted>::vertices() const
{
    return num;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Array<Tp, num, bidirectional, is_weighted>::edges() const
{
    size_t _res = 0;
    for(auto const &iter:this->Container) _res += iter.size();
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Array<Tp, num, bidirectional, is_weighted>::degree(const size_t &i) const
{
    size_t _res = this->Container[i].size();
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

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Array<Tp, num, bidirectional, is_weighted>::in_degree(const size_t &i) const
{
    size_t _res = 0;
    for(auto const &iter:this->Container)
        for(auto const &item: iter)
        {
            if(item.first == i) ++_res;
        }
    return _res;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
size_t Adjacent_Array<Tp, num, bidirectional, is_weighted>::out_degree(const size_t &i) const
{
    return this->Container[i].size();
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
bool Adjacent_Array<Tp, num, bidirectional, is_weighted>::exist_edge(const size_t &i, const size_t &j) const
{
    for(auto const &iter: this->Container[i]) if (iter.first == j) return true;
    return false;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
bool Adjacent_Array<Tp, num, bidirectional, is_weighted>::directed() const
{
    return !bidirectional;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
bool Adjacent_Array<Tp, num, bidirectional, is_weighted>::weighted() const
{
    return is_weighted;
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
void Adjacent_Array<Tp, num, bidirectional, is_weighted>::insert_edge(const size_t &i, const size_t &j, const ssize_t &weight)
{
    if (i>= num||j>=num) throw;
    if (is_weighted)
    {
        if (weight <= -1) return;
        else {
            this->Container[i].emplace_back(j, weight);
            if (bidirectional) this->Container[j].template emplace_back(i, weight);
        }
    } else {
        if (weight > 0) return;
        else {
            this->Container[i].template emplace_back({j, 1});
            if (bidirectional) this->Container[j].template emplace_back({i, 1});
        }
    }
}

template<typename Tp, size_t num, bool bidirectional, bool is_weighted>
void Adjacent_Array<Tp, num, bidirectional, is_weighted>::remove_edge(const size_t &i, const size_t &j)
{
    if (i>= num||j>=num) throw;
    for (size_t idx=0; idx!=Container[i].size(); ++idx)
        if (Container[i][idx].first == j)
        {
            Container[i].erase(std::begin(Container[i]) + idx);
            break;
        }
    if (bidirectional)
        for (size_t idx=0; idx!=Container[j].size(); ++idx)
            if (Container[j][idx].first == i)
            {
                Container[j].erase(std::begin(Container[j]) + idx);
                break;
            }
}

#endif //DATASTRUCTURE_GRAPH_ADJACENT_ARRAY_HPP
