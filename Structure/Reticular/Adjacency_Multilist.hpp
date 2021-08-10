#ifndef DATASTRUCTURE_ADJACENCY_MULTILIST_HPP
#define DATASTRUCTURE_ADJACENCY_MULTILIST_HPP

#include "../Abstract/Abstract_Graph.hpp"

struct AM_Edge {
    size_t weight{};
    size_t V1{};
    size_t V2{};
    AM_Edge *I{};
    AM_Edge *II{};
};

struct AM_Vertex {
    AM_Edge *radio{};
};

template<size_t num, bool is_weight>
struct Orthogonal_MultiList: public Graph {
    AM_Vertex Container[num] {};

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
constexpr size_t Orthogonal_MultiList<num, is_weight>::vertices() const {
    return num;
}

template<size_t num, bool is_weight>
size_t Orthogonal_MultiList<num, is_weight>::edges() const {
    size_t sum {};
    for (size_t i=0;i!=num;++i) {sum += degree(i);}
    return sum/2;
}

template<size_t num, bool is_weight>
size_t Orthogonal_MultiList<num, is_weight>::degree(const size_t &index) const {
    size_t n {};
    for(AM_Edge *i = Container[index].radio; i!= nullptr;i=i->I, ++n);
    return n;
}

template<size_t num, bool is_weight>
size_t Orthogonal_MultiList<num, is_weight>::in_degree(const size_t &index) const {
    return degree(index);
}

template<size_t num, bool is_weight>
size_t Orthogonal_MultiList<num, is_weight>::out_degree(const size_t &index) const {
    return degree(index);
}

template<size_t num, bool is_weight>
bool Orthogonal_MultiList<num, is_weight>::exist_edge(const size_t &I, const size_t &II) const {
    for (AM_Edge *i = Container[I].radio; i!= nullptr; i=i->I) {
        if (i->V2 == II) return true;
    }
    return false;
}

template<size_t num, bool is_weight>
constexpr bool Orthogonal_MultiList<num, is_weight>::directed() const {
    return false;
}

template<size_t num, bool is_weight>
constexpr bool Orthogonal_MultiList<num, is_weight>::weighted() const {
    return is_weight;
}

template<size_t num, bool is_weight>
void Orthogonal_MultiList<num, is_weight>::insert_edge
(const size_t &I, const size_t &II, const size_t &weight) {
    auto *edge = new AM_Edge {weight, I, II, nullptr, nullptr};
    if (Container[I].radio == nullptr) {
        Container[I].radio = edge;
    } else {
        AM_Edge *iter = Container[I].radio;
        while(iter->I != nullptr) iter = iter->I;
        iter->I = edge;
    }
    if (Container[II].radio == nullptr) {
        Container[II].radio = edge;
    } else {
        AM_Edge *iter = Container[II].radio;
        while (iter->II != nullptr) iter = iter->II;
        iter->II = edge;
    }
}

template<size_t num, bool is_weight>
void Orthogonal_MultiList<num, is_weight>::remove_edge(const size_t &I, const size_t &II) {
    if (Container[I].radio == nullptr) return;
    if (Container[I].radio->II == II)
        Container[I].radio == nullptr;
    else {
        for (AM_Edge *iter = Container[I].radio;
             iter->I != nullptr; iter = iter->I) {
            if (iter->I->V2 == II)
                iter->I = iter->I->I;
        }
    }
    if (Container[II].radio->V1 == I)
        Container[II].radio == nullptr;
    else {
        for (AM_Edge *iter = Container[II].radio;
             iter->II != nullptr; iter = iter->II) {
            if (iter->II->V1 == I)
                iter->II = iter->II->II;
        }
    }
}


#endif //DATASTRUCTURE_ADJACENCY_MULTILIST_HPP
