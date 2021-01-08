#ifndef DATASTRUCTURE_CHAIN_B
#define DATASTRUCTURE_CHAIN_B

#include "Abstract_Linear_List.hpp"
#include "Node_Bidirectional.hpp"

template<typename T>
class ChainB : public LinearList<T> {
public:
    explicit ChainB(size_t const &);

    ChainB(ChainB<T> const &);

    ~ChainB() = default;

    void resize(size_t const &);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    size_t find(T const &) const;

    void erase(size_t const &);

    void insert(size_t const &, T const &);

    T &operator[](size_t const &) const;

    friend std::ostream &operator<<(std::ostream &out, ChainB<T> const &x) {
        NodeB_Iter<T> iterator{x.head_c()->next_ptr()};
        for (; iterator != x.tail_c(); ++iterator) {
            out << (*iterator)() << " ";
        }
        return out;
    }

    inline NodeB<T> *head() { return this->Head; }

    inline NodeB<T> *head_c() const { return this->Head; }

    inline NodeB<T> *tail() { return this->Tail; }

    inline NodeB<T> *tail_c() const { return this->Tail; }

protected:
    NodeB<T> *Head;
    NodeB<T> *Tail;
    size_t Size;
    size_t Capacity;
};

template<typename T>
ChainB<T>::ChainB(size_t const &cap)
        : Tail{new NodeB<T>{T()}}, Head{new NodeB<T>{T()}}, Size{0}, Capacity{cap} {
    Head->link_after(*Tail);
    Tail->link_front(*Head);
}

template<typename T>
ChainB<T>::ChainB(const ChainB<T> &op)
        : Tail{op.Tail}, Head{op.Head}, Size{op.Size}, Capacity{op.Capacity} {}

template<typename T>
bool ChainB<T>::empty() const {
    return this->Size == 0;
}

template<typename T>
size_t ChainB<T>::size() const {
    return this->Size;
}

template<typename T>
size_t ChainB<T>::find(const T &x) const {
    NodeB<T> *iterator = this->Head;
    for (auto iter = 0; iter != this->Size; iter++) {
        iterator = iterator->next_ptr();
        if ((*iterator)() == x) return iter;
    }
    return -1;
}

template<typename T>
void ChainB<T>::erase(size_t const &x) {
    if (0 > x || x >= this->Size) throw;
    auto iterator = this->Head;
    for (auto iter = 0; iter != x; iter++) {
        iterator = &iterator->next();
    }
    iterator->link_after(iterator->next().next());
    iterator->next().link_front(*iterator);
    this->Size -= 1;
}

template<typename T>
void ChainB<T>::insert(size_t const &index, T const &elem) {
    if (0 > index || index > this->Size) throw;
    if (this->Capacity == this->Size) throw;
    NodeB<T> *iterator = this->Head;
    NodeB<T> *temp = nullptr;
    for (auto iter = 0; iter != index; iter++) {
        iterator = iterator->next_ptr();
    }
    iterator->link_after(*(new NodeB<T>(elem, iterator, iterator->next_ptr())));
    this->Size += 1;
}

template<typename T>
T &ChainB<T>::operator[](size_t const &x) const {
    NodeB<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; iter++) {
        iterator = iterator->next_ptr();
    }
    return (*iterator)();
}

template<typename T>
void ChainB<T>::resize(size_t const &size) {
    this->Size = size;
}

#endif //DATASTRUCTURE_CHAIN_BIDIRECTIONAL_HPP
