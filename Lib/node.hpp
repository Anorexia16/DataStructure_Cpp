#ifndef DATASTRUCTURE_NODE_HPP
#define DATASTRUCTURE_NODE_HPP

#ifndef ax_size
#define ax_size
typedef unsigned long long size_t;
typedef long long ssize_t;
#endif

#include "vector.hpp"

namespace ax
{
    template<typename T>
    struct unidirectional_node
    {
        unidirectional_node();

        explicit unidirectional_node(T const &);

        explicit unidirectional_node(T const & , unidirectional_node<T> *);

        unidirectional_node<T> *Next;

        T Element;
    };

    template<typename T>
    class unidirectional_node_iterator
    {
    public:
        unidirectional_node_iterator();

        explicit unidirectional_node_iterator(unidirectional_node<T> &);

        explicit unidirectional_node_iterator(const unidirectional_node<T> *const &);

        inline T &operator*();

        inline unidirectional_node_iterator<T> &operator++();

        inline unidirectional_node_iterator<T> const operator++(int) const;

        inline bool operator==(unidirectional_node_iterator<T> const &) const;

        inline bool operator!=(unidirectional_node_iterator<T> const &) const;

        inline bool operator==(const unidirectional_node<T> *const &) const;

        inline bool operator!=(const unidirectional_node<T> *const &) const;

        unidirectional_node_iterator(unidirectional_node_iterator<T> const &) = default;

        unidirectional_node<T> *Ptr;
    };

    template<typename T>
    struct bidirectional_node
    {
        bidirectional_node();
        explicit bidirectional_node(T const &);
        bidirectional_node(T const &, bidirectional_node<T> *, bidirectional_node<T> *);

        bidirectional_node<T> *Next;
        bidirectional_node<T> *Prev;
        T Element;
    };

    template<typename T>
    class bidirectional_node_iterator
    {
    public:
        bidirectional_node_iterator();

        explicit bidirectional_node_iterator(bidirectional_node<T> &);
        explicit bidirectional_node_iterator(const bidirectional_node<T> *const &);

        inline T &operator*();
        inline T *operator->();

        inline bidirectional_node_iterator<T> &operator++();
        inline bidirectional_node_iterator<T> &operator--();
        inline const bidirectional_node_iterator<T> operator++(int) const;
        inline const bidirectional_node_iterator<T> operator--(int) const;

        inline bool operator==(bidirectional_node_iterator<T> const &) const;
        inline bool operator!=(bidirectional_node_iterator<T> const &) const;
        inline bool operator==(const bidirectional_node<T> *const &) const;
        inline bool operator!=(const bidirectional_node<T> *const &) const;

        bidirectional_node<T> *Ptr;
    };

    template<typename cls>
    struct reticular_node {
        explicit reticular_node(cls const & = *new cls {});

        template<class Iterable_Container1, class Iterable_Container2>
        reticular_node(cls const &, Iterable_Container1 const &, Iterable_Container2 const &);

        reticular_node(cls const &, reticular_node<cls> **&, size_t const &, reticular_node<cls> **&, size_t const &);

        vector<reticular_node<cls> *> Destination;

        vector<reticular_node<cls> *> Source;

        cls Value;
    };

    template<typename cls>
    class reticular_node_iterator
    {
    public:
        reticular_node_iterator();

        explicit reticular_node_iterator(reticular_node<cls> const &);

        explicit reticular_node_iterator(const reticular_node<cls> * const &);

        inline reticular_node<cls> &operator*();

        inline reticular_node<cls> *operator->();

        reticular_node_iterator<cls> &operator=(const reticular_node<cls> * const &);

        inline vector<reticular_node_iterator<cls> *> &operator++();

        inline vector<reticular_node_iterator<cls> *> &operator--();

        inline vector<reticular_node_iterator<cls> *> const operator++(int) const;

        inline vector<reticular_node_iterator<cls> *> const operator--(int) const;

        inline bool operator==(reticular_node_iterator<cls> const &) const;

        inline bool operator!=(reticular_node_iterator<cls> const &) const;

        inline bool operator==(const reticular_node<cls> * const &) const;

        inline bool operator!=(const reticular_node<cls> * const &) const;

        reticular_node<cls> *Ptr;
    };

    template<typename cls>
    struct nonlinear_node
    {
        explicit nonlinear_node(cls const & = *new cls{});

        template<class Iterable_Container>
        nonlinear_node(cls const &, nonlinear_node<cls> &, Iterable_Container const &);

        nonlinear_node(cls const &, nonlinear_node<cls> &, nonlinear_node<cls> **&, size_t const &);

        vector<nonlinear_node<cls> *> Destination;

        nonlinear_node<cls> *Source;

        cls Value;
    };

    template<typename cls>
    class nonlinear_node_iterator
    {
    public:
        nonlinear_node_iterator();

        explicit nonlinear_node_iterator(nonlinear_node<cls> &&);

        explicit nonlinear_node_iterator(const nonlinear_node<cls> *const &);

        nonlinear_node_iterator(nonlinear_node_iterator<cls> &&) noexcept = default;

        nonlinear_node_iterator(nonlinear_node_iterator<cls> const &) = default;

        nonlinear_node_iterator<cls> &operator=(nonlinear_node_iterator<cls> &&) noexcept = default;

        nonlinear_node_iterator<cls> &operator=(nonlinear_node_iterator<cls> const &) = default;

        inline nonlinear_node<cls> &operator*();

        inline nonlinear_node<cls> *operator->();

        inline vector<nonlinear_node<cls> *> &operator++();

        inline const vector<nonlinear_node<cls> *> operator++(int) const;

        inline nonlinear_node_iterator<cls> &operator--();

        inline const nonlinear_node_iterator<cls> operator--(int) const;

        inline bool operator==(nonlinear_node_iterator<cls> const &) const;

        inline bool operator!=(nonlinear_node_iterator<cls> const &) const;

        inline bool operator==(const nonlinear_node<cls> *const &);

        inline bool operator!=(const nonlinear_node<cls> *const &);

        nonlinear_node<cls> *Ptr;
    };

    template<typename cls>
    reticular_node<cls>::reticular_node(const cls &i)
            :Value{i}, Source{}, Destination{} {}

    template<typename cls>
    template<class Iterable_Container1, class Iterable_Container2>
    reticular_node<cls>::reticular_node(const cls &value, const Iterable_Container1 &cont_source, const Iterable_Container2 &cont_destination)
            :Value{value}, Source{}, Destination{}
    {
        for (auto &&iter: cont_source) Source.template emplace_back(iter);
        for (auto &&iter: cont_destination) Destination.template emplace_back(iter);
    }

    template<typename cls>
    reticular_node<cls>::reticular_node(const cls &value, reticular_node<cls> **&array_source, const size_t &size_source,
                                        reticular_node<cls> **&array_destination, const size_t &size_destination)
            :Value{value}, Source{}, Destination{}
    {
        for (auto i = 0; i != size_source; ++i) Source.template emplace_back(array_source[i]);
        for (auto i = 0; i != size_destination; ++i) Destination.template emplace_back(array_destination[i]);
    }

    template<typename cls>
    nonlinear_node<cls>::nonlinear_node(const cls &value)
            :Value{value}, Source{nullptr}, Destination{} {}

    template<typename cls>
    template<class Iterable_Container>
    nonlinear_node<cls>::nonlinear_node(const cls &value, nonlinear_node<cls> &ptr, const Iterable_Container &cont)
            :Value{value}, Source{&ptr}, Destination{}
    {
        for (auto &&iter: cont) Destination.template emplace_back(iter);
    }

    template<typename cls>
    nonlinear_node<cls>::nonlinear_node(const cls &value, nonlinear_node<cls> &ptr, nonlinear_node<cls> **&array,
                                        const size_t &size)
            :Value{value}, Source{ptr}, Destination{}
    {
        for (auto i = 0; i != size; ++i) Destination.template emplace_back(array[i]);
    }

    template<typename cls>
    nonlinear_node_iterator<cls>::nonlinear_node_iterator()
            : Ptr{nullptr} {}

    template<typename cls>
    nonlinear_node_iterator<cls>::nonlinear_node_iterator(const nonlinear_node<cls> *const &ptr)
            :Ptr{static_cast<nonlinear_node<cls> *>(ptr)} {}

    template<typename cls>
    nonlinear_node_iterator<cls>::nonlinear_node_iterator(nonlinear_node<cls> &&node)
            :Ptr{&std::forward<>(node)} {}

    template<typename cls>
    nonlinear_node<cls> &nonlinear_node_iterator<cls>::operator*()
    {
        return *this->Value;
    }

    template<typename cls>
    nonlinear_node<cls> *nonlinear_node_iterator<cls>::operator->()
    {
        return &*this->Value;
    }

    template<typename cls>
    vector<nonlinear_node<cls> *> &nonlinear_node_iterator<cls>::operator++()
    {
        return this->Destination;
    }

    template<typename cls>
    const vector<nonlinear_node<cls> *> nonlinear_node_iterator<cls>::operator++(int) const
    {
        return this->Destination;
    }

    template<typename cls>
    nonlinear_node_iterator<cls> &nonlinear_node_iterator<cls>::operator--()
    {
        return *this->Source;
    }

    template<typename cls>
    const nonlinear_node_iterator<cls> nonlinear_node_iterator<cls>::operator--(int) const
    {
        return *this->Source;
    }

    template<typename cls>
    bool nonlinear_node_iterator<cls>::operator==(const nonlinear_node_iterator<cls> &op) const
    {
        return this->Ptr==op.Ptr;
    }

    template<typename cls>
    bool nonlinear_node_iterator<cls>::operator!=(const nonlinear_node_iterator<cls> &op) const
    {
        return this->Ptr!=op.Ptr;
    }

    template<typename cls>
    bool nonlinear_node_iterator<cls>::operator==(const nonlinear_node<cls> *const &op)
    {
        return this->Ptr == op;
    }

    template<typename cls>
    bool nonlinear_node_iterator<cls>::operator!=(const nonlinear_node<cls> *const &op)
    {
        return this->Ptr != op;
    }

    template<typename cls>
    reticular_node_iterator<cls>::reticular_node_iterator()
            :Ptr{nullptr} {}

    template<typename cls>
    reticular_node_iterator<cls>::reticular_node_iterator(const reticular_node<cls> *const &ptr)
            :Ptr{const_cast<reticular_node<cls> *>(ptr)} {}

    template<typename cls>
    reticular_node_iterator<cls>::reticular_node_iterator(reticular_node<cls> const &node)
            :Ptr{&node} {}

    template<typename cls>
    reticular_node<cls> &reticular_node_iterator<cls>::operator*()
    {
        return *(this->Ptr);
    }

    template<typename cls>
    reticular_node<cls> *reticular_node_iterator<cls>::operator->()
    {
        return this->Ptr;
    }

    template<typename cls>
    vector<reticular_node_iterator<cls> *> &reticular_node_iterator<cls>::operator++()
    {
        return this->Destination;
    }

    template<typename cls>
    vector<reticular_node_iterator<cls> *> &reticular_node_iterator<cls>::operator--()
    {
        return this->Source;
    }

    template<typename cls>
    const vector<reticular_node_iterator<cls> *> reticular_node_iterator<cls>::operator++(int) const
    {
        return this->Destination;
    }

    template<typename cls>
    const vector<reticular_node_iterator<cls> *> reticular_node_iterator<cls>::operator--(int) const
    {
        return this->Source;
    }

    template<typename cls>
    bool reticular_node_iterator<cls>::operator==(const reticular_node_iterator<cls> &op) const
    {
        return this->Ptr==op.Ptr;
    }

    template<typename cls>
    bool reticular_node_iterator<cls>::operator!=(const reticular_node_iterator<cls> &op) const
    {
        return this->Ptr!=op.Ptr;
    }

    template<typename cls>
    bool reticular_node_iterator<cls>::operator==(const reticular_node<cls> *const &ptr) const
    {
        return static_cast<void*>(this->Ptr)==static_cast<void*>(ptr);
    }

    template<typename cls>
    bool reticular_node_iterator<cls>::operator!=(const reticular_node<cls> *const &ptr) const
    {
        return static_cast<void*>(this->Ptr)!=static_cast<void*>(ptr);
    }

    template<typename cls>
    reticular_node_iterator<cls> &reticular_node_iterator<cls>::operator=(const reticular_node<cls> *const &ptr)
    {
        this->Ptr = const_cast<reticular_node<cls> *>(ptr);
        return *this;
    }

    template<typename T>
    unidirectional_node<T>::unidirectional_node()
            : Element{T{}}, Next{nullptr} {}

    template<typename T>
    unidirectional_node<T>::unidirectional_node(const T &x)
            : Element{x}, Next{nullptr} {}

    template<typename T>
    unidirectional_node<T>::unidirectional_node(T const &x, unidirectional_node<T> * ptr)
            : Element{const_cast<T &>(x)}, Next{ptr} {}


    template<typename T>
    unidirectional_node_iterator<T>::unidirectional_node_iterator()
            : Ptr(nullptr) {}

    template<typename T>
    unidirectional_node_iterator<T>::unidirectional_node_iterator(unidirectional_node<T> &elem)
            : Ptr(&elem) {}

    template<typename T>
    unidirectional_node_iterator<T>::unidirectional_node_iterator(const unidirectional_node<T> *const &ptr)
            : Ptr(const_cast<unidirectional_node<T> *>(ptr)) {}

    template<typename T>
    T &unidirectional_node_iterator<T>::operator*()
    {
        return this->Ptr->Element;
    }

    template<typename T>
    unidirectional_node_iterator<T> &unidirectional_node_iterator<T>::operator++()
    {
        this->Ptr = this->Ptr->Next;
        return *this;
    }

    template<typename T>
    unidirectional_node_iterator<T> const unidirectional_node_iterator<T>::operator++(int) const
    {
        unidirectional_node<T> temp = *this;
        ++(*this);
        return temp;
    }

    template<typename T>
    bool unidirectional_node_iterator<T>::operator==(const unidirectional_node<T> *const &ptr) const
    {
        return this->Ptr == ptr;
    }

    template<typename T>
    bool unidirectional_node_iterator<T>::operator!=(const unidirectional_node<T> *const &ptr) const
    {
        return this->Ptr != ptr;
    }

    template<typename T>
    bool unidirectional_node_iterator<T>::operator==(const unidirectional_node_iterator<T> &op) const
    {
        return this->Ptr == op.Ptr;
    }

    template<typename T>
    bool unidirectional_node_iterator<T>::operator!=(const unidirectional_node_iterator<T> &op) const
    {
        return this->Ptr != op.Ptr;
    }


    template<typename T>
    bidirectional_node_iterator<T>::bidirectional_node_iterator()
            : Ptr(nullptr) {}

    template<typename T>
    bidirectional_node_iterator<T>::bidirectional_node_iterator(bidirectional_node<T> &elem)
            : Ptr(&elem) {}

    template<typename T>
    bidirectional_node_iterator<T>::bidirectional_node_iterator(const bidirectional_node<T> *const &ptr)
            :Ptr(const_cast<bidirectional_node<T> *>(ptr)) {}

    template<typename T>
    T &bidirectional_node_iterator<T>::operator*()
    {
        return this->Ptr->Element;
    }

    template<typename T>
    T *bidirectional_node_iterator<T>::operator->()
    {
        return &this->Ptr->Element;
    }

    template<typename T>
    bidirectional_node_iterator<T> &bidirectional_node_iterator<T>::operator++()
    {
        this->Ptr = this->Ptr->Next;
        return *this;
    }

    template<typename T>
    bidirectional_node_iterator<T> &bidirectional_node_iterator<T>::operator--()
    {
        this->Ptr = this->Ptr->Prev;
        return *this;
    }

    template<typename T>
    const bidirectional_node_iterator<T> bidirectional_node_iterator<T>::operator++(int) const
    {
        bidirectional_node<T> temp = *this;
        ++(*this);
        return temp;
    }

    template<typename T>
    const bidirectional_node_iterator<T> bidirectional_node_iterator<T>::operator--(int) const
    {
        bidirectional_node<T> temp = *this;
        --(*this);
        return temp;
    }

    template<typename T>
    bool bidirectional_node_iterator<T>::operator==(const bidirectional_node_iterator<T> &op) const
    {
        return this->Ptr == op.Ptr;
    }

    template<typename T>
    bool bidirectional_node_iterator<T>::operator!=(const bidirectional_node_iterator<T> &op) const
    {
        return this->Ptr != op.Ptr;
    }

    template<typename T>
    bool bidirectional_node_iterator<T>::operator==(const bidirectional_node<T> *const &ptr) const
    {
        return this->Ptr == ptr;
    }

    template<typename T>
    bool bidirectional_node_iterator<T>::operator!=(const bidirectional_node<T> *const &ptr) const
    {
        return this->Ptr != ptr;
    }

    template<typename T>
    bidirectional_node<T>::bidirectional_node()
            :Element{T{}}, Prev{nullptr}, Next{nullptr} {}

    template<typename T>
    bidirectional_node<T>::bidirectional_node(const T &x)
            :Element{x}, Prev{nullptr}, Next{nullptr} {}

    template<typename T>
    bidirectional_node<T>::bidirectional_node(const T &x, bidirectional_node<T> *ptr1, bidirectional_node<T> *ptr2)
            : Element{x}, Prev{ptr1}, Next{ptr2} {}

}

#endif //DATASTRUCTURE_NODE_HPP
