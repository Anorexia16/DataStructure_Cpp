#ifndef DATASTRUCTURE_NODE_RETICULAR_HPP
#define DATASTRUCTURE_NODE_RETICULAR_HPP

#include <iostream>
#include <vector>

template<typename cls>
struct NodeR {
    explicit NodeR(cls const & = *new cls {});

    template<class Iterable_Container1, class Iterable_Container2>
    NodeR(cls const &, Iterable_Container1 const &, Iterable_Container2 const &);

    NodeR(cls const &, NodeR<cls> **&, size_t const &, NodeR<cls> **&, size_t const &);

    std::vector<NodeR<cls> *> Destination;

    std::vector<NodeR<cls> *> Source;

    cls Value;
};

template<typename cls>
NodeR<cls>::NodeR(const cls &i)
        :Value{i}, Source{}, Destination{} {}

template<typename cls>
template<class Iterable_Container1, class Iterable_Container2>
NodeR<cls>::NodeR(const cls &value, const Iterable_Container1 &cont_source, const Iterable_Container2 &cont_destination)
        :Value{value}, Source{}, Destination{}
{
    for (auto &&iter: cont_source) Source.template emplace_back(iter);
    for (auto &&iter: cont_destination) Destination.template emplace_back(iter);
}

template<typename cls>
NodeR<cls>::NodeR(const cls &value, NodeR<cls> **&array_source, const size_t &size_source,
                  NodeR<cls> **&array_destination, const size_t &size_destination)
        :Value{value}, Source{}, Destination{}
{
    for (auto i = 0; i != size_source; ++i) Source.template emplace_back(array_source[i]);
    for (auto i = 0; i != size_destination; ++i) Destination.template emplace_back(array_destination[i]);
}

template<typename cls>
class NodeR_Iter: std::iterator<std::bidirectional_iterator_tag, cls>
{
public:
    NodeR_Iter();

    explicit NodeR_Iter(NodeR<cls> const &);

    explicit NodeR_Iter(const NodeR<cls> * const &);

    inline NodeR<cls> &operator*();

    inline NodeR<cls> *operator->();

    NodeR_Iter<cls> &operator=(const NodeR<cls> * const &);

    inline std::vector<NodeR_Iter<cls> *> &operator++();

    inline std::vector<NodeR_Iter<cls> *> &operator--();

    inline std::vector<NodeR_Iter<cls> *> const operator++(int) const;

    inline std::vector<NodeR_Iter<cls> *> const operator--(int) const;

    inline bool operator==(NodeR_Iter<cls> const &) const;

    inline bool operator!=(NodeR_Iter<cls> const &) const;

    inline bool operator==(const NodeR<cls> * const &) const;

    inline bool operator!=(const NodeR<cls> * const &) const;

    NodeR<cls> *Ptr;
};

template<typename cls>
NodeR_Iter<cls>::NodeR_Iter()
    :Ptr{nullptr} {}

template<typename cls>
NodeR_Iter<cls>::NodeR_Iter(const NodeR<cls> *const &ptr)
    :Ptr{const_cast<NodeR<cls> *>(ptr)} {}

template<typename cls>
NodeR_Iter<cls>::NodeR_Iter(NodeR<cls> const &node)
    :Ptr{&node} {}

template<typename cls>
NodeR<cls> &NodeR_Iter<cls>::operator*()
{
    return *(this->Ptr);
}

template<typename cls>
NodeR<cls> *NodeR_Iter<cls>::operator->()
{
    return this->Ptr;
}

template<typename cls>
std::vector<NodeR_Iter<cls> *> &NodeR_Iter<cls>::operator++()
{
    return this->Destination;
}

template<typename cls>
std::vector<NodeR_Iter<cls> *> &NodeR_Iter<cls>::operator--()
{
    return this->Source;
}

template<typename cls>
const std::vector<NodeR_Iter<cls> *> NodeR_Iter<cls>::operator++(int) const
{
    return this->Destination;
}

template<typename cls>
const std::vector<NodeR_Iter<cls> *> NodeR_Iter<cls>::operator--(int) const
{
    return this->Source;
}

template<typename cls>
bool NodeR_Iter<cls>::operator==(const NodeR_Iter<cls> &op) const
{
    return this->Ptr==op.Ptr;
}

template<typename cls>
bool NodeR_Iter<cls>::operator!=(const NodeR_Iter<cls> &op) const
{
    return this->Ptr!=op.Ptr;
}

template<typename cls>
bool NodeR_Iter<cls>::operator==(const NodeR<cls> *const &ptr) const
{
    return static_cast<void*>(this->Ptr)==static_cast<void*>(ptr);
}

template<typename cls>
bool NodeR_Iter<cls>::operator!=(const NodeR<cls> *const &ptr) const
{
    return static_cast<void*>(this->Ptr)!=static_cast<void*>(ptr);
}

template<typename cls>
NodeR_Iter<cls> &NodeR_Iter<cls>::operator=(const NodeR<cls> *const &ptr)
{
    this->Ptr = const_cast<NodeR<cls> *>(ptr);
    return *this;
}

#endif //DATASTRUCTURE_NODE_RETICULAR_HPP
