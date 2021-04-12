#ifndef DATASTRUCTURE_CHAIN_MOVE
#define DATASTRUCTURE_CHAIN_MOVE

#include "../../Structure/Linear/Chain_Unidirectional_Circle.hpp"

template<typename T>
class ChainMove {
public:
    explicit ChainMove(size_t const &);

    explicit ChainMove(ChainUC<T> const &);

    void move_l();

    void move_r();

    T &left_first();

    T &right_first();

    T &operator[](size_t const &);

private:
    ChainUC<T> Positive;
    ChainUC<T> Reverse;
};

template<typename T>
ChainMove<T>::ChainMove(size_t const &cap)
        : Positive{cap}, Reverse{cap} {}

template<typename T>
ChainMove<T>::ChainMove(const ChainUC<T> &op)
        : Positive{op}, Reverse{op.Capacity} {}

template<typename T>
void ChainMove<T>::move_l() {
    if (this->Reverse.size() == 0 || this->Positive.size() == this->Positive.Capacity) throw;
    this->Reverse.insert(0, this->Positive.Head->next()());
    this->Positive.erase(0);
}

template<typename T>
void ChainMove<T>::move_r() {
    if (this->Positive.size() == 0 || this->Reverse.size() == this->Reverse.Capacity) throw;
    this->Positive.insert(0, this->Reverse.Head->next()());
    this->Reverse.erase(0);
}

template<typename T>
T &ChainMove<T>::left_first() {
    return this->Reverse.Head->next()();
}

template<typename T>
T &ChainMove<T>::right_first() {
    return this->Positive.Head->next()();
}

template<typename T>
T &ChainMove<T>::operator[](size_t const &x) {
    int index;
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

#endif //DATASTRUCTURE_CHAIN_MOVE_HPP
