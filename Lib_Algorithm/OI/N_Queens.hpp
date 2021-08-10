#ifndef DATASTRUCTURE_N_QUEENS_HPP
#define DATASTRUCTURE_N_QUEENS_HPP

#include <array>

size_t Abs(ssize_t const &num) {
    return num>0 ?num : -num;
}

enum NQ_Optimize {Optimize0, Optimize1, Optimize2};

template<size_t queens, NQ_Optimize=Optimize0>
struct NQ_Func {};

template<size_t queens>
struct NQ_Func
<queens, Optimize0>
{
    std::array<size_t, queens>
    n_queens()
    {
        std::array<size_t, queens> _platform {};
        constexpr size_t _shape = queens;
        size_t _depth{};
        bool valid;
        while(_depth!=_shape)
        {
            if (_platform[_depth] == _shape)
            {
                _platform[_depth] = 0;
                ++_platform[--_depth];
                continue;
            }
            valid = true;
            for (size_t _i=0;_i!=_depth;++_i)
            {
                if (_platform[_i]==_platform[_depth]||
                    Abs((ssize_t)(_platform[_i])-(ssize_t)(_platform[_depth]))==
                    Abs((ssize_t)(_i)-(ssize_t)(_depth)))
                {
                    valid = false;
                    break;
                }
            }
            valid? ++_depth : ++_platform[_depth];
        }
        return _platform;
    }
};

template<size_t queens>
struct NQ_Func
<queens, Optimize1>
{
    std::array<size_t, queens>
    n_queens()
    {
        std::array<size_t, queens> _platform {};
        constexpr size_t _shape = queens;
        size_t _depth{};
        bool valid;
        while(_depth!=_shape)
        {
            if (_platform[_depth] == _shape)
            {
                _platform[_depth] = 0;
                ++_platform[--_depth];
                continue;
            }
            valid = true;
            for (size_t _i=0;_i!=_depth;++_i)
            {
                if (_platform[_i]==_platform[_depth]||
                Abs((ssize_t)(_platform[_i])-(ssize_t)(_platform[_depth]))==
                Abs((ssize_t)(_i)-(ssize_t)(_depth)))
                {
                    valid = false;
                    break;
                }
            }
            valid? ++_depth : ++_platform[_depth];
        }
        return _platform;
    }
};

template<size_t queens>
struct NQ_Func
<queens, Optimize2>
{
    std::array<size_t, queens>
    n_queens()
    {
        std::array<size_t, queens> _platform {};
        std::array<bool, queens> _filled {};
        constexpr size_t _shape = queens;
        size_t _depth{};
        bool valid;
        while(_depth!=_shape) {
            if (_platform[_depth] == _shape)
            {
                _platform[_depth] = 0;
                --_depth;
                _filled[_platform[_depth]] = false;
                ++_platform[_depth];
                continue;
            }
            if (_filled[_platform[_depth]])
            {
                ++_platform[_depth];
                continue;
            }
            valid = true;
            for (size_t _i=0;_i!=_depth;++_i)
            {
                if (_platform[_i]==_platform[_depth]||
                    Abs((ssize_t)(_platform[_i])-(ssize_t)(_platform[_depth]))==
                    Abs((ssize_t)(_i)-(ssize_t)(_depth)))
                {
                    valid = false;
                    break;
                }
            }
            if (valid) _filled[_platform[_depth++]]=true;
            else ++_platform[_depth];
        }
        return _platform;
    }
};

#endif //DATASTRUCTURE_N_QUEENS_HPP
