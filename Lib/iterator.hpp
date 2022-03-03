#ifndef DATASTRUCTURE_ITERATOR_HPP
#define DATASTRUCTURE_ITERATOR_HPP

#ifndef ax_size
#define ax_size
typedef unsigned long long size_t;
typedef long long ssize_t;
#endif

namespace ax {
    template<class Arg>
    concept forward_iterator
    = requires(Arg iter)
    {
        Arg();Arg(iter);iter = iter;
        iter == iter;iter != iter;
        *iter;&*iter;
        iter++;++iter;
        iter.operator->();
    };

    template<class Arg>
    concept bidirectional_iterator
    = requires(Arg iter)
      {
          iter--;--iter;
      } && forward_iterator<Arg>;

    template<class Arg>
    concept random_access_iterator
    = requires(Arg iter)
      {
          iter + 1;iter - 1;iter - iter;
          iter < iter;iter > iter;iter <= iter;iter >= iter;
          iter += 1;iter -= 1;
      } && bidirectional_iterator<Arg>;

    template<class Arg>
    concept iterable_container
    = requires(Arg container)
    {
        container.begin;container.end();
    };

    namespace iter_template {
        template<bidirectional_iterator iterator, typename Tp>
        class reverse_bidirectional_iterator {
        public:
            reverse_bidirectional_iterator();
            template<class ...Args>
            explicit reverse_bidirectional_iterator(Args &&...);
            reverse_bidirectional_iterator(reverse_bidirectional_iterator const &);

            bool operator==(reverse_bidirectional_iterator const &) const;
            bool operator!=(reverse_bidirectional_iterator const &) const;
            bool operator==(iterator const &) const;
            bool operator!=(iterator const &) const;

            reverse_bidirectional_iterator &operator++();
            reverse_bidirectional_iterator &operator--();
            reverse_bidirectional_iterator const operator++(int);
            reverse_bidirectional_iterator const operator--(int);

            Tp &operator*();
            Tp *operator->();
            Tp const &operator*() const;
            Tp const *operator->() const;

        protected:
            iterator normal_iterator;
        };

        template<random_access_iterator iterator, typename Tp>
        class reverse_random_access_iterator {
        public:
            reverse_random_access_iterator();
            template<class ...Args>
            explicit reverse_random_access_iterator(Args &&...);
            reverse_random_access_iterator(reverse_random_access_iterator const &);

            bool operator==(reverse_random_access_iterator const &) const;
            bool operator!=(reverse_random_access_iterator const &) const;
            bool operator==(iterator const &) const;
            bool operator!=(iterator const &) const;

            reverse_random_access_iterator &operator++();
            reverse_random_access_iterator &operator--();
            reverse_random_access_iterator const operator++(int);
            reverse_random_access_iterator const operator--(int);

            Tp &operator*();
            Tp *operator->();
            Tp const &operator*() const;
            Tp const *operator->() const;

            reverse_random_access_iterator operator+(size_t) const;
            reverse_random_access_iterator operator-(size_t) const;
            ssize_t operator-(reverse_random_access_iterator const &) const;
            ssize_t operator-(iterator const &) const;

            bool operator<(iterator const &) const;
            bool operator>(iterator const &) const;
            bool operator<=(iterator const &) const;
            bool operator>=(iterator const &) const;
            bool operator<(reverse_random_access_iterator const &) const;
            bool operator>(reverse_random_access_iterator const &) const;
            bool operator<=(reverse_random_access_iterator const &) const;
            bool operator>=(reverse_random_access_iterator const &) const;

            reverse_random_access_iterator& operator+=(size_t);
            reverse_random_access_iterator& operator-=(size_t);

        protected:
            iterator normal_iterator;
        };

        template<forward_iterator iterator, typename Tp>
        class const_forward_iterator {
        public:
            const_forward_iterator();
            template<class ...Args>
            explicit const_forward_iterator(Args &&...);
            const_forward_iterator(const_forward_iterator const &) noexcept;

            bool operator==(const_forward_iterator const &) const;
            bool operator!=(const_forward_iterator const &) const;
            bool operator==(iterator const &) const;
            bool operator!=(iterator const &) const;

            const_forward_iterator &operator++();
            const_forward_iterator const operator++(int);

            const Tp &operator*() const;
            const Tp *operator->() const;

        protected:
            iterator normal_iterator;
        };

        template<bidirectional_iterator iterator, typename Tp>
        class const_bidirectional_iterator {
        public:
            const_bidirectional_iterator();
            template<class ...Args>
            explicit const_bidirectional_iterator(Args &&...);
            const_bidirectional_iterator(const_bidirectional_iterator const &) noexcept;

            bool operator==(const_bidirectional_iterator const &) const;
            bool operator!=(const_bidirectional_iterator const &) const;
            bool operator==(iterator const &) const;
            bool operator!=(iterator const &) const;

            const_bidirectional_iterator &operator++();
            const_bidirectional_iterator &operator--();
            const_bidirectional_iterator const operator++(int);
            const_bidirectional_iterator const operator--(int);

            const Tp &operator*() const;
            const Tp *operator->() const;

        protected:
            iterator normal_iterator;
        };

        template<random_access_iterator iterator, typename Tp>
        class const_random_access_iterator {
        public:
            const_random_access_iterator();
            const_random_access_iterator(const_random_access_iterator const &) noexcept;
            template<class ...Args>
            explicit const_random_access_iterator(Args &&...);

            bool operator==(const_random_access_iterator const &) const;
            bool operator!=(const_random_access_iterator const &) const;
            bool operator==(iterator const &) const;
            bool operator!=(iterator const &) const;

            const_random_access_iterator &operator++();
            const_random_access_iterator &operator--();
            const_random_access_iterator const operator++(int);
            const_random_access_iterator const operator--(int);

            const Tp &operator*() const;
            const Tp *operator->() const;

            const_random_access_iterator operator+(size_t) const;
            const_random_access_iterator operator-(size_t) const;
            ssize_t operator-(const_random_access_iterator const &) const;
            ssize_t operator-(iterator const &) const;

            bool operator<(iterator const &) const;
            bool operator>(iterator const &) const;
            bool operator<=(iterator const &) const;
            bool operator>=(iterator const &) const;
            bool operator<(const_random_access_iterator const &) const;
            bool operator>(const_random_access_iterator const &) const;
            bool operator<=(const_random_access_iterator const &) const;
            bool operator>=(const_random_access_iterator const &) const;

            const_random_access_iterator& operator+=(size_t);
            const_random_access_iterator& operator-=(size_t);

        protected:
            iterator normal_iterator;
        };

        template<forward_iterator iterator, typename Tp>
        const_forward_iterator<iterator, Tp>::const_forward_iterator()
                : normal_iterator {} {}

        template<forward_iterator iterator, typename Tp>
        template<class... Args>
        const_forward_iterator<iterator, Tp>::const_forward_iterator(Args&&... args)
                : normal_iterator {args...} {}

        template<forward_iterator iterator, typename Tp>
        bool const_forward_iterator<iterator, Tp>::operator==
                (const const_forward_iterator &op) const
        {
            return normal_iterator==op.normal_iterator;
        }

        template<forward_iterator iterator, typename Tp>
        bool const_forward_iterator<iterator, Tp>::operator!=
                (const const_forward_iterator &op) const
        {
            return normal_iterator!=op.normal_iterator;
        }

        template<forward_iterator iterator, typename Tp>
        bool const_forward_iterator<iterator, Tp>::operator==
                (const iterator &op) const
        {
            return normal_iterator==op;
        }

        template<forward_iterator iterator, typename Tp>
        bool const_forward_iterator<iterator, Tp>::operator!=
                (const iterator &op) const
        {
            return normal_iterator!=op;
        }

        template<forward_iterator iterator, typename Tp>
        const_forward_iterator<iterator, Tp>
        &const_forward_iterator<iterator, Tp>::operator++()
        {
            ++normal_iterator;
            return *this;
        }

        template<forward_iterator iterator, typename Tp>
        const_forward_iterator<iterator, Tp> const
        const_forward_iterator<iterator, Tp>::operator++(int)
        {
            const_forward_iterator<iterator, Tp> temp =*this;
            ++(*this);
            return temp;
        }

        template<forward_iterator iterator, typename Tp>
        const Tp &const_forward_iterator<iterator, Tp>::operator*() const
        {
            const Tp &a {*normal_iterator};
            return a;
        }

        template<forward_iterator iterator, typename Tp>
        const Tp *const_forward_iterator<iterator, Tp>::operator->() const
        {
            const Tp &a {*normal_iterator};
            return &a;
        }

        template<forward_iterator iterator, typename Tp>
        const_forward_iterator<iterator, Tp>::const_forward_iterator
                (const const_forward_iterator &iter) noexcept
                :normal_iterator{iter.normal_iterator} {}

        template<bidirectional_iterator iterator, typename Tp>
        const_bidirectional_iterator<iterator, Tp>::const_bidirectional_iterator()
                : normal_iterator {} {}

        template<bidirectional_iterator iterator, typename Tp>
        template<class... Args>
        const_bidirectional_iterator<iterator, Tp>::const_bidirectional_iterator(Args&&... args)
                : normal_iterator {args...} {}

        template<bidirectional_iterator iterator, typename Tp>
        bool const_bidirectional_iterator<iterator, Tp>::operator==(const const_bidirectional_iterator &op) const
        {
            return normal_iterator==op.normal_iterator;
        }

        template<bidirectional_iterator iterator, typename Tp>
        bool const_bidirectional_iterator<iterator, Tp>::operator!=(const const_bidirectional_iterator &op) const
        {
            return normal_iterator!=op.normal_iterator;
        }

        template<bidirectional_iterator iterator, typename Tp>
        bool const_bidirectional_iterator<iterator, Tp>::operator==(const iterator &op) const
        {
            return normal_iterator==op;
        }

        template<bidirectional_iterator iterator, typename Tp>
        bool const_bidirectional_iterator<iterator, Tp>::operator!=(const iterator &op) const
        {
            return normal_iterator!=op;
        }

        template<bidirectional_iterator iterator, typename Tp>
        const_bidirectional_iterator<iterator, Tp>
        &const_bidirectional_iterator<iterator, Tp>::operator++()
        {
            ++normal_iterator;
            return *this;
        }

        template<bidirectional_iterator iterator, typename Tp>
        const_bidirectional_iterator<iterator, Tp> const
        const_bidirectional_iterator<iterator, Tp>::operator++(int)
        {
            const_forward_iterator<iterator, Tp> temp =*this;
            ++(*this);
            return temp;
        }

        template<bidirectional_iterator iterator, typename Tp>
        const Tp &const_bidirectional_iterator<iterator, Tp>::operator*() const
        {
            const Tp &a {*normal_iterator};
            return a;
        }

        template<bidirectional_iterator iterator, typename Tp>
        const Tp *const_bidirectional_iterator<iterator, Tp>::operator->() const
        {
            const Tp &a {*normal_iterator};
            return &a;
        }

        template<bidirectional_iterator iterator, typename Tp>
        const_bidirectional_iterator<iterator, Tp>
        &const_bidirectional_iterator<iterator, Tp>::operator--()
        {
            --normal_iterator;
            return *this;
        }

        template<bidirectional_iterator iterator, typename Tp>
        const_bidirectional_iterator<iterator, Tp> const
        const_bidirectional_iterator<iterator, Tp>::operator--(int)
        {
            const_bidirectional_iterator<iterator, Tp> temp {*this};
            --(*this);
            return temp;
        }

        template<bidirectional_iterator iterator, typename Tp>
        const_bidirectional_iterator<iterator, Tp>::const_bidirectional_iterator
                (const const_bidirectional_iterator &iter) noexcept
                : normal_iterator{iter.normal_iterator} {}

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp>::const_random_access_iterator()
                : normal_iterator {} {}

        template<random_access_iterator iterator, typename Tp>
        template<class... Args>
        const_random_access_iterator<iterator, Tp>::const_random_access_iterator(Args&&... args)
                : normal_iterator {args...} {}

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator==(const const_random_access_iterator &op) const
        {
            return normal_iterator==op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator!=(const const_random_access_iterator &op) const
        {
            return normal_iterator!=op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator==(const iterator &op) const
        {
            return normal_iterator==op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator!=(const iterator &op) const
        {
            return normal_iterator!=op;
        }

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp>
        &const_random_access_iterator<iterator, Tp>::operator++()
        {
            ++normal_iterator;
            return *this;
        }

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp> const
        const_random_access_iterator<iterator, Tp>::operator++(int)
        {
            const_random_access_iterator<iterator, Tp> temp = *this;
            ++(*this);
            return temp;
        }

        template<random_access_iterator iterator, typename Tp>
        const Tp &const_random_access_iterator<iterator, Tp>::operator*() const
        {
            const Tp &a {*normal_iterator};
            return a;
        }

        template<random_access_iterator iterator, typename Tp>
        const Tp *const_random_access_iterator<iterator, Tp>::operator->() const
        {
            const Tp &a {*normal_iterator};
            return &a;
        }

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp>
        &const_random_access_iterator<iterator, Tp>::operator--()
        {
            --normal_iterator;
            return *this;
        }

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp> const
        const_random_access_iterator<iterator, Tp>::operator--(int)
        {
            const_random_access_iterator<iterator, Tp> temp {*this};
            --(*this);
            return temp;
        }

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp>
        const_random_access_iterator<iterator, Tp>::operator+(size_t dev) const
        {
            const_random_access_iterator<iterator, Tp> res {*this};
            res+=dev;
            return res;
        }

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp>
        const_random_access_iterator<iterator, Tp>::operator-(size_t dev) const
        {
            const_random_access_iterator<iterator, Tp> res {*this};
            res-=dev;
            return res;
        }

        template<random_access_iterator iterator, typename Tp>
        ssize_t const_random_access_iterator<iterator, Tp>::operator-(const const_random_access_iterator &op) const
        {
            return (normal_iterator-op.normal_iterator);
        }

        template<random_access_iterator iterator, typename Tp>
        ssize_t const_random_access_iterator<iterator, Tp>::operator-(const iterator &op) const
        {
            return normal_iterator-op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator<(const iterator &op) const
        {
            return normal_iterator<op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator>(const iterator &op) const
        {
            return normal_iterator>op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator<=(const iterator &op) const
        {
            return normal_iterator<=op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator>=(const iterator &op) const
        {
            return normal_iterator>=op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator<(const const_random_access_iterator &op) const
        {
            return normal_iterator<op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator>(const const_random_access_iterator &op) const
        {
            return normal_iterator>op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator<=(const const_random_access_iterator &op) const
        {
            return normal_iterator<=op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool const_random_access_iterator<iterator, Tp>::operator>=(const const_random_access_iterator &op) const
        {
            return normal_iterator>=op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp>
        &const_random_access_iterator<iterator, Tp>::operator+=
                (size_t dev)
        {
            normal_iterator+=dev;
            return *this;
        }

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp>
        &const_random_access_iterator<iterator, Tp>::operator-=
                (size_t dev)
        {
            normal_iterator-=dev;
            return *this;
        }

        template<random_access_iterator iterator, typename Tp>
        const_random_access_iterator<iterator, Tp>::const_random_access_iterator
                (const const_random_access_iterator &iter) noexcept
                :normal_iterator{iter.normal_iterator} {}

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp>::reverse_random_access_iterator()
                : normal_iterator {} {}

        template<random_access_iterator iterator, typename Tp>
        template<class ...Args>
        reverse_random_access_iterator<iterator, Tp>::reverse_random_access_iterator(Args&&... args)
                : normal_iterator {args...} {}

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator==
                (const reverse_random_access_iterator &op) const
        {
            return normal_iterator==op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator!=
                (const reverse_random_access_iterator &op) const
        {
            return normal_iterator!=op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator==(const iterator &op) const
        {
            return normal_iterator==op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator!=(const iterator &op) const
        {
            return normal_iterator!=op;
        }

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp>
        &reverse_random_access_iterator<iterator, Tp>::operator++()
        {
            --normal_iterator;
            return *this;
        }

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp>
        &reverse_random_access_iterator<iterator, Tp>::operator--()
        {
            ++normal_iterator;
            return *this;
        }

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp> const
        reverse_random_access_iterator<iterator, Tp>::operator++(int)
        {
            reverse_random_access_iterator<iterator, Tp> temp = *this;
            --normal_iterator;
            return temp;
        }

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp> const
        reverse_random_access_iterator<iterator, Tp>::operator--(int)
        {
            reverse_random_access_iterator<iterator, Tp> temp {*this};
            ++normal_iterator;
            return temp;
        }

        template<random_access_iterator iterator, typename Tp>
        Tp &reverse_random_access_iterator<iterator, Tp>::operator*()
        {
            return *normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        Tp *reverse_random_access_iterator<iterator, Tp>::operator->()
        {
            return normal_iterator.operator->();
        }

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp>
        reverse_random_access_iterator<iterator, Tp>::operator+
                (size_t dev) const
        {
            reverse_random_access_iterator<iterator, Tp> res{*this};
            res+=dev;
            return res;
        }

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp>
        reverse_random_access_iterator<iterator, Tp>::operator-
                (size_t dev) const
        {
            reverse_random_access_iterator<iterator, Tp> res{*this};
            res-=dev;
            return res;
        }

        template<random_access_iterator iterator, typename Tp>
        ssize_t reverse_random_access_iterator<iterator, Tp>::operator-
                (const reverse_random_access_iterator &iter) const
        {
            return -(normal_iterator-iter.normal_iterator);
        }

        template<random_access_iterator iterator, typename Tp>
        ssize_t reverse_random_access_iterator<iterator, Tp>::operator-
                (const iterator &iter) const
        {
            return -(normal_iterator-iter);
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator<
                (const iterator &op) const
        {
            return normal_iterator>=op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator>
                (const iterator &op) const
        {
            return normal_iterator<=op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator<=
                (const iterator &op) const
        {
            return normal_iterator>op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator>=
                (const iterator &op) const
        {
            return normal_iterator<op;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator<
                (const reverse_random_access_iterator &op) const
        {
            return normal_iterator>=op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator>
                (const reverse_random_access_iterator &op) const
        {
            return normal_iterator<=op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator<=
                (const reverse_random_access_iterator &op) const
        {
            return normal_iterator>op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        bool reverse_random_access_iterator<iterator, Tp>::operator>=
                (const reverse_random_access_iterator &op) const
        {
            return normal_iterator<op.normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp>
        &reverse_random_access_iterator<iterator, Tp>::operator+=
                (size_t dev)
        {
            normal_iterator-=dev;
            return *this;
        }

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp>
        &reverse_random_access_iterator<iterator, Tp>::operator-=
                (size_t dev)
        {
            normal_iterator+=dev;
            return *this;
        }

        template<random_access_iterator iterator, typename Tp>
        Tp const &reverse_random_access_iterator<iterator, Tp>::operator*() const
        {
            return *normal_iterator;
        }

        template<random_access_iterator iterator, typename Tp>
        Tp const *reverse_random_access_iterator<iterator, Tp>::operator->() const
        {
            return normal_iterator.operator->();
        }

        template<random_access_iterator iterator, typename Tp>
        reverse_random_access_iterator<iterator, Tp>::reverse_random_access_iterator
                (const reverse_random_access_iterator &iter)
                :normal_iterator{iter.normal_iterator} {}

        template<bidirectional_iterator iterator, typename Tp>
        reverse_bidirectional_iterator<iterator, Tp>::reverse_bidirectional_iterator()
                : normal_iterator{} {}

        template<bidirectional_iterator iterator, typename Tp>
        template<class ...Args>
        reverse_bidirectional_iterator<iterator, Tp>::reverse_bidirectional_iterator(Args&&... args)
                : normal_iterator{args...} {}

        template<bidirectional_iterator iterator, typename Tp>
        bool reverse_bidirectional_iterator<iterator, Tp>::operator==
                (const reverse_bidirectional_iterator &op) const
        {
            return normal_iterator==op.normal_iterator;
        }

        template<bidirectional_iterator iterator, typename Tp>
        bool reverse_bidirectional_iterator<iterator, Tp>::operator!=
                (const reverse_bidirectional_iterator &op) const
        {
            return normal_iterator!=op.normal_iterator;
        }

        template<bidirectional_iterator iterator, typename Tp>
        bool reverse_bidirectional_iterator<iterator, Tp>::operator==(const iterator &op) const
        {
            return normal_iterator==op;
        }

        template<bidirectional_iterator iterator, typename Tp>
        bool reverse_bidirectional_iterator<iterator, Tp>::operator!=(const iterator &op) const
        {
            return normal_iterator!=op;
        }

        template<bidirectional_iterator iterator, typename Tp>
        reverse_bidirectional_iterator<iterator, Tp>
        &reverse_bidirectional_iterator<iterator, Tp>::operator++()
        {
            --normal_iterator;
            return *this;
        }

        template<bidirectional_iterator iterator, typename Tp>
        reverse_bidirectional_iterator<iterator, Tp>
        &reverse_bidirectional_iterator<iterator, Tp>::operator--()
        {
            ++normal_iterator;
            return *this;
        }

        template<bidirectional_iterator iterator, typename Tp>
        reverse_bidirectional_iterator<iterator, Tp>
        const reverse_bidirectional_iterator<iterator, Tp>::operator++(int)
        {
            reverse_bidirectional_iterator<iterator, Tp> temp = *this;
            --normal_iterator;
            return temp;
        }

        template<bidirectional_iterator iterator, typename Tp>
        reverse_bidirectional_iterator<iterator, Tp>
        const reverse_bidirectional_iterator<iterator, Tp>::operator--(int)
        {
            reverse_bidirectional_iterator<iterator, Tp> temp{*this};
            ++normal_iterator;
            return temp;
        }

        template<bidirectional_iterator iterator, typename Tp>
        Tp &reverse_bidirectional_iterator<iterator, Tp>::operator*()
        {
            return *normal_iterator;
        }

        template<bidirectional_iterator iterator, typename Tp>
        Tp *reverse_bidirectional_iterator<iterator, Tp>::operator->()
        {
            return normal_iterator.operator->();
        }

        template<bidirectional_iterator iterator, typename Tp>
        Tp const &reverse_bidirectional_iterator<iterator, Tp>::operator*() const
        {
            return *normal_iterator;
        }

        template<bidirectional_iterator iterator, typename Tp>
        Tp const *reverse_bidirectional_iterator<iterator, Tp>::operator->() const
        {
            return normal_iterator.operator->();
        }

        template<bidirectional_iterator iterator, typename Tp>
        reverse_bidirectional_iterator<iterator, Tp>::reverse_bidirectional_iterator
                (const reverse_bidirectional_iterator &iter):
                normal_iterator{iter.normal_iterator} {}

    }
}

template<ax::random_access_iterator iterator>
iterator &operator+(size_t value, iterator iter)
{
    return iter+value;
}

#endif //DATASTRUCTURE_ITERATOR_HPP
