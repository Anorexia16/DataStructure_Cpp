#ifndef DATASTRUCTURE_SECTION3_LINEAR_CHAIN_HPP
#define DATASTRUCTURE_SECTION3_LINEAR_CHAIN_HPP

#include "../../Structure/Linear/Chain_Unidirectional_Circle.hpp"
#include "../../Structure/Linear/Chain_Bidirectional_Circle.hpp"
#include "../../Structure/Linear/Array_List.hpp"
#include "../../Structure/Assistance/Node_Bidirectional.hpp"

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

    static ChainU03<T> meld(ChainU03<T> &, ChainU03<T> &);

    ChainU03<T> merge(ChainU03<T> &);

    static ChainU03<T> merge(ChainU03<T> &, ChainU03<T> &);

    std::pair<ChainU03<T>, ChainU03<T>> split();

    static std::pair<ChainU03<T>, ChainU03<T>> split(ChainU03<T> const &);

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
// (f,a,b,c,d,e)  (f,a,b,g,c,d,e)  (f,a,b,g,c,d,e,h)  (a,b,g,c,d,e,h)  (a,b,g,mod_five,e,h)

// 3.2
template<typename T>
void ChainU03<T>::set_size(int const &x)
{
    NodeU<T> *iterator = this->Head;
    if (x < this->Size)
    {
        for (auto iter = 0; iter != x; ++iter) iterator = iterator->Next;
        iterator->Next = this->Head;
    } else {
        for (auto iter = 0; iter != this->Size; ++iter) iterator = iterator->Next;
        for (auto iter = 0; iter != x - this->Size; ++iter)
        {
            iterator->Next = new NodeU<T> {};
            iterator = iterator->Next;
        }
    }
    this->Size = x;
}

// 3.3
template<typename T>
void ChainU03<T>::set(int const &index, T const &elem)
{
    if (index < 0 || index >= this->Size) throw;
    NodeU<T> *iterator = this->Head->Next;
    for (auto iter = 0; iter != index; ++iter)
    {
        iterator = iterator->Next;
    }
    iterator->Element = elem;
}

// 3.4
template<typename T>
void ChainU03<T>::remove_range(int const &u, const T &v)
{
    if (u < 0 || u >= this->Size || v < 0 || v >= this->Size || v < u) throw;
    if (u == v) {
        this->erase(u);
    } else {
        NodeU<T> *iteratorU = this->Head;
        for (auto iter = 0; iter != u; ++iter)
        {
            iteratorU = iteratorU->Next;
        }
        NodeU<T> *iteratorV = iteratorU;
        for (auto iter = 0; iter != v; ++iter)
        {
            iteratorV = iteratorV->Next;
        }
        iteratorU->Next = iteratorV->Next;
    }
    this->Size -= v - u;
}

// 3.5
template<typename T>
int ChainU03<T>::last_index(const T &x) const {
    NodeU<T> *iterator = &this->Head;
    int index = -1;
    for (auto iter = 0; iter != this->Size; ++iter)
    {
        iterator = iterator->Next;
        if (iterator->Element == x) index = iter;
    }
    return index;
}

// 3.6
template<typename T>
T &ChainU03<T>::operator[](int const &x) const
{
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; ++iter)
    {
        iterator = iterator->Next;
    }
    return iterator->Next;
}

// 3.7
template<typename T>
bool ChainU03<T>::operator==(const ChainU03<T> &op) const {
    if (this->Size != op.Size) return false;
    NodeU<T> *iterator_this = &this->Head;
    NodeU<T> *iterator_op = op.Head;
    for (; iterator_op != op.Head; iterator_this = iterator_this->Next, iterator_op = iterator_op->Next)
    {
        if (iterator_this->Element != iterator_op->Element) return false;
    }
    return true;
}

// 3.8
template<typename T>
bool ChainU03<T>::operator!=(const ChainU03<T> &op) const {
    if (this->Size != op.Size) return true;
    NodeU<T> *iterator_this = &this->Head;
    NodeU<T> *iterator_op = op.Head;
    for (; iterator_op != op.Head; iterator_this = iterator_this->Next, iterator_op = iterator_op->Next)
    {
        iterator_this = iterator_this->Next;
        iterator_op = iterator_op->Next;
        if (iterator_this->Element != iterator_op->Element) return true;
    }
    return false;
}

// 3.9
template<typename T>
bool ChainU03<T>::operator<(const ChainU03<T> &op) const {
    NodeU<T> *iterator_this = &this->Head;
    NodeU<T> *iterator_op = op.Head;
    for (; iterator_op != op.Head && iterator_this != this->Head;
           iterator_this = iterator_this->Next, iterator_op = iterator_op->Next)
    {
        iterator_this = iterator_this->Next;
        iterator_op = iterator_op->Next;
        if (iterator_this->Element < iterator_op->Element) return true;
    }
    return this->Size < op.Size;
}

// 3.10
template<typename T>
void ChainU03<T>::swap(ChainU03<T> &op)
{
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
ChainU03<T> &array_to_list(ArrayList<T> const &op)
{
    auto target = ChainU03<T>(op.Capacity);
    for (auto iter = op.Size;iter != -1; --iter)
    {
        target.insert(0, op.Container[iter]);
    }
    target.Size = op.Size;
    return target;
}

// 3.12
template<typename T>
ArrayList<T> &list_to_array(ChainU03<T> const &op)
{
    auto target = ArrayList<T>(op.Capacity);
    NodeU<T> *iterator = op.Head;
    int tick = 0;
    for (; iterator->next_ptr() != op.Head; iterator = iterator->Next)
    {
        target.insert(tick, op.Container[iterator]);
        ++tick;
    }
    target.Size = op.Size;
    return target;
}

// 3.13
template<typename T>
ChainU03<T> &ChainU03<T>::from_array(ArrayList<T> const &op)
{
    this->Capacity = op.Capacity;
    this->Size = op.Size;
    for (auto iter = op.Size; iter != -1; --iter)
    {
        this->insert(0, op.Container[iter]);
    }
    return *this;
}

template<typename T>
ArrayList<T> &ChainU03<T>::to_array()
{
    auto target = ArrayList<T>(this->Capacity);
    NodeU<T> *iterator = this->Head;
    target.Size = this->Size;
    int tick = 0;
    for (; iterator->next_ptr() != this->Head; iterator = iterator->Next)
    {
        target.insert(tick, this->Container[iterator]);
        ++tick;
    }
    return target;
}

// 3.14
template<typename T>
void ChainU03<T>::left_shift(int const &x)
{
    if (x < 0 || x >= this->Size) throw;
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; iter++)
    {
        iterator = iterator->Next;
    }
    this->Head->Next = iterator->Next;
    this->Size -= x;
}

// 3.15-16
template<typename T>
void ChainU03<T>::reverse() {
    if (this->Size == 0) return;
    NodeU<T> *iterator = this->Head->Next;
    NodeU<T> *front = this->Head;
    NodeU<T> *after = iterator->Next;
    for (auto iter = 0; iter != this->Size + 1; iter++)
    {
        iterator->Next = front;
        front = iterator;
        iterator = after;
        after = iterator->Next;
    }
}

// 3.17-18
template<typename T>
ChainU03<T> ChainU03<T>::meld(ChainU03<T> &op)
{
    return ChainU03<T>::meld(*this, op);
}

template<typename T>
ChainU03<T> ChainU03<T>::meld(ChainU03<T> &op1, ChainU03<T> &op2)
{
    ChainU03<T> container(op1.Capacity + op2.Capacity);
    NodeU<T> *iterator1 = op1.Head->Next;
    NodeU<T> *iterator2 = op2.Head->Next;
    NodeU<T> *iteratorC = container.Head->Next;
    container.Size = op1.Size + op2.Size;
    for (; iterator1 != op1.Head && iterator2 != op2.Head;
           iterator1 = iterator1->next_ptr(), iterator2 = iterator2->Next)
    {
        iteratorC->Next = new NodeU<T> {iterator1->Element};
        iteratorC = iteratorC->Next;
        iteratorC->Next = new NodeU<T> {iterator2->Element};
        iteratorC = iteratorC->Next;
    }
    if (iterator1 != op1.Head && iterator2 == op2.Head)
    {
        for (; iterator1 != op1.Head;
               iterator1 = iterator1->Next, iteratorC = iteratorC->Next)
            iteratorC->Next = new NodeU<T> {iterator1->Element};
    } else if (iterator1 == op1.Head && iterator2 != op2.Head)
    {
        for (; iterator2 != op2.Head;
               iterator2 = iterator2->Next, iteratorC = iteratorC->Next)
            iteratorC->Next = new NodeU<T> {iterator2->Element};
    }
    iteratorC->Next = container.Head;
    op1.Size = 0;
    op2.Size = 0;
    return container;
}


// 3.19-20
template<typename T>
ChainU03<T> ChainU03<T>::merge(ChainU03<T> &op)
{
    return ChainU03<T>::merge(*this, op);
}

template<typename T>
ChainU03<T> ChainU03<T>::merge(ChainU03<T> &op1, ChainU03<T> &op2)
{
    ChainU03<T> container(op1.Capacity + op2.Capacity);
    NodeU<T> *iterator1 = op1.Head->Next;
    NodeU<T> *iterator2 = op2.Head->Next;
    NodeU<T> *iteratorC = container.Head->Next;
    container.Size = op1.Size + op2.Size;
    for (; iterator1 != op1.Head && iterator2 != op2.Head;) {
        if (iterator1->Element < iterator2->Element) {
            iteratorC->Next = new NodeU<T> {iterator1->Element};
            iterator1 = iterator1->Next;
        } else {
            iteratorC->Next = new NodeU<T> {iterator2->Element};
            iterator2 = iterator2->Next;
        }
        iteratorC = iteratorC->Next;
    }
    if (iterator1 != op1.Head && iterator2 == op2.Head) {
        for (; iterator1 != op1.Head;
               iterator1 = iterator1->Next, iteratorC = iteratorC->Next)
            iteratorC->Next = new NodeU<T> {iterator1->Element};
    } else if (iterator1 == op1.Head && iterator2 != op2.Head) {
        for (; iterator2 != op2.Head;
               iterator2 = iterator2->Next, iteratorC = iteratorC->Next)
            iteratorC->Next = new NodeU<T> {iterator2->Element};
    }
    iteratorC->Next = container.Head;
    op1.Size = 0;
    op2.Size = 0;
    return container;
}

// 3.21-22
template<typename T>
std::pair<ChainU03<T>, ChainU03<T>> ChainU03<T>::split()
{
    return ChainU03::split(*this);
}

template<typename T>
std::pair<ChainU03<T>, ChainU03<T>> ChainU03<T>::split(const ChainU03<T> &op)
{
    ChainU03<T> a{op.Capacity / 2 + 1}, b{op.Capacity / 2 + 1};
    NodeU<T> *iteratorO = op.Head;
    NodeU<T> *iteratorA = a.Head;
    NodeU<T> *iteratorB = b.Head;
    bool flag = true;
    for (; iteratorO->Next != op.Head; iteratorO = iteratorO->Next)
    {
        if (flag)
        {
            iteratorA->Next = iteratorO->Next;
            iteratorA = iteratorA->Next;
            flag = false;
            a.Size += 1;
        } else {
            iteratorB->Next = iteratorO->Next;
            iteratorB = iteratorB->Next;
            flag = true;
            b.Size += 1;
        }
    }
    return std::pair<ChainU03<T>, ChainU03<T>>
            {a, b};
}

// 3.23
template<typename T>
void ChainU03<T>::circle_shift(int const &x)
{
    if (x < 0 || x > this->Size) throw;
    NodeU<T> *iteratorT = this->Head;
    NodeU<T> *iteratorH = this->Head;
    int pos = 0;
    for (; iteratorT->Next != this->Head; iteratorT = iteratorT->Next)
    {
        if (pos == x) iteratorH = iteratorT;
        pos += 1;
    }
    iteratorT->Next = this->Head->Next;
    this->Head->Next = iteratorH->Next;
    iteratorH->Next = this->Head;
}

// 3.24
// Details in:
//      ./Special_Structure/Chain_Move.hpp

// 3.25
// Details in:
//      ./Special_Structure/Chain_Move_Linear.hpp

// 3.26
// Details in:
//      ./Lib_Algorithm/Chain_Insert_Sort.hpp
//      ./Lib_Algorithm/Chain_Bubble_Sort.hpp

// 3.27 - 3.36
// pass

// 3.37
template<typename T>
void ChainU03<T>::erase2(const int &x)
{
    if (x < 0 || x >= this->size()) throw;
    int tick = 0;
    NodeU<T> *iterator = this->Head->Next;
    for (; tick != x; tick++) iterator = iterator->Next;
    if (iterator->Next == this->Head)
    {
        iterator->Element = this->Head->Next->Element;
        this->Head->Next = this->Head->Next->Next;
    } else {
        iterator->Element = this->Head->Next->Element;
        iterator->Next = iterator->Next->Next;
    }
    this->Size -= 1;
}

// 3.38-43
// skip

// 3.44
template<typename T>
void ChainB03<T>::extend(ChainB03<T> &op)
{
    if (this->Size + op.Size > this->Capacity) throw;
    NodeB<T> *iterator = op.Head->Next;
    for (; iterator != op.head(); iterator = op.Head.Next)
    {
        this->Head->Prev->Next = new NodeB<T>{iterator->Element, this->Head->Prev, this->Head};
        this->Head->Prev = this->Head->Prev.Next;
        op.Head->next = op.Head->Next->Next;
        op.Head->Next->Prev = op.Head;
    }
    this->Size += op.size();
    op.Size = 0;
}

// 3.45-33
// pass

// 3.34-35
// Details in:
//      ./Lib_Algorithm/Chain_Radix_Sort.hpp

// 3.36
// Details in:
//      ./Lib/Deck_Box_Sort.hpp

// 3.37
// Details in:
//      ./Lib/No_Limits_Calculations_C.hpp
//      ./Lib/No_Limits_Calculations_A.hpp

#endif //DATASTRUCTURE_SECTION3_LINEAR_CHAIN_HPP
