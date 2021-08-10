#ifndef DATASTRUCTURE_PRIME_HPP
#define DATASTRUCTURE_PRIME_HPP

#include <array>

template<size_t range>
std::array<bool, range+1> &Prime_Sieve() {
    auto &_pool = *new std::array<bool, range+1> {};
    size_t base;

    for (size_t i=2; i<=range; ++i) _pool[i] = true;
    for (size_t i=2; i<=range; ++i) {
        if (_pool[i]) {
            base=2;
            while (base*i<=range)
            {
                _pool[base*i] = false;
                ++base;
            }
        } else {
            continue;
        }
    }
    return _pool;
}

#endif //DATASTRUCTURE_PRIME_HPP
