#ifndef DATASTRUCTURE_CHAIN_MOVE
#define DATASTRUCTURE_CHAIN_MOVE

#include "../../Structure/Abstract/Abstract_Linear_List.hpp"
#include "../../Structure/Linear/Chain_Unidirectional_Circle.hpp"

template<typename T>
class ChainMove : LinearList<T>, ChainUC<T> {
public:
    ~ChainMove() = default;

    [[nodiscard]] bool empty() const;

    [[nodiscard]] bool size() const;

    size_t find(T const &) const;

    void erase(size_t const &);

    void insert(const &, T

    const &);

    virtual T &operator[](size_t const &) const;

    void reset();

    T &current();

    [[nodiscard]] bool atEnd() const;

    [[nodiscard]] bool atFront() const;

    void moveToNext();

    void moveToPrevious();

private:
    ChainUC<T> Positive;
    ChainUC<T> Reverse;
};

template<typename T>
bool ChainMove<T>::empty() const {
    return this->Positive.size() + this->Reverse.size() == 0;
}

template<typename T>
bool ChainMove<T>::size() const {
    return this->Positive.size() + this->Reverse.size();
}

template<typename T>
size_t ChainMove<T>::find(const T &x) const {
    size_t tick = 0;
    NodeU<T> *iteratorR = this->Reverse.Head;
    NodeU<T> *iteratorP = this->Positive.Head;
    for (; iteratorR->next_ptr() != this->Reverse.Head;
           iteratorR = iteratorR->next_ptr())
        if (*(iteratorR)() == x) {
            return this->Reverse.size() - tick - 1;
        } else {
            tick += 1;
        }
    tick = 0;
    for (; iteratorP->next_ptr() != this->Positive.Head;
           iteratorP = iteratorP->next_ptr())
        if (*(iteratorP)() == x) {
            return this->Reverse.size() + tick;
        } else {
            tick += 1;
        }
    return -1;
}

template<typename T>
void ChainMove<T>::erase(size_t const &x) {
    NodeU<T> *iterator;
    if (x >= this->Reverse.size()) {
        x = x - this->Reverse.size();
        iterator = this->Positive.Head;
        for (auto iter = 0; iter != x; iter++) {
            iterator = iterator->next_ptr();
        }
        iterator->link(iterator->next());
    } else {
        x = this->Reverse.size() - x - 1;
        iterator = this->Reverse.Head;
        for (auto iter = 0; iter != x; iter++) {
            iterator = iterator->next_ptr();
        }
        iterator->link(iterator->next());
    }
}

template<typename T>
void ChainMove<T>::insert(size_t const &index, const T &elem) {
    NodeU<T> *iterator;
    if (index >= this->Reverse.size()) {
        index = index - this->Reverse.size();
        iterator = this->Positive.Head;
        for (auto iter = 0; iter != index; iter++) {
            iterator = iterator->next_ptr();
        }
        iterator(NodeU<T>(elem, iterator->next_ptr()));
    } else {
        index = this->Reverse.size() - index - 1;
        iterator = this->Reverse.Head;
        for (auto iter = 0; iter != index; iter++) {
            iterator = iterator->next_ptr();
        }
        iterator(NodeU<T>(elem, iterator->next_ptr()));
    }
}

template<typename T>
T &ChainMove<T>::operator[](size_t const &x) const {
    size_t index;
    NodeU<T> *iterator;
    if (x >= this->Reverse.size()) {
        index = x - this->Reverse.size();
        iterator = this->Positive.Head;
        for (auto iter = 0; iter != index; iter++) {
            iterator = iterator->next_ptr();
        }
        return (*iterator)();
    } else {
        index = this->Reverse.size() - x - 1;
        iterator = this->Reverse.Head;
        for (auto iter = 0; iter != index; iter++) {
            iterator = iterator->next_ptr();
        }
        return (*iterator)();
    }
}

template<typename T>
void ChainMove<T>::reset() {
    NodeU<T> *iterator = this->Reverse.Head->next_ptr();
    NodeU<T> *front = this->Reverse.Head;
    NodeU<T> *after = iterator->next_ptr();
    for (auto iter = 0; iter != this->Size + 1; iter++) {
        iterator->link(*front);
        front = iterator;
        iterator = after;
        after = iterator->next_ptr();
    }
    for (NodeU<T> *iter = this->Reverse.Head; iter != this->Reverse.Head;
         iter = iter->next_ptr()) {
        this->Positive.Head->link(NodeU<T>((*iter)(), this->Positive.Head->next_ptr()));
        (*iter)().~T();
    }
    this->Reverse.size() = 0;
}

template<typename T>
T &ChainMove<T>::current() {
    return this->Positive.Head->next()();
}

template<typename T>
bool ChainMove<T>::atEnd() const {
    return this->Positive.size() == 1;
}

template<typename T>
bool ChainMove<T>::atFront() const {
    return (this->Reverse.size == 0 && this->Positive.size != 0);
}

template<typename T>
void ChainMove<T>::moveToNext() {
    if (this->Positive.size() == 0 || this->Reverse.size() == this->Reverse.Capacity) throw;
    this->Positive.insert(0, this->Reverse.Head->next()());
    this->Positive.Head->link(this->Positive.Head->next_ptr()->next());
    this->Reverse.Size -= 1;
}

template<typename T>
void ChainMove<T>::moveToPrevious() {
    if (this->Reverse.size() == 0 || this->Positive.size() == this->Positive.Capacity) throw;
    this->Reverse.insert(0, this->Positive.Head->next()());
    this->Reverse.Head->link(this->Reverse.Head->next_ptr()->next());
    this->Positive.Size -= 1;
}

#endif //DATASTRUCTURE_CHAIN_MOVE_LINEAR_HPP
