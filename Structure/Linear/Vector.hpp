#ifndef DATASTRUCTURE_VECTOR_HPP
#define DATASTRUCTURE_VECTOR_HPP

#include <iterator>
#include <array>

template<typename Tp>
class Vector {
protected:
    class vector_iterator: std::iterator<std::random_access_iterator_tag, Tp> {
    public:
        explicit vector_iterator(Vector &vec)
        : owner{vec}, ticks{} {}

        vector_iterator(Vector &vec, size_t x)
        : owner{vec}, ticks{x} {}

        vector_iterator &operator=(vector_iterator const &) noexcept = default;
        vector_iterator &operator=(vector_iterator &&) noexcept = default;
        vector_iterator(vector_iterator const &) noexcept = default;
        vector_iterator(vector_iterator &&) noexcept = default;
        ~vector_iterator() = default;

        Tp *operator->() {
            if (owner.overflow(ticks)) return nullptr;
            return owner.at + ticks;
        }

        Tp &operator*() {
            if (owner.overflow(ticks)) throw;
            return owner.at[ticks];
        }

        vector_iterator operator++(int) const {
            vector_iterator _temp {this};
            ++(*this);
            return _temp;
        }

        vector_iterator operator--(int) const {
            if (ticks == 0) throw;
            vector_iterator _temp {this};
            --(*this);
            return _temp;
        }

        vector_iterator operator+(ssize_t x) const {
            vector_iterator _temp {this};
            _temp += x;
            return _temp;
        }

        vector_iterator operator-(ssize_t x) const {
            vector_iterator _temp {this};
            _temp -= x;
            return _temp;
        }

        vector_iterator &operator+=(ssize_t x) {
            this->ticks += x;
            return *this;
        }

        vector_iterator &operator-=(ssize_t x) {
            if (ticks < x) throw;
            this->ticks -= x;
            return *this;
        }

        Tp &operator[](size_t x) {
            return owner.operator[](x);
        }

        ptrdiff_t operator-(vector_iterator const &iter) {
            return this->ticks - iter.ticks;
        }

        bool operator==(vector_iterator const &op) const {
            if (this->owner != this->owner) throw;
            return this->ticks == op.ticks;
        }

        bool operator!=(vector_iterator const &op) const {
            if (this->owner != this->owner) throw;
            return this->ticks != op.ticks;
        }

        bool operator>(vector_iterator const &op) const {
            if (this->owner != this->owner) throw;
            return this->ticks > op.ticks;
        }

        bool operator<(vector_iterator const &op) const {
            if (this->owner != this->owner) throw;
            return this->ticks < op.ticks;
        }

        bool operator>=(vector_iterator const &op) const {
            if (this->owner != this->owner) throw;
            return this->ticks >= op.ticks;
        }

        bool operator<=(vector_iterator const &op) const {
            if (this->owner != this->owner) throw;
            return this->ticks <= op.ticks;
        }

        vector_iterator &operator++() {
            ++ticks;
            return *this;
        }

        vector_iterator &operator--() {
            if (ticks == 0) throw;
            --ticks;
            return *this;
        }

    protected:
        Vector& owner;
        size_t ticks;
    };

    size_t Capacity;
    size_t Size;
    Tp *Container;

public:
    Vector(std::initializer_list<Tp> &&list):
    Capacity{2*list.size()}, Size{list.size()}, Container{new Tp[2*list.size()]} {
        size_t tick {};
        for (auto const &iter:list) Container[tick++] = iter;
    }

    template<class cls, template<class elem, typename=std::allocator<elem>> class Cont>
    explicit Vector(Cont<Tp> const &container):
    Capacity{2*container.index()}, Size{container.index()}, Container{new Tp[2 * container.index()]} {
        size_t tick {};
        for (auto const &iter:container) Container[tick++] = iter;
    }

    template<size_t n>
    explicit Vector(std::array<Tp, n> const &array):
    Capacity{2*n}, Size{n}, Container{new Tp[2*n]} {
        size_t tick{};
        for (auto const &iter:array) Container[tick++] = iter;
    }

    template<size_t n>
    explicit Vector(Tp const (&arr)[n]):
    Capacity{2*n}, Size{n}, Container{new Tp[2*n]} {
        for (size_t tick=0;tick!=n;++tick) {
            Container[tick] = arr[tick];
        }
    }

    Vector(Tp const * const &ptr, size_t n):
    Capacity{2*n}, Size{n}, Container{new Tp[2*n]} {
        for (size_t tick=0;tick!=n;++tick) {
            Container[tick] = *(ptr+tick);
        }
    }

    Vector(Tp const &value, size_t n):
    Capacity{2*n}, Size{n}, Container{new Tp[2*n]} {
        for (size_t tick=0;tick!=n;++tick) {
            Container[tick] = value;
        }
    }

    size_t size() noexcept {
        return Size;
    }

    bool empty() noexcept {
        return Size==0;
    }

    void resize(size_t new_size) {
        if (new_size > Size) {
            size_t _size = Size;
            reverse(new_size);
            for (size_t i=_size;i!=new_size;++i) Container[i] = Tp{};
        } else {
            reverse(new_size);
        }
    }

    void reverse(size_t new_cap) {
        Tp *Room = new Tp[new_cap];
        for (size_t i=0;i!= new_cap > Size ? Size : new_cap; ++i) {
            Room[i] = Container[i];
        }
        delete[] Container;
        Container = Room;
    }

    void shrink() {
        reverse(Size);
    }

    inline void overflow(size_t x) const {
        if (x>=Size) throw;
    }

    template<class cls>
    void push(vector_iterator const &iter, cls &&elem) {
        if (Size == Capacity) reverse(static_cast<size_t>(Capacity*1.5));
        if (iter+1==end()) {
            push_back(std::forward<>(elem));
        } else {
            overflow(iter-begin());
            for(size_t i=size();i!=iter-begin();--i) {
                Container[i+1] = Container[i];
            }
            Container[iter-begin()] = std::forward<>(elem);
            ++Size;
        }
    }

    template<class cls>
    vector_iterator insert(vector_iterator const &pos, cls &&elem) {
        if (Size == Capacity) reverse(static_cast<size_t>(Capacity*1.5));
        if (pos+1==end()) {
            push_back(std::forward<>(elem));
        } else {
            overflow(pos-begin());
            for(size_t i=size();i!=pos-begin();--i) {
                Container[i+1] = Container[i];
            }
            Container[pos-begin()] = std::forward<>(elem);
            ++Size;
        }
        return vector_iterator(*this, pos-begin());
    }

    template<class cls, std::forward_iterator forward_iterator>
    vector_iterator insert(vector_iterator const &pos, forward_iterator begin, forward_iterator end) {
        size_t const _length = end-begin;
        if (Size + _length > Capacity) reverse(static_cast<size_t>((_length + Capacity)*1.5));
        if (pos+1==end()) {
            for (forward_iterator iter=begin;iter!=end;++iter) {
                push_back(std::forward<>(*iter));
            }
        } else {
            overflow(pos-begin());
            for(size_t i=size();i!=pos-begin();--i) {
                Container[i+_length] = Container[i];
            }
            for(forward_iterator iter=begin;iter!=end;++iter) {
                Container[iter-begin()] = *iter;
            }
            ++Size;
        }
        return vector_iterator(*this, pos-begin());
    }

    template<typename ...Args>
    void emplace(vector_iterator const &iter, Args const &...args) {
        push(iter, Tp{args...});
    }

    template<class cls>
    void push_back(cls &&elem) {
        if (Size == Capacity) reverse(static_cast<size_t>(Capacity*1.5));
        Container[Size++] = std::forward<>(elem);
        ++Size;
    }

    template<typename ...Args>
    void emplace_back(Args const &...args) {
        push_back(Tp{args...});
    }

    template<class cls>
    vector_iterator find(cls &&value) const {
        Tp _key {std::forward<>(value)};
        size_t _pos {};
        for (auto const &iter:*this) {
            if (_key == iter) break;
            ++_pos;
        }
        return vector_iterator(*this, _pos);
    }

    template<class cls>
    bool exist(cls &&value) const {
        Tp _key {std::forward<>(value)};
        size_t _pos {};
        for (auto const &iter:*this) {
            if (_key == iter) return true;
        }
        return false;
    }

    void remove(vector_iterator iter) {
        overflow(iter.ticks);
        this->operator[](iter.ticks) = Tp {};
        --Size;
    }

    void erase(vector_iterator iter) {
        size_t _pos = iter - begin();
        size_t _size = size();
        for (size_t i=_pos;i!=_size-1;++i) {
            Container[i] = Container[i+1];
        }
        Container[--Size] = Tp {};
    }

    Tp *data() noexcept {
        return Container;
    }

    vector_iterator at(size_t x) {
        return vector_iterator(*this, x);
    }

    Tp &operator[](size_t x) {
        overflow(x);
        return Container[x];
    }

    template<class ...cls>
    void assign(size_t x, cls &&...value) {
        Tp *Room = new Tp[2*x];
        Tp elem {value...};
        for (size_t i=0;i!=x;++i) {
            Room[i] = elem;
        }
        delete[] Container;
        Container = Room;
    }

    void assign(vector_iterator const &begin, vector_iterator const &end) {
        Tp _unit {};
        for (vector_iterator iter=begin;iter!=end;++iter) {
            *iter = _unit++;
        }
    }

    template<class cls>
    void assign(vector_iterator const &begin, vector_iterator const &end, cls &&value) {
        Tp _unit {std::forward<>(value)};
        for (vector_iterator iter=begin;iter!=end;++iter) {
            *iter = _unit++;
        }
    }

    Vector &operator=(Vector const &) noexcept = default;
    Vector &operator=(Vector &&) noexcept = default;
    Vector(Vector const &) noexcept = default;
    Vector(Vector &&) noexcept = default;
    ~Vector() = default;

    vector_iterator begin() {
        return vector_iterator(*this, 0);
    }

    vector_iterator end() {
        return vector_iterator(*this, Size);
    }

    vector_iterator cbegin() const {
        return vector_iterator(*this, 0);
    }

    vector_iterator cend() const {
        return vector_iterator(*this, Size);
    }
};


#endif //DATASTRUCTURE_VECTOR_HPP
