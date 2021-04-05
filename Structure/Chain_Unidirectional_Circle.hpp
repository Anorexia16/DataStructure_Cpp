#ifndef DATASTRUCTURE_CHAIN
#define DATASTRUCTURE_CHAIN

#include "Abstract_Linear_List.hpp"
#include "Node_Unidirectional.hpp"

template<typename T>
class ChainUC : public LinearList<T>
{
public:
    explicit ChainUC(size_t const & = 256);

    ChainUC(ChainUC<T> const &);

    ~ChainUC() = default;

    void resize(size_t const &);

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    size_t find(T const &) const;

    void erase(size_t const &);

    void insert(size_t const &, T const &);

    T &operator[](size_t const &);

    friend std::ostream &operator<<(std::ostream &out, ChainUC<T> &x)
    {
        NodeU_Iter<T> iterator{x.head_c()->next_ptr()};
        for (; iterator != x.head_c(); ++iterator)
        {
            out << *iterator << " ";
        }
        return out;
    }

    NodeU<T> *Head;

    NodeU_Iter<T> begin() {return NodeU_Iter<T>{this->Head->next_ptr()};}

    NodeU_Iter<T> end() {return NodeU_Iter<T>{this->Head};}

protected:
    size_t Size;
};

template<typename T>
ChainUC<T>::ChainUC(size_t const &cap)
        : Head{new NodeU<T>{T()}}, Size{0}
{
    Head->Next = Head;
}

template<typename T>
ChainUC<T>::ChainUC(const ChainUC<T> &op)
        : Head{op.Head}, Size{op.Size} {}

template<typename T>
bool ChainUC<T>::empty() const
{
    return this->Size == 0;
}

template<typename T>
size_t ChainUC<T>::size() const
{
    return this->Size;
}

template<typename T>
size_t ChainUC<T>::find(const T &x) const
{
    NodeU<T> *iterator = &this->Head->Next;
    for (auto iter = 0; iter != this->Size; ++iter, iterator = iterator->Next) if (iterator->Element == x) return iter;
    return -1;
}

template<typename T>
void ChainUC<T>::erase(size_t const &x)
{
    if (0 > x || x >= this->Size) throw;
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != x; ++iter, iterator = iterator->Next);
    iterator->Next = iterator->Next->Next;
    --this->Size;
}

template<typename T>
void ChainUC<T>::insert(size_t const &index, const T &elem)
{
    if (0 > index || index > this->Size) throw;
    NodeU<T> *iterator = this->Head;
    for (auto iter = 0; iter != index; ++iter, iterator = iterator->Next);
    iterator->Next = new NodeU<T> {elem, iterator->Next};
    ++this->Size;
}

template<typename T>
T &ChainUC<T>::operator[](size_t const &x)
{
    NodeU<T> *iterator = this->Head->Next;
    for (auto iter = 0; iter != x; ++iter) iterator = iterator->Next;
    return iterator->Element;
}

template<typename T>
void ChainUC<T>::resize(size_t const &x)
{
    this->Size = x;
}

#endif //DATASTRUCTURE_CHAIN_UNIDIRECTIONAL_CIRCLE_HPP
