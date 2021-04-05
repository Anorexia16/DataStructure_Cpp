#ifndef DATASTRUCTURE_CHAIN_B
#define DATASTRUCTURE_CHAIN_B

#include "Abstract_Linear_List.hpp"
#include "Node_Bidirectional.hpp"

template<typename T>
class ChainB : public LinearList<T>
{
public:
    explicit ChainB(size_t const &);

    ChainB(ChainB<T> const &);

    ~ChainB() = default;

    void resize(size_t const &);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    size_t find(T const &) const;

    void erase(size_t const &);

    void insert(size_t const &, T const &);

    T &operator[](size_t const &);

    friend std::ostream &operator<<(std::ostream &out, ChainB<T> const &x)
    {
        NodeB_Iter<T> iterator{x.head_c()->next_ptr()};
        for (; iterator != x.tail_c(); ++iterator)
        {
            out << (*iterator)() << " ";
        }
        return out;
    }

    NodeB<T> *Head;

    NodeB<T> *Tail;

protected:
    size_t Size;
};

template<typename T>
ChainB<T>::ChainB(size_t const &cap)
        : Tail{new NodeB<T>{T()}}, Head{new NodeB<T>{T()}}, Size{0}
{
    Head->Next = Tail;
    Tail->Prev = Head;
}

template<typename T>
ChainB<T>::ChainB(const ChainB<T> &op)
        : Tail{op.Tail}, Head{op.Head}, Size{op.Size} {}

template<typename T>
bool ChainB<T>::empty() const
{
    return this->Size == 0;
}

template<typename T>
size_t ChainB<T>::size() const
{
    return this->Size;
}

template<typename T>
size_t ChainB<T>::find(const T &x) const
{
    NodeB<T> *iterator = this->Head->Next;
    for (auto iter = 0; iter != this->Size; ++iter)
    {
        iterator = iterator->Next;
        if (iterator->Element == x) return iter;
    }
    return -1;
}

template<typename T>
void ChainB<T>::erase(size_t const &x)
{
    if (0 > x || x >= this->Size) throw;
    auto iterator = this->Head;
    for (auto iter = 0; iter != x; ++iter)
    {
        iterator = iterator->Next;
    }
    iterator->Next = iterator->Next->Next;
    iterator->Next->Prev = iterator;
    --this->Size;
}

template<typename T>
void ChainB<T>::insert(size_t const &index, T const &elem)
{
    if (0 > index || index > this->Size) throw;
    NodeB<T> *iterator = this->Head;
    for (auto iter = 0; iter != index; ++iter, iterator = iterator->Next);
    iterator->Next = new NodeB<T> {elem, iterator, iterator->Next};
    iterator->Next->Next->Prev = iterator->Next;
    ++this->Size;
}

template<typename T>
T &ChainB<T>::operator[](size_t const &x)
{
    NodeB<T> *iterator = this->Head->Next;
    for (auto iter = 0; iter != x; ++iter, iterator = iterator->Next);
    return iterator->Element;
}

template<typename T>
void ChainB<T>::resize(size_t const &size)
{
    this->Size = size;
}

#endif //DATASTRUCTURE_CHAIN_BIDIRECTIONAL_HPP
