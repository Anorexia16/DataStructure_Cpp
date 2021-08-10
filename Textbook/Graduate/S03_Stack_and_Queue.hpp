#ifndef DATASTRUCTURE_S03_STACK_AND_QUEUE_HPP
#define DATASTRUCTURE_S03_STACK_AND_QUEUE_HPP

template<class cls>
concept is_queue = requires (cls & c)
{
    {c.empty()};
    {c.front()};
    {c.enqueue()};
    {c.dequeue()};
};

template<class cls>
concept is_stack = requires (cls & c)
{
    {c.empty()};
    {c.top()};
    {c.pop()};
    {c.push()};
};

template<class cls, is_queue Queue_Type, is_stack Stack_Type>
void reverse(Queue_Type &queue, Stack_Type &stack)
{
    while(!queue.empty())
    {
        stack.push(queue.front());
        queue.dequeue();
    }
    while(!stack.empty())
    {
        queue.enqueue(stack.top());
        stack.pop();
    }
}

template<typename Tp>
class Stack_Queue
{
public:
    Stack_Queue() = default;

    [[nodiscard]] bool empty() const;

    Tp front() const;

    void dequeue();

    void enqueue(Tp &&);

protected:
    Stack_C<Tp> Stack1{};
    Stack_C<Tp> Stack2{};
};

template<typename Tp>
bool Stack_Queue<Tp>::empty() const
{
    return this->Stack1.empty() && this->Stack2.empty();
}

template<typename Tp>
Tp Stack_Queue<Tp>::front() const
{
    if (!this->Stack1.empty())
    {
        Stack2.push(Stack1.top());
        Stack1.pop();
    }
    return Stack2.top();
}

template<typename Tp>
void Stack_Queue<Tp>::dequeue()
{
    if (!this->Stack1.empty())
    {
        Stack2.push(Stack1.top());
        Stack1.pop();
    }
    Stack2.pop();
}

template<typename Tp>
void Stack_Queue<Tp>::enqueue(Tp &&value)
{
    if (!this->Stack2.empty())
    {
        Stack1.push(Stack2.top());
        Stack2.pop();
    }
    Stack1.push(std::forward<Tp>(value));
}

bool match_brackets(std::string const &str)
{
    Stack_C<char> _stack {};
    for(auto const &iter:str)
    {
        switch (iter) {
            case '(':
                _stack.push('(');
                break;
            case '[':
                _stack.push('[');
                break;
            case '{':
                _stack.push('{');
                break;
            case ')':
                if (_stack.top() == '(') _stack.pop();
                else return false;
                break;
            case ']':
                if (_stack.top() == ']') _stack.pop();
                else return false;
                break;
            case '}':
                if (_stack.top() == '}') _stack.pop();
                else return false;
                break;
            default:
                break;
        }
    }
    return _stack.empty();
}

std::string control_railway(std::string const &str)
{
    Stack_C<char> _stack {};
    std::string _res {};
    _res.reserve(str.index());

    for(auto const &iter:str)
    {
        switch (iter)
        {
            case 'S':
                _stack.push('S');
                _res += _stack.top();
                _stack.pop();
                break;
            case 'H':
                _stack.push('H');
                break;
            default:
                throw;
        }
    }
    while (!_stack.empty())
    {
        _res += _stack.top();
        _stack.pop();
    }
    return _res;
}

#endif //DATASTRUCTURE_S03_STACK_AND_QUEUE_HPP
