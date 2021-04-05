#ifndef DATASTRUCTURE_STACK_CHAIN_HPP
#define DATASTRUCTURE_STACK_CHAIN_HPP

#include "Node_Unidirectional.hpp"

template<typename T>
class Stack_C
{
public:
    Stack_C();

    void push(T const & = *new T{});

    T top() const;

    void pop();

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

protected:
    NodeU<T> *Top;

    NodeU<T> *Bottom;

    size_t Size;
};

template<typename T>
Stack_C<T>::Stack_C()
        : Bottom{new NodeU<T> {}}, Top{Bottom}, Size{} {}

template<typename T>
void Stack_C<T>::push(T const &x)
{
    auto *_new = new NodeU<T> {x, Top};
    Top = _new;
    ++Size;
}

template<typename T>
T Stack_C<T>::top() const
{
    return this->Top->Element;
}

template<typename T>
void Stack_C<T>::pop()
{
    if (this->empty()) throw;
    this->Top = this->Top->Next;
    --Size;
}

template<typename T>
bool Stack_C<T>::empty() const
{
    return this->Top == this->Bottom;
}

template<typename T>
size_t Stack_C<T>::size() const
{
    return this->Size;
}


#endif //DATASTRUCTURE_STACK_CHAIN_HPP
