#ifndef DATASTRUCTURE_NODE_NONLINEAR_HPP
#define DATASTRUCTURE_NODE_NONLINEAR_HPP

#include <iostream>

template<typename cls>
class NodeN {
public:
    NodeN();

    explicit NodeN(cls const &);

    NodeN(cls const &, NodeN<cls> &, std::initializer_list<NodeN<cls> *> const &);

    template<template<typename elem, typename = std::allocator<elem>> class Cont>
    NodeN(cls const &, NodeN<cls> &, Cont<NodeN<cls> *> const &);

    NodeN(cls const &, NodeN<cls> &, NodeN<cls> **&, size_t const &);

    NodeN(NodeN<cls> &&) noexcept = default;

    NodeN(NodeN<cls> const &) = default;

    NodeN<cls> &operator=(NodeN<cls> &&) noexcept = default;

    NodeN<cls> &operator=(NodeN<cls> const &) = default;

    NodeN<cls> &operator=(cls const &);

    inline cls &operator()();

    virtual inline cls value_c() const;

    virtual inline NodeN<cls> &next();

    virtual inline NodeN<cls> *next_ptr();

    virtual inline NodeN<cls> &next(size_t const &);

    virtual inline NodeN<cls> *next_ptr(size_t const &);

    virtual inline NodeN<cls> &prev();

    virtual inline NodeN<cls> *prev_ptr();

    inline void link_front(NodeN<cls> &);

    inline void link_after(NodeN<cls> &);

    inline void remove_link(size_t const &);

    friend std::ostream &operator<<(std::ostream &out, NodeN<cls> const &node) {
        out << node.Value;
        return out;
    }

protected:
    std::vector<NodeN<cls> *> Destination;
    NodeN<cls> *Source;
    cls Value;
};

template<typename cls>
NodeN<cls>::NodeN()
        :Value{}, Source{nullptr}, Destination{} {

}

template<typename cls>
NodeN<cls>::NodeN(const cls &value)
        :Value{value}, Source{nullptr}, Destination{} {}

template<typename cls>
NodeN<cls>::NodeN(const cls &value, NodeN<cls> &ptr,
                  const std::initializer_list<NodeN<cls> *> &list)
        :Value{value}, Source{&ptr}, Destination{} {
    for (auto &&iter: list) Destination.template emplace_back(iter);
}

template<typename cls>
template<template<typename elem, typename = std::allocator<elem>> class Cont>
NodeN<cls>::NodeN(const cls &value, NodeN<cls> &ptr, const Cont<NodeN<cls> *> &cont)
        :Value{value}, Source{&ptr}, Destination{} {
    for (auto &&iter: cont) Destination.template emplace_back(iter);
}

template<typename cls>
NodeN<cls>::NodeN(const cls &value, NodeN<cls> &ptr, NodeN<cls> **&array,
                  const size_t &size)
        :Value{value}, Source{ptr}, Destination{} {
    for (auto i = 0; i != size; ++i) Destination.template emplace_back(array[i]);
}

template<typename cls>
NodeN<cls> &NodeN<cls>::operator=(const cls &v) {
    return NodeN{v};
}

template<typename cls>
cls &NodeN<cls>::operator()() {
    return this->Value;
}

template<typename cls>
cls NodeN<cls>::value_c() const {
    return this->Value;
}

template<typename cls>
NodeN<cls> &NodeN<cls>::next() {
    return *this->Destination[0];
}

template<typename cls>
NodeN<cls> *NodeN<cls>::next_ptr() {
    return this->Destination[0];
}

template<typename cls>
NodeN<cls> &NodeN<cls>::next(const size_t &index) {
    return *this->Destination[index];
}

template<typename cls>
NodeN<cls> *NodeN<cls>::next_ptr(const size_t &index) {
    return this->Destination[index];
}

template<typename cls>
NodeN<cls> &NodeN<cls>::prev() {
    return *this->Source;
}

template<typename cls>
NodeN<cls> *NodeN<cls>::prev_ptr() {
    return this->Source;
}

template<typename cls>
void NodeN<cls>::link_front(NodeN<cls> &node) {
    this->Source = &node;
}

template<typename cls>
void NodeN<cls>::link_after(NodeN<cls> &node) {
    this->Destination.template emplace_back(node);
}

template<typename cls>
void NodeN<cls>::remove_link(const size_t &index) {
    this->Destination.erase(std::begin(this->Destination) + index);
}

template<typename cls>
class NodeN_Iter : virtual public NodeN<cls> {
protected:
    NodeN<cls> *Ptr;
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

    inline std::vector<NodeN_Iter<cls> *> &operator++();

    inline std::vector<NodeN_Iter<cls> *> operator++(int) const;

    inline NodeN_Iter<cls> &operator--();

    inline const NodeN_Iter<cls> operator--(int) const;

    inline bool operator==(NodeN_Iter<cls> const &) const;

    inline bool operator!=(NodeN_Iter<cls> const &) const;

    inline bool operator==(const NodeN<cls> *const &);

    inline bool operator!=(const NodeN<cls> *const &);

    inline NodeN_Iter<cls> &turn_to(const NodeN<cls> *const &);

    inline cls value_c() const;

    inline NodeN<cls> &next();

    inline NodeN<cls> &next(size_t const &index);

    inline NodeN<cls> *next_ptr();

    inline NodeN<cls> *next_ptr(size_t const &index);

    inline NodeN<cls> &prev();

    inline NodeN<cls> *prev_ptr();
};

template<typename cls>
NodeN_Iter<cls>::NodeN_Iter()
    : Ptr{nullptr} {}

template<typename cls>
NodeN_Iter<cls>::NodeN_Iter(const NodeN<cls> *const &ptr)
    :Ptr{static_cast<NodeN<cls> *>(ptr)} {}

template<typename cls>
NodeN_Iter<cls>::NodeN_Iter(NodeN<cls> &&node)
    :Ptr{&std::forward<>(node)} {
}

template<typename cls>
NodeN<cls> &NodeN_Iter<cls>::operator*() {
    return *this->Value;
}

template<typename cls>
NodeN<cls> *NodeN_Iter<cls>::operator->() {
    return &*this->Value;
}

template<typename cls>
std::vector<NodeN_Iter<cls> *> &NodeN_Iter<cls>::operator++() {
    return this->Destination;
}

template<typename cls>
std::vector<NodeN_Iter<cls> *> NodeN_Iter<cls>::operator++(int) const {
    return this->Destination;
}

template<typename cls>
NodeN_Iter<cls> &NodeN_Iter<cls>::operator--() {
    return *this->Source;
}

template<typename cls>
NodeN_Iter<cls> const NodeN_Iter<cls>::operator--(int) const {
    return *this->Source;
}

template<typename cls>
bool NodeN_Iter<cls>::operator==(const NodeN_Iter<cls> &op) const {
    return this->Ptr==op.Ptr;
}

template<typename cls>
bool NodeN_Iter<cls>::operator!=(const NodeN_Iter<cls> &op) const {
    return this->Ptr!=op.Ptr;
}

template<typename cls>
bool NodeN_Iter<cls>::operator==(const NodeN<cls> *const &op) {
    return static_cast<void*>(this->Ptr) == static_cast<void*>(op);
}

template<typename cls>
bool NodeN_Iter<cls>::operator!=(const NodeN<cls> *const &op) {
    return static_cast<void*>(this->Ptr) != static_cast<void*>(op);
}

template<typename cls>
NodeN_Iter<cls> &NodeN_Iter<cls>::turn_to(const NodeN<cls> *const &op) {
    this->Ptr = const_cast<NodeN<cls> *>(op);
    return *this;
}

template<typename cls>
cls NodeN_Iter<cls>::value_c() const {
    return this->Ptr->value_c();
}

template<typename cls>
NodeN<cls> &NodeN_Iter<cls>::next() {
    return this->Ptr->next();
}

template<typename cls>
NodeN<cls> &NodeN_Iter<cls>::next(const size_t &index) {
    return this->Ptr->next(index);
}

template<typename cls>
NodeN<cls> *NodeN_Iter<cls>::next_ptr() {
    return this->Ptr->next_ptr();
}

template<typename cls>
NodeN<cls> *NodeN_Iter<cls>::next_ptr(const size_t &index) {
    return this->Ptr->next_ptr(index);
}

template<typename cls>
NodeN<cls> &NodeN_Iter<cls>::prev() {
    return this->Ptr->prev();
}

template<typename cls>
NodeN<cls> *NodeN_Iter<cls>::prev_ptr() {
    return this->Ptr->prev_ptr();
}

#endif //DATASTRUCTURE_NODE_NONLINEAR_HPP
