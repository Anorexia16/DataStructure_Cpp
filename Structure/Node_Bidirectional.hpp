#ifndef DATASTRUCTURE_NODE_B
#define DATASTRUCTURE_NODE_B

#include <iostream>

template<typename T>
class NodeB {
public:
    explicit NodeB();

    explicit NodeB(T &);

    explicit NodeB(T const &);

    NodeB(T const &, NodeB<T> *, NodeB<T> *);

    NodeB<T> &operator=(T const &);

    NodeB<T> &operator=(T &);

    T &operator()();

    virtual NodeB<T> &next();

    virtual NodeB<T> *next_ptr();

    virtual NodeB<T> &prev();

    virtual NodeB<T> *prev_ptr();

    void link_front(NodeB<T> &);

    void link_after(NodeB<T> &);

    T const &value_c() const;

    friend std::ostream &operator<<(std::ostream &out, NodeB<T> &x) {
        out << x.element;
        return out;
    }

protected:
    NodeB<T> *Next;
    NodeB<T> *Prev;
    T Element;
};

template<typename T>
NodeB<T>::NodeB()
        : Element{T()}, Next{nullptr}, Prev{nullptr} {}

template<typename T>
NodeB<T>::NodeB(T &x)
        : Element{x}, Next{nullptr}, Prev{nullptr} {}

template<typename T>
NodeB<T>::NodeB(const T &x)
        : Element{const_cast<T &>(x)}, Next{nullptr}, Prev{nullptr} {}

template<typename T>
NodeB<T>::NodeB(const T &x, NodeB<T> *ptr1, NodeB<T> *ptr2)
        : Element{const_cast<T &>(x)}, Prev{ptr1}, Next{ptr2} {}

template<typename T>
NodeB<T> &NodeB<T>::operator=(const T &x) {
    this->Element = const_cast<T &>(x);
}

template<typename T>
NodeB<T> &NodeB<T>::operator=(T &x) {
    this->Element = x;
}

template<typename T>
T &NodeB<T>::operator()() {
    return this->Element;
}

template<typename T>
NodeB<T> &NodeB<T>::next() {
    return *this->Next;
}

template<typename T>
NodeB<T> &NodeB<T>::prev() {
    return *this->Prev;
}

template<typename T>
NodeB<T> *NodeB<T>::next_ptr() {
    return this->Next;
}

template<typename T>
NodeB<T> *NodeB<T>::prev_ptr() {
    return this->Prev;
}

template<typename T>
void NodeB<T>::link_front(NodeB<T> &x) {
    this->Prev = &x;
}

template<typename T>
void NodeB<T>::link_after(NodeB<T> &x) {
    this->Next = &x;
}

template<typename T>
T const &NodeB<T>::value_c() const {
    return this->Element;
}

template<typename T>
class NodeB_Iter : virtual public NodeB<T> {
private:
    NodeB<T> *Ptr;
public:
    NodeB_Iter();

    explicit NodeB_Iter(NodeB<T> &&);

    explicit NodeB_Iter(const NodeB<T> *);

    inline NodeB<T> &operator*();

    inline NodeB<T> *operator->();

    inline NodeB_Iter<T> &operator++();

    inline NodeB_Iter<T> &operator--();

    inline NodeB_Iter<T> const operator++(int) const;

    inline NodeB_Iter<T> const operator--(int) const;

    inline bool operator==(NodeB_Iter<T> const &) const;

    inline bool operator!=(NodeB_Iter<T> const &) const;

    inline bool operator==(const NodeB<T> *) const;

    inline bool operator!=(const NodeB<T> *) const;

    inline NodeB_Iter<T> &turn_to(const NodeB<T> *);

    inline const T &value_c() { return this->Ptr->value_c(); }

    inline NodeB<T> &next() { return this->Ptr->next(); }

    inline NodeB<T> *next_ptr() { return this->Ptr->next_ptr(); }

    inline NodeB<T> &prev() { return this->Ptr->prev(); }

    inline NodeB<T> *prev_ptr() { return this->Ptr->prev_ptr(); }
};

template<typename T>
NodeB_Iter<T>::NodeB_Iter()
        : Ptr(nullptr) {}

template<typename T>
NodeB_Iter<T>::NodeB_Iter(NodeB<T> &&elem)
        : Ptr(&elem) {}

template<typename T>
NodeB_Iter<T>::NodeB_Iter(const NodeB<T> *ptr)
        :Ptr(const_cast<NodeB<T> *>(ptr)) {}

template<typename T>
NodeB<T> &NodeB_Iter<T>::operator*() {
    return *(this->Ptr);
}

template<typename T>
NodeB<T> *NodeB_Iter<T>::operator->() {
    return &*(this->Ptr);
}

template<typename T>
NodeB_Iter<T> &NodeB_Iter<T>::operator++() {
    this->Ptr = this->Ptr->next_ptr();
    return *this;
}

template<typename T>
NodeB_Iter<T> &NodeB_Iter<T>::operator--() {
    this->Ptr = this->Ptr->prev_ptr();
    return *this;
}

template<typename T>
const NodeB_Iter<T> NodeB_Iter<T>::operator++(int) const {
    NodeB<T> temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
const NodeB_Iter<T> NodeB_Iter<T>::operator--(int) const {
    NodeB<T> temp = *this;
    --(*this);
    return temp;
}

template<typename T>
bool NodeB_Iter<T>::operator==(const NodeB_Iter<T> &op) const {
    return this->Ptr == op.Ptr;
}

template<typename T>
bool NodeB_Iter<T>::operator!=(const NodeB_Iter<T> &op) const {
    return this->Ptr != op.Ptr;
}

template<typename T>
bool NodeB_Iter<T>::operator==(const NodeB<T> *ptr) const {
    return this->Ptr == ptr;
}

template<typename T>
bool NodeB_Iter<T>::operator!=(const NodeB<T> *ptr) const {
    return this->Ptr != ptr;
}

template<typename T>
NodeB_Iter<T> &NodeB_Iter<T>::turn_to(const NodeB<T> *ptr) {
    this->Ptr = const_cast<NodeB<T> *>(ptr);
    return *this;
}


#endif //DATASTRUCTURE_NODE_BIDIRECTIONAL_HPP
