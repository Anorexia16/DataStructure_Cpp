#ifndef DATASTRUCTURE_NODE_NONLINEAR_HPP
#define DATASTRUCTURE_NODE_NONLINEAR_HPP

#include <iostream>
#include <vector>

template<typename cls>
struct NodeN
{
    explicit NodeN(cls const & = *new cls{});

    template<class Iterable_Container>
    NodeN(cls const &, NodeN<cls> &, Iterable_Container const &);

    NodeN(cls const &, NodeN<cls> &, NodeN<cls> **&, size_t const &);

    std::vector<NodeN<cls> *> Destination;

    NodeN<cls> *Source;

    cls Value;
};

template<typename cls>
NodeN<cls>::NodeN(const cls &value)
        :Value{value}, Source{nullptr}, Destination{} {}

template<typename cls>
template<class Iterable_Container>
NodeN<cls>::NodeN(const cls &value, NodeN<cls> &ptr, const Iterable_Container &cont)
        :Value{value}, Source{&ptr}, Destination{}
{
    for (auto &&iter: cont) Destination.template emplace_back(iter);
}

template<typename cls>
NodeN<cls>::NodeN(const cls &value, NodeN<cls> &ptr, NodeN<cls> **&array,
                  const size_t &size)
        :Value{value}, Source{ptr}, Destination{}
{
    for (auto i = 0; i != size; ++i) Destination.template emplace_back(array[i]);
}

template<typename cls>
class NodeN_Iter: std::iterator<std::bidirectional_iterator_tag, cls>
{
public:
    NodeN_Iter();

    explicit NodeN_Iter(NodeN<cls> &&);

    explicit NodeN_Iter(const NodeN<cls> *const &);

    NodeN_Iter(NodeN_Iter<cls> &&) noexcept = default;

    NodeN_Iter(NodeN_Iter<cls> const &) = default;

    NodeN_Iter<cls> &operator=(NodeN_Iter<cls> &&) noexcept = default;

    NodeN_Iter<cls> &operator=(NodeN_Iter<cls> const &) = default;

    inline NodeN<cls> &operator*();

    inline NodeN<cls> *operator->();

    inline std::vector<NodeN<cls> *> &operator++();

    inline const std::vector<NodeN<cls> *> operator++(int) const;

    inline NodeN_Iter<cls> &operator--();

    inline const NodeN_Iter<cls> operator--(int) const;

    inline bool operator==(NodeN_Iter<cls> const &) const;

    inline bool operator!=(NodeN_Iter<cls> const &) const;

    inline bool operator==(const NodeN<cls> *const &);

    inline bool operator!=(const NodeN<cls> *const &);

    NodeN<cls> *Ptr;
};

template<typename cls>
NodeN_Iter<cls>::NodeN_Iter()
    : Ptr{nullptr} {}

template<typename cls>
NodeN_Iter<cls>::NodeN_Iter(const NodeN<cls> *const &ptr)
    :Ptr{static_cast<NodeN<cls> *>(ptr)} {}

template<typename cls>
NodeN_Iter<cls>::NodeN_Iter(NodeN<cls> &&node)
    :Ptr{&std::forward<>(node)} {}

template<typename cls>
NodeN<cls> &NodeN_Iter<cls>::operator*()
{
    return *this->Value;
}

template<typename cls>
NodeN<cls> *NodeN_Iter<cls>::operator->()
{
    return &*this->Value;
}

template<typename cls>
std::vector<NodeN<cls> *> &NodeN_Iter<cls>::operator++()
{
    return this->Destination;
}

template<typename cls>
const std::vector<NodeN<cls> *> NodeN_Iter<cls>::operator++(int) const
{
    return this->Destination;
}

template<typename cls>
NodeN_Iter<cls> &NodeN_Iter<cls>::operator--()
{
    return *this->Source;
}

template<typename cls>
const NodeN_Iter<cls> NodeN_Iter<cls>::operator--(int) const
{
    return *this->Source;
}

template<typename cls>
bool NodeN_Iter<cls>::operator==(const NodeN_Iter<cls> &op) const
{
    return this->Ptr==op.Ptr;
}

template<typename cls>
bool NodeN_Iter<cls>::operator!=(const NodeN_Iter<cls> &op) const
{
    return this->Ptr!=op.Ptr;
}

template<typename cls>
bool NodeN_Iter<cls>::operator==(const NodeN<cls> *const &op)
{
    return this->Ptr == op;
}

template<typename cls>
bool NodeN_Iter<cls>::operator!=(const NodeN<cls> *const &op)
{
    return this->Ptr != op;
}

#endif //DATASTRUCTURE_NODE_NONLINEAR_HPP
