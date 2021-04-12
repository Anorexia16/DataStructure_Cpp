#ifndef DATASTRUCTURE_ABSTRACT_GRAPH_HPP
#define DATASTRUCTURE_ABSTRACT_GRAPH_HPP

template<typename Tp>
class Graph
{
public:
    [[nodiscard]] virtual size_t vertices() const = 0;

    [[nodiscard]] virtual size_t edges() const = 0;

    [[nodiscard]] virtual size_t degree(size_t const &) const = 0;

    [[nodiscard]] virtual size_t in_degree(size_t const &) const = 0;

    [[nodiscard]] virtual size_t out_degree(size_t const &) const = 0;

    [[nodiscard]] virtual bool exist_edge(size_t const &, size_t const &) const = 0;

    [[nodiscard]] virtual bool directed() const = 0;

    [[nodiscard]] virtual bool weighted() const = 0;
};

#endif //DATASTRUCTURE_ABSTRACT_GRAPH_HPP
