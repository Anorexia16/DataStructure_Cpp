#ifndef DATASTRUCTURE_NODE_U
#define DATASTRUCTURE_NODE_U

#include <ostream>


template<typename T>
class NodeU {
public:
    explicit NodeU();

    explicit NodeU(T const &);

    NodeU(T const &, NodeU<T> *);

    NodeU<T> &operator=(T const &);

    NodeU<T> &operator=(T &);

    inline T &operator()();

    virtual inline T value_c() const;

    virtual inline NodeU<T> &next();

    virtual inline NodeU<T> *next_ptr();

    inline void link(NodeU<T> &);

    friend std::ostream &operator<<(std::ostream &out, NodeU<T> &x) {
        out << x.Element;
        return out;
    }

protected:
    NodeU<T> *Next;
    T Element;
};

template<typename T>
NodeU<T>::NodeU()
        : Element{T()}, Next{nullptr} {}

template<typename T>
NodeU<T>::NodeU(T const &x)
        : Element{const_cast<T &>(x)}, Next{nullptr} {}

template<typename T>
NodeU<T>::NodeU(T const &x, NodeU<T> *ptr)
        : Element{const_cast<T &>(x)}, Next{ptr} {}

template<typename T>
NodeU<T> &NodeU<T>::operator=(const T &x) {
    this = const_cast<T &>(x);
}

template<typename T>
NodeU<T> &NodeU<T>::operator=(T &x) {
    this->Element = x;
}

template<typename T>
T &NodeU<T>::operator()() {
    return this->Element;
}

template<typename T>
T NodeU<T>::value_c() const {
    return this->Element;
}

template<typename T>
void NodeU<T>::link(NodeU<T> &x) {
    this->Next = &x;
}

template<typename T>
NodeU<T> &NodeU<T>::next() {
    return *this->Next;
}

template<typename T>
NodeU<T> *NodeU<T>::next_ptr() {
    return this->Next;
}

template<typename T>
class NodeU_Iter : virtual public NodeU<T> {
protected:
    NodeU<T> *Ptr;
public:
    NodeU_Iter();

    explicit NodeU_Iter(NodeU<T> &);

    explicit NodeU_Iter(const NodeU<T> *const &);

    inline NodeU<T> &operator*();

    inline NodeU<T> *operator->();

    inline NodeU_Iter<T> &operator++();

    inline const NodeU_Iter<T> operator++(int) const;

    inline bool operator==(NodeU_Iter<T> const &) const;

    inline bool operator!=(NodeU_Iter<T> const &) const;

    inline bool operator==(const NodeU<T> *const &) const;

    inline bool operator!=(const NodeU<T> *const &) const;

    inline NodeU_Iter<T> &turn_to(const NodeU<T> *const &);

    inline T value_c() const;

    inline NodeU<T> &next();

    inline NodeU<T> *next_ptr();
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
NodeU<T> &NodeU_Iter<T>::operator*() {
    return *(this->Ptr);
}

template<typename T>
NodeU<T> *NodeU_Iter<T>::operator->() {
    return &*(this->Ptr);
}

template<typename T>
NodeU_Iter<T> &NodeU_Iter<T>::operator++() {
    this->Ptr = this->Ptr->next_ptr();
    return *this;
}

template<typename T>
const NodeU_Iter<T> NodeU_Iter<T>::operator++(int) const {
    NodeU<T> temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
bool NodeU_Iter<T>::operator==(const NodeU<T> *const &ptr) const {
    return this->Ptr == ptr;
}

template<typename T>
bool NodeU_Iter<T>::operator!=(const NodeU<T> *const &ptr) const {
    return this->Ptr != ptr;
}

template<typename T>
bool NodeU_Iter<T>::operator==(const NodeU_Iter<T> &op) const {
    return this->Ptr == op.Ptr;
}

template<typename T>
bool NodeU_Iter<T>::operator!=(const NodeU_Iter<T> &op) const {
    return this->Ptr != op.Ptr;
}

template<typename T>
NodeU_Iter<T> &NodeU_Iter<T>::turn_to(const NodeU<T> *const &ptr) {
    this->Ptr = const_cast<NodeU<T> *>(ptr);
    return *this;
}

template<typename T>
T NodeU_Iter<T>::value_c() const {
    return this->Ptr->value_c();
}

template<typename T>
NodeU<T> &NodeU_Iter<T>::next() {
    return this->Ptr->next();
}

template<typename T>
NodeU<T> *NodeU_Iter<T>::next_ptr() {
    return this->Ptr->next_ptr();
}

#endif //DATASTRUCTURE_NODE_UNIDIRECTIONAL_HPP
