#ifndef DATASTRUCTURE_KMP_HPP
#define DATASTRUCTURE_KMP_HPP

#include <string>
#include <vector>
#include <cmath>

template<class cls>
        concept iterable = requires(cls c) {c.begin(); c.back(); c.begin().operator++();};

using str = std::string;

class Re {
public:
    static Re &Instance();

    Re &operator=(Re const &) noexcept = delete;

    Re &operator=(Re &&) noexcept = delete;

    Re(Re const &) noexcept = delete;

    Re(Re &&) noexcept = delete;

    [[nodiscard]] static size_t find (str const &, str const &);

    [[nodiscard]] static size_t find_between(str const &, str const &, size_t const &, size_t const &);

    [[nodiscard]] static size_t naive_find(str const &, str const &);

    [[nodiscard]] static bool naive_equal(str const &, str const &);

    [[nodiscard]] static str slice(str const &, size_t const &, size_t const &);

    template<iterable cls>
    static str join(cls const &, str const &);

    [[nodiscard]] static str repeat(str const &, size_t const &);

    [[nodiscard]] static str fill(str const &, size_t const &, str const &);

    [[nodiscard]] static std::vector<str> split(str const &, str const &);

    [[nodiscard]] static std::vector<size_t> get_next(str const &);

    [[nodiscard]] static std::vector<size_t> get_nextVal(str const &, std::vector<size_t> * const & = nullptr);

private:
    static Re * _instance;

    Re()= default;
};

Re &Re::Instance()
{
    if (_instance == nullptr)
        _instance = new Re {};
    return *_instance;
}

Re *Re::_instance = nullptr;

size_t Re::find(const str &_a, const str &_b)
{
    if (_a.size() < _b.size()) return _a.size();

    std::vector<size_t> const _next = Re::get_next(_b);
    size_t const _length = _a.size();
    size_t const _distance = _b.size();
    size_t _tick_dev = 0;
    bool _flag;

    for (size_t _index = 0; _index + _distance < _length ;)
    {
        _flag = true;
        for (size_t _tick = _tick_dev; _tick != _distance; ++_tick, ++_index)
        {
            if (_a[_index] != _b[_tick]) {
                if (_next[_tick] == 0) {
                    _tick_dev = 0;
                    ++_index;
                } else {
                    _tick_dev = _next[_tick] - 1;
                }
                _flag = false;
                break;
            }
        }
        if (_flag) return _index - _distance;
    }
    return _length;
}

size_t Re::find_between(const str &_a, const str &_b, const size_t &_begin, const size_t &_end) {
    if (_a.size() < _b.size()) return _a.size();


    std::vector<size_t> const _next = Re::get_next(_b);
    size_t const _distance = _b.size();
    size_t _tick_dev = 0;
    bool _flag;

    for (size_t _index = _begin; _index + _distance <= _end;)
    {
        _flag = true;
        for (size_t _tick = _tick_dev; _tick != _distance; ++_tick, ++_index)
        {
            if (_a[_index] != _b[_tick])
            {
                if (_next[_tick] == 0)
                {
                    _tick_dev = 0;
                    ++_index;
                } else {
                    _tick_dev = _next[_tick] - 1;
                }
                _flag = false;
                break;
            }
        }
        if (_flag) return _index - _distance;
    }
    return _end;
}

size_t Re::naive_find(const str &_a, const str &_b) {
    bool _found = true;
    size_t const _length = _a.size();
    size_t const _distance = _b.size();

    for (size_t _index=0; _index +_distance < _length; ++_index)
    {
        if (!Re::naive_equal(_a.substr(_index, _distance), _b))
        {
            _found = false;
        }
        if (_found) return _index;
    }
    return _length;
}

bool Re::naive_equal(const str &_a, const str &_b)
{
    if (_a.size()!=_b.size()) return false;
    size_t const _size = _a.size();

    for(size_t _index = 0; _index != _size; ++_index)
    {
        if (_a[_index] != _b[_index]) return false;
    }
    return true;
}

std::vector<size_t> Re::get_next(const str &_s)
{
    std::vector<size_t> res {0};
    size_t const _size = _s.size();
    size_t _max_common;

    for(size_t _index = 1; _index < _size; ++_index)
    {
        _max_common = 0;
        for(size_t _len = 1; _len != _index; ++_len)
        {
            if (Re::naive_equal(_s.substr(0, _len), _s.substr(_index - _len, _len)))
            {
                _max_common = _len;
            }
        }
        res.emplace_back(_max_common + 1);
    }
    return res;
}

std::vector<size_t> Re::get_nextVal(const str &_s, std::vector<size_t> *const &ptr)
{
    std::vector<size_t> res {};
    std::vector<size_t> const &_next = ptr == nullptr? Re::get_next(_s): *ptr;
    size_t const _size = _s.size();
    size_t _val;

    for(size_t _index = 0; _index != _size; ++_index)
    {
        _val = _index;
        for(; _val != 0 && _val != _next[_val] - 1; _val = _next[_val] - 1)
        {
            if (_s[_val] != _s[_next[_val] - 1]) break;
        }
        res.emplace_back(_next[_val]);
    }
    return res;
}

str Re::slice(const str &_s, const size_t &_l, const size_t &_r)
{
    return _s.substr(_l, _r - _l);
}

template<iterable Tp>
str Re::join(const Tp &cont, const str &s)
{
    std::string _res {};
    for (auto _iter = cont.begin(); _iter!= cont.back() - 1; ++_iter)
    {
        cont += *_iter + s;
    }
    _res += cont.back() - 1;
    return _res;
}

str Re::repeat(const str &s, size_t const &length)
{
    str _res {};
    for (size_t i = 0; i < length; ++i)
    {
        _res += s;
    }
    return _res;
}

str Re::fill(const str &word, size_t const &length, const str &sub) {
    if (word.size() <= length) return word;
    size_t const remain = word.size() - length;
    size_t const pre_remain = std::ceil((remain + 1) / 2);
    size_t const lst_remain = std::ceil(remain / 2);
    return Re::repeat(sub, pre_remain) + word + Re::repeat(sub, lst_remain);
}

std::vector<str> Re::split(const str &_a, const str &_b) {
    std::vector<size_t> cache {};
    std::vector<str> res {};
    size_t const _length = _a.size();
    size_t const _distance = _b.size();
    size_t _pos = 0;

    for(size_t _index = 0; _index + _distance < _length;)
    {
        _pos  = Re::find_between(_a, _b, _index, _length);
        if (_pos != _length)
        {
            cache.emplace_back(_pos);
            _index = _pos + _distance;
        } else {
            ++_index;
        }
    }

    size_t _begin = 0;
    res.reserve(cache.size());
    for (auto const &_iter :cache)
    {
        res.emplace_back(Re::slice(_a, _begin, _iter));
        _begin = _iter + _distance;
    }
    res.emplace_back(Re::slice(_a, _begin, _length));
    return res;
}


#endif //DATASTRUCTURE_KMP_HPP