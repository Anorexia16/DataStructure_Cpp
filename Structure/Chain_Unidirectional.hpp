#ifndef DATASTRUCTURE_CHAIN_U
#define DATASTRUCTURE_CHAIN_U

#include "Abstract_Linear_List.hpp"
#include "Node_Unidirectional.hpp"

template<typename T>
class ChainU : public LinearList<T>
{
public:
    explicit ChainU(size_t const &);

    ChainU(ChainU<T> const &);

    void resize(size_t const &);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    size_t find(T const &) const;

    void erase(size_t const &);

    void insert(size_t const &, T const &);

    T &operator[](size_t const &);

    friend std::ostream &operator<<(std::ostream &out, ChainU<T> const &x)
    {
        NodeU_Iter<T> iterator{x.head_c()->next_ptr()};
        for (; iterator != x.tail_c(); ++iterator)
        {
            out << (*iterator)() << " ";
        }
        return out;
    }

    NodeU<T> *Head;

    NodeU<T> *Tail;

protected:

    size_t Size;
};

template<typename T>
ChainU<T>::ChainU(size_t const &cap)
        : Tail{new NodeU<T>{T()}}, Head{new NodeU<T>{T()}}, Size{0}
{
    Head->Next = Tail;
}

template<typename T>
ChainU<T>::ChainU(const ChainU<T> &op)
        : Tail{op.Tail}, Head{op.Head}, Size{op.Size} {}

template<typename T>
bool ChainU<T>::empty() const
{
    return this->Size == 0;
}

template<typename T>
size_t ChainU<T>::size() const
{
    return this->Size;
}

template<typename T>
size_t ChainU<T>::find(const T &x) const
{
    NodeU<T> *iterator = this->Head->Next;
    for (auto iter = 0; iter != this->Size; ++iter)
    {
        iterator = iterator->Next;
        if (iterator->Element == x) return iter;
    }
    return this->Size;
}

template<typename T>
void ChainU<T>::erase(size_t const &x)
{
    if (0 > x || x >= this->Size) throw;
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; ++iter) iterator = iterator->Next;
    iterator->Next = iterator->Next->Next;
    --this->Size;
}

template<typename T>
void ChainU<T>::insert(size_t const &index, const T &elem)
{
    if (0 > index || index > this->Size) throw;
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != index; ++iter, iterator = iterator->Next);
    iterator->Next = new NodeU<T> {elem, iterator->Next};
    ++this->Size;
}

template<typename T>
T &ChainU<T>::operator[](size_t const &x)
{
    NodeU<T> *iterator = this->Head->Next;
    for (auto iter = 0; iter != x; ++iter)
    {
        iterator = iterator->Next;
    }
    return iterator->Element;
}

template<typename T>
void ChainU<T>::resize(size_t const &size) {
    this->Size = size;
}

#endif //DATASTRUCTURE_CHAIN_UNIDIRECTIONAL_HPP
