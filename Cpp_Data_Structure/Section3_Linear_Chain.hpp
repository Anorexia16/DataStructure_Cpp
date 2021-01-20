#ifndef DATASTRUCTURE_SECTION3_LINEAR_CHAIN_HPP
#define DATASTRUCTURE_SECTION3_LINEAR_CHAIN_HPP

#include "../Structure/Chain_Unidirectional_Circle.hpp"
#include "../Structure/Chain_Bidirectional_Circle.hpp"
#include "../Structure/Array_List.hpp"
#include "../Structure/Node_Bidirectional.hpp"

// assistance interface
template<typename T>
class ChainU03 : public ChainUC<T> {
public:
    explicit ChainU03(int const &);

    void set_size(int const &);

    void set(int const &, T const &);

    void remove_range(int const &, T const &);

    int last_index(T const &) const;

    T &operator[](int const &) const;

    bool operator==(ChainU03<T> const &) const;

    bool operator!=(ChainU03<T> const &) const;

    bool operator<(ChainU03<T> const &) const;

    void swap(ChainU03<T> &);

    ChainU03<T> &from_array(ArrayList<T> const &);

    ArrayList <T> &to_array();

    void left_shift(int const &);

    void reverse();

    ChainU03<T> meld(ChainU03<T> &);

    template<typename F>
    friend ChainU03<F> meld(ChainU03<F> &, ChainU03<F> &);

    ChainU03<T> merge(ChainU03<T> &);

    template<typename F>
    friend ChainU03<F> merge(ChainU03<F> &, ChainU03<F> &);

    std::pair<ChainU03<T>, ChainU03<T>> split();

    template<typename F>
    friend std::pair<ChainU03<F>, ChainU03<F>> split(ChainU03<F> const &);

    void circle_shift(int const &);

    void erase2(const int &);
};

template<typename T>
ChainU03<T>::ChainU03(int const &cap)
        : ChainUC<T>(cap) {}

template<typename T>
class ChainB03 : public ChainBC<T> {
public:
    explicit ChainB03(int const &);

    void extend(ChainB03<T> &);
};

template<typename T>
ChainB03<T>::ChainB03(int const &cap)
        : ChainBC<T>::ChainBC(cap) {}

// 3.1
// (f,a,b,c,d,e)  (f,a,b,g,c,d,e)  (f,a,b,g,c,d,e,h)  (a,b,g,c,d,e,h)  (a,b,g,c,e,h)

// 3.2
template<typename T>
void ChainU03<T>::set_size(int const &x) {
    NodeU<T> *iterator = this->Head;
    if (x < this->Size) {
        for (auto iter = 0; iter != x; iter++) iterator = iterator->next_ptr();
        iterator->link(*this->head());
    } else {
        for (auto iter = 0; iter != this->Size; iter++) iterator = &iterator->next();
        for (auto iter = 0; iter != x - this->Size; iter++) {
            iterator->link(*new NodeU<T>);
            iterator = iterator->next_ptr();
        }
    }
    this->Size = x;
}

// 3.3
template<typename T>
void ChainU03<T>::set(int const &index, T const &elem) {
    if (index < 0 || index >= this->Size) throw;
    NodeU<T> *iterator = &this->Head->next();
    for (auto iter = 0; iter != index; iter++) {
        iterator = iterator->next_ptr();
    }
    *iterator = elem;
}

// 3.4
template<typename T>
void ChainU03<T>::remove_range(int const &u, const T &v) {
    if (u < 0 || u >= this->Size || v < 0 || v >= this->Size || v < u) throw;
    if (u == v) {
        this->erase(u);
    } else {
        NodeU<T> *iteratorU = this->Head;
        for (auto iter = 0; iter != u; iter++) {
            iteratorU = iteratorU->next_ptr();
        }
        NodeU<T> *iteratorV = iteratorU;
        for (auto iter = 0; iter != v; iter++) {
            iteratorV = iteratorV->next_ptr();
        }
        iteratorU->link(iteratorV->next());
    }
    this->Size -= v - u;
}

// 3.5
template<typename T>
int ChainU03<T>::last_index(const T &x) const {
    NodeU<T> *iterator = &this->Head;
    int index = -1;
    for (auto iter = 0; iter != this->Size; iter++) {
        iterator = iterator->next_ptr();
        if ((*iterator)() == x) index = iter;
    }
    return index;
}

// 3.6
template<typename T>
T &ChainU03<T>::operator[](int const &x) const {
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; iter++) {
        iterator = iterator->next_ptr();
    }
    return (*iterator)();
}

// 3.7
template<typename T>
bool ChainU03<T>::operator==(const ChainU03<T> &op) const {
    if (this->Size != op.Size) return false;
    NodeU<T> *iterator_this = &this->Head;
    NodeU<T> *iterator_op = op.Head;
    for (; iterator_op != op.Head; iterator_this = iterator_this->next_ptr(), iterator_op = iterator_op->next_ptr()) {
        if ((*iterator_this)() != (*iterator_op)()) return false;
    }
    return true;
}

// 3.8
template<typename T>
bool ChainU03<T>::operator!=(const ChainU03<T> &op) const {
    if (this->Size != op.Size) return true;
    NodeU<T> *iterator_this = &this->Head;
    NodeU<T> *iterator_op = op.Head;
    for (; iterator_op != op.Head; iterator_this = iterator_this->next_ptr(), iterator_op = iterator_op->next_ptr()) {
        iterator_this = iterator_this->next_ptr();
        iterator_op = iterator_op->next_ptr();
        if ((*iterator_this)() != (*iterator_op)()) return true;
    }
    return false;
}

// 3.9
template<typename T>
bool ChainU03<T>::operator<(const ChainU03<T> &op) const {
    NodeU<T> *iterator_this = &this->Head;
    NodeU<T> *iterator_op = op.Head;
    for (; iterator_op != op.Head && iterator_this != this->Head;
           iterator_this = iterator_this->next_ptr(), iterator_op = iterator_op->next_ptr()) {
        iterator_this = iterator_this->next_ptr();
        iterator_op = iterator_op->next_ptr();
        if ((*iterator_this)() < (*iterator_op)()) return true;
    }
    return this->Size < op.Size;
}

// 3.10
template<typename T>
void ChainU03<T>::swap(ChainU03<T> &op) {
    if (this->Size > op.Capacity || op.Size > this->Capacity) throw;
    NodeU<T> *temp = this->Head;
    int temp_size = this->Size;
    this->Head = op.Head;
    op.Head = temp;
    this->Size = op.Size;
    op.Size = temp_size;
}

// 3.11
template<typename T>
ChainU03<T> &array_to_list(ArrayList<T>
                           const &op) {
    auto target = ChainU03<T>(op.Capacity);
    for (
            auto iter = op.Size;
            iter != -1; iter--) {
        target.insert(0, op.Container[iter]);
    }
    target.
            Size = op.Size;
    return
target;
}

// 3.12
template<typename T>
ArrayList<T> &list_to_array(ChainU03<T> const &op) {
    auto target = ArrayList<T>(op.Capacity);
    NodeU<T> *iterator = op.Head;
    int tick = 0;
    for (; iterator->next_ptr() != op.Head; iterator = iterator->next_ptr()) {
        target.insert(tick, op.Container[iterator]);
        tick++;
    }
    target.Size = op.Size;
    return target;
}

// 3.13
template<typename T>
ChainU03<T> &ChainU03<T>::from_array(ArrayList<T> const &op) {
    this->Capacity = op.Capacity;
    this->Size = op.Size;
    for (auto iter = op.Size; iter != -1; iter--) {
        this->insert(0, op.Container[iter]);
    }
    return *this;
}

template<typename T>
ArrayList<T> &ChainU03<T>::to_array() {
    auto target = ArrayList<T>(this->Capacity);
    NodeU<T> *iterator = this->Head;
    target.Size = this->Size;
    int tick = 0;
    for (; iterator->next_ptr() != this->Head; iterator = iterator->next_ptr()) {
        target.insert(tick, this->Container[iterator]);
        tick++;
    }
    return target;
}

// 3.14
template<typename T>
void ChainU03<T>::left_shift(int const &x) {
    if (x < 0 || x >= this->Size) throw;
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; iter++) {
        iterator = iterator->next_ptr();
    }
    this->Head->link(iterator->next());
    this->Size -= x;
}

// 3.15-16
template<typename T>
void ChainU03<T>::reverse() {
    if (this->Size == 0) return;
    NodeU<T> *iterator = this->Head->next_ptr();
    NodeU<T> *front = this->Head;
    NodeU<T> *after = iterator->next_ptr();
    for (auto iter = 0; iter != this->Size + 1; iter++) {
        iterator->link(*front);
        front = iterator;
        iterator = after;
        after = iterator->next_ptr();
    }
}

// 3.17-18
template<typename T>
ChainU03<T> ChainU03<T>::meld(ChainU03<T> &op) {
    return ::meld(*this, op);
}

template<typename F>
ChainU03<F> meld(ChainU03<F> &op1, ChainU03<F> &op2) {
    ChainU03<F> container(op1.Capacity + op2.Capacity);
    NodeU<F> *iterator1 = op1.Head->next_ptr();
    NodeU<F> *iterator2 = op2.Head->next_ptr();
    NodeU<F> *iteratorC = container.Head->next_ptr();
    container.Size = op1.Size + op2.Size;
    for (; iterator1 != op1.Head && iterator2 != op2.Head;
           iterator1 = iterator1->next_ptr(), iterator2 = iterator2->next_ptr()) {
        iteratorC->link(*new NodeU<F>((*iterator1)()));
        iteratorC = iteratorC->next_ptr();
        iteratorC->link(*new NodeU<F>((*iterator2)()));
        iteratorC = iteratorC->next_ptr();
    }
    if (iterator1 != op1.Head && iterator2 == op2.Head) {
        for (; iterator1 != op1.Head;
               iterator1 = iterator1->next_ptr(), iteratorC = iteratorC->next_ptr())
            iteratorC->link(*new NodeU<F>((*iterator1)()));
    } else if (iterator1 == op1.Head && iterator2 != op2.Head) {
        for (; iterator2 != op2.Head;
               iterator2 = iterator2->next_ptr(), iteratorC = iteratorC->next_ptr())
            iteratorC->link(*new NodeU<F>((*iterator2)()));
    }
    iteratorC->link(*container.Head);
    op1.Size = 0;
    op2.Size = 0;
    return container;
}


// 3.19-20
template<typename T>
ChainU03<T> ChainU03<T>::merge(ChainU03<T> &op) {
    return ::merge(*this, op);
}

template<typename F>
ChainU03<F> merge(ChainU03<F> &op1, ChainU03<F> &op2) {
    ChainU03<F> container(op1.Capacity + op2.Capacity);
    NodeU<F> *iterator1 = op1.Head->next_ptr();
    NodeU<F> *iterator2 = op2.Head->next_ptr();
    NodeU<F> *iteratorC = container.Head->next_ptr();
    container.Size = op1.Size + op2.Size;
    for (; iterator1 != op1.Head && iterator2 != op2.Head;) {
        if ((*iterator1)() < (*iterator2)()) {
            iteratorC->link(*new NodeU<F>((*iterator1)()));
            iterator1 = iterator1->next_ptr();
        } else {
            iteratorC->link(*new NodeU<F>((*iterator2)()));
            iterator2 = iterator2->next_ptr();
        }
        iteratorC = iteratorC->next_ptr();
    }
    if (iterator1 != op1.Head && iterator2 == op2.Head) {
        for (; iterator1 != op1.Head;
               iterator1 = iterator1->next_ptr(), iteratorC = iteratorC->next_ptr())
            iteratorC->link(*new NodeU<F>((*iterator1)()));
    } else if (iterator1 == op1.Head && iterator2 != op2.Head) {
        for (; iterator2 != op2.Head;
               iterator2 = iterator2->next_ptr(), iteratorC = iteratorC->next_ptr())
            iteratorC->link(*new NodeU<F>((*iterator2)()));
    }
    iteratorC->link(*container.Head);
    op1.Size = 0;
    op2.Size = 0;
    return container;
}

// 3.21-22
template<typename T>
std::pair<ChainU03<T>, ChainU03<T>> ChainU03<T>::split() {
    return ::split(*this);
}

template<typename F>
std::pair<ChainU03<F>, ChainU03<F>> split(const ChainU03<F> &op) {
    ChainU03<F> a{op.Capacity / 2 + 1}, b{op.Capacity / 2 + 1};
    NodeU<F> *iteratorO = op.Head;
    NodeU<F> *iteratorA = a.Head;
    NodeU<F> *iteratorB = b.Head;
    bool flag = true;
    for (; iteratorO->next_ptr() != op.Head; iteratorO = iteratorO->next_ptr()) {
        if (flag) {
            iteratorA->link(iteratorO->next());
            iteratorA = iteratorA->next_ptr();
            flag = false;
            a.Size += 1;
        } else {
            iteratorB->link(iteratorO->next());
            iteratorB = iteratorB->next_ptr();
            flag = true;
            b.Size += 1;
        }
    }
    return std::pair<ChainU03<F>, ChainU03<F>>
            {a, b};
}

// 3.23
template<typename T>
void ChainU03<T>::circle_shift(int const &x) {
    if (x < 0 || x > this->Size) throw;
    NodeU<T> *iteratorT = this->Head;
    NodeU<T> *iteratorH = this->Head;
    int pos = 0;
    for (; iteratorT->next_ptr() != this->Head; iteratorT = iteratorT->next_ptr()) {
        if (pos == x) iteratorH = iteratorT;
        pos += 1;
    }
    iteratorT->link(this->Head->next());
    this->Head->link(iteratorH->next());
    iteratorH->link(*this->head());
}

// 3.24
// Details in:
//      ./Special_Structure/Chain_Move.hpp

// 3.25
// Details in:
//      ./Special_Structure/Chain_Move_Linear.hpp

// 3.26
// Details in:
//      ./Algorithm/Chain_Insert_Sort.hpp
//      ./Algorithm/Chain_Bubble_Sort.hpp

// 3.27 - 3.36
// pass

// 3.37
template<typename T>
void ChainU03<T>::erase2(const int &x) {
    if (x < 0 || x >= this->size()) throw;
    int tick = 0;
    NodeU<T> *iterator = this->Head->next_ptr();
    for (; tick != x; tick++) iterator = iterator->next_ptr();
    if (iterator->next_ptr() == this->Head) {
        (*iterator)() = this->head()->next()();
        this->head()->link(this->head()->next_ptr()->next());
    } else {
        (*iterator)() = this->head()->next()();
        iterator->link(iterator->next_ptr()->next());
    }
    this->Size -= 1;
}

// 3.38-43
// skip

// 3.44
template<typename T>
void ChainB03<T>::extend(ChainB03<T> &op) {
    if (this->Size + op.Size > this->Capacity) throw;
    NodeB<T> *iterator = op.head()->next_ptr();
    for (; iterator != op.head(); iterator = op.head()->next_ptr()) {
        this->head()->prev().link_after(*new NodeB<T>{(*iterator)(), this->head()->prev_ptr(), this->head()});
        this->head()->link_front(this->head()->prev().next());
        op.head()->link_after(op.head()->next().next());
        op.head()->next_ptr()->link_front(*op.head());
    }
    this->Size += op.size();
    op.Size = 0;
}

// 3.45-33
// pass

// 3.34-35
// Details in:
//      ./Algorithm/Chain_Radix_Sort.hpp

// 3.36
// Details in:
//      ./Lib/Deck_Box_Sort.hpp

// 3.37
// Details in:
//      ./Lib/No_Limits_Calculations_C.hpp
//      ./Lib/No_Limits_Calculations_A.hpp

#endif //DATASTRUCTURE_SECTION3_LINEAR_CHAIN_HPP
