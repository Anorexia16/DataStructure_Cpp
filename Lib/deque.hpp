#ifndef DATASTRUCTURE_DEQUE_HPP
#define DATASTRUCTURE_DEQUE_HPP

#include "vector.hpp"
#include "node.hpp"

namespace ax
{
    template<typename Tp>
    class linked_deque {
    public:
        linked_deque();

        template<class Iterable_Container>
        explicit linked_deque(Iterable_Container const &);

        linked_deque(const Tp *const &, size_t const &);

        void emplace_front(Tp const &);

        void emplace_back(Tp const &);

        void pop_front();

        void pop_back();

        Tp front() const;

        Tp back() const;

        [[nodiscard]] inline bool empty() const;

        [[nodiscard]] inline size_t size() const;

    protected:
        bidirectional_node<Tp> *Head;

        size_t Size;
    };

    template<typename Tp>
    class circle_linked_deque
    {
    public:
        explicit circle_linked_deque(size_t const & = 99);

        template<class Iterable_Container>
        explicit circle_linked_deque(Iterable_Container const &, size_t const & = 99);

        circle_linked_deque(const Tp *const &, size_t const &, size_t const & = 99);

        void emplace_front(Tp const &);

        void emplace_back(Tp const &);

        void pop_front();

        void pop_back();

        Tp front() const;

        Tp back() const;

        [[nodiscard]] inline bool full() const;

        [[nodiscard]] inline bool empty() const;

        [[nodiscard]] inline size_t size() const;

    protected:
        bidirectional_node<Tp> *First;

        bidirectional_node<Tp> *Rear;

        size_t Size;
    };

    template<typename Tp>
    class standard_container_deque
    {
    public:
        standard_container_deque();

        explicit standard_container_deque(std::istream &&);

        standard_container_deque(std::initializer_list<Tp> const &);

        template<size_t n>
        explicit standard_container_deque(std::array<Tp, n> const &);

        template<template<typename elem, typename = std::allocator<elem>> class Cont>
        explicit standard_container_deque(Cont<Tp> const &);

        standard_container_deque(const Tp * const &, size_t const &);

        void emplace_front(Tp const &);

        void emplace_back(Tp const &);

        void pop_front();

        void pop_back();

        Tp front() const;

        Tp back() const;

        [[nodiscard]] inline bool empty() const;

        [[nodiscard]] inline size_t size() const;

    private:
        vector<Tp> Container;
    };

    template<typename Tp>
    using deque = linked_deque<Tp>;

    template<typename Tp>
    standard_container_deque<Tp>::standard_container_deque()
            :Container{} {}

    template<typename Tp>
    standard_container_deque<Tp>::standard_container_deque(std::istream &&in)
            :Container{}
    {
        std::move(std::istream_iterator<Tp>(in), std::istream_iterator<Tp>(), std::begin(Container));
    }

    template<typename Tp>
    standard_container_deque<Tp>::standard_container_deque(const std::initializer_list<Tp> &list)
            :Container{}
    {
        std::copy(std::cbegin(list), std::cend(list), std::begin(Container));
    }

    template<typename Tp>
    template<size_t n>
    standard_container_deque<Tp>::standard_container_deque(const std::array<Tp, n> &array)
            :Container{}
    {
        std::copy(std::cbegin(array), std::cend(array), std::begin(Container));
    }

    template<typename Tp>
    template<template<typename elem, typename = std::allocator<elem>> class Cont>
    standard_container_deque<Tp>::standard_container_deque(const Cont<Tp> &cont)
            :Container{}
    {
        std::copy(std::cbegin(cont), std::cend(cont), std::begin(Container));
    }

    template<typename Tp>
    standard_container_deque<Tp>::standard_container_deque(const Tp *const &ptr, const size_t &size)
            :Container{}
    {
        for(auto i=0;i!=size;++i) Container.template emplace_back(const_cast<Tp>(ptr[i]));
    }

    template<typename Tp>
    void standard_container_deque<Tp>::emplace_front(const Tp &value)
    {
        this->Container.insert(value, std::begin(this->Container));
    }

    template<typename Tp>
    void standard_container_deque<Tp>::emplace_back(const Tp &value)
    {
        this->Container.template emplace_back(value);
    }

    template<typename Tp>
    void standard_container_deque<Tp>::pop_front()
    {
        this->Container.erase(std::rbegin(this->Container));
    }

    template<typename Tp>
    void standard_container_deque<Tp>::pop_back()
    {
        this->Container.erase(std::begin(this->Container));
    }

    template<typename Tp>
    Tp standard_container_deque<Tp>::front() const
    {
        return *std::begin(this->Container);
    }

    template<typename Tp>
    Tp standard_container_deque<Tp>::back() const
    {
        return *std::rbegin(this->Container);
    }

    template<typename Tp>
    bool standard_container_deque<Tp>::empty() const
    {
        return this->Container.empty();
    }

    template<typename Tp>
    size_t standard_container_deque<Tp>::size() const
    {
        return this->Container.size();
    }

    template<typename Tp>
    circle_linked_deque<Tp>::circle_linked_deque(const size_t &capacity)
            :First{new bidirectional_node<Tp> {}}, Rear{nullptr}, Size{}
    {
        First->Next = First;
        First->Prev = First;
        for (auto i = 0; i != capacity-1; ++i)
        {
            First->Next = new bidirectional_node<Tp>{Tp{}, First, First->Next};
            First->Next->Next->Prev = First->Next;
        }
    }

    template<typename Tp>
    template<class Iterable_Container>
    circle_linked_deque<Tp>::circle_linked_deque(const Iterable_Container &cont, const size_t &capacity)
            :First{new bidirectional_node<Tp> {}}, Rear{nullptr}
    {
        First->Next = First;
        First->Prev = First;
        size_t size = cont.index();
        for (auto const &iterator:cont)
        {
            First->Next = new bidirectional_node<Tp>{iterator, First, First->Next};
            First->Next->Next->Prev = First->Next;
            First = First->Next;
        }
        for(auto i=0;i<capacity-size;++i)
        {
            First->Next = new bidirectional_node<Tp>{Tp{}, First, First->Next};
            First->Next->Next->Prev = First->Next;
        }
        Rear = First;
        Size = size;
    }

    template<typename Tp>
    circle_linked_deque<Tp>::circle_linked_deque(const Tp *const &ptr, const size_t &size, const size_t &capacity)
            :First{new bidirectional_node<Tp> {}}, Rear{nullptr}
    {
        for (auto i = 0; i != size; ++i)
        {
            First->Next = new bidirectional_node<Tp>{ptr[i], First, First->Next};
            First->Next->Next->Prev = First->Next;
        }
        for(auto i=0;i<capacity-size;++i)
        {
            First->Next = new bidirectional_node<Tp>{Tp{}, First, First->Next};
            First->Next->Next->Prev = First->Next;
        }
        Size = size;
        Rear = First;
    }

    template<typename Tp>
    void circle_linked_deque<Tp>::emplace_front(const Tp &value)
    {
        if (this->full()) throw;
        First = First->Prev;
        First->Element = value;
        ++this->Size;
    }

    template<typename Tp>
    void circle_linked_deque<Tp>::emplace_back(const Tp &value)
    {
        if (this->full()) throw;
        Rear = Rear->Next;
        Rear->Element = value;
        ++this->Size;
    }

    template<typename Tp>
    void circle_linked_deque<Tp>::pop_front()
    {
        if (this->empty()) throw;
        First->Element = Tp{};
        First = First->Next;
        --this->Size;
    }

    template<typename Tp>
    void circle_linked_deque<Tp>::pop_back()
    {
        if (this->empty()) throw;
        Rear = Rear->Prev;
        Rear = Rear->Prev;
        --this->Size;
    }

    template<typename Tp>
    Tp circle_linked_deque<Tp>::front() const
    {
        return First->Element;
    }

    template<typename Tp>
    Tp circle_linked_deque<Tp>::back() const
    {
        return Rear->Prev->Element;
    }

    template<typename Tp>
    bool circle_linked_deque<Tp>::empty() const
    {
        return this->Size == 0;
    }

    template<typename Tp>
    size_t circle_linked_deque<Tp>::size() const
    {
        return this->Size;
    }

    template<typename Tp>
    bool circle_linked_deque<Tp>::full() const
    {
        return Rear->Next=First && this->Size!=0;
    }

    template<typename Tp>
    linked_deque<Tp>::linked_deque()
            :Head{new bidirectional_node<Tp> {}}, Size{}
    {
        Head->Next = Head;
        Head->Prev = Head;
    }

    template<typename Tp>
    template<class Iterable_Container>
    linked_deque<Tp>::linked_deque(const Iterable_Container &list)
            :Head{new bidirectional_node<Tp> {}}, Size{}
    {
        Head->Next = Head;
        Head->Prev = Head;

        bidirectional_node<Tp> *bi {Head};
        for(auto const &ci:list)
        {
            bi->Next = new bidirectional_node<Tp>{ci, bi->Next};
            bi->Next->Next->Prev = bi->Next;
            ++bi;
        }
        this->Size = list.index();
    }

    template<typename Tp>
    linked_deque<Tp>::linked_deque(const Tp *const &ptr, const size_t &size)
            :Head{new bidirectional_node<Tp> {}}, Size{size}
    {
        Head->Next = Head;
        Head->Prev = Head;

        bidirectional_node<Tp> *bi {Head};
        for(auto i=0;i!=size;++i)
        {
            bi->Next = new bidirectional_node<Tp>{ptr[i], bi->Next};
            bi->Next->Next->Prev = bi->Next;
            ++bi;
        }
        this->Size = size;
    }

    template<typename Tp>
    void linked_deque<Tp>::emplace_front(const Tp &value)
    {
        bidirectional_node<Tp> *_iter {this->Head};
        _iter->Next = new bidirectional_node<Tp>{value, _iter, _iter->Next};
        _iter->Next->Next->Prev = _iter->Next;
        ++this->Size;
    }

    template<typename Tp>
    void linked_deque<Tp>::emplace_back(const Tp &value)
    {
        bidirectional_node<Tp> *_iter {this->Head};
        _iter->Prev = new bidirectional_node<Tp>{value, _iter->Prev, _iter};
        _iter->Prev->Prev->Next = _iter->Prev;
        ++this->Size;
    }

    template<typename Tp>
    void linked_deque<Tp>::pop_front()
    {
        if (this->empty()) throw;
        bidirectional_node<Tp> *_iter {this->Head};
        _iter->Next = _iter->Next->Next;
        _iter->Next->Prev = _iter;
        --this->Size;
    }

    template<typename Tp>
    void linked_deque<Tp>::pop_back()
    {
        if (this->empty()) throw;
        bidirectional_node<Tp> *_iter {this->Head};
        _iter->Prev = _iter->Prev->Prev;
        _iter->Prev->Next = _iter;
        --this->Size;
    }

    template<typename Tp>
    Tp linked_deque<Tp>::front() const
    {
        return this->Head->Next->Element;
    }

    template<typename Tp>
    Tp linked_deque<Tp>::back() const
    {
        return this->Head->Prev->Element;
    }

    template<typename Tp>
    bool linked_deque<Tp>::empty() const
    {
        return this->Size == 0;
    }

    template<typename Tp>
    size_t linked_deque<Tp>::size() const
    {
        return this->Size;
    }
}

#endif //DATASTRUCTURE_DEQUE_HPP
