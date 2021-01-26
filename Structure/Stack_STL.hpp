#ifndef DATASTRUCTURE_STACK
#define DATASTRUCTURE_STACK

#include<ostream>
#include<deque>

template<typename T,
        template<typename elem, typename = std::allocator<elem> > class Cont = std::deque>
class Stack {
public:
    Stack();

    Stack(const Stack &) = delete;

    Stack(Stack &&) = delete;

    ~Stack() = default;

    explicit Stack(Stack<T> const &);

    [[nodiscard]] bool empty() const;

    void push(T const &);

    [[nodiscard]] size_t size() const;

    void pop();

    T top() const;

    Cont<T> &operator*() { return Container; }

    Cont<T> *operator->() { return &Container; }

    template<typename T2, template<typename, typename> class Cont2>
    friend std::ostream &operator<<(std::ostream &, Stack<T2, Cont2> const &);

    template<typename T2, template<typename, typename> class cont2>
    Stack<T, Cont> &operator=(Stack<T2, cont2> const &);

protected:
    Cont<T> Container;
};

template<typename T, template<typename elem, typename = std::allocator<elem>> class Cont>
Stack<T, Cont>::Stack(): Container{Cont < T > {}} {}

template<typename T, template<typename, typename> class Cont>
Stack<T, Cont>::Stack(Stack<T> const &x) = default;

template<typename T, template<typename, typename> class Cont>
inline bool Stack<T, Cont>::empty() const {
    return Container.empty();
}

template<typename T, template<typename, typename> class Cont>
void Stack<T, Cont>::push(T const &x) {
    Container.emplace_back(x);
}

template<typename T, template<typename, typename> class Cont>
size_t Stack<T, Cont>::size() const {
    return Container.Size();
}

template<typename T, template<typename, typename> class Cont>
void Stack<T, Cont>::pop() {
    if (this->empty()) {
        throw std::out_of_range("Stack is empty");
    }
    Container.pop_back();
}

template<typename T, template<typename, typename> class Cont>
T Stack<T, Cont>::top() const {
    if (this->empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return Container.back();
}

template<typename T2, template<typename, typename> class Cont2>
std::ostream &operator<<(std::ostream &out, Stack<T2, Cont2> const &x) {
    for (auto &&iter: x.Container) out << iter << ' ';
    return out;
}

template<typename T, template<typename, typename> class Cont>
template<typename T2, template<typename, typename> class cont2>
Stack<T, Cont> &Stack<T, Cont>::operator=(Stack<T2, cont2> const &x) {
    if ((void *) this == (void *) x) { return *this; }
    this->Container.clear();
    for (auto &&iter: x.Container) this->Container.emplace_back(static_cast<T>(iter));
    return *this;
}

#endif //DATASTRUCTURE_STACK_H
