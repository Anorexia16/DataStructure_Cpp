#ifndef DATASTRUCTURE_STACK_CHAIN_HPP
#define DATASTRUCTURE_STACK_CHAIN_HPP

#include "Chain_Unidirectional_Circle.hpp"

template<typename T>
class Stack_C {
    Stack_C();

    void push(T const &);

    T top() const;

    void pop();

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    friend std::ostream &operator<<(std::ostream &out, Stack_C<T> const &op) {
        for (NodeU_Iter<T> iterator{op.Container.head_c()->next_ptr()}; iterator != op.Container.head_c(); ++iterator) {
            out << iterator.value_c();
        }
        out << std::endl;
        return out;
    }

protected:
    ChainUC<T> Container;
};

template<typename T>
Stack_C<T>::Stack_C()
        : Container{ChainUC<T>(100)} {}

template<typename T>
void Stack_C<T>::push(T const &x) {
    this->Container.insert(0, x);
}

template<typename T>
T Stack_C<T>::top() const {
    return this->Container.head_c()->next()();
}

template<typename T>
void Stack_C<T>::pop() {
    this->Container.erase(0);
}

template<typename T>
bool Stack_C<T>::empty() const {
    return this->Container.size() == 0;
}

template<typename T>
size_t Stack_C<T>::size() const {
    return this->Container.size();
}


#endif //DATASTRUCTURE_STACK_CHAIN_HPP
