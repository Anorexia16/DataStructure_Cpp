#ifndef DATASTRUCTURE_DEQUE_CHAIN_HPP
#define DATASTRUCTURE_DEQUE_CHAIN_HPP

#include <iostream>
#include "../Assistance/Node_Bidirectional.hpp"

template<typename Tp>
class Deque_C {
public:
    Deque_C();

    explicit Deque_C(std::istream &&);

    template<class Iterable_Container>
    explicit Deque_C(Iterable_Container const &);

    Deque_C(const Tp *const &, size_t const &);

    void emplace_front(Tp const &);

    void emplace_back(Tp const &);

    void pop_front();

    void pop_back();

    Tp front() const;

    Tp back() const;

    [[nodiscard]] inline bool empty() const;

    [[nodiscard]] inline size_t size() const;

protected:
    NodeB<Tp> *Head;

    size_t Size;
};

template<typename Tp>
Deque_C<Tp>::Deque_C()
    :Head{new NodeB<Tp> {}}, Size{}
{
    Head->Next = Head;
    Head->Prev = Head;
}

template<typename Tp>
Deque_C<Tp>::Deque_C(std::istream &&in)
    :Head{new NodeB<Tp> {}}, Size{}
{
    Head->Next = Head;
    Head->Prev = Head;

    Tp temp{};
    size_t size {};
    for(NodeB<Tp> *bi {Head};in.good();++bi, ++size)
    {
        in >> temp;
        bi->Next = new NodeB<Tp>{temp, bi->Next};
        bi->Next->Next->Prev = bi->Next;
    }
    this->Size = size;
}

template<typename Tp>
template<class Iterable_Container>
Deque_C<Tp>::Deque_C(const Iterable_Container &list)
        :Head{new NodeB<Tp> {}}, Size{}
{
    Head->Next = Head;
    Head->Prev = Head;

    NodeB<Tp> *bi {Head};
    for(auto const &ci:list)
    {
        bi->Next = new NodeB<Tp>{ci, bi->Next};
        bi->Next->Next->Prev = bi->Next;
        ++bi;
    }
    this->Size = list.size();
}

template<typename Tp>
Deque_C<Tp>::Deque_C(const Tp *const &ptr, const size_t &size)
        :Head{new NodeB<Tp> {}}, Size{size}
{
    Head->Next = Head;
    Head->Prev = Head;

    NodeB<Tp> *bi {Head};
    for(auto i=0;i!=size;++i)
    {
        bi->Next = new NodeB<Tp>{ptr[i], bi->Next};
        bi->Next->Next->Prev = bi->Next;
        ++bi;
    }
    this->Size = size;
}

template<typename Tp>
void Deque_C<Tp>::emplace_front(const Tp &value)
{
    NodeB<Tp> *_iter {this->Head};
    _iter->Next = new NodeB<Tp>{value, _iter, _iter->Next};
    _iter->Next->Next->Prev = _iter->Next;
    ++this->Size;
}

template<typename Tp>
void Deque_C<Tp>::emplace_back(const Tp &value)
{
    NodeB<Tp> *_iter {this->Head};
    _iter->Prev = new NodeB<Tp>{value, _iter->Prev, _iter};
    _iter->Prev->Prev->Next = _iter->Prev;
    ++this->Size;
}

template<typename Tp>
void Deque_C<Tp>::pop_front()
{
    if (this->empty()) throw;
    NodeB<Tp> *_iter {this->Head};
    _iter->Next = _iter->Next->Next;
    _iter->Next->Prev = _iter;
    --this->Size;
}

template<typename Tp>
void Deque_C<Tp>::pop_back()
{
    if (this->empty()) throw;
    NodeB<Tp> *_iter {this->Head};
    _iter->Prev = _iter->Prev->Prev;
    _iter->Prev->Next = _iter;
    --this->Size;
}

template<typename Tp>
Tp Deque_C<Tp>::front() const
{
    return this->Head->Next->Element;
}

template<typename Tp>
Tp Deque_C<Tp>::back() const
{
    return this->Head->Prev->Element;
}

template<typename Tp>
bool Deque_C<Tp>::empty() const
{
    return this->Size == 0;
}

template<typename Tp>
size_t Deque_C<Tp>::size() const
{
    return this->Size;
}


#endif //DATASTRUCTURE_DEQUE_CHAIN_HPP
