#ifndef DATASTRUCTURE_SHARED_STACK_HPP
#define DATASTRUCTURE_SHARED_STACK_HPP

#include "../Assistance/Node_Bidirectional.hpp"

template<typename Tp>
class Static_Shared_Stack
{
public:
    explicit Static_Shared_Stack(size_t const &);

    void push(size_t, Tp const &);

    Tp top(size_t) const;

    void pop(size_t);

    [[nodiscard]] bool empty(size_t) const;

    [[nodiscard]] bool full() const;

protected:
    NodeB<Tp> *Bottom;

    NodeB<Tp> *Right;

    NodeB<Tp> *Left;
};

template<typename Tp>
Static_Shared_Stack<Tp>::Static_Shared_Stack(size_t const &capacity)
:Bottom{new NodeB<Tp> {}}, Left{Bottom}, Right{Bottom}
{
    for(size_t i =0;i!=capacity-1;++i)
    {
        Bottom->Next = new NodeB<Tp> {Tp{}, Bottom, Bottom->Next};
        Bottom->Next->Next->Prev = Bottom->Next;
    }
}

template<typename Tp>
void Static_Shared_Stack<Tp>::push(size_t num, const Tp &value)
{
    switch (num)
    {
        case 0:
            Left = Left->Prev;
            Left->Element = value;
            break;
        case 1:
            Right = Right->Next;
            Right->Element = value;
            break;
        default:
            return;
    }
}

template<typename Tp>
Tp Static_Shared_Stack<Tp>::top(size_t num) const
{
    switch(num)
    {
        case 0:
            return Left->Element;
        case 1:
            return Right->Element;
        default:
            return Tp{};
    }
}

template<typename Tp>
void Static_Shared_Stack<Tp>::pop(size_t num)
{
    switch(num)
    {
        case 0:
            Left = Tp{};
            Left = Left->Next;
            break;
        case 1:
            Right = Tp{};
            Right = Right->Prev;
            break;
        default:
            return;
    }
}

template<typename Tp>
bool Static_Shared_Stack<Tp>::empty(size_t num) const
{
    switch (num)
    {
        case 0:
            return Left == Bottom;
        case 1:
            return Right == Bottom;
        default:
            return false;
    }
}

template<typename Tp>
bool Static_Shared_Stack<Tp>::full() const
{
    return Left->Next == Right;
}

template<typename Tp>
class Shared_Stack
{
public:
    Shared_Stack();

    void push(size_t, Tp const &);

    Tp top(size_t) const;

    void pop(size_t);

    [[nodiscard]] bool empty(size_t) const;

    [[nodiscard]] bool full() const;
protected:
    NodeB<Tp> *Bottom;

    NodeB<Tp> *Left;

    NodeB<Tp> *Right;
};

template<typename Tp>
Shared_Stack<Tp>::Shared_Stack()
:Bottom{new NodeB<Tp> {}}, Left{Bottom}, Right{Bottom} {}

template<typename Tp>
void Shared_Stack<Tp>::push(size_t num, const Tp &value)
{
    switch (num)
    {
        case 0:
            Left->Prev = new NodeB<Tp> {value, Left->Prev, Left};
            Left->Prev->Prev->Next = Left->Prev;
            Left = Left->Prev;
            return;
        case 1:
            Right->Next = new NodeB<Tp> {value, Right, Right->Next};
            Right->Next->Next->Prev = Right->Next;
            Right = Right->Next;
            return;
        default:
            return;
    }
}

template<typename Tp>
Tp Shared_Stack<Tp>::top(size_t num) const
{
    switch (num)
    {
        case 0:
            return Left->Element;
        case 1:
            return Right->Element;
        default:
            return;
    };
}

template<typename Tp>
void Shared_Stack<Tp>::pop(size_t num)
{
    switch (num)
    {
        case 0:
            Left->Next->Prev = Left->Prev;
            Left->Prev->Next = Left->Next;
            Left = Left->Next;
            return;
        case 1:
            Right->Next->Prev = Right->Prev;
            Right->Prev->Next = Right->Next;
            Right = Right->Prev;
            return;
        default:
            return;
    }
}

template<typename Tp>
bool Shared_Stack<Tp>::empty(size_t num) const
{
    switch (num)
    {
        case 0:
            return Left == Bottom;
        case 1:
            return Right == Bottom;
        default:
            return false;
    }
}

template<typename Tp>
bool Shared_Stack<Tp>::full() const
{
    return false;
}


#endif //DATASTRUCTURE_SHARED_STACK_HPP
