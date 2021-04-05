#ifndef DATASTRUCTURE_NODE_U
#define DATASTRUCTURE_NODE_U

#include <ostream>
#include <iterator>

template<typename T>
struct NodeU
{
    explicit NodeU(T const & = *new T {}, NodeU<T> * = nullptr);

    NodeU<T> *Next;

    T Element;
};

template<typename T>
NodeU<T>::NodeU(T const &x, NodeU<T> * ptr)
        : Element{const_cast<T &>(x)}, Next{ptr} {}

template<typename T>
class NodeU_Iter :std::iterator<std::forward_iterator_tag, T>
{
public:
    NodeU_Iter();

    explicit NodeU_Iter(NodeU<T> &);

    explicit NodeU_Iter(const NodeU<T> *const &);

    inline T &operator*();

    inline NodeU_Iter<T> &operator++();

    inline NodeU_Iter<T> const operator++(int) const;

    inline bool operator==(NodeU_Iter<T> const &) const;

    inline bool operator!=(NodeU_Iter<T> const &) const;

    inline bool operator==(const NodeU<T> *const &) const;

    inline bool operator!=(const NodeU<T> *const &) const;

    NodeU_Iter(NodeU_Iter<T> const &) = default;

    NodeU<T> *Ptr;
};

template<typename T>
NodeU_Iter<T>::NodeU_Iter()
        : Ptr(nullptr) {}

template<typename T>
NodeU_Iter<T>::NodeU_Iter(NodeU<T> &elem)
        : Ptr(&elem) {}

template<typename T>
NodeU_Iter<T>::NodeU_Iter(const NodeU<T> *const &ptr)
        : Ptr(const_cast<NodeU<T> *>(ptr)) {}

template<typename T>
T &NodeU_Iter<T>::operator*()
{
    return this->Ptr->Element;
}

template<typename T>
NodeU_Iter<T> &NodeU_Iter<T>::operator++()
{
    this->Ptr = this->Ptr->Next;
    return *this;
}

template<typename T>
NodeU_Iter<T> const NodeU_Iter<T>::operator++(int) const
{
    NodeU<T> temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
bool NodeU_Iter<T>::operator==(const NodeU<T> *const &ptr) const
{
    return this->Ptr == ptr;
}

template<typename T>
bool NodeU_Iter<T>::operator!=(const NodeU<T> *const &ptr) const
{
    return this->Ptr != ptr;
}

template<typename T>
bool NodeU_Iter<T>::operator==(const NodeU_Iter<T> &op) const
{
    return this->Ptr == op.Ptr;
}

template<typename T>
bool NodeU_Iter<T>::operator!=(const NodeU_Iter<T> &op) const
{
    return this->Ptr != op.Ptr;
}

#endif //DATASTRUCTURE_NODE_UNIDIRECTIONAL_HPP
