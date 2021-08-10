#ifndef DATASTRUCTURE_STRING_HASH_HPP
#define DATASTRUCTURE_STRING_HASH_HPP

#include <string>

unsigned long long string_hash(std::string const &str)
{
    size_t const base = 67453, time = 223, size = str.size();
    size_t float_size = size<6 ? 6: size;
    unsigned long long _res;
    for (size_t i=0; i!=float_size; ++i) {
        _res = (_res * time + (str[i % size] - ' ')) % base;
    }
    return _res;
}

#endif //DATASTRUCTURE_STRING_HASH_HPP
