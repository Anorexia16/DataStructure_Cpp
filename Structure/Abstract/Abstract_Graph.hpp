#ifndef DATASTRUCTURE_ABSTRACT_GRAPH_HPP
#define DATASTRUCTURE_ABSTRACT_GRAPH_HPP

#include <cstdlib>

class Graph
{
public:
    [[nodiscard]] constexpr virtual size_t vertices() const = 0;

    [[nodiscard]] virtual size_t edges() const = 0;

    [[nodiscard]] virtual size_t degree(size_t const &) const = 0;

    [[nodiscard]] virtual size_t in_degree(size_t const &) const = 0;

    [[nodiscard]] virtual size_t out_degree(size_t const &) const = 0;

    [[nodiscard]] virtual bool exist_edge(size_t const &, size_t const &) const = 0;

    [[nodiscard]] virtual constexpr bool directed() const = 0;

    [[nodiscard]] virtual constexpr bool weighted() const = 0;

    virtual void insert_edge(size_t const &, size_t const &, size_t const &) = 0;

    virtual void remove_edge(size_t const &, size_t const &) = 0;
};

#endif //DATASTRUCTURE_ABSTRACT_GRAPH_HPP
