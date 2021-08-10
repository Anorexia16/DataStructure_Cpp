#ifndef DATASTRUCTURE_DEQUE_CIRCLE_HPP
#define DATASTRUCTURE_DEQUE_CIRCLE_HPP

#include <iostream>
#include <vector>
#include <array>
#include "Chain_Bidirectional_Circle.hpp"

template<typename Tp>
class Deque_CC
{
public:
    explicit Deque_CC(size_t const & = 99);

    explicit Deque_CC(std::istream &&, size_t const & = 99);

    template<class Iterable_Container>
    explicit Deque_CC(Iterable_Container const &, size_t const & = 99);

    Deque_CC(const Tp *const &, size_t const &, size_t const & = 99);

    void emplace_front(Tp const &);

    void emplace_back(Tp const &);

    void pop_front();

    void pop_back();

    Tp front() const;

    Tp back() const;

    [[nodiscard]] inline bool full() const;

    [[nodiscard]] inline bool empty() const;

    [[nodiscard]] inline size_t size() const;

protected:
    NodeB<Tp> *First;

    NodeB<Tp> *Rear;

    size_t Size;
};

template<typename Tp>
Deque_CC<Tp>::Deque_CC(const size_t &capacity)
    :First{new NodeB<Tp> {}}, Rear{nullptr}, Size{}
{
    First->Next = First;
    First->Prev = First;
    for (auto i = 0; i != capacity-1; ++i)
    {
        First->Next = new NodeB<Tp>{Tp{}, First, First->Next};
        First->Next->Next->Prev = First->Next;
    }
}

template<typename Tp>
Deque_CC<Tp>::Deque_CC(std::istream &&in, const size_t &capacity)
        : First{new NodeB<Tp> {}}, Rear{nullptr}, Size{}
{
    First->Next = First;
    First->Prev = First;
    size_t size {};
    for(Tp temp;in.good();++size)
    {
        in >> temp;
        First->Next = new NodeB<Tp>{temp, First, First->Next};
        First->Next->Next->Prev = First->Next;
    }
    for(auto i=0;i<capacity-size;++i)
    {
        First->Next = new NodeB<Tp>{Tp{}, First, First->Next};
        First->Next->Next->Prev = First->Next;
    }
    Rear = First;
}

template<typename Tp>
template<class Iterable_Container>
Deque_CC<Tp>::Deque_CC(const Iterable_Container &cont, const size_t &capacity)
        :First{new NodeB<Tp> {}}, Rear{nullptr}
{
    First->Next = First;
    First->Prev = First;
    size_t size = cont.index();
    for (auto const &iterator:cont)
    {
        First->Next = new NodeB<Tp>{iterator, First, First->Next};
        First->Next->Next->Prev = First->Next;
        First = First->Next;
    }
    for(auto i=0;i<capacity-size;++i)
    {
        First->Next = new NodeB<Tp>{Tp{}, First, First->Next};
        First->Next->Next->Prev = First->Next;
    }
    Rear = First;
    Size = size;
}

template<typename Tp>
Deque_CC<Tp>::Deque_CC(const Tp *const &ptr, const size_t &size, const size_t &capacity)
    :First{new NodeB<Tp> {}}, Rear{nullptr}
{
    for (auto i = 0; i != size; ++i)
    {
        First->Next = new NodeB<Tp>{ptr[i], First, First->Next};
        First->Next->Next->Prev = First->Next;
    }
    for(auto i=0;i<capacity-size;++i)
    {
        First->Next = new NodeB<Tp>{Tp{}, First, First->Next};
        First->Next->Next->Prev = First->Next;
    }
    Size = size;
    Rear = First;
}

template<typename Tp>
void Deque_CC<Tp>::emplace_front(const Tp &value)
{
    if (this->full()) throw;
    First = First->Prev;
    First->Element = value;
    ++this->Size;
}

template<typename Tp>
void Deque_CC<Tp>::emplace_back(const Tp &value)
{
    if (this->full()) throw;
    Rear = Rear->Next;
    Rear->Element = value;
    ++this->Size;
}

template<typename Tp>
void Deque_CC<Tp>::pop_front()
{
    if (this->empty()) throw;
    First->Element = Tp{};
    First = First->Next;
    --this->Size;
}

template<typename Tp>
void Deque_CC<Tp>::pop_back()
{
    if (this->empty()) throw;
    Rear = Rear->Prev;
    Rear = Rear->Prev;
    --this->Size;
}

template<typename Tp>
Tp Deque_CC<Tp>::front() const
{
    return First->Element;
}

template<typename Tp>
Tp Deque_CC<Tp>::back() const
{
    return Rear->Prev->Element;
}

template<typename Tp>
bool Deque_CC<Tp>::empty() const
{
    return this->Size == 0;
}

template<typename Tp>
size_t Deque_CC<Tp>::size() const
{
    return this->Size;
}

template<typename Tp>
bool Deque_CC<Tp>::full() const
{
    return Rear->Next=First && this->Size!=0;
}


#endif //DATASTRUCTURE_DEQUE_CIRCLE_HPP
