#ifndef DATASTRUCTURE_VECTOR_HPP
#define DATASTRUCTURE_VECTOR_HPP

#include <initializer_list>
#include "iterator.hpp"
#include <algorithm>

#ifndef ax_size
#define ax_size
typedef unsigned long long size_t;
typedef long long ssize_t;
#endif

namespace ax {
    template<class cls>
    class vector
    {
    private:
        class vector_iterator final {
        public:
            vector_iterator();
            vector_iterator &operator=(vector_iterator const &) noexcept;
            vector_iterator(vector_iterator const &) noexcept;
            vector_iterator(const vector * ptr , ssize_t);

            bool operator==(vector_iterator const &) const noexcept;
            bool operator!=(vector_iterator const &) const noexcept;
            bool operator<=(vector_iterator const &) const noexcept;
            bool operator>=(vector_iterator const &) const noexcept;
            bool operator<(vector_iterator const &) const noexcept;
            bool operator>(vector_iterator const &) const noexcept;

            cls const &operator*() const noexcept;
            cls const *operator->() const noexcept;
            cls& operator*() noexcept;
            cls* operator->() noexcept;

            vector_iterator const operator++(int);
            vector_iterator const operator--(int);
            vector_iterator &operator++();
            vector_iterator &operator--();

            ssize_t operator-(vector_iterator const &) const;
            vector_iterator operator+(size_t) const;
            vector_iterator operator-(size_t) const;
            vector_iterator &operator+=(size_t);
            vector_iterator &operator-=(size_t);
            inline void valid_qualified() const;

        private:
            vector * const owner;
            ssize_t idx;
        };

    public:
        vector();
        vector(cls, size_t);
        template<forward_iterator iterator>
        vector(iterator, iterator);
        template<random_access_iterator iterator>
        vector(iterator, iterator);
        vector(std::initializer_list<cls> const &);

        ~vector();

        [[nodiscard]] size_t capacity() const noexcept;
        [[nodiscard]] size_t size() const noexcept;
        [[nodiscard]] bool empty() const noexcept;

        void reserve(size_t);
        void shrink_to_fit();
        void resize(size_t);

        template<class ...Args>
        void emplace(vector_iterator, Args...);
        template<class ...Args>
        void emplace_back(Args...) noexcept;
        void push_back(cls const &);
        void push_back(cls &&);
        void pop_back();

        void insert(vector_iterator, cls const &);
        void insert(vector_iterator, size_t, cls const &);
        template<forward_iterator iter>
        void insert(vector_iterator, iter, iter);
        template<random_access_iterator iter>
        void insert(vector_iterator, iter, iter);
        void insert(vector_iterator, cls &&);
        template<iterable_container container>
        void insert(vector_iterator, container const &);

        template<forward_iterator iter>
        void assign(iter, iter);

        void erase(vector_iterator);
        void swap(vector<cls> &) noexcept;
        void clear() noexcept;

        using vecr_iterator = iter_template::reverse_random_access_iterator<vector_iterator, cls>;
        using vecc_iterator = iter_template::const_random_access_iterator<vector_iterator, cls>;
        using vecrc_iterator = iter_template::const_random_access_iterator<vecr_iterator, cls>;

        vector_iterator begin() noexcept;
        vector_iterator end() noexcept;
        vecr_iterator rbegin() noexcept;
        vecr_iterator rend() noexcept;
        vecc_iterator cbegin() const noexcept;
        vecc_iterator cend() const noexcept;
        vecrc_iterator crbegin() const noexcept;
        vecrc_iterator crend() const noexcept;

        bool operator==(vector const &op) const noexcept;
        bool operator!=(vector const &op) const noexcept;
        bool operator<=(vector const &op) const noexcept;
        bool operator>=(vector const &op) const noexcept;
        bool operator<(vector const &op) const noexcept;
        bool operator>(vector const &op) const noexcept;

        cls &operator[](size_t);
        cls &at(size_t) noexcept;
        cls &front();
        cls &back();
        cls *data();

    protected:
        size_t Capacity, Size;
        cls *array;
    };

    template<class cls>
    vector<cls>::vector_iterator::vector_iterator()
            : owner{nullptr}, idx {} {}

    template<class cls>
    vector<cls>::vector_iterator::vector_iterator(const vector * const ptr, ssize_t n)
            : owner{const_cast<vector * const>(ptr)}, idx{n} {}

    template<class cls>
    bool vector<cls>::vector_iterator::operator==
            (const vector::vector_iterator &op) const noexcept
    {
        if (owner!=op.owner) return false;
        return idx==op.idx;
    }

    template<class cls>
    bool vector<cls>::vector_iterator::operator!=
            (const vector::vector_iterator &op) const noexcept
    {
        if (owner!=op.owner) return true;
        return idx!=op.idx;
    }

    template<class cls>
    bool vector<cls>::vector_iterator::operator<=
            (const vector::vector_iterator &op) const noexcept
    {
        return idx<=op.idx;
    }

    template<class cls>
    bool vector<cls>::vector_iterator::operator>=
            (const vector::vector_iterator &op) const noexcept {
        return idx>=op.idx;
    }

    template<class cls>
    bool vector<cls>::vector_iterator::operator<
            (const vector::vector_iterator &op) const noexcept
    {
        return idx<op.idx;
    }

    template<class cls>
    bool vector<cls>::vector_iterator::operator>
            (const vector::vector_iterator &op) const noexcept
    {
        return idx>op.idx;
    }

    template<class cls>
    cls &vector<cls>::vector_iterator::operator*() noexcept
    {
        return owner->at(idx);
    }

    template<class cls>
    cls *vector<cls>::vector_iterator::operator->() noexcept
    {
        return &owner->at(idx);
    }

    template<class cls>
    const typename vector<cls>::vector_iterator vector<cls>::vector_iterator::operator++(int)
    {
        vector_iterator temp {*this};
        ++(*this);
        return temp;
    }

    template<class cls>
    const typename vector<cls>::vector_iterator vector<cls>::vector_iterator::operator--(int)
    {
        vector_iterator temp {*this};
        --(*this);
        return temp;
    }

    template<class cls>
    typename vector<cls>::vector_iterator &vector<cls>::vector_iterator::operator++()
    {
        ++idx;
        return *this;
    }

    template<class cls>
    typename vector<cls>::vector_iterator &vector<cls>::vector_iterator::operator--()
    {
        --idx;
        return *this;
    }

    template<class cls>
    ssize_t vector<cls>::vector_iterator::operator-(const vector::vector_iterator &op) const {
        if (owner!=op.owner) return false;
        return idx-op.idx;
    }

    template<class cls>
    typename vector<cls>::vector_iterator vector<cls>::vector_iterator::operator+(size_t n) const {
        vector_iterator res {*this};
        res+=n;
        return res;
    }

    template<class cls>
    typename vector<cls>::vector_iterator vector<cls>::vector_iterator::operator-(size_t n) const {
        vector_iterator res {*this};
        res-=n;
        return res;
    }

    template<class cls>
    typename vector<cls>::vector_iterator &vector<cls>::vector_iterator::operator+=(size_t n) {
        idx+=n;
        return *this;
    }

    template<class cls>
    typename vector<cls>::vector_iterator &vector<cls>::vector_iterator::operator-=(size_t n) {
        idx-=n;
        return *this;
    }

    template<class cls>
    void vector<cls>::vector_iterator::valid_qualified() const
    {
        if (idx<0||idx>=owner->Size) throw;
    }

    template<class cls>
    typename vector<cls>::vector_iterator &vector<cls>::vector_iterator::operator=
            (const vector::vector_iterator &iter) noexcept {
        if (*this==iter) return *this;
        if (owner!=iter.owner) throw;
        idx=iter.idx;
        return *this;
    }

    template<class cls>
    cls const &vector<cls>::vector_iterator::operator*() const noexcept {
        return owner->at(idx);
    }

    template<class cls>
    vector<cls>::vector_iterator::vector_iterator
            (const vector::vector_iterator &op) noexcept
            :owner{op.owner}, idx{op.idx} {}

    template<class cls>
    cls const *vector<cls>::vector_iterator::operator->()
    const noexcept
    {
        return &owner->at(idx);
    }

    template<class cls>
    vector<cls>::vector()
            : Capacity{32}, Size{}, array{new cls[32] {}} {}

    template<class cls>
    vector<cls>::vector(cls var, unsigned long long int n)
            : Capacity{2*n}, Size{}, array{new cls[2 * n] {}}
    {
        for(size_t i=0;i!=n;++i)
        {
            array[i] = var;
        }
    }

    template<class cls>
    template<forward_iterator iterator>
    vector<cls>::vector(iterator begin, iterator end)
    :Capacity{32}, Size{}, array{new cls[32] {}}
{
size_t idx=0;
for(iterator iter=begin;iter!=end;++iter, ++idx)
{
push_back(*iter);
}
}

template<class cls>
template<random_access_iterator iterator>
vector<cls>::vector(iterator begin, iterator end)
:Capacity{2*(end-begin)}, Size{}, array{new cls[2*(end-begin)] {}}
{
size_t idx=0;
for(iterator iter=begin;iter!=end;++iter, ++idx)
{
push_back(*iter);
}
}

template<class cls>
vector<cls>::~vector()
{
    delete[] array;
}

template<class cls>
size_t vector<cls>::size() const noexcept
{
    return Size;
}

template<class cls>
size_t vector<cls>::capacity() const noexcept
{
    return Capacity;
}

template<class cls>
bool vector<cls>::empty() const noexcept
{
    return Size==0;
}

template<class cls>
void vector<cls>::reserve(size_t tar)
{
    cls *old = array;
    size_t s = tar<Capacity?tar:Capacity;
    array = new cls[tar] {};
    for(int i=0;i!=s;++i)
    {
        array[i] = old[i];
    }
}

template<class cls>
void vector<cls>::shrink_to_fit()
{
    reserve(Size);
}

template<class cls>
void vector<cls>::resize(size_t tar)
{
    reserve(tar);
    if (tar>Size)
    {
        for(size_t i=Size; i!=tar;++i)
        {
            array[i] = cls{};
        }
    }
}

template<class cls>
void vector<cls>::pop_back()
{
    if(empty()) throw;
    --Size;
}

template<class cls>
void vector<cls>::push_back(const cls &var)
{
    if(Size==Capacity) reserve(2*Capacity);
    array[Size++] = var;
}

template<class cls>
void vector<cls>::push_back(cls &&var)
{
    if(Size==Capacity) reserve(2*Capacity);
    array[Size++] = std::move(var);
}

template<class cls>
cls &vector<cls>::front()
{
    if (empty()) throw;
    return array[0];
}

template<class cls>
cls &vector<cls>::back()
{
    if (empty()) throw;
    return array[Size-1];
}

template<class cls>
void vector<cls>::clear() noexcept
{
    delete[] array;
    array = new cls[32] {};
    Size = 0, Capacity = 32;
}

template<class cls>
cls *vector<cls>::data()
{
    return array;
}

template<class cls>
cls &vector<cls>::operator[](size_t idx)
{
    return array[idx];
}

template<class cls>
cls &vector<cls>::at(size_t idx) noexcept
{
    if (idx>=Size) return *new cls{};
    return array[idx];
}

template<class cls>
void vector<cls>::swap(vector<cls> &op) noexcept
{
    cls *ta = array;
    size_t ts = Size, tc=Capacity;
    array = op.array; Size = op.Size; Capacity=op.Capacity;
    op.array = ta; op.Size = ts; op.Capacity = ts;
}

template<class cls>
template<forward_iterator iter>
void vector<cls>::assign(iter begin, iter end)
{
clear();
try
{
reserve(end-begin);
} catch (...) {}
for(iter i=begin;i!=end;++i)
{
push_back(*i);
}
}

template<class cls>
bool vector<cls>::operator==(const vector &op) const noexcept
{
    auto iter = begin(), oi = op.begin();
    auto en = end(), oe = op.end;
    for(;iter!=en&&oi!=oe;++iter, ++oi)
    {
        if (*iter!=*oi) return false;
    }
    if (iter!=en||oi!=oe) return false;
    return true;
}

template<class cls>
bool vector<cls>::operator!=(const vector &op) const noexcept
{
    auto iter = begin(), oi = op.begin();
    auto en = end(), oe = op.end;
    for(;iter!=en&&oi!=oe;++iter, ++oi)
    {
        if (*iter!=*oi) return true;
    }
    if (iter!=en||oi!=oe) return true;
    return false;
}

template<class cls>
bool vector<cls>::operator<=(const vector &op) const noexcept
{
    auto iter = begin(), oi = op.begin();
    auto en = end(), oe = op.end;
    for(;iter!=en&&oi!=oe;++iter, ++oi)
    {
        if (*iter>*oi) return false;
        if (*iter<*oi) return true;
    }
    return iter==en;
}

template<class cls>
bool vector<cls>::operator>=(const vector &op) const noexcept
{
    auto iter = begin(), oi = op.begin();
    auto en = end(), oe = op.end;
    for(;iter!=en&&oi!=oe;++iter, ++oi)
    {
        if (*iter<*oi) return false;
        if (*iter>*oi) return true;
    }
    return oi==oe;
}

template<class cls>
bool vector<cls>::operator<(const vector &op) const noexcept
{
    auto iter = begin(), oi = op.begin();
    auto en = end(), oe = op.end;
    for(;iter!=en&&oi!=oe;++iter, ++oi)
    {
        if (*iter>*oi) return false;
        if (*iter<*oi) return true;
    }
    return iter==en&&oi!=oe;
}

template<class cls>
bool vector<cls>::operator>(const vector &op) const noexcept
{
    auto iter = begin(), oi = op.begin();
    auto en = end(), oe = op.end;
    for(;iter!=en&&oi!=oe;++iter, ++oi)
    {
        if (*iter<*oi) return false;
        if (*iter>*oi) return true;
    }
    return iter!=en&&oi==oe;
}

template<class cls>
template<class... Args>
void vector<cls>::emplace_back(Args... args) noexcept
{
    if (Capacity==Size) reserve(2*Size);
    array[Size++] = cls {args...};
}

template<class cls>
void vector<cls>::insert(vector::vector_iterator iter, const cls &var)
{
    iter.valid_qualified();
    if (Size==Capacity) reserve(2*Size);
    ++Size;
    for(vecr_iterator i=rbegin();i!=iter;++i)
    {
        *i = *(i+1);
    }
    *iter = var;
}

template<class cls>
void vector<cls>::insert(vector::vector_iterator iter, size_t n, const cls &var)
{
    iter.valid_qualified();
    if (Size+n>=Capacity) reserve(2*Size+n);
    Size += n;
    for(vecr_iterator i=rbegin();i!=iter;++i)
    {
        *i = *(i+n);
    }
    for(;n!=0;--n,++iter)
    {
        *iter = var;
    }
}

template<class cls>
template<class... Args>
void vector<cls>::emplace(vector::vector_iterator iter, Args...args)
{
    iter.valid_qualified();
    if (Size==Capacity) reserve(2*Size);
    vector_iterator end = end();
    ++Size;
    for(vecr_iterator i=rbegin();i!=iter;++i)
    {
        *i = *(i+1);
    }
    *iter = cls{args...};
}

template<class cls>
template<forward_iterator iter>
void vector<cls>::insert
        (vector::vector_iterator pos, iter input_iter_I, iter input_iter_II)
{
    pos.valid_qualified();
    cls *ptr = new cls [2*Size];
    size_t idx {}, len{};
    for(auto i=begin();i!=pos;++i)
    {
        ptr[idx++] = *i;
    }
    for(auto outer=input_iter_I;outer!=input_iter_II;++outer, ++len)
    {
        push_back(*outer);
    }
    auto en = end();
    for(auto i=pos;i!=en;++i)
    {
        push_back(*i);
    }
    delete []array;
    array = ptr;
    Size += len;
}

template<class cls>
template<random_access_iterator iter>
void vector<cls>::insert
        (vector::vector_iterator pos, iter input_iter_I, iter input_iter_II)
{
    pos.valid_qualified();
    size_t n = input_iter_II-input_iter_I;
    if (Size+n>=Capacity) reserve(2*Size+n);
    Size += n;
    for(vecr_iterator i=rbegin();i!=pos;++i)
    {
        *i = *(i+n);
    }
    vector_iterator ii = pos;
    for(auto i=input_iter_I;i!=input_iter_II;++i, ++ii)
    {
        *ii=*i;
    }
}

template<class cls>
void vector<cls>::insert(vector::vector_iterator iter, cls &&var)
{
    iter.valid_qualified();
    if (Size==Capacity) reserve(2*Size);
    vector_iterator end = end();
    ++Size;
    for(vecr_iterator i=rbegin();i!=iter;++i)
    {
        *i = *(i+1);
    }
    *iter = std::move(var);
}

template<class cls>
void vector<cls>::erase(vector::vector_iterator iter)
{
    iter.valid_qualified();
    vector_iterator en = end()-1;
    for(auto i = iter;i!=en;++i)
    {
        *i = *(i+1);
    }
    --Size;
}

template<class cls>
typename vector<cls>::vector_iterator vector<cls>::begin() noexcept
{
    return vector::vector_iterator{this, 0};
}

template<class cls>
typename vector<cls>::vector_iterator vector<cls>::end() noexcept
{
    return vector::vector_iterator{this, static_cast<ssize_t>(Size)};
}

template<class cls>
typename vector<cls>::vecr_iterator vector<cls>::rbegin() noexcept
{
    return ax::vector<cls>::vecr_iterator{this, static_cast<ssize_t>(Size)-1};
}

template<class cls>
typename vector<cls>::vecr_iterator vector<cls>::rend() noexcept
{
    return ax::vector<cls>::vecr_iterator{this, -1};
}

template<class cls>
typename vector<cls>::vecc_iterator vector<cls>::cbegin() const noexcept
{
    return ax::vector<cls>::vecc_iterator{this, 0};
}

template<class cls>
typename vector<cls>::vecc_iterator vector<cls>::cend() const noexcept
{
    return ax::vector<cls>::vecc_iterator{this, static_cast<ssize_t>(Size)};
}

template<class cls>
typename vector<cls>::vecrc_iterator vector<cls>::crbegin() const noexcept
{
    return ax::vector<cls>::vecrc_iterator{this, static_cast<ssize_t>(Size)-1};
}

template<class cls>
typename vector<cls>::vecrc_iterator vector<cls>::crend() const noexcept
{
    return ax::vector<cls>::vecrc_iterator{this, -1};
}

template<class cls>
vector<cls>::vector(const std::initializer_list<cls> &list)
        :Capacity{2*list.size()}, Size{list.size()}, array{new cls[2*list.size()] {}}
{
    size_t idx=0;
    for(auto const &iter:list)
    {
        array[idx++] = iter;
    }
}

template<class cls>
void swap(vector<cls> &x, vector<cls> &y)
{
    x.swap(y);
}
}

template<typename cls>
typename ax::vector<cls>::vector_iterator operator+
(size_t n, typename ax::vector<cls>::vector_iterator iter)
{
    return iter+n;
}

template<typename cls>
typename ax::vector<cls>::vecr_iterator operator+
(size_t n, typename ax::vector<cls>::vecr_iterator iter)
{
    return iter+n;
}

template<typename cls>
typename ax::vector<cls>::veccr_iterator operator+
(size_t n, typename ax::vector<cls>::vecc_iterator iter)
{
    return iter+n;
}

template<typename cls>
typename ax::vector<cls>::vecrc_iterator operator+
(size_t n, typename ax::vector<cls>::vecrc_iterator iter)
{
    return iter+n;
}


#endif //DATASTRUCTURE_VECTOR_HPP
