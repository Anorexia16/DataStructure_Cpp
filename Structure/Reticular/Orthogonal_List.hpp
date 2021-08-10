#ifndef DATASTRUCTURE_ORTHOGONAL_LIST_HPP
#define DATASTRUCTURE_ORTHOGONAL_LIST_HPP

#include "../Abstract/Abstract_Graph.hpp"

struct OL_Edge {
    size_t weight{};
    size_t from_vertex{};
    size_t to_vertex{};
    OL_Edge *source{};
    OL_Edge *destination{};
};

struct OL_Vertex {
    OL_Edge *to_this{};
    OL_Edge *from_this{};
};

template<size_t num, bool is_weight>
struct Orthogonal_List: public Graph {
    OL_Vertex Container[num] {};

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
};

template<size_t num, bool is_weight>
constexpr size_t Orthogonal_List<num, is_weight>::vertices() const {
    return num;
}

template<size_t num, bool is_weight>
size_t Orthogonal_List<num, is_weight>::edges() const {
    size_t sum=0;
    for (size_t i=0;i!=num;++i) {sum+= degree(i);}
    return 0;
}

template<size_t num, bool is_weight>
size_t Orthogonal_List<num, is_weight>::degree(const size_t &x) const {
    size_t n {};
    for (OL_Edge *node=Container[x].to_this;node!= nullptr;node = node->destination) ++n;
    for (OL_Edge *node=Container[x].from_this;node!= nullptr;node = node->source) ++n;
    return n;
}

template<size_t num, bool is_weight>
size_t Orthogonal_List<num, is_weight>::in_degree(const size_t &to) const {
    size_t n {};
    for (OL_Edge *node=Container[to].to_this;node!= nullptr;node = node->destination) ++n;
    return n;
}

template<size_t num, bool is_weight>
size_t Orthogonal_List<num, is_weight>::out_degree(const size_t &from) const {
    size_t n {};
    for (OL_Edge *node=Container[from].from_this;node!= nullptr;node = node->source) ++n;
    return n;
}

template<size_t num, bool is_weight>
bool Orthogonal_List<num, is_weight>::exist_edge
(const size_t &from, const size_t &to) const {
    for (OL_Edge *node=Container[from].from_this;node!= nullptr;node = node->source) {
        if (node->from_vertex == from && node->to_vertex == to) {
            return true;
        }
    }
    return false;
}

template<size_t num, bool is_weight>
constexpr bool Orthogonal_List<num, is_weight>::directed()
const {
    return true;
}

template<size_t num, bool is_weight>
constexpr bool Orthogonal_List<num, is_weight>::weighted()
const {
    return is_weight;
}

template<size_t num, bool is_weight>
void Orthogonal_List<num, is_weight>::insert_edge
(const size_t &from, const size_t &to, const size_t &weight) {
    auto *_edge = new OL_Edge {weight, from, to, nullptr, nullptr};
    if (Container[from].from_this == nullptr) {
        Container[from].from_this = _edge;
    } else {
        OL_Edge *iter = Container[from].from_this;
        while(iter->source!= nullptr) iter= iter->source;
        iter->source = _edge;
    }
    if (Container[to].to_this == nullptr) {
        Container[to].to_this = _edge;
    } else {
        OL_Edge *iter = Container[to].to_this;
        while(iter->destination!= nullptr) iter= iter->destination;
        iter->destination = _edge;
    }
}

template<size_t num, bool is_weight>
void Orthogonal_List<num, is_weight>::remove_edge
(const size_t &from, const size_t &to) {
    if (Container[from].from_this == nullptr) return;
    if (Container[from].from_this->to_vertex == to)
        Container[from].from_this == nullptr;
    else {
        for (OL_Edge *iter = Container[from].from_this;
             iter->source != nullptr; iter = iter->source) {
            if (iter->source->to_vertex == to)
                iter->source = iter->source->source;
        }
    }
    if (Container[to].to_this->from_vertex == from)
        Container[to].to_this == nullptr;
    else {
        for (OL_Edge *iter = Container[to].to_this;
             iter->destination != nullptr; iter = iter->destination) {
            if (iter->destination->from_vertex == to)
                iter->destination = iter->destination->destination;
        }
    }
}
#endif //DATASTRUCTURE_ORTHOGONAL_LIST_HPP
