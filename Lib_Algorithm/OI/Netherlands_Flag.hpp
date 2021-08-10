#ifndef DATASTRUCTURE_NETHERLANDS_FLAG_HPP
#define DATASTRUCTURE_NETHERLANDS_FLAG_HPP

#include <array>

template<size_t n>
std::array<char, n> &solution(std::array<char, n> &arr) {
    size_t tick{}, white{}, blue{};
    for (;tick!=n;++tick) {
        if (arr[tick] == 'r') {
            arr[blue++] = 'w';
            arr[white++] = 'r';
            arr[tick] = 'b';
        } else if (arr[tick] == 'w') {
            arr[blue++] = 'w';
            arr[tick] = 'b';
        }
    }
    return arr;
}

#endif //DATASTRUCTURE_NETHERLANDS_FLAG_HPP
