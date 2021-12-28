#ifndef DATASTRUCTURE_CHAIN_BIDIRECTIONAL
#define DATASTRUCTURE_CHAIN_BIDIRECTIONAL

#include "../Abstract/Abstract_Linear_List.hpp"
#include "../Assistance/Node_Bidirectional.hpp"

template<typename T>
class ChainBC : public LinearList<T>
{
public:
    explicit ChainBC(size_t const & = 1);

    ChainBC(ChainBC<T> const &);

    ~ChainBC() = default;

    void resize(size_t const &);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    size_t find(T const &) const;

    void erase(size_t const &);

    void insert(size_t const &, T const &);

    T &operator[](size_t const &);

    friend std::ostream &operator<<(std::ostream &out, ChainBC<T> const &x)
    {
        NodeB_Iter<T> iterator{x.head_c()->next_ptr()};
        for (; iterator != x.head_c(); ++iterator)
        {
            out << (*iterator)() << " ";
        }
        return out;
    }

    NodeB<T> *Head;

protected:
    size_t Size;
};

template<typename T>
ChainBC<T>::ChainBC(size_t const &cap)
        : Head{new NodeB<T>{T()}}, Size{}
{
    Head->Next = Head;
    Head->Prev = Head;
}

template<typename T>
ChainBC<T>::ChainBC(const ChainBC<T> &op)
        : Head{op.Head}, Size{op.Size} {}

template<typename T>
bool ChainBC<T>::empty() const
{
    return this->Size == 0;
}

template<typename T>
size_t ChainBC<T>::size() const
{
    return this->Size;
}

template<typename T>
size_t ChainBC<T>::find(const T &x) const
{
    NodeB<T> *iterator = this->Head->Next;
    for (auto iter = 0; iter != this->Size; ++iter, iterator = iterator->Next) if (iterator->Element == x) return iter;
    return -1;
}

template<typename T>
void ChainBC<T>::erase(size_t const &x)
{
    if (0 > x || x >= this->Size) throw;
    NodeB<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; ++iter, iterator = iterator->Next);
    iterator->Next = iterator->Next->Next;
    iterator->Next->Prev = iterator;
    --this->Size;
}

template<typename T>
void ChainBC<T>::insert(size_t const &index, T const &elem)
{
    if (0 > index || index > this->Size) throw;
    NodeB<T> *iterator = this->Head;
    for (auto iter = 0; iter != index; ++iter, iterator = iterator->Next);
    NodeB<T> *temp = iterator->Next;
    iterator->Next = new NodeB<T> {elem, iterator, iterator->Next};
    temp->Prev = iterator->Next;
    ++this->Size;
}

template<typename T>
T &ChainBC<T>::operator[](size_t const &x)
{
    NodeB<T> *iterator = this->Head->Next;
    for (auto iter = 0; iter != x; ++iter, iterator = iterator->Next);
    return iterator->Element;
}

template<typename T>
void ChainBC<T>::resize(size_t const &size) {
    this->Size = size;
}

#endif //DATASTRUCTURE_CHAIN_BIDIRECTIONAL
