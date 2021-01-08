#ifndef DATASTRUCTURE_CHAIN_BIDIRECTIONAL
#define DATASTRUCTURE_CHAIN_BIDIRECTIONAL

#include "Abstract_Linear_List.hpp"
#include "Node_Bidirectional.hpp"

template<typename T>
class ChainBC : public LinearList<T> {
public:
    explicit ChainBC(size_t const &);

    ChainBC(ChainBC<T> const &);

    ~ChainBC() = default;

    void resize(size_t const &);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    size_t find(T const &) const;

    void erase(size_t const &);

    void insert(size_t const &, T const &);

    T &operator[](size_t const &) const;

    friend std::ostream &operator<<(std::ostream &out, ChainBC<T> const &x) {
        NodeB_Iter<T> iterator{x.head_c()->next_ptr()};
        for (; iterator != x.head_c(); ++iterator) {
            out << (*iterator)() << " ";
        }
        return out;
    }

    inline NodeB<T> *head() { return this->Head; }

    inline NodeB<T> *head_c() const { return this->Head; }

protected:
    NodeB<T> *Head;
    size_t Size;
    size_t Capacity;
};

template<typename T>
ChainBC<T>::ChainBC(size_t const &cap)
        : Head{new NodeB<T>{T()}}, Size{0}, Capacity{cap} {
    Head->link_after(*Head);
    Head->link_front(*Head);
}

template<typename T>
ChainBC<T>::ChainBC(const ChainBC<T> &op)
        : Head{op.Head}, Size{op.Size}, Capacity{op.Capacity} {}

template<typename T>
bool ChainBC<T>::empty() const {
    return this->Size == 0;
}

template<typename T>
size_t ChainBC<T>::size() const {
    return this->Size;
}

template<typename T>
size_t ChainBC<T>::find(const T &x) const {
    NodeB<T> *iterator = this->Head;
    for (auto iter = 0; iter != this->Size; iter++) {
        iterator = iterator->next_ptr();
        if ((*iterator)() == x) return iter;
    }
    return -1;
}

template<typename T>
void ChainBC<T>::erase(size_t const &x) {
    if (0 > x || x >= this->Size) throw;
    NodeB<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; iter++) {
        iterator = iterator->next_ptr();
    }
    iterator->link_after(iterator->next().next());
    iterator->next().link_front(*iterator);
    this->Size -= 1;
}

template<typename T>
void ChainBC<T>::insert(size_t const &index, T const &elem) {
    if (0 > index || index > this->Size) throw;
    if (this->Capacity == this->Size) throw;
    NodeB<T> *iterator = this->Head;
    for (auto iter = 0; iter != index; iter++) {
        iterator = iterator->next_ptr();
    }
    NodeB<T> *temp = iterator->next_ptr();
    iterator->link_after(*new NodeB<T>(elem, iterator, iterator->next_ptr()));
    temp->link_front(iterator->next());
    this->Size += 1;
}

template<typename T>
T &ChainBC<T>::operator[](size_t const &x) const {
    NodeB<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; iter++) {
        iterator = iterator->next_ptr();
    }
    return (*iterator)();
}

template<typename T>
void ChainBC<T>::resize(size_t const &size) {
    this->Size = size;
}

#endif //DATASTRUCTURE_CHAIN_BIDIRECTIONAL_CIRCLE_HPP
