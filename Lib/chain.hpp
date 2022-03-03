#ifndef DATASTRUCTURE_CHAIN_B
#define DATASTRUCTURE_CHAIN_B

#include "node.hpp"
#include <iostream>
#ifndef ax_size
#define ax_size
typedef unsigned long long size_t;
typedef long long ssize_t;
#endif

namespace ax
{
    template<typename T>
    class bidirectional_chain
    {
    public:
        explicit bidirectional_chain(size_t const &);

        bidirectional_chain(bidirectional_chain<T> const &);

        ~bidirectional_chain() = default;

        void resize(size_t const &);

        [[nodiscard]] bool empty() const;

        [[nodiscard]] size_t size() const;

        size_t find(T const &) const;

        void erase(size_t const &);

        void insert(size_t const &, T const &);

        T &operator[](size_t const &);

        friend std::ostream &operator<<(std::ostream &out, bidirectional_chain<T> const &x)
        {
            bidirectional_node_iterator<T> iterator{x.head_c()->next_ptr()};
            for (; iterator != x.tail_c(); ++iterator)
            {
                out << (*iterator)() << " ";
            }
            return out;
        }

        bidirectional_node<T> *Head;

        bidirectional_node<T> *Tail;

    protected:
        size_t Size;
    };

    template<typename T>
    class bidirectional_circle_chain
    {
    public:
        explicit bidirectional_circle_chain(size_t const & = 1);

        bidirectional_circle_chain(bidirectional_circle_chain<T> const &);

        ~bidirectional_circle_chain() = default;

        void resize(size_t const &);

        [[nodiscard]] bool empty() const;

        [[nodiscard]] size_t size() const;

        size_t find(T const &) const;

        void erase(size_t const &);

        void insert(size_t const &, T const &);

        T &operator[](size_t const &);

        friend std::ostream &operator<<(std::ostream &out, bidirectional_circle_chain<T> const &x)
        {
            bidirectional_node_iterator<T> iterator{x.head_c()->next_ptr()};
            for (; iterator != x.head_c(); ++iterator)
            {
                out << (*iterator)() << " ";
            }
            return out;
        }

        bidirectional_node<T> *Head;

    protected:
        size_t Size;
    };

    template<typename T>
    class unidirectional_chain
    {
    public:
        explicit unidirectional_chain(size_t const &);

        unidirectional_chain(unidirectional_chain<T> const &);

        void resize(size_t const &);

        [[nodiscard]] bool empty() const;

        [[nodiscard]] size_t size() const;

        size_t find(T const &) const;

        void erase(size_t const &);

        void insert(size_t const &, T const &);

        T &operator[](size_t const &);

        friend std::ostream &operator<<(std::ostream &out, unidirectional_chain<T> const &x)
        {
            unidirectional_node_iterator<T> iterator{x.head_c()->next_ptr()};
            for (; iterator != x.tail_c(); ++iterator)
            {
                out << (*iterator)() << " ";
            }
            return out;
        }

        unidirectional_node<T> *Head;

        unidirectional_node<T> *Tail;

    protected:

        size_t Size;
    };

    template<typename T>
    class unidirectional_circle_chain
    {
    public:
        explicit unidirectional_circle_chain(size_t const & = 256);

        unidirectional_circle_chain(unidirectional_circle_chain<T> const &);

        ~unidirectional_circle_chain() = default;

        void resize(size_t const &);

        [[nodiscard]] bool empty() const;

        [[nodiscard]] size_t size() const;

        size_t find(T const &) const;

        void erase(size_t const &);

        void insert(size_t const &, T const &);

        T &operator[](size_t const &);

        friend std::ostream &operator<<(std::ostream &out, unidirectional_circle_chain<T> &x)
        {
            unidirectional_node_iterator<T> iterator{x.head_c()->next_ptr()};
            for (; iterator != x.head_c(); ++iterator)
            {
                out << *iterator << " ";
            }
            return out;
        }

        unidirectional_node<T> *Head;

        unidirectional_node_iterator<T> begin() {return unidirectional_node_iterator<T>{this->Head->next_ptr()};}

        unidirectional_node_iterator<T> end() {return unidirectional_node_iterator<T>{this->Head};}

    protected:
        size_t Size;
    };

    template<typename Tp>
    using chain = bidirectional_circle_chain<Tp>;

    template<typename T>
    unidirectional_circle_chain<T>::unidirectional_circle_chain(size_t const &cap)
            : Head{new unidirectional_node<T>{T()}}, Size{0}
    {
        Head->Next = Head;
    }

    template<typename T>
    unidirectional_circle_chain<T>::unidirectional_circle_chain(const unidirectional_circle_chain<T> &op)
            : Head{op.Head}, Size{op.Size} {}

    template<typename T>
    bool unidirectional_circle_chain<T>::empty() const
    {
        return this->Size == 0;
    }

    template<typename T>
    size_t unidirectional_circle_chain<T>::size() const
    {
        return this->Size;
    }

    template<typename T>
    size_t unidirectional_circle_chain<T>::find(const T &x) const
    {
        unidirectional_node<T> *iterator = &this->Head->Next;
        for (auto iter = 0; iter != this->Size; ++iter, iterator = iterator->Next) if (iterator->Element == x) return iter;
        return -1;
    }

    template<typename T>
    void unidirectional_circle_chain<T>::erase(size_t const &x)
    {
        if (0 > x || x >= this->Size) throw;
        unidirectional_node<T> *iterator = this->Head;
        for (auto iter = 0; iter != x; ++iter, iterator = iterator->Next);
        iterator->Next = iterator->Next->Next;
        --this->Size;
    }

    template<typename T>
    void unidirectional_circle_chain<T>::insert(size_t const &index, const T &elem)
    {
        if (0 > index || index > this->Size) throw;
        unidirectional_node<T> *iterator = this->Head;
        for (auto iter = 0; iter != index; ++iter, iterator = iterator->Next);
        iterator->Next = new unidirectional_node<T> {elem, iterator->Next};
        ++this->Size;
    }

    template<typename T>
    T &unidirectional_circle_chain<T>::operator[](size_t const &x)
    {
        unidirectional_node<T> *iterator = this->Head->Next;
        for (auto iter = 0; iter != x; ++iter) iterator = iterator->Next;
        return iterator->Element;
    }

    template<typename T>
    void unidirectional_circle_chain<T>::resize(size_t const &x)
    {
        this->Size = x;
    }

    template<typename T>
    unidirectional_chain<T>::unidirectional_chain(size_t const &cap)
            : Tail{new unidirectional_node<T>{T()}}, Head{new unidirectional_node<T>{T()}}, Size{0}
    {
        Head->Next = Tail;
    }

    template<typename T>
    unidirectional_chain<T>::unidirectional_chain(const unidirectional_chain<T> &op)
            : Tail{op.Tail}, Head{op.Head}, Size{op.Size} {}

    template<typename T>
    bool unidirectional_chain<T>::empty() const
    {
        return this->Size == 0;
    }

    template<typename T>
    size_t unidirectional_chain<T>::size() const
    {
        return this->Size;
    }

    template<typename T>
    size_t unidirectional_chain<T>::find(const T &x) const
    {
        unidirectional_node<T> *iterator = this->Head->Next;
        for (auto iter = 0; iter != this->Size; ++iter)
        {
            iterator = iterator->Next;
            if (iterator->Element == x) return iter;
        }
        return this->Size;
    }

    template<typename T>
    void unidirectional_chain<T>::erase(size_t const &x)
    {
        if (0 > x || x >= this->Size) throw;
        unidirectional_node<T> *iterator = this->Head;
        for (auto iter = 0; iter != x; ++iter) iterator = iterator->Next;
        iterator->Next = iterator->Next->Next;
        --this->Size;
    }

    template<typename T>
    void unidirectional_chain<T>::insert(size_t const &index, const T &elem)
    {
        if (0 > index || index > this->Size) throw;
        unidirectional_node<T> *iterator = this->Head;
        for (auto iter = 0; iter != index; ++iter, iterator = iterator->Next);
        iterator->Next = new unidirectional_node<T> {elem, iterator->Next};
        ++this->Size;
    }

    template<typename T>
    T &unidirectional_chain<T>::operator[](size_t const &x)
    {
        unidirectional_node<T> *iterator = this->Head->Next;
        for (auto iter = 0; iter != x; ++iter)
        {
            iterator = iterator->Next;
        }
        return iterator->Element;
    }

    template<typename T>
    void unidirectional_chain<T>::resize(size_t const &size) {
        this->Size = size;
    }

    template<typename T>
    bidirectional_circle_chain<T>::bidirectional_circle_chain(size_t const &cap)
            : Head{new bidirectional_node<T>{T()}}, Size{}
    {
        Head->Next = Head;
        Head->Prev = Head;
    }

    template<typename T>
    bidirectional_circle_chain<T>::bidirectional_circle_chain(const bidirectional_circle_chain<T> &op)
            : Head{op.Head}, Size{op.Size} {}

    template<typename T>
    bool bidirectional_circle_chain<T>::empty() const
    {
        return this->Size == 0;
    }

    template<typename T>
    size_t bidirectional_circle_chain<T>::size() const
    {
        return this->Size;
    }

    template<typename T>
    size_t bidirectional_circle_chain<T>::find(const T &x) const
    {
        bidirectional_node<T> *iterator = this->Head->Next;
        for (auto iter = 0; iter != this->Size; ++iter, iterator = iterator->Next) if (iterator->Element == x) return iter;
        return -1;
    }

    template<typename T>
    void bidirectional_circle_chain<T>::erase(size_t const &x)
    {
        if (0 > x || x >= this->Size) throw;
        bidirectional_node<T> *iterator = this->Head;
        for (auto iter = 0; iter != x; ++iter, iterator = iterator->Next);
        iterator->Next = iterator->Next->Next;
        iterator->Next->Prev = iterator;
        --this->Size;
    }

    template<typename T>
    void bidirectional_circle_chain<T>::insert(size_t const &index, T const &elem)
    {
        if (0 > index || index > this->Size) throw;
        bidirectional_node<T> *iterator = this->Head;
        for (auto iter = 0; iter != index; ++iter, iterator = iterator->Next);
        bidirectional_node<T> *temp = iterator->Next;
        iterator->Next = new bidirectional_node<T> {elem, iterator, iterator->Next};
        temp->Prev = iterator->Next;
        ++this->Size;
    }

    template<typename T>
    T &bidirectional_circle_chain<T>::operator[](size_t const &x)
    {
        bidirectional_node<T> *iterator = this->Head->Next;
        for (auto iter = 0; iter != x; ++iter, iterator = iterator->Next);
        return iterator->Element;
    }

    template<typename T>
    void bidirectional_circle_chain<T>::resize(size_t const &size) {
        this->Size = size;
    }

    template<typename T>
    bidirectional_chain<T>::bidirectional_chain(size_t const &cap)
            : Tail{new bidirectional_node<T>{T()}}, Head{new bidirectional_node<T>{T()}}, Size{0}
    {
        Head->Next = Tail;
        Tail->Prev = Head;
    }

    template<typename T>
    bidirectional_chain<T>::bidirectional_chain(const bidirectional_chain<T> &op)
            : Tail{op.Tail}, Head{op.Head}, Size{op.Size} {}

    template<typename T>
    bool bidirectional_chain<T>::empty() const
    {
        return this->Size == 0;
    }

    template<typename T>
    size_t bidirectional_chain<T>::size() const
    {
        return this->Size;
    }

    template<typename T>
    size_t bidirectional_chain<T>::find(const T &x) const
    {
        bidirectional_node<T> *iterator = this->Head->Next;
        for (auto iter = 0; iter != this->Size; ++iter)
        {
            iterator = iterator->Next;
            if (iterator->Element == x) return iter;
        }
        return -1;
    }

    template<typename T>
    void bidirectional_chain<T>::erase(size_t const &x)
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
    void bidirectional_chain<T>::insert(size_t const &index, T const &elem)
    {
        if (0 > index || index > this->Size) throw;
        bidirectional_node<T> *iterator = this->Head;
        for (auto iter = 0; iter != index; ++iter, iterator = iterator->Next);
        iterator->Next = new bidirectional_node<T> {elem, iterator, iterator->Next};
        iterator->Next->Next->Prev = iterator->Next;
        ++this->Size;
    }

    template<typename T>
    T &bidirectional_chain<T>::operator[](size_t const &x)
    {
        bidirectional_node<T> *iterator = this->Head->Next;
        for (auto iter = 0; iter != x; ++iter, iterator = iterator->Next);
        return iterator->Element;
    }

    template<typename T>
    void bidirectional_chain<T>::resize(size_t const &size)
    {
        this->Size = size;
    }

}



#endif //DATASTRUCTURE_CHAIN_BIDIRECTIONAL_HPP
