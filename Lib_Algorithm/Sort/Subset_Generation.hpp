#ifndef DATASTRUCTURE_SUBSET_GENERATION_HPP
#define DATASTRUCTURE_SUBSET_GENERATION_HPP

#include <vector>
#include <iterator>

template<class cls>
concept Iterable_Container = requires (cls instance)
{
    instance.operator[](0);
    instance.size();
};

inline size_t valid_length(size_t k) {
    size_t ans {};
    while(k!=0) {
        k = k&(k-1);
        ++ans;
    }
    return ans;
}

template<Iterable_Container Container, typename Tp>
class Subset_Generator {
public:
    Subset_Generator(): _owner{} {}

    Subset_Generator adapt(Container const &);

    struct _iterator {
        Container const *_owner;
        ssize_t _bit;

        _iterator():_owner{nullptr}, _bit{} {}

        _iterator const operator++(int) const;
        _iterator const operator--(int) const;
        _iterator &operator++();
        _iterator &operator--();

        bool operator>(_iterator const &) const;
        bool operator<(_iterator const &) const;
        bool operator>=(_iterator const &) const;
        bool operator<=(_iterator const &) const;
        bool operator==(_iterator const &) const;
        bool operator!=(_iterator const &) const;

        inline void valid(_iterator const &) const;
        std::vector<Tp> &operator*();
        std::vector<Tp> *operator->();
    };

    struct _r_iterator {
        Container const *_owner;
        ssize_t _bit;
        _r_iterator const operator++(int) const;
        _r_iterator const operator--(int) const;
        _r_iterator &operator++();
        _r_iterator &operator--();

        bool operator>(_r_iterator const &) const;
        bool operator<(_r_iterator const &) const;
        bool operator>=(_r_iterator const &) const;
        bool operator<=(_r_iterator const &) const;
        bool operator==(_r_iterator const &) const;
        bool operator!=(_r_iterator const &) const;

        inline void valid(_r_iterator const &) const;
        std::vector<Tp> &operator*();
        std::vector<Tp> *operator->();
    };

    _iterator begin();

    _iterator end();

    _r_iterator rbegin();

    _r_iterator rend();
private:
    Container const *_owner;

    size_t power2(size_t);
};

template<Iterable_Container Container, typename Tp>
const typename Subset_Generator<Container, Tp>::_iterator
Subset_Generator<Container, Tp>::_iterator::operator++(int) const {
    Subset_Generator::_iterator _temp {*this};
    ++(*this);
    return _temp;
}

template<Iterable_Container Container, typename Tp>
const typename Subset_Generator<Container, Tp>::_iterator
Subset_Generator<Container, Tp>::_iterator::operator--(int) const {
    Subset_Generator::_iterator _temp {*this};
    --(*this);
    return _temp;
}

template<Iterable_Container Container, typename Tp>
typename Subset_Generator<Container, Tp>::_iterator &
Subset_Generator<Container, Tp>::_iterator::_iterator::operator++() {
    ++_bit;
    return *this;
}

template<Iterable_Container Container, typename Tp>
typename Subset_Generator<Container, Tp>::_iterator &
Subset_Generator<Container, Tp>::_iterator::_iterator::operator--() {
    --_bit;
    return *this;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_iterator::operator>
(const Subset_Generator::_iterator &iter) const {
    valid(iter);
    return this->_bit>iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_iterator::operator<
(const Subset_Generator::_iterator &iter) const {
    valid(iter);
    return this->_bit<iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_iterator::operator>=
(const Subset_Generator::_iterator &iter) const {
    valid(iter);
    return this->_bit>=iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_iterator::operator<=
(const Subset_Generator::_iterator &iter) const {
    valid(iter);
    return this->_bit<=iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_iterator::operator==
(const Subset_Generator::_iterator &iter) const {
    valid(iter);
    return this->_bit==iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_iterator::operator!=
(const Subset_Generator::_iterator &iter) const {
    valid(iter);
    return this->_bit!=iter._bit;
}

template<Iterable_Container Container, typename Tp>
void Subset_Generator<Container, Tp>::_iterator::valid(const Subset_Generator::_iterator &op) const {
    if (this->_owner!=op._owner) throw;
}

template<Iterable_Container Container, typename Tp>
std::vector<Tp> &Subset_Generator<Container, Tp>::_iterator::operator*() {
    auto &_res = *new std::vector<Tp>{};
    _res.reserve(valid_length(_bit));
    size_t method {_bit}, dev{};
    while(method!=0) {
        if (method%2) _res.template emplace_back((*_owner)[dev]);
        ++dev;
        method/=2;
    }
    return _res;
}

template<Iterable_Container Container, typename Tp>
std::vector<Tp> *Subset_Generator<Container, Tp>::_iterator::operator->() {
    auto &_res = *new std::vector<Tp>{};
    _res.reserve(valid_length(_bit));
    size_t method {_bit}, dev{};
    while(method!=0) {
        if (method%2) _res.template emplace_back((*_owner)[dev]);
        ++dev;
        method/=2;
    }
    return &_res;
}

template<Iterable_Container Container, typename Tp>
const typename Subset_Generator<Container, Tp>::_r_iterator
Subset_Generator<Container, Tp>::_r_iterator::operator++(int) const {
    auto _ans {*this};
    ++(*this);
    return _ans;
}

template<Iterable_Container Container, typename Tp>
const typename Subset_Generator<Container, Tp>::_r_iterator
Subset_Generator<Container, Tp>::_r_iterator::operator--(int) const {
    auto _ans {*this};
    --(*this);
    return _ans;
}

template<Iterable_Container Container, typename Tp>
typename Subset_Generator<Container, Tp>::_r_iterator&
Subset_Generator<Container, Tp>::_r_iterator::operator++() {
    --_bit;
    return *this;
}

template<Iterable_Container Container, typename Tp>
typename Subset_Generator<Container, Tp>::_r_iterator&
Subset_Generator<Container, Tp>::_r_iterator::operator--() {
    ++_bit;
    return *this;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_r_iterator::operator>
(const Subset_Generator::_r_iterator &iter) const {
    valid(iter);
    return this->_bit<iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_r_iterator::operator<
        (const Subset_Generator::_r_iterator &iter) const {
    valid(iter);
    return this->_bit>iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_r_iterator::operator>=
        (const Subset_Generator::_r_iterator &iter) const {
    valid(iter);
    return this->_bit<=iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_r_iterator::operator<=
        (const Subset_Generator::_r_iterator &iter) const {
    valid(iter);
    return this->_bit>=iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_r_iterator::operator==
        (const Subset_Generator::_r_iterator &iter) const {
    valid(iter);
    return this->_bit==iter._bit;
}

template<Iterable_Container Container, typename Tp>
bool Subset_Generator<Container, Tp>::_r_iterator::operator!=
        (const Subset_Generator::_r_iterator &iter) const {
    valid(iter);
    return this->_bit!=iter._bit;
}

template<Iterable_Container Container, typename Tp>
void Subset_Generator<Container, Tp>::_r_iterator::
valid(const Subset_Generator::_r_iterator &iter) const {
    if (this->_owner!=iter._owner) throw;
}

template<Iterable_Container Container, typename Tp>
std::vector<Tp> &Subset_Generator<Container, Tp>::_r_iterator::operator*() {
    auto &_res = *new std::vector<Tp>{};
    _res.reserve(valid_length(_bit));
    size_t method {_bit}, dev{};
    while(method!=0) {
        if (method%2) _res.template emplace_back((*_owner)[dev]);
        ++dev;
        method/=2;
    }
    return _res;
}

template<Iterable_Container Container, typename Tp>
std::vector<Tp> *Subset_Generator<Container, Tp>::_r_iterator::operator->() {
    auto &_res = *new std::vector<Tp>{};
    _res.reserve(valid_length(_bit));
    size_t method {_bit}, dev{};
    while(method!=0) {
        if (method%2) _res.template emplace_back((*_owner)[dev]);
        ++dev;
        method/=2;
    }
    return &_res;
}

template<Iterable_Container Container, typename Tp>
Subset_Generator<Container, Tp> Subset_Generator<Container, Tp>::
adapt(const Container &container)
{
    return Subset_Generator{&container};
}

template<Iterable_Container Container, typename Tp>
typename Subset_Generator<Container, Tp>::_iterator
Subset_Generator<Container, Tp>::begin() {
    return Subset_Generator::_iterator{this->_owner, 0};
}

template<Iterable_Container Container, typename Tp>
typename Subset_Generator<Container, Tp>::_iterator
Subset_Generator<Container, Tp>::end() {
    return Subset_Generator::_iterator {this->_owner, power2(_owner->size())};
}

template<Iterable_Container Container, typename Tp>
typename Subset_Generator<Container, Tp>::_r_iterator
Subset_Generator<Container, Tp>::rbegin() {
    return Subset_Generator::_r_iterator {this->_owner, power2(_owner->size())-1};
}

template<Iterable_Container Container, typename Tp>
typename Subset_Generator<Container, Tp>::_r_iterator
Subset_Generator<Container, Tp>::rend() {
    return Subset_Generator::_r_iterator {this->_owner, -1};
}

template<Iterable_Container Container, typename Tp>
size_t Subset_Generator<Container, Tp>::power2(size_t x) {
    size_t _ans {1};
    while(x!=0) {
        _ans*=2;
        --x;
    }
    return _ans;
}


#endif //DATASTRUCTURE_SUBSET_GENERATION_HPP
