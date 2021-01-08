#ifndef DATASTRUCTURE_CHAIN
#define DATASTRUCTURE_CHAIN

#include "Abstract_Linear_List.hpp"
#include "Node_Unidirectional.hpp"

template<typename T>
class ChainUC : public LinearList<T> {
public:
    explicit ChainUC(size_t const &);

    ChainUC(ChainUC<T> const &);

    ~ChainUC() = default;

    void resize(size_t const &);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    size_t find(T const &) const;

    void erase(size_t const &);

    void insert(size_t const &, T const &);

    T &operator[](size_t const &) const;

    friend std::ostream &operator<<(std::ostream &out, ChainUC<T> &x) {
        NodeU_Iter<T> iterator{x.head_c()->next_ptr()};
        for (; iterator != x.head_c(); ++iterator) {
            out << (*iterator)() << " ";
        }
        return out;
    }

    inline NodeU<T> *head() { return this->Head; }

    inline NodeU<T> *head_c() const { return this->Head; }

protected:
    NodeU<T> *Head;
    size_t Size;
    size_t Capacity;
};

template<typename T>
ChainUC<T>::ChainUC(size_t const &cap)
        : Head{new NodeU<T>{T()}}, Size{0}, Capacity{cap} {
    Head->link(*this->Head);
}

template<typename T>
ChainUC<T>::ChainUC(const ChainUC<T> &op)
        : Head{op.Head}, Size{op.Size}, Capacity{op.Capacity} {}

template<typename T>
bool ChainUC<T>::empty() const {
    return this->Size == 0;
}

template<typename T>
size_t ChainUC<T>::size() const {
    return this->Size;
}

template<typename T>
size_t ChainUC<T>::find(const T &x) const {
    NodeU<T> *iterator = &this->Head->next();
    for (auto iter = 0; iter != this->Size; iter++) {
        iterator = iterator->next_ptr();
        if ((*iterator)() == x) return iter;
    }
    return -1;
}

template<typename T>
void ChainUC<T>::erase(size_t const &x) {
    if (0 > x || x >= this->Size) throw;
    size_t xc = x + 1;
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != xc - 1; iter++) {
        iterator = &iterator->next();
    }
    iterator->link(iterator->next().next());
    this->Size -= 1;
}

template<typename T>
void ChainUC<T>::insert(size_t const &index, const T &elem) {
    if (0 > index || index > this->Size) throw;
    if (this->Capacity == this->Size) throw;
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != index; iter++) {
        iterator = &iterator->next();
    }
    iterator->link(*(new NodeU<T>(elem, iterator->next_ptr())));
    this->Size += 1;
}

template<typename T>
T &ChainUC<T>::operator[](size_t const &x) const {
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; iter++) {
        iterator = iterator->next_ptr();
    }
    return (*iterator)();
}

template<typename T>
void ChainUC<T>::resize(size_t const &x) {
    this->Size = x;
}

#endif //DATASTRUCTURE_CHAIN_UNIDIRECTIONAL_CIRCLE_HPP
