#ifndef DATASTRUCTURE_QUEUE_CHAIN_HPP
#define DATASTRUCTURE_QUEUE_CHAIN_HPP

#include <iostream>
#include "../Assistance/Node_Bidirectional.hpp"

template<typename Tp>
class Queue_C
{
public:
    Queue_C();

    explicit Queue_C(std::istream &&);

    template<class Iterable_Container>
    explicit Queue_C(Iterable_Container const &);

    Queue_C(const Tp * const &, size_t const &);
    
    void enqueue(Tp const & = *new Tp {});
    
    void dequeue();
    
    Tp front() const;
    
    [[nodiscard]] inline bool empty() const;
    
    [[nodiscard]] inline size_t size() const;

protected:
    NodeB<Tp> *Head;

    size_t Size;
};

template<typename Tp>
Queue_C<Tp>::Queue_C() 
    :Head{new NodeB<Tp> {}}, Size{}
{
    Head->Prev = Head;
    Head->Next = Head;
}

template<typename Tp>
Queue_C<Tp>::Queue_C(std::istream &&in)
    :Head{new NodeB<Tp> {}}, Size{}
{
    NodeB<Tp> *bi {Head};
    size_t size {};
    Tp temp;

    Head->Prev = Head;
    Head->Next = Head;
    for(;in.good(); ++bi, ++size)
    {
        in >> temp;
        bi->Next = new NodeB<Tp> {temp, bi->Next};
        bi->Next->Next->Prev = bi->Next;
    }
    Size = size;
}

template<typename Tp>
template<class Iterable_Container>
Queue_C<Tp>::Queue_C(const Iterable_Container &list)
        :Head{new NodeB<Tp> {}}, Size{}
{
    NodeB<Tp> *bi {Head};
    for(auto const &ci:list)
    {
        bi->Next = new NodeB<Tp> {ci, bi->Next};
        bi->Next->Next->Prev = bi->Next;
        ++bi;
    }
    Size = list.size();
}

template<typename Tp>
Queue_C<Tp>::Queue_C(const Tp *const &ptr, const size_t &size)
        :Head{new NodeB<Tp> {}}, Size{}
{
    NodeB<Tp> *bi {Head};
    for(auto i=0;i!=size;++i)
    {
        bi->Next = new NodeB<Tp> {ptr[i], bi->Next};
        bi->Next->Next->Prev = bi->Next;
        ++bi;
    }
    Size = size;
}

template<typename Tp>
void Queue_C<Tp>::enqueue(Tp const &value)
{
    Head->Prev = new NodeB<Tp>{value, Head->Prev, &*Head};
    Head->Prev->Prev->Next = Head->Prev;
    ++this->Size;
}

template<typename Tp>
void Queue_C<Tp>::dequeue()
{
    if (this->empty()) throw;
    Head->Next = Head->Next->Next;
    Head->Next->Prev = Head;
    --this->Size;
}

template<typename Tp>
Tp Queue_C<Tp>::front() const
{
    return this->Head->Next->Element;
}

template<typename Tp>
bool Queue_C<Tp>::empty() const
{
    return this->Size == 0;
}

template<typename Tp>
size_t Queue_C<Tp>::size() const
{
    return this->Size;
}

#endif //DATASTRUCTURE_QUEUE_CHAIN_HPP
