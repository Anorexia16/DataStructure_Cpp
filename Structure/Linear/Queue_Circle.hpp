#ifndef DATASTRUCTURE_QUEUE_CIRCLE_HPP
#define DATASTRUCTURE_QUEUE_CIRCLE_HPP

#include <iostream>
#include <vector>
#include <array>
#include "Chain_Bidirectional_Circle.hpp"

template<typename Tp>
class Queue_CC
{
public:
    explicit Queue_CC(size_t const &);
    
    explicit Queue_CC(std::istream &&, size_t const &);

    template<class Iterable_Container>
    explicit Queue_CC(Iterable_Container const &, size_t const &);

    Queue_CC(const Tp *const &, size_t const &, size_t const &);

    void enqueue(Tp const &);

    void dequeue();

    Tp first() const;

    [[nodiscard]] inline bool full() const;

    [[nodiscard]] inline bool empty() const;

    [[nodiscard]] inline size_t size() const;

protected:
    NodeB<Tp> *First;

    NodeB<Tp> *Rear;

    size_t Size;
};

template<typename Tp>
Queue_CC<Tp>::Queue_CC(const size_t &capacity)
    :First{new NodeB<Tp> {}}, Rear{First}, Size{}
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
Queue_CC<Tp>::Queue_CC(std::istream &&in, const size_t &capacity)
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
Queue_CC<Tp>::Queue_CC(const Iterable_Container &cont, const size_t &capacity)
    :First{new NodeB<Tp> {}}, Rear{nullptr}
{
    First->Next = First;
    First->Prev = First;
    size_t size = cont.size();
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
Queue_CC<Tp>::Queue_CC(const Tp *const &ptr, const size_t &size, const size_t &capacity)
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
void Queue_CC<Tp>::enqueue(const Tp &value)
{
    if(this->full()) throw;
    Rear->Element = value;
    Rear = Rear->Next;
    ++this->Size;
}

template<typename Tp>
void Queue_CC<Tp>::dequeue()
{
    if (this->empty()) throw;
    First->Element = Tp{};
    First = First->Next;
    --this->Size;
}

template<typename Tp>
Tp Queue_CC<Tp>::first() const
{
    return First->Element;
}

template<typename Tp>
bool Queue_CC<Tp>::full() const
{
    return this->Rear == this->First && this->Size != 0;
}

template<typename Tp>
bool Queue_CC<Tp>::empty() const
{
    return this->Size == 0;
}

template<typename Tp>
size_t Queue_CC<Tp>::size() const
{
    return this->Size;
}

#endif //DATASTRUCTURE_QUEUE_CIRCLE_HPP
