#ifndef DATASTRUCTURE_NODE_B
#define DATASTRUCTURE_NODE_B

#include <iostream>

template<typename T>
struct NodeB
{
    explicit NodeB(T const & = *new T{}, NodeB<T> * = nullptr, NodeB<T> * = nullptr);

    NodeB<T> *Next;

    NodeB<T> *Prev;

    T Element;
};

template<typename T>
NodeB<T>::NodeB(const T &x, NodeB<T> *ptr1, NodeB<T> *ptr2)
        : Element{const_cast<T &>(x)}, Prev{ptr1}, Next{ptr2} {}


template<typename T>
class NodeB_Iter : std::iterator<std::bidirectional_iterator_tag, T>
{
public:
    NodeB_Iter();

    explicit NodeB_Iter(NodeB<T> &);

    explicit NodeB_Iter(const NodeB<T> *const &);

    inline T &operator*();

    inline T *operator->();

    inline NodeB_Iter<T> &operator++();

    inline NodeB_Iter<T> &operator--();

    inline const NodeB_Iter<T> operator++(int) const;

    inline const NodeB_Iter<T> operator--(int) const;

    inline bool operator==(NodeB_Iter<T> const &) const;

    inline bool operator!=(NodeB_Iter<T> const &) const;

    inline bool operator==(const NodeB<T> *const &) const;

    inline bool operator!=(const NodeB<T> *const &) const;

    NodeB<T> *Ptr;
};

template<typename T>
NodeB_Iter<T>::NodeB_Iter()
        : Ptr(nullptr) {}

template<typename T>
NodeB_Iter<T>::NodeB_Iter(NodeB<T> &elem)
        : Ptr(&elem) {}

template<typename T>
NodeB_Iter<T>::NodeB_Iter(const NodeB<T> *const &ptr)
        :Ptr(const_cast<NodeB<T> *>(ptr)) {}

template<typename T>
T &NodeB_Iter<T>::operator*()
{
    return this->Ptr->Element;
}

template<typename T>
T *NodeB_Iter<T>::operator->()
{
    return &this->Ptr->Element;
}

template<typename T>
NodeB_Iter<T> &NodeB_Iter<T>::operator++()
{
    this->Ptr = this->Ptr->Next;
    return *this;
}

template<typename T>
NodeB_Iter<T> &NodeB_Iter<T>::operator--()
{
    this->Ptr = this->Ptr->Prev;
    return *this;
}

template<typename T>
const NodeB_Iter<T> NodeB_Iter<T>::operator++(int) const
{
    NodeB<T> temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
const NodeB_Iter<T> NodeB_Iter<T>::operator--(int) const
{
    NodeB<T> temp = *this;
    --(*this);
    return temp;
}

template<typename T>
bool NodeB_Iter<T>::operator==(const NodeB_Iter<T> &op) const
{
    return this->Ptr == op.Ptr;
}

template<typename T>
bool NodeB_Iter<T>::operator!=(const NodeB_Iter<T> &op) const
{
    return this->Ptr != op.Ptr;
}

template<typename T>
bool NodeB_Iter<T>::operator==(const NodeB<T> *const &ptr) const
{
    return this->Ptr == ptr;
}

template<typename T>
bool NodeB_Iter<T>::operator!=(const NodeB<T> *const &ptr) const
{
    return this->Ptr != ptr;
}

#endif //DATASTRUCTURE_NODE_BIDIRECTIONAL_HPP
