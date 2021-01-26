#ifndef DATASTRUCTURE_NODE_RETICULAR_HPP
#define DATASTRUCTURE_NODE_RETICULAR_HPP

#include <iostream>

template<typename cls>
class NodeR {
public:
    NodeR(NodeR<cls> &&) noexcept = default;

    NodeR(NodeR<cls> const &) = default;

    NodeR<cls> &operator=(NodeR<cls> &&) noexcept = default;

    NodeR<cls> &operator=(NodeR<cls> const &) = default;

    NodeR();

    explicit NodeR(cls const &);

    NodeR(cls const &, std::initializer_list<NodeR<cls> *> const &, std::initializer_list<NodeR<cls> *> const &);

    template<template<typename elem, typename =std::allocator<elem>> class Cont>
    NodeR(cls const &, Cont<NodeR<cls> *> const &, Cont<NodeR<cls> *> const &);

    NodeR(cls const &, NodeR<cls> **&, size_t const &, NodeR<cls> **&, size_t const &);

    inline cls &operator()();

    virtual inline cls value_c() const;

    virtual inline NodeR<cls> &next();

    virtual inline NodeR<cls> *next_ptr();

    virtual inline NodeR<cls> &next(size_t const &);

    virtual inline NodeR<cls> *next_ptr(size_t const &);

    virtual inline NodeR<cls> &prev();

    virtual inline NodeR<cls> *prev_ptr();

    virtual inline NodeR<cls> &prev(size_t const &);

    virtual inline NodeR<cls> *prev_ptr(size_t const &);

    inline void link_front(NodeR<cls> &);

    inline void link_after(NodeR<cls> &);

    inline void remove_link_p(size_t const &);

    inline void remove_link_n(size_t const &);

    friend std::ostream &operator<<(std::ostream &out, NodeR<cls> const &node) {
        out << node.Value;
        return out;
    }

protected:
    std::vector<NodeR<cls> *> Destination;
    std::vector<NodeR<cls> *> Source;
    cls Value;
};

template<typename cls>
NodeR<cls>::NodeR() {

}

template<typename cls>
NodeR<cls>::NodeR(const cls &)
        :Value{}, Source{}, Destination{} {}

template<typename cls>
NodeR<cls>::NodeR(const cls &value, const std::initializer_list<NodeR<cls> *> &list_source,
                  const std::initializer_list<NodeR<cls> *> &list_destination)
        :Value{value}, Source{}, Destination{} {
    for (auto &&iter: list_source) Source.template emplace_back(iter);
    for (auto &&iter: list_destination) Destination.template emplace_back(iter);
}

template<typename cls>
template<template<typename elem, typename =std::allocator<elem>> class Cont>
NodeR<cls>::NodeR(const cls &value, const Cont<NodeR<cls> *> &cont_source, const Cont<NodeR<cls> *> &cont_destination)
        :Value{value}, Source{}, Destination{} {
    for (auto &&iter: cont_source) Source.template emplace_back(iter);
    for (auto &&iter: cont_destination) Destination.template emplace_back(iter);
}

template<typename cls>
NodeR<cls>::NodeR(const cls &value, NodeR<cls> **&array_source, const size_t &size_source,
                  NodeR<cls> **&array_destination, const size_t &size_destination)
        :Value{value}, Source{}, Destination{} {
    for (auto i = 0; i != size_source; ++i) Source.template emplace_back(array_source[i]);
    for (auto i = 0; i != size_destination; ++i) Destination.template emplace_back(array_destination[i]);
}

template<typename cls>
cls &NodeR<cls>::operator()() {
    return this->Value;
}

template<typename cls>
cls NodeR<cls>::value_c() const {
    return this->Value;
}

template<typename cls>
NodeR<cls> &NodeR<cls>::next() {
    return *this->Destination[0];
}

template<typename cls>
NodeR<cls> *NodeR<cls>::next_ptr() {
    return this->Destination[0];
}

template<typename cls>
NodeR<cls> &NodeR<cls>::next(const size_t &index) {
    return *this->Destination[index];
}

template<typename cls>
NodeR<cls> *NodeR<cls>::next_ptr(const size_t &index) {
    return this->Destination[index];
}

template<typename cls>
NodeR<cls> &NodeR<cls>::prev() {
    return *this->Source[0];
}

template<typename cls>
NodeR<cls> *NodeR<cls>::prev_ptr() {
    return this->Source[0];
}

template<typename cls>
NodeR<cls> &NodeR<cls>::prev(const size_t &index) {
    return *this->Source[index];
}

template<typename cls>
NodeR<cls> *NodeR<cls>::prev_ptr(const size_t &index) {
    return this->Source[index];
}

template<typename cls>
void NodeR<cls>::link_front(NodeR<cls> &node) {
    this->Source.template emplace_back(&node);
}

template<typename cls>
void NodeR<cls>::link_after(NodeR<cls> &node) {
    this->Destination.template emplace_back(&node);
}

template<typename cls>
void NodeR<cls>::remove_link_p(size_t const &index) {
    this->Source.erase(std::begin(this->Source) + index);
}

template<typename cls>
void NodeR<cls>::remove_link_n(size_t const &index) {
    this->Destination.erase(std::begin(this->Destination) + index);
}

template<typename cls>
class NodeR_Iter: virtual public NodeR<cls> {
protected:
    NodeR<cls> *Ptr;
public:
    NodeR_Iter();

    explicit NodeR_Iter(NodeR<cls> &&);

    explicit NodeR_Iter(const NodeR<cls> * const &);

    NodeR_Iter(NodeR_Iter<cls> &&) noexcept = default;

    NodeR_Iter(NodeR_Iter<cls> const &) = default;

    NodeR_Iter<cls> &operator=(NodeR_Iter<cls> &&) noexcept = default;

    NodeR_Iter<cls> &operator=(NodeR_Iter<cls> const &) = default;

    inline NodeR<cls> &operator*();

    inline NodeR<cls> *operator->();

    inline std::vector<NodeR_Iter<cls> *> &operator++();

    inline std::vector<NodeR_Iter<cls> *> &operator--();

    inline std::vector<NodeR_Iter<cls> *> const operator++(int) const;

    inline std::vector<NodeR_Iter<cls> *> const operator--(int) const;

    inline bool operator==(NodeR_Iter<cls> const &) const;

    inline bool operator!=(NodeR_Iter<cls> const &) const;

    inline bool operator==(const NodeR<cls> * const &) const;

    inline bool operator!=(const NodeR<cls> * const &) const;

    inline NodeR_Iter<cls> &turn_to(const NodeR<cls> * const &);

    inline cls value_c() const;

    inline NodeR<cls> &next();

    inline NodeR<cls> &prev();

    inline NodeR<cls> &next(size_t const &);

    inline NodeR<cls> &prev(size_t const &);

    inline NodeR_Iter *next_ptr();

    inline NodeR_Iter *prev_ptr();

    inline NodeR<cls> *next_ptr(size_t const &);

    inline NodeR<cls> *prev_ptr(size_t const &);
};

template<typename cls>
NodeR_Iter<cls>::NodeR_Iter()
    :Ptr{nullptr} {}

template<typename cls>
NodeR_Iter<cls>::NodeR_Iter(const NodeR<cls> *const &ptr)
    :Ptr{const_cast<NodeR<cls> *>(ptr)} {}

template<typename cls>
NodeR_Iter<cls>::NodeR_Iter(NodeR<cls> &&node)
    :Ptr{&std::forward<>(node)} {}

template<typename cls>
NodeR<cls> &NodeR_Iter<cls>::operator*() {
    return *(this->Ptr);
}

template<typename cls>
NodeR<cls> *NodeR_Iter<cls>::operator->() {
    return this->Ptr;
}

template<typename cls>
std::vector<NodeR_Iter<cls> *> &NodeR_Iter<cls>::operator++() {
    return this->Destination;
}

template<typename cls>
std::vector<NodeR_Iter<cls> *> &NodeR_Iter<cls>::operator--() {
    return this->Source;
}

template<typename cls>
const std::vector<NodeR_Iter<cls> *> NodeR_Iter<cls>::operator++(int) const {
    return this->Destination;
}

template<typename cls>
const std::vector<NodeR_Iter<cls> *> NodeR_Iter<cls>::operator--(int) const {
    return this->Source;
}

template<typename cls>
bool NodeR_Iter<cls>::operator==(const NodeR_Iter<cls> &op) const {
    return this->Ptr==op.Ptr;
}

template<typename cls>
bool NodeR_Iter<cls>::operator!=(const NodeR_Iter<cls> &op) const {
    return this->Ptr!=op.Ptr;
}

template<typename cls>
bool NodeR_Iter<cls>::operator==(const NodeR<cls> *const &ptr) const {
    return static_cast<void*>(this->Ptr)==static_cast<void*>(ptr);
}

template<typename cls>
bool NodeR_Iter<cls>::operator!=(const NodeR<cls> *const &ptr) const {
    return static_cast<void*>(this->Ptr)!=static_cast<void*>(ptr);
}

template<typename cls>
NodeR_Iter<cls> &NodeR_Iter<cls>::turn_to(const NodeR<cls> *const &ptr) {
    this->Ptr=static_cast<void*>(ptr);
    return *this;
}

template<typename cls>
cls NodeR_Iter<cls>::value_c() const {
    return this->Value;
}

template<typename cls>
NodeR<cls> &NodeR_Iter<cls>::next() {
    return this->Ptr->next();
}

template<typename cls>
NodeR<cls> &NodeR_Iter<cls>::prev() {
    return this->Ptr->prev();
}

template<typename cls>
NodeR<cls> &NodeR_Iter<cls>::next(const size_t &index) {
    return this->Ptr->next(index);
}

template<typename cls>
NodeR<cls> &NodeR_Iter<cls>::prev(const size_t &index) {
    return this->Ptr->prev(index);
}

template<typename cls>
NodeR_Iter<cls> *NodeR_Iter<cls>::next_ptr() {
    return this->Ptr.next_ptr();
}

template<typename cls>
NodeR_Iter<cls> *NodeR_Iter<cls>::prev_ptr() {
    return this->Ptr->prev_ptr();
}

template<typename cls>
NodeR<cls> *NodeR_Iter<cls>::next_ptr(const size_t &index) {
    return this->Ptr.next_ptr(index);
}

template<typename cls>
NodeR<cls> *NodeR_Iter<cls>::prev_ptr(const size_t &index) {
    return this->Ptr.prev_ptr(index);
}

#endif //DATASTRUCTURE_NODE_RETICULAR_HPP
